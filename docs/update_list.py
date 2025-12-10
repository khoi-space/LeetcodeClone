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
    """Find the index of the problem entry line."""
    for i, line in enumerate(lines):
        if line.strip().startswith(f"* [{number_str}]"):
            return i
    return None

def check_duplicate_link(lines, entry_idx, lang_line):
    """Check if the language link already exists in the entry block."""
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
    """Add a language link to the problem entry in the markdown file."""
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
    difficulties = {
        "easy": "## 🟢Easy",
        "medium": "## 🟡Medium",
        "hard": "## 🔴Hard",
    }

    try:
        number_str = input("Problem number: ").strip()
        if not number_str.isdigit():
            print("Alert: Problem number must be numeric")
            return False

        # Check existence in list
        with open(md_filepath, "r", encoding="utf-8") as f:
            lines = f.read().splitlines()
        identifier = f"[{number_str}]"
        if any(identifier in line for line in lines if line.strip().startswith("* [")):
            print(f"Alert: Problem {number_str} already listed")
            return False

        name = input("Problem name: ").strip()
        if not name:
            print("Alert: Problem name is required")
            return False

        difficulty_key = input("Difficulty (easy/medium/hard): ").strip().lower()
        if difficulty_key not in difficulties:
            print("Alert: Difficulty must be easy, medium, or hard")
            return False

        header = difficulties[difficulty_key]

        header_idx = None
        for i, line in enumerate(lines):
            if line.strip() == header:
                header_idx = i
                break

        if header_idx is None:
            print(f"Error: Not found section {header}")
            return False

        section_end = len(lines)
        for j in range(header_idx + 1, len(lines)):
            if lines[j].startswith("## "):
                section_end = j
                break

        slug = _slugify(name)
        if not slug:
            print("Error: Unable to derive LeetCode slug from problem name")
            return False

        leetcode_url = f"https://leetcode.com/problems/{slug}/"

        lang_map = {k: v.format(num=number_str) for k, v in LANG_MAP.items()}
        lang_input = get_language_input(lang_map)
        if lang_input is None:
            return False

        # Kiểm tra và tạo file code nếu chưa tồn tại
        code_link = lang_map[lang_input]
        # Lấy đường dẫn file từ link markdown
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
                code_path.parent.mkdir(parents=True, exist_ok=True)
                with open(code_path, "w", encoding="utf-8") as fcode:
                    fcode.write('#include "solution.h"\n#include "test.h"\nusing namespace std;\n')
                file_created = True

        # Thêm dấu * nếu file vừa được tạo
        number_display = f"{number_str}*" if file_created else number_str
        entry_lines = [f"* [{number_display}] {name} [[{leetcode_url}]({leetcode_url})]", code_link, ""]

        # Find the idx for problem to insert sortedly
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
        # Insert to the tail if not found any gap to insert
        while insert_idx > header_idx + 1 and not lines[insert_idx - 1].strip():
            insert_idx -= 1
        for offset, entry_line in enumerate(entry_lines):
            lines.insert(insert_idx + offset, entry_line)
        with open(md_filepath, "w", encoding="utf-8") as f:
            f.write("\n".join(lines) + "\n")
        if file_created:
            print(f"Created code file: {code_path}")
        print(f"Added problem {number_str} to {header}")
        return True

    except FileNotFoundError:
        print(f"Error: Not found file {md_filepath}")
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False


def update_problem_count(md_filepath: Path):
    """Update the total solved problems count based on README links."""
    md_filepath = Path(md_filepath)
    link_pattern = re.compile(r'(?:\./|\.\./)*src/(?:[^/]+/)?(\d+)\.[^\s)]+', re.IGNORECASE)

    placeholder_pattern = re.compile(r'(\s*)(\d+)(\s*)', re.DOTALL)

    try:
        with open(md_filepath, 'r', encoding='utf-8') as f:
            content = f.read()

        content_no_comments = re.sub(r'<!--.*?-->', '', content, flags=re.DOTALL)
        matches = link_pattern.findall(content_no_comments)
        total_problems = len(set(matches))

        def replacement_function(match):
            """
            Replace the placeholder digits with the current problem count while preserving surrounding whitespace.
            """
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