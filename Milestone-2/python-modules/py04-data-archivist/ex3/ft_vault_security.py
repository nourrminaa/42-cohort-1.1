def secure_archive(filename, action="read", content=""):
    try:
        if action == "read":
            with open(filename, 'r') as file:
                return (True, file.read())
        elif action == "write":
            with open(filename, 'w') as file:
                file.write(content)
                return (True, "Content successfully written to file")
        else:
            return (False, f"Invalid action: {action}")
    except Exception as e:
        return (False, str(e))


def main():
    print("=== Cyber Archives Security ===\n")
    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))
    print()
    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/master.passwd"))
    print()
    print("Using 'secure_archive' to read from a regular file:")
    result = secure_archive("ancient_fragment.txt")
    print(result)
    print()
    print("Using 'secure_archive' to write previous content to a new file:")
    if result[0]:
        print(secure_archive("new_fragment.txt", "write", result[1]))


if __name__ == "__main__":
    main()
