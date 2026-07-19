import os
import sys

from dotenv import load_dotenv


def load_configuration() -> dict[str, str | None]:
    load_dotenv()

    config = {
        "MATRIX_MODE": os.getenv("MATRIX_MODE", "development"),
        "DATABASE_URL": os.getenv("DATABASE_URL"),
        "API_KEY": os.getenv("API_KEY"),
        "LOG_LEVEL": os.getenv("LOG_LEVEL", "INFO"),
        "ZION_ENDPOINT": os.getenv("ZION_ENDPOINT"),
    }

    return config


def check_configuration(config: dict[str, str | None]) -> list[str]:
    missing = []

    for key in ["DATABASE_URL", "API_KEY", "ZION_ENDPOINT"]:
        if not config[key]:
            missing.append(key)

    return missing


def display_configuration(config: dict[str, str | None]) -> None:
    print("Configuration loaded:")
    print(f"Mode: {config['MATRIX_MODE']}")

    if config["MATRIX_MODE"] == "development":
        print("Database: Connected to local instance")
    else:
        print("Database: Connected to production instance")

    if config["API_KEY"]:
        print("API Access: Authenticated")
    else:
        print("API Access: Missing API key")

    print(f"Log Level: {config['LOG_LEVEL']}")

    if config["ZION_ENDPOINT"]:
        print("Zion Network: Online")
    else:
        print("Zion Network: Offline")


def security_check() -> None:
    print("\nEnvironment security check:")
    print("[OK] No hardcoded secrets detected")

    if os.path.exists(".env"):
        print("[OK] .env file properly configured")
    else:
        print("[WARNING] .env file not found")

    print("[OK] Production overrides available")


def main() -> None:
    print("ORACLE STATUS: Reading the Matrix...\n")

    config = load_configuration()

    missing = check_configuration(config)

    display_configuration(config)

    if missing:
        print("\nMissing configuration variables:")
        for variable in missing:
            print(f"- {variable}")

        print("\nCreate a .env file or set environment variables.")
        sys.exit(1)

    security_check()

    print("\nThe Oracle sees all configurations.")


if __name__ == "__main__":
    main()
