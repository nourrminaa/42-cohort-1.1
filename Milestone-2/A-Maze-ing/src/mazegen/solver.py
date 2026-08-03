"""Breadth-first search shortest-path solver for a maze grid.

Given a maze represented as a grid of wall bitmasks (matching the
project's output-file wall encoding), this module finds the shortest
path between two cells. Since every move between adjacent cells costs
exactly one step (the grid is unweighted), breadth-first search (BFS)
guarantees the first time the goal is reached, it has been reached by
the shortest possible route.
"""

from collections import deque
from typing import Dict, List, Optional, Tuple
from mazegen.errors import MazeError
from mazegen.cell import DIRECTIONS


Coordinate = Tuple[int, int]


def _validate_inputs(
    grid: List[List[int]],
    width: int,
    height: int,
    start: Coordinate,
    goal: Coordinate,
) -> None:
    """Validate solver inputs before running BFS.
    Args:
        grid: The maze grid of wall bitmasks.
        width: Number of columns in the maze.
        height: Number of rows in the maze.
        start: Starting coordinate.
        goal: Target coordinate.
    Raises:
        ConfigError: If the grid dimensions are inconsistent, or if
            start/goal are missing, equal, or outside the maze
            bounds.
    """
    # validate grid dimensions
    if len(grid) != height or any(len(row) != width for row in grid):
        raise MazeError(f"Grid dimensions do not match width={width},"
                        f" height={height}.")

    # validate start and goal coordinates
    for name, coordinate in (("start", start), ("goal", goal)):
        x, y = coordinate
        if not (0 <= x < width and 0 <= y < height):
            raise MazeError(f"{name} coordinate {coordinate} is out of "
                            f"bounds for a {width}x{height} maze.")

    # validate that start and goal are not the same
    if start == goal:
        raise MazeError(f"'start' and 'goal' must be different, "
                        f"both are {start}.")


def solve(
    grid: List[List[int]],
    width: int,
    height: int,
    start: Coordinate,
    goal: Coordinate,
) -> str:
    """Find the shortest path between two cells using BFS.

    Args:
        grid: The maze grid of wall bitmasks produced by ageneration algorithm.
        width: Number of columns in the maze.
        height: Number of rows in the maze.
        start: Entry coordinate.
        goal: Exit coordinate.
    Returns:
        The shortest path from start to goal as a string of
        N/E/S/W letters, one per move.
    Raises:
        ConfigError: If the inputs are invalid, or if no path exists
            between start and goal.
    """
    _validate_inputs(grid, width, height, start, goal)

    # keep track of the path taken to reach each cell, so we can reconstruct
    came_from: Dict[Coordinate, Optional[Tuple[Coordinate, str]]] = {
        start: None
    }

    # double ended queue for BFS, initialized with the start cell
    # deque because BFS is FIFO: we pop from the left and append to the right
    queue: "deque[Coordinate]" = deque([start])

    while queue:
        x, y = queue.popleft()

        if (x, y) == goal:
            return _reconstruct_path(came_from, goal)

        cell_walls = grid[y][x]
        for dx, dy, wall, letter in DIRECTIONS:
            if cell_walls & wall:
                continue  # wall is closed, this direction is invalid

            neighbor = (x + dx, y + dy)
            nx, ny = neighbor
            if not (0 <= nx < width and 0 <= ny < height):
                continue
            if neighbor in came_from:
                continue  # already visited

            came_from[neighbor] = ((x, y), letter)
            queue.append(neighbor)

    raise MazeError(f"No path exists between {start} and {goal}.")


def _reconstruct_path(
    came_from: Dict[Coordinate, Optional[Tuple[Coordinate, str]]],
    goal: Coordinate,
) -> str:
    """Rebuild the path taken from the BFS came_from.

    Args:
        came_from: Mapping from each visited cell to the
            (previous_cell, move_letter) used to reach it
        goal: The cell the search ended at.

    Returns:
        The path from the start cell to goal as a string of
        N/E/S/W letters, in travel order.
    """
    letters: List[str] = []
    node = goal

    while came_from[node] is not None:
        previous = came_from[node]

        if previous is None:
            break

        previous_node, letter = previous
        letters.append(letter)
        node = previous_node

    letters.reverse()
    solution = "".join(letters)
    return solution
