import os
import sys


def is_venv() -> bool:
    return sys.prefix != sys.base_prefix


def main() -> None:
    print("MATRIX STATUS: ", end="")

    if is_venv():
        py_version = f"{sys.version_info.major}.{sys.version_info.minor}"
        site_packages = os.path.join(
            sys.prefix, "lib", f"python{py_version}", "site-packages"
        )
        print("Welcome to the construct\n")
        print(f"Current Python: {sys.executable}")
        print(f"Virtual Environment: {os.path.basename(sys.prefix)}")
        print(f"Environment Path: {sys.prefix}\n")
        print("SUCCESS: You're in an isolated environment!")
        print(
            "Safe to install packages without affecting\nthe global system.\n"
        )
        print(f"Package installation path:\n{site_packages}")
    else:
        print("You're still plugged in\n")
        print(f"Current Python: {sys.executable}")
        print("Virtual Environment: None detected\n")
        print("WARNING: You're in the global environment!")
        print("The machines can see everything you install.\n")
        print("To enter the construct, run:")
        print("python -m venv matrix_env")
        print("source matrix_env/bin/activate # On Unix")
        print("matrix_env\\Scripts\\activate # On Windows\n")
        print("Then run this program again.")


if __name__ == "__main__":
    main()
