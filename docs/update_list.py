import re
import unicodedata
from pathlib import Path


DOCS_DIR = Path(__file__).resolve().parent
README_PATH = DOCS_DIR / "README.md"
LIST_PATH = DOCS_DIR / "PROBLEM_LIST.md"

def add_problem_entry(md_filepath: Path) -> bool:
    md_filepath = Path(md_filepath)
    difficulties = {
        "easy": "## 🟢Easy",
        "medium": "## 🟡Medium",
        "hard": "## 🔴Hard",
    }

    try:
        name = input("Problem name: ").strip()
        if not name:
            print("Alert: Problem name is required")
            return False

        number_str = input("Problem number: ").strip()
        if not number_str.isdigit():
            print("Alert: Problem number must be numeric")
            return False

        difficulty_key = input("Difficulty (easy/medium/hard): ").strip().lower()
        if difficulty_key not in difficulties:
            print("Alert: Difficulty must be easy, medium, or hard")
            return False

        header = difficulties[difficulty_key]

        with open(md_filepath, "r", encoding="utf-8") as f:
            lines = f.read().splitlines()

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

        section_slice = lines[header_idx + 1:section_end]
        identifier = f"[{number_str}]"
        if any(identifier in line for line in section_slice):
            print(f"Alert: Problem {number_str} already listed")
            return False

        slug = _slugify(name)
        if not slug:
            print("Error: Unable to derive LeetCode slug from problem name")
            return False

        leetcode_url = f"https://leetcode.com/problems/{slug}/"

        lang_input = input("Languages (cpp/python/java/all): ").strip().lower()
        valid_langs = {"cpp", "python", "java", "all"}
        if lang_input not in valid_langs:
            print("Alert: Language must be cpp, python, java, or all")
            return False

        entry_lines = [f"* [{number_str}] {name} [[{leetcode_url}]({leetcode_url})]"]
        if lang_input == "cpp" or lang_input == "all":
            entry_lines.append(f"    * [C++](../src/cpp/{number_str}.cpp)")
        if lang_input == "python" or lang_input == "all":
            entry_lines.append(f"    * [Python](../src/py/{number_str}.py)")
        if lang_input == "java" or lang_input == "all":
            entry_lines.append(f"    * [Java](../src/java/{number_str}.java)")
        entry_lines.append("")

        insert_idx = section_end
        while insert_idx > header_idx + 1 and not lines[insert_idx - 1].strip():
            insert_idx -= 1

        for offset, entry_line in enumerate(entry_lines):
            lines.insert(insert_idx + offset, entry_line)

        with open(md_filepath, "w", encoding="utf-8") as f:
            f.write("\n".join(lines) + "\n")

        print(f"Added problem {number_str} to {header}")
        return True

    except FileNotFoundError:
        print(f"Error: Not found file {md_filepath}")
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False


def _slugify(title: str) -> str:
    """Return a LeetCode-friendly slug derived from the problem title."""
    normalized = unicodedata.normalize("NFKD", title)
    ascii_only = normalized.encode("ascii", "ignore").decode().lower()
    slug = re.sub(r"[^a-z0-9]+", "-", ascii_only).strip("-")
    return slug


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
            print("Alert: No change or not found placeholder")
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
            lang_input = input("Language (cpp/python/java): ").strip().lower()
            valid_langs = {"cpp", "python", "java"}
            if lang_input not in valid_langs:
                print("Alert: Language must be cpp, python, or java")
                return
                # Find and add language path to problem
            try:
                with open(markdown_file_path, "r", encoding="utf-8") as f:
                    lines = f.read().splitlines()
                identifier = f"[{number_str}]"
                entry_idx = None
                # Find the problem entry line (should start with '* [number]')
                for i, line in enumerate(lines):
                    if line.strip().startswith(f"* [{number_str}]"):
                        entry_idx = i
                        break
                if entry_idx is None:
                    print(f"Alert: Problem {number_str} not found")
                    return
                # Prepare language link (4 spaces indent)
                lang_map = {
                    "cpp": f"    * [C++](../src/cpp/{number_str}.cpp)",
                    "python": f"    * [Python](../src/py/{number_str}.py)",
                    "java": f"    * [Java](../src/java/{number_str}.java)"
                }
                lang_line = lang_map[lang_input]
                # Find the region of language links (lines after entry_idx, indented)
                entry_end = entry_idx + 1
                while entry_end < len(lines) and (lines[entry_end].startswith("    * ") or lines[entry_end].strip() == ""):
                    entry_end += 1
                # Check for duplicates in the entry region (ignore whitespace)
                found = False
                lang_line_normalized = lang_line.replace(' ', '').lower()
                for j in range(entry_idx+1, entry_end):
                    line_j = lines[j].replace(' ', '').lower()
                    if line_j == lang_line_normalized or line_j == f'<!--{lang_line_normalized}-->':
                        found = True
                        break
                if found:
                    print(f"Alert: {lang_input} link already exists for problem {number_str}")
                    return
                # Insert the language line before the first blank line or at the end of the block
                insert_idx = entry_end
                if insert_idx > entry_idx+1 and lines[insert_idx-1].strip() == "":
                    insert_idx -= 1
                lines.insert(insert_idx, lang_line)
                with open(markdown_file_path, "w", encoding="utf-8") as f:
                    f.write("\n".join(lines) + "\n")
                print(f"Added {lang_input} link for problem {number_str}")
            except Exception as e:
                print(f"Error: {e}")
        else:
            update_problem_count(markdown_file_path)


if __name__ == "__main__":
    main()