"""Centralized custom exceptions used across the project."""


class ConfigError(Exception):
    """Raised when the config.txt file has one or more problems.

    Attributes:
        errors: The list of individual error messages describing what
            is wrong with the configuration file.
    """

    def __init__(self, errors: list[str]) -> None:
        """Initialize the exception with a list of error messages.

        Args:
            errors: A list of human-readable strings, each describing
                one problem found in the configuration file.
        """
        message = "\n".join(f"- {err}" for err in errors)
        super().__init__(f"ERROR: Invalid configuration:\n{message}")
