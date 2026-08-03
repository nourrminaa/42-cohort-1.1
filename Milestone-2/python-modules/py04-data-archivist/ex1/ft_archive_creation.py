import sys


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_archive_creation.py <file>")
        return

    print("=== Cyber Archives Recovery & Preservation ===")
    print(f"Accessing file '{sys.argv[1]}'")
    try:
        with open(sys.argv[1], 'r') as file:
            print("---\n")
            content = file.read()
            print(content)
            print("\n---")
        print(f"File '{sys.argv[1]}' closed.")
    except Exception as e:
        print(f"Error opening file '{sys.argv[1]}': {e}")
        return

    lines = content.splitlines()
    transformed_lines = []
    for line in lines:
        transformed_lines.append(line + "#")
    transformed = "\n".join(transformed_lines)

    print("\nTransform data:")
    print("---\n")
    print(transformed)
    print("\n---")

    new_file = input("Enter new file name (or empty): ")

    if new_file == "":
        print("Not saving data.")
        return

    print(f"Saving data to '{new_file}'")
    try:
        with open(new_file, 'w') as file:
            file.write(transformed + "\n")
        print(f"Data saved in file '{new_file}'.")
    except Exception as e:
        print(f"Error saving file '{new_file}': {e}")


if __name__ == "__main__":
    main()
