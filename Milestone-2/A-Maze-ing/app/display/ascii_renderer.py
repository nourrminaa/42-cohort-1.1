"""Render a maze as colored ASCII art in the terminal."""

import sys
import time

from app.display.design_configs import (
    ENTRY_CHAR,
    ENTRY_COLOR,
    EXIT_CHAR,
    EXIT_COLOR,
    H_WALL_CHAR,
    LOGO_CHAR,
    PATH_CHAR,
    PATH_COLOR,
    PATTERN_COLOR,
    RESET,
    SPINNER_DURATION_SECONDS,
    SPINNER_FRAMES,
    WALL_CHAR,
)

NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

# Horizontal scaling factor to stretch the maze horizontally
# and make it proportional to the vertical scaling
H_SCALE = 3


def clear_screen() -> None:
    r"""Clear the terminal and move the cursor to the top.

    Uses ANSI escape codes to control formatting/colors in terminal
    output:

    - ``\033`` is the escape character, signaling the start of an ANSI
      sequence.
    - ``[2J`` clears the whole screen (``2``: whole screen, ``J``:
      clear screen).
    - ``[H`` moves the cursor to row 1, column 1 (top-left corner).

    Note:
        An ANSI clear screen is not the same as a carriage return
        (``\r``), which moves the cursor to the start of the current
        line without clearing it or moving to a new line.

    ``end=""`` prevents ``print()`` from adding a newline after the
    sequence, so the cursor stays on the first line.
    """
    print("\033[2J\033[H", end="")


def _build_canvas(
    grid: list[list[int]],
    entry_coords: tuple[int, int],
    exit_coords: tuple[int, int],
    path: list[tuple[int, int]] | None,
    pattern_cells: set[tuple[int, int]] | None,
) -> list[list[str]]:
    """Build the maze as a grid of printable characters.

    Args:
        grid: 2D grid where each cell stores its walls as a bitmask.
        entry_coords: (x, y) coordinates of the maze entry point.
        exit_coords: (x, y) coordinates of the maze exit point.
        path: Ordered list of (x, y) cells forming the solution path,
            or None if no path should be drawn.
        pattern_cells: Set of (x, y) cells forming a decorative logo
            pattern, or None if no pattern should be drawn.

    Returns:
        A 2D list of single-character strings representing the maze,
        ready to be colorized and printed row by row.
    """
    height = len(grid)
    width = len(grid[0])

    # *H+1 to account for horizontal scaling (proportional)
    canvas_width = (H_SCALE + 1) * width + 1
    canvas_height = 2 * height + 1

    # Create an empty canvas.
    canvas: list[list[str]] = []
    for _ in range(canvas_height):
        canvas.append([" "] * canvas_width)

    # Draw the outer grid of wall intersections.
    for row in range(0, canvas_height, 2):
        for col in range(0, canvas_width, H_SCALE + 1):
            canvas[row][col] = WALL_CHAR

    # Draw the walls of each cell.
    for row in range(height):
        for col in range(width):
            # Find the position of the cell in the canvas.
            canvas_row = row * 2 + 1
            canvas_col = col * (H_SCALE + 1) + 1

            # Each cell stores its walls as bits.
            cell = grid[row][col]

            # If the bit for a direction is set, the AND operation is
            # non-zero (truthy), so we draw a wall there; otherwise
            # we leave it empty.
            if cell & NORTH:
                for k in range(H_SCALE):
                    canvas[canvas_row - 1][canvas_col + k] = H_WALL_CHAR[k]

            if cell & SOUTH:
                for k in range(H_SCALE):
                    canvas[canvas_row + 1][canvas_col + k] = H_WALL_CHAR[k]

            if cell & EAST:
                canvas[canvas_row][canvas_col + H_SCALE] = WALL_CHAR

            if cell & WEST:
                canvas[canvas_row][canvas_col - 1] = WALL_CHAR

    # Draw the 42 logo pattern.
    if pattern_cells:
        xs = [x for x, _ in pattern_cells]
        ys = [y for _, y in pattern_cells]
        logo_width = max(xs) - min(xs) + 1
        logo_height = max(ys) - min(ys) + 1

        if width < logo_width or height < logo_height:
            print(
                "WARNING: maze too small to display the '42' logo! "
                "Skipping logo design..."
            )
        else:
            # y is the row index & x is the column index.
            for x, y in pattern_cells:
                canvas_col = x * (H_SCALE + 1) + 1
                canvas_row = y * 2 + 1
                logo_str = f"{LOGO_CHAR:^{H_SCALE}}"[:H_SCALE]
                for k in range(H_SCALE):
                    canvas[canvas_row][canvas_col + k] = logo_str[k]

    # Draw the solution path.
    if path:
        for x, y in path:
            canvas_col = x * (H_SCALE + 1) + 1
            canvas_row = y * 2 + 1
            path_str = f"{PATH_CHAR:^{H_SCALE}}"[:H_SCALE]
            for k in range(H_SCALE):
                canvas[canvas_row][canvas_col + k] = path_str[k]

    # Draw the entry & exit points.
    entry_col = entry_coords[0] * (H_SCALE + 1) + 1
    entry_row = entry_coords[1] * 2 + 1
    entry_str = f"{ENTRY_CHAR:^{H_SCALE}}"[:H_SCALE]
    for k in range(H_SCALE):
        canvas[entry_row][entry_col + k] = entry_str[k]

    exit_col = exit_coords[0] * (H_SCALE + 1) + 1
    exit_row = exit_coords[1] * 2 + 1
    exit_str = f"{EXIT_CHAR:^{H_SCALE}}"[:H_SCALE]
    for k in range(H_SCALE):
        canvas[exit_row][exit_col + k] = exit_str[k]

    return canvas


def render_maze(
    grid: list[list[int]],
    entry_coords: tuple[int, int],
    exit_coords: tuple[int, int],
    path: list[tuple[int, int]] | None = None,
    pattern_cells: set[tuple[int, int]] | None = None,
    wall_color: str = "",
) -> None:
    """Print the maze to the terminal as colorized ASCII output.

    Args:
        grid: 2D grid where each cell stores its walls as a bitmask.
        entry_coords: (x, y) coordinates of the maze entry point.
        exit_coords: (x, y) coordinates of the maze exit point.
        path: Ordered list of (x, y) cells forming the solution path,
            or None if no path should be drawn.
        pattern_cells: Set of (x, y) cells forming a decorative logo
            pattern, or None if no pattern should be drawn.
        wall_color: ANSI color code applied to wall characters.
    """
    canvas = _build_canvas(
        grid, entry_coords, exit_coords, path, pattern_cells
    )

    for row in canvas:
        line = ""
        for character in row:
            if character in (WALL_CHAR, H_WALL_CHAR[0]):
                line += f"{wall_color}{character}{RESET}"

            elif character == PATH_CHAR:
                line += f"{PATH_COLOR}{character}{RESET}"

            elif character == LOGO_CHAR:
                line += f"{PATTERN_COLOR}{character}{RESET}"

            elif character == ENTRY_CHAR:
                line += f"{ENTRY_COLOR}{character}{RESET}"

            elif character == EXIT_CHAR:
                line += f"{EXIT_COLOR}{character}{RESET}"

            else:
                line += character
        # Print the maze line by line.
        print(line)


def animate_generation(
    grid: list[list[int]],
    entry_coords: tuple[int, int],
    exit_coords: tuple[int, int],
    pattern_cells: set[tuple[int, int]] | None,
    wall_color: str,
) -> None:
    """Show a loading spinner, then reveal the finished maze.

    Args:
        grid: 2D grid where each cell stores its walls as a bitmask.
        entry_coords: (x, y) coordinates of the maze entry point.
        exit_coords: (x, y) coordinates of the maze exit point.
        pattern_cells: Set of (x, y) cells forming a decorative logo
            pattern, or None if no pattern should be drawn.
        wall_color: ANSI color code applied to wall characters.
    """
    clear_screen()
    print("\n")
    start_time = time.time()
    # Frame index tracks which spinner frame to display next.
    frame_index = 0
    while time.time() - start_time < SPINNER_DURATION_SECONDS:
        # Display a spinner, looping when frame_index exceeds the
        # number of available frames.
        frame = SPINNER_FRAMES[frame_index % len(SPINNER_FRAMES)]
        # Carriage return keeps the cursor on the same line, so the
        # spinner updates in place (overwrites the previous frame).
        sys.stdout.write(f"\r{wall_color}{frame}{RESET} generating maze...")
        time.sleep(0.3)
        frame_index += 1

    # Same carriage-return trick to overwrite the spinner with the maze.
    sys.stdout.write("\r")
    render_maze(
        grid,
        entry_coords,
        exit_coords,
        pattern_cells=pattern_cells,
        wall_color=wall_color,
    )
