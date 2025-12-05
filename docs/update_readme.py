import re

def add_problem_entry(md_filepath: str) -> bool:
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

        entry_lines = [
            f"* {name} [{number_str}]",
            f"    * [C++](src/cpp/{number_str}.cpp)",
            f"    * [Python](src/py/{number_str}.py)",
            "",
        ]

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


def update_problem_count(md_filepath: str):
    """
    Use to update numbers of my solved Leetcode problems
    """
    link_pattern = re.compile(r'src/(?:[^/]+/)?(\d+)\.[^\s)]+', re.IGNORECASE)

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
    markdown_file_path = "README.md"
    choice = input("Add new problem entry? (y/n): ").strip().lower()
    if choice == "y":
        add_problem_entry(markdown_file_path)
    update_problem_count(markdown_file_path)


if __name__ == "__main__":
    main()