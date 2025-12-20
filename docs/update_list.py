import re
import unicodedata
from pathlib import Path

DOCS_DIR = Path(__file__).resolve().parent
README_PATH = DOCS_DIR / "README.md"
LIST_PATH = DOCS_DIR / "PROBLEM_LIST.md"

LANG_MAP = {
    "1": "    * [C++](../src/cpp/{num}.cpp)",
    "2": "    * [C#](../src/csharp/{num}.cs)",
    "3": "    * [C](../src/c/{num}.c)",
    "4": "    * [Python](../src/python/{num}.py)",
    "5": "    * [Java](../src/java/{num}.java)",
    "6": "    * [Javascript](../src/javascript/{num}.js)",
    "7": "    * [TypeScript](../src/typescript/{num}.ts)"
}

def _slugify(title: str) -> str:
    """Return a LeetCode-friendly slug derived from the problem title."""
    normalized = unicodedata.normalize("NFKD", title)
    ascii_only = normalized.encode("ascii", "ignore").decode().lower()
    slug = re.sub(r"[^a-z0-9]+", "-", ascii_only).strip("-")
    return slug

def find_problem_entry(lines, number_str):
    """Find the index of the problem entry line in the markdown file."""
    for i, line in enumerate(lines):
        if line.strip().startswith(f"* [{number_str}]"):
            return i
    return None

def check_duplicate_link(lines, entry_idx, lang_line):
    """Check if the language link already exists in the entry block for a problem."""
    entry_end = entry_idx + 1
    while entry_end < len(lines) and (lines[entry_end].startswith("    * ") or lines[entry_end].strip() == ""):
        entry_end += 1
    lang_line_normalized = lang_line.replace(' ', '').lower()
    for j in range(entry_idx+1, entry_end):
        line_j = lines[j].replace(' ', '').lower()
        if line_j == lang_line_normalized or line_j == f'<!--{lang_line_normalized}-->':
            return True
    return False

def add_language_link_to_problem(number_str, lang_key, lang_map, markdown_file_path):
    """Add a language link to the problem entry in the markdown file. Avoid duplicates."""
    try:
        with open(markdown_file_path, "r", encoding="utf-8") as f:
            lines = f.read().splitlines()
        entry_idx = find_problem_entry(lines, number_str)
        if entry_idx is None:
            print(f"Alert: Problem {number_str} not found")
            return False
        lang_line = lang_map[lang_key]
        if check_duplicate_link(lines, entry_idx, lang_line):
            print(f"Alert: Link already exists for problem {number_str}")
            return False
        # Find the region of language links (lines after entry_idx, indented)
        entry_end = entry_idx + 1
        while entry_end < len(lines) and (lines[entry_end].startswith("    * ") or lines[entry_end].strip() == ""):
            entry_end += 1
        # Insert the language line before the first blank line or at the end of the block
        insert_idx = entry_end
        if insert_idx > entry_idx+1 and lines[insert_idx-1].strip() == "":
            insert_idx -= 1
        lines.insert(insert_idx, lang_line)
        with open(markdown_file_path, "w", encoding="utf-8") as f:
            f.write("\n".join(lines) + "\n")
        print(f"Added link for problem {number_str}")
        return True
    except Exception as e:
        print(f"Error: {e}")
        return False
    
def get_language_input(lang_map, prompt=None):
    """Prompt user to select language by number and return the corresponding key."""
    if prompt is None:
        prompt = "Language:\n"
        for k, v in sorted(lang_map.items(), key=lambda x: int(x[0])):
            lang_name = v.split('[')[1].split(']')[0]
            prompt += f"{k}. {lang_name}\n"
        prompt += ">>> "
    while True:
        lang_input = input(prompt).strip()
        if lang_input in lang_map:
            return lang_input
        print(f"Alert: Please enter a number from 1 to {len(lang_map)}.")

def add_problem_entry(md_filepath: Path) -> bool:
    md_filepath = Path(md_filepath)
    # Mapping for difficulty headers in the markdown file
    difficulties = {
        "easy": "## 🟢Easy",
        "medium": "## 🟡Medium",
        "hard": "## 🔴Hard",
    }

    try:
        # Prompt for problem number and check if it is numeric
        number_str = input("Problem number: ").strip()
        if not number_str.isdigit():
            print("Alert: Problem number must be numeric")
            return False

        # Check if the problem number already exists in any section
        with open(md_filepath, "r", encoding="utf-8") as f:
            lines = f.read().splitlines()
        identifier = f"[{number_str}]"
        if any(identifier in line for line in lines if line.strip().startswith("* [")):
            print(f"Alert: Problem {number_str} already listed")
            return False

        # Prompt for problem name
        name = input("Problem name: ").strip()
        if not name:
            print("Alert: Problem name is required")
            return False

        # Prompt for difficulty and validate
        difficulty_key = input("Difficulty (easy/medium/hard): ").strip().lower()
        if difficulty_key not in difficulties:
            print("Alert: Difficulty must be easy, medium, or hard")
            return False

        header = difficulties[difficulty_key]

        # Find the index of the section header for the selected difficulty
        header_idx = None
        for i, line in enumerate(lines):
            if line.strip() == header:
                header_idx = i
                break

        if header_idx is None:
            print(f"Error: Not found section {header}")
            return False

        # Find the end of the section (next header or end of file)
        section_end = len(lines)
        for j in range(header_idx + 1, len(lines)):
            if lines[j].startswith("## "):
                section_end = j
                break

        # Generate the LeetCode URL slug from the problem name
        slug = _slugify(name)
        if not slug:
            print("Error: Unable to derive LeetCode slug from problem name")
            return False

        leetcode_url = f"https://leetcode.com/problems/{slug}/"

        # Prompt for language and build the language map for the selected problem number
        lang_map = {k: v.format(num=number_str) for k, v in LANG_MAP.items()}
        lang_input = get_language_input(lang_map)
        if lang_input is None:
            return False

        # Check and create the code file if it does not exist
        code_link = lang_map[lang_input]
        # Extract the relative file path from the markdown link
        import os
        import re
        m = re.search(r'\((\.\./src/[^)]+)\)', code_link)
        file_created = False
        code_path = None
        if m:
            rel_path = m.group(1).replace('/', os.sep)
            workspace_root = DOCS_DIR
            code_path = (workspace_root / rel_path).resolve()
            if not code_path.exists():
                # ---------- Create new file -------------
                # Create parent directories if needed and write default content for C++
                code_path.parent.mkdir(parents=True, exist_ok=True)
                with open(code_path, "w", encoding="utf-8") as fcode:
                    fcode.write(
                        '''#include "test.h"
#include "global.h"
using namespace std;

//#define DEBUG
#define MAX_APR 1
#define APR     1

/**
 * Problem {}: {}
 * @input: 
 * @output: 
*/


void test{}() {{
    cout << "Approach " << APR << " / " << MAX_APR << endl;

    struct Case {{

    }};

    vector<Case> cases = {{
        
    }};

    for (int i = 0; i < (int)cases.size(); ++i) {{
        Case c = cases[i];
        
        assertTest(res, c.exp, i);
    }}
}}
'''.format(number_str, name, number_str)
)
        print(f"Created code file: {code_path}")
        file_created = True
        number_display = f"{number_str}" if file_created else number_str
        # Prepare the entry lines for the markdown file (problem and code link)
        entry_lines = [f"* [{number_display}] {name} [[{leetcode_url}]({leetcode_url})]", code_link]

        # Find the correct index to insert the new problem so the list stays sorted by problem number
        insert_idx = section_end
        new_num = int(number_str)
        for j in range(header_idx + 1, section_end):
            line = lines[j]
            m = re.match(r"\* \[(\d+)\]", line.strip())
            if m:
                cur_num = int(m.group(1))
                if cur_num > new_num:
                    insert_idx = j
                    break
        # Avoid inserting extra blank lines before the new entry
        while insert_idx > header_idx + 1 and not lines[insert_idx - 1].strip():
            insert_idx -= 1
        # Insert the new entry lines into the markdown file
        for offset, entry_line in enumerate(entry_lines):
            lines.insert(insert_idx + offset, entry_line)
        # Write the updated lines back to the markdown file
        with open(md_filepath, "w", encoding="utf-8") as f:
            f.write("\n".join(lines) + "\n")
        print(f"Added problem {number_str} to {header}")
    
        # ------------ Update test.h ----------------
        # Insert the prototype in sorted order in test.h
        test_h_path = workspace_root.parent / 'inc' / 'test.h'
        try:
            proto = f'void test{number_str}();\n'
            with open(test_h_path, 'r', encoding='utf-8') as ftest:
                lines = ftest.readlines()
            # Find the correct position to insert so the prototypes are sorted
            insert_idx = None
            for i, line in enumerate(lines):
                m = re.match(r'void test(\d+)\(\);', line.strip())
                if m:
                    cur_num = int(m.group(1))
                    # Insert before the first prototype with a greater number
                    if int(number_str) < cur_num:
                        insert_idx = i
                        break
            if insert_idx is None:
                # If not found, insert at the end before EOF
                insert_idx = len(lines)
            # Avoid duplicate prototypes
            if proto not in lines:
                lines.insert(insert_idx, proto)
                with open(test_h_path, 'w', encoding='utf-8') as ftest:
                    ftest.writelines(lines)
            print('Update test.h')
        except Exception as e:
            print(f"Warning: Could not update test.h: {e}")

        # ----------------- Update main.cpp --------------------
        # Insert #elif for the new test in main.cpp in sorted order (giống logic update test.h)
        main_cpp_path = workspace_root.parent / 'main.cpp'
        try:
            proto_elif = f'    #elif TEST_TO_RUN == {number_str}\n'
            proto_call = f'        test{number_str}();\n'
            with open(main_cpp_path, 'r', encoding='utf-8') as fmain:
                main_lines = fmain.readlines()
            # Kiểm tra trùng lặp
            for line in main_lines:
                m = re.match(r'\s*#elif TEST_TO_RUN == (\d+)', line.strip())
                if m and int(m.group(1)) == int(number_str):
                    print(f"main.cpp: TEST_TO_RUN == {number_str} already exists, no update needed.")
                    return True
            # Tìm vị trí chèn theo thứ tự tăng dần
            insert_idx = None
            for i, line in enumerate(main_lines):
                m = re.match(r'\s*#elif TEST_TO_RUN == (\d+)', line.strip())
                if m:
                    cur_num = int(m.group(1))
                    num_to_add = int(number_str)
                    if num_to_add < cur_num and insert_idx is None:
                        insert_idx = i
                        break
            new_block = [proto_elif, proto_call]
            if insert_idx is not None:
                main_lines[insert_idx:insert_idx] = new_block
            else:
                # Insert trước #else
                for i, line in enumerate(main_lines):
                    if line.strip().startswith('#else'):
                        main_lines[i:i] = new_block
                        break
            with open(main_cpp_path, 'w', encoding='utf-8') as fmain:
                fmain.writelines(main_lines)
            print('Update main.cpp')
        except Exception as e:
            print(f"Warning: Could not update main.cpp: {e}")

        return True
    except FileNotFoundError:
        print(f"Error: Not found file {md_filepath}")
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False


def update_problem_count(md_filepath: Path):
    """Update the total solved problems count based on code links in the markdown file."""
    md_filepath = Path(md_filepath)
    # Regex to match code file links and extract problem numbers
    link_pattern = re.compile(r'(?:\./|\.\./)*src/(?:[^/]+/)?(\d+)\.[^\s)]+', re.IGNORECASE)

    # Regex to match the placeholder for the total problem count
    placeholder_pattern = re.compile(r'(\s*)(\d+)(\s*)', re.DOTALL)

    try:
        with open(md_filepath, 'r', encoding='utf-8') as f:
            content = f.read()

        # Remove HTML comments and count unique problem numbers from code links
        content_no_comments = re.sub(r'<!--.*?-->', '', content, flags=re.DOTALL)
        matches = link_pattern.findall(content_no_comments)
        total_problems = len(set(matches))

        def replacement_function(match):
            """Replace the placeholder digits with the current problem count while preserving surrounding whitespace."""
            return match.group(1) + str(total_problems) + match.group(3)
        
        new_content = placeholder_pattern.sub(replacement_function, content, count=1)

        if new_content == content:
            print("Alert: No change problem count or not found placeholder")
            return
        
        with open(md_filepath, 'w', encoding='utf-8') as f:
            f.write(new_content)

        print(f"Total problem: {total_problems}")
        print(f"Updated to file {md_filepath}")

    except FileNotFoundError:
        print(f"Error: Not found file {md_filepath}")
    except Exception as e:
        print(f"Error: {e}")


def main():
    markdown_file_path = LIST_PATH
    choice = input("Add new problem entry? (y/n): ").strip().lower()
    if choice == "y":
        add_problem_entry(markdown_file_path)
        update_problem_count(markdown_file_path)
    else:
        lang_choice = input("Add new language for a problem? (y/n): ").strip().lower()
        if lang_choice == "y":
            number_str = input("Problem number: ").strip()
            if not number_str.isdigit():
                print("Alert: Problem number must be numeric")
                return
            lang_map = {k: v.format(num=number_str) for k, v in LANG_MAP.items()}
            lang_input = get_language_input(lang_map)
            if lang_input is None:
                return
            add_language_link_to_problem(number_str, lang_input, lang_map, markdown_file_path)
        else:
            update_problem_count(markdown_file_path)


if __name__ == "__main__":
    main()