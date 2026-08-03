"""ANSI escape codes for terminal colors, formatting, and display constants.

This module centralizes all ANSI color codes, character glyphs, and
timing constants used by the ASCII maze renderer.
"""

# [0m: resets all formatting
RESET = "\033[0m"

GREEN = "\033[32m"
CYAN = "\033[36m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
YELLOW = "\033[33m"
WHITE = "\033[37m"
RED = "\033[31m"

WALL_PALETTE: list[tuple[str, str]] = [
    ("Cyan", CYAN),
    ("Blue", BLUE),
    ("Magenta", MAGENTA),
]

ENTRY_COLOR = WHITE
EXIT_COLOR = RED
PATH_COLOR = RED
PATTERN_COLOR = WHITE

WALL_CHAR = "░"
H_WALL_CHAR = "░░░"
EMPTY_PATH = "   "

PATH_CHAR = " ❀ "
LOGO_CHAR = "█"
ENTRY_CHAR = " E "
EXIT_CHAR = " X "

SPINNER_FRAMES: list[str] = [
    "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏",
]
SPINNER_DURATION_SECONDS: int = 2
