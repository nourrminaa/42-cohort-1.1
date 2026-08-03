"""A-Maze-ing: an interactive terminal maze generator and viewer."""

import sys
from typing import cast

from app import ConfigError, parse_config
from app.display import (
    WALL_PALETTE,
    animate_generation,
    clear_screen,
    render_maze,
)
from app.writer import output_writer
from mazegen import MazeGenerator


def main() -> None:
    """Parse the config file, generate a maze, and run the menu loop.

    Reads the config file path from the command line, builds a
    ``MazeGenerator`` from the parsed configuration, writes the maze
    to the configured output file, displays the maze, and then
    presents an interactive menu that lets the user regenerate the
    maze, toggle the solution path, rotate wall colors, or quit.
    """
    if len(sys.argv) != 2:
        print("Usage: python3 a_maze_ing.py <config_file>")
        sys.exit(1)

    file_path = sys.argv[1]

    try:
        config = parse_config(file_path)
    except ConfigError as e:
        print(f"failed to parse config: {e}")
        sys.exit(1)

    width = cast(int, config["width"])
    height = cast(int, config["height"])
    entry_coords = cast(tuple[int, int], config["entry"])
    exit_coords = cast(tuple[int, int], config["exit"])
    seed = cast("int | None", config["seed"])
    output_file = cast(str, config["output_file"])
    algorithm = config["algorithm"]
    if algorithm is None:
        # default to backtracker if no algorithm is specified
        algorithm = "backtracker"
    algorithm = cast(str, algorithm)
    perfect = cast(bool, config["perfect"])

    maze = MazeGenerator(
        width=width,
        height=height,
        entry_coords=entry_coords,
        exit_coords=exit_coords,
        seed=seed,
        algorithm=algorithm,
        perfect=perfect,
    )

    # Defaults.
    show_path = False
    color_index = 0

    maze.generate()

    try:
        output_writer(
            output_file,
            maze.get_grid(),
            entry_coords,
            exit_coords,
            maze.get_solution_letters(),
        )
    except OSError as e:
        print(f"WARNING: could not write output file: {e}")

    # First print of the maze (with animation).
    animate_generation(
        maze.get_grid(),
        entry_coords,
        exit_coords,
        pattern_cells=maze.get_pattern_cells(),
        wall_color=WALL_PALETTE[color_index][1],
    )

    while True:
        print("\n=== A-Maze-ing ===")
        print("1. Re-generate a new maze")
        print("2. Show/Hide path from entry to exit")
        print("3. Rotate maze colors")
        print("4. Quit")
        choice = input("Choice? (1-4): ").strip()

        if choice == "1":
            maze.generate()

            try:
                output_writer(
                    output_file,
                    maze.get_grid(),
                    entry_coords,
                    exit_coords,
                    maze.get_solution_letters(),
                )
            except OSError as e:
                print(f"WARNING: could not write output file: {e}")

            clear_screen()
            animate_generation(
                maze.get_grid(),
                entry_coords,
                exit_coords,
                pattern_cells=maze.get_pattern_cells(),
                wall_color=WALL_PALETTE[color_index][1],
            )

        elif choice == "2":
            show_path = not show_path
            clear_screen()
            render_maze(
                maze.get_grid(),
                entry_coords,
                exit_coords,
                path=maze.get_solution() if show_path else None,
                pattern_cells=maze.get_pattern_cells(),
                wall_color=WALL_PALETTE[color_index][1],
            )

        elif choice == "3":
            # Loop through the color palette indefinitely.
            color_index = (color_index + 1) % len(WALL_PALETTE)
            clear_screen()
            render_maze(
                maze.get_grid(),
                entry_coords,
                exit_coords,
                path=maze.get_solution() if show_path else None,
                pattern_cells=maze.get_pattern_cells(),
                wall_color=WALL_PALETTE[color_index][1],
            )

        elif choice == "4":
            print("Adios :)")
            break

        else:
            print("Unrecognized option. Try again!")


if __name__ == "__main__":
    main()
