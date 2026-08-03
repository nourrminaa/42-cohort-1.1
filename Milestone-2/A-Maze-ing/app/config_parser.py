"""Parses and validates the maze configuration file (config.txt)."""

import os

from app.errors import ConfigError

MANDATORY_KEYS = ["WIDTH", "HEIGHT", "ENTRY", "EXIT", "OUTPUT_FILE", "PERFECT"]
OPTIONAL_KEYS = ["SEED", "ALGORITHM"]

VALID_ALGORITHMS = {"BACKTRACKER"}

# Maps every accepted string form of the PERFECT key to its bool value.
BOOLEAN_VALUES = {
    "1": True,
    "0": False,
    "FALSE": False,
    "TRUE": True
}

MIN_DIMENSION = 1
MAX_DIMENSION = 10000  # Practical cap, NOT a Python int limit.


def _read_raw_lines(file_path: str) -> list[str]:
    """Read the config file and return its lines.

    Args:
        file_path: Path to the config.txt file.

    Returns:
        A list of strings, one per line in the file.

    Raises:
        ConfigError: If the file does not exist, cannot be read due to
            permissions, or another unexpected error occurs.
    """
    try:
        with open(file_path, "r") as file:
            return file.readlines()
    except FileNotFoundError:
        raise ConfigError([f"config file not found: {file_path}"])
    except PermissionError:
        raise ConfigError([f"no permission to read config file: {file_path}"])
    except Exception as e:
        raise ConfigError([f"unexpected error reading config file: {e}"])


def _parse_lines(file_lines: list[str]) -> dict[str, str]:
    """Turn raw file lines into a dict of KEY -> VALUE string pairs.

    Args:
        file_lines: Raw lines read from the config file.

    Returns:
        A dict mapping each uppercased key to its raw string value.

    Raises:
        ConfigError: If any line is malformed (missing/duplicate keys,
            missing '=', or empty key/value).
    """
    raw_values: dict[str, str] = {}
    errors: list[str] = []

    for line_number, original_line in enumerate(file_lines, start=1):
        # Only take the part before '#'.
        line = original_line.split("#", 1)[0]
        line = line.strip()

        # Skip lines that are blank, or only a comment.
        if not line:
            continue

        # A line should only have one '='.
        if line.count("=") != 1:
            errors.append(
                f"line {line_number}: expected exactly one '=' "
                f"@ {original_line!r}"
            )
            # Continue to collect all errors in one pass.
            continue

        key, value = line.split("=")
        key = key.strip().upper()
        value = value.strip()

        if not key:
            errors.append(f"line {line_number}: empty key @ {original_line!r}")
            continue

        if not value:
            errors.append(
                f"line {line_number}: empty value @ {original_line!r}"
            )
            continue

        # 'in' always searches keys, not values.
        if key in raw_values:
            errors.append(f"line {line_number}: duplicate key '{key}'")
            continue

        raw_values[key] = value

    if errors:
        raise ConfigError(errors)

    return raw_values


def _validate_dimension(
    key: str, value: str, errors: list[str]
) -> int | None:
    """Validate the WIDTH or HEIGHT key.

    Args:
        key: The config key name being validated ("WIDTH" or "HEIGHT").
        value: The raw string value to validate.
        errors: List of error messages to append to on failure.

    Returns:
        The validated integer value, or None if invalid.
    """
    try:
        number = int(value)
    except ValueError:
        errors.append(f"{key} must be an integer! Got '{value}'")
        return None

    if number <= 0:
        errors.append(f"{key} must be a positive integer! Got {number}")
        return None

    if number > MAX_DIMENSION:
        errors.append(
            f"{key} is too large (max {MAX_DIMENSION})! Got {number}"
        )
        return None

    return number


def _validate_coordinate(
    key: str,
    value: str,
    width: int | None,
    height: int | None,
    errors: list[str],
) -> tuple[int, int] | None:
    """Validate the ENTRY or EXIT key in 'x,y' format.

    Args:
        key: The config key name being validated ("ENTRY" or "EXIT").
        value: The raw string value to validate.
        width: The validated maze width, or None if invalid/unknown.
        height: The validated maze height, or None if invalid/unknown.
        errors: List of error messages to append to on failure.

    Returns:
        The validated (x, y) tuple, or None if invalid.
    """
    parts = value.split(",")

    if len(parts) != 2:
        errors.append(f"{key} must be in 'x,y' format! Got '{value}'")
        return None

    try:
        x, y = int(parts[0]), int(parts[1])
    except ValueError:
        errors.append(f"{key} coordinates must be integers! Got '{value}'")
        return None

    if x < 0 or y < 0:
        errors.append(f"{key} coordinates must not be negative! Got '{value}'")
        return None

    if width is not None and x >= width:
        errors.append(f"{key} x={x} is out of bounds! (WIDTH={width})")
        return None

    if height is not None and y >= height:
        errors.append(f"{key} y={y} is out of bounds! (HEIGHT={height})")
        return None

    return (x, y)


def _validate_output_file(value: str, errors: list[str]) -> str | None:
    """Validate the OUTPUT_FILE key.

    Write permission is checked later, at write time.

    Args:
        value: The raw output file path to validate.
        errors: List of error messages to append to on failure.

    Returns:
        The validated output file path, or None if invalid.
    """
    if not value:
        errors.append("OUTPUT_FILE must not be empty!")
        return None

    parent_dir = os.path.dirname(value) or "."
    if not os.path.isdir(parent_dir):
        errors.append(f"OUTPUT_FILE directory does not exist: {parent_dir}")
        return None

    return value


def _validate_perfect(value: str, errors: list[str]) -> bool | None:
    """Validate the PERFECT key.

    Args:
        value: The raw string value to validate.
        errors: List of error messages to append to on failure.

    Returns:
        The validated boolean value, or None if invalid.
    """
    value = value.upper()
    if value in BOOLEAN_VALUES:
        return BOOLEAN_VALUES[value]

    errors.append(
        f"PERFECT must be one of True/False/1/0/true/false! Got '{value}'"
    )
    return None


def _validate_seed(value: str, errors: list[str]) -> int | None:
    """Validate the optional SEED key.

    Args:
        value: The raw string value to validate.
        errors: List of error messages to append to on failure.

    Returns:
        The validated integer seed, or None if invalid.
    """
    try:
        return int(value)
    except ValueError:
        errors.append(f"SEED must be an integer! Got '{value}'")
        return None


def _validate_algorithm(value: str, errors: list[str]) -> str | None:
    """Validate the optional ALGORITHM key.

    Args:
        value: The raw string value to validate.
        errors: List of error messages to append to on failure.

    Returns:
        The validated, uppercased algorithm name, or None if invalid.
    """
    algorithm = value.upper()
    if algorithm not in VALID_ALGORITHMS:
        valid_list = ", ".join(VALID_ALGORITHMS)
        errors.append(
            f"ALGORITHM '{value}' is not recognized. "
            f"Valid options: {valid_list}"
        )
        return None
    return algorithm


def parse_config(path: str) -> dict[str, object]:
    """Parse and fully validate a maze config file.

    Args:
        path: Path to the config.txt file.

    Returns:
        A dict of validated configuration values with keys: "width",
        "height", "entry", "exit", "output_file", "perfect", "seed",
        and "algorithm".

    Raises:
        ConfigError: If the file is missing, empty, malformed, or
            fails validation for any mandatory or optional key.
    """
    lines = _read_raw_lines(path)
    raw_values = _parse_lines(lines)

    if not raw_values:
        raise ConfigError(["config file is empty (no keys found!)"])

    missing = []
    for key in MANDATORY_KEYS:
        if key not in raw_values:
            missing.append(key)
    if missing:
        raise ConfigError([f"missing mandatory key: {key}" for key in missing])

    # List of errors to collect all errors in one pass instead of
    # failing fast.
    errors: list[str] = []

    width = _validate_dimension("WIDTH", raw_values["WIDTH"], errors)
    height = _validate_dimension("HEIGHT", raw_values["HEIGHT"], errors)
    entry_coords = _validate_coordinate(
        "ENTRY", raw_values["ENTRY"], width, height, errors
    )
    exit_coords = _validate_coordinate(
        "EXIT", raw_values["EXIT"], width, height, errors
    )
    output_file = _validate_output_file(raw_values["OUTPUT_FILE"], errors)
    perfect = _validate_perfect(raw_values["PERFECT"], errors)

    if (
        entry_coords is not None
        and exit_coords is not None
        and entry_coords == exit_coords
    ):
        errors.append(
            f"ENTRY and EXIT must be different, both are {entry_coords}"
        )

    seed = None
    # Check if SEED is present before validating it, since it's optional.
    if "SEED" in raw_values:
        seed = _validate_seed(raw_values["SEED"], errors)

    algorithm = None
    if "ALGORITHM" in raw_values:
        algorithm = _validate_algorithm(raw_values["ALGORITHM"], errors)

    if errors:
        raise ConfigError(errors)

    return {
        "width": width,
        "height": height,
        "entry": entry_coords,
        "exit": exit_coords,
        "output_file": output_file,
        "perfect": perfect,
        "seed": seed,
        "algorithm": algorithm,
    }
