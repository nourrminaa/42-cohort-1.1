"""Writes the maze to the hex output file format described in the
subject: one hex digit per cell, then a blank line, then
entry coords, exit coords, and the solution path.
"""

from typing import List, Tuple

Coordinate = Tuple[int, int]


def output_writer(
    output_path: str,
    grid: List[List[int]],
    entry_coords: Coordinate,
    exit_coords: Coordinate,
    solution_letters: str,
) -> None:
    """Write the maze grid and metadata to output_path.

    Args:
        output_path: Where to write the file.
        grid: The maze grid of wall bitmasks.
        entry_coords: (x, y) entry cell.
        exit_coords: (x, y) exit cell.
        solution_letters: Shortest path as N/E/S/W letters.

    Raises:
        OSError: If the file cannot be written (permissions, etc).
    """
    with open(output_path, "w") as file:
        for row in grid:
            line = ""
            for cell in row:
                line += format(cell, "X")
            file.write(line + "\n")

        file.write("\n")
        file.write(f"{entry_coords[0]},{entry_coords[1]}\n")
        file.write(f"{exit_coords[0]},{exit_coords[1]}\n")
        file.write(solution_letters + "\n")
