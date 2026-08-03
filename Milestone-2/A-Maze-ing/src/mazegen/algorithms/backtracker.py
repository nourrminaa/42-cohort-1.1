"""Recursive backtracker maze generation algorithm.

The recursive backtracker is a randomized depth-first search over the
grid of cells: starting from a random cell, it walks to a random
unvisited neighbor (knocking down the wall between them), and
backtracks (steps back to the previous cell) whenever it reaches a
cell with no unvisited neighbors left. It stops once every cell has
been visited, producing a perfect maze (a spanning tree: exactly one
path between any two cells).
"""
from random import Random
from typing import List, Optional, Tuple
from mazegen.errors import MazeError
from mazegen.cell import (
    ALL_WALLS,
    DIRECTIONS,
    OPPOSITE_WALL,
)


def generate(
    width: int,
    height: int,
    random: Random,
    seed: Optional[int] = None,
    start: Optional[Tuple[int, int]] = None,
    blocked: Optional[set[Tuple[int, int]]] = None,
) -> List[List[int]]:
    """Generate a perfect maze using the recursive backtracker algorithm.

    Args:
        width: Number of columns in the maze. Must be positive.
        height: Number of rows in the maze. Must be positive.
        seed: Optional seed for reproducible generation.
        start: Optional starting position for the maze.
        blocked: Cells representing the "42" design walls.
    Returns:
        A grid of height rows by width columns, where each cell
        is an integer bitmask of the walls still standing, combining
        NORTH, EAST, SOUTH, and WEST.
    Raises:
        ValueError: If width or height is not a positive integer.
    """

    if height <= 0 or width <= 0:
        raise ValueError('Width and height must be positive non-zero integers')

    if start is None:
        start = (0, 0)

    if blocked is None:
        blocked = set()

    if start in blocked:
        raise MazeError(f"Starting pos {start} can't be a blocked cell.")

    dir_selector = random

    # create the grid that will hold the maze
    # initially all walls are present in each cell
    # fill all cells with 1111 (4 walls present)
    grid: List[List[int]] = []
    for row in range(height):
        grid_row: List[int] = []
        for col in range(width):
            grid_row.append(ALL_WALLS)
        grid.append(grid_row)

    # create a grid to track which cells have been visited, initially all False
    visited: List[List[bool]] = []
    for row in range(height):
        visited_row: List[bool] = []
        for col in range(width):
            visited_row.append(False)
        visited.append(visited_row)

    # starting position
    start_x, start_y = start
    visited[start_y][start_x] = True
    stack: List[Tuple[int, int]] = [(start_x, start_y)]

    # backtracking loop: while there are still cells in the stack
    # keep visiting unvisited neighbors
    while stack:
        x, y = stack[-1]

        unvisited_neighbors = []
        for dx, dy, wall, _ in DIRECTIONS:
            nx = x + dx
            ny = y + dy

            if 0 <= nx < width and 0 <= ny < height:
                if not visited[ny][nx] and (nx, ny) not in blocked:
                    unvisited_neighbors.append((nx, ny, wall))

        if not unvisited_neighbors:
            stack.pop()
            continue

        # select a random cell out of the unvisited neighbors
        next_x, next_y, wall = dir_selector.choice(unvisited_neighbors)

        # knock down the wall between the current cell and selected neighbor
        grid[y][x] &= ~wall
        grid[next_y][next_x] &= ~OPPOSITE_WALL[wall]

        # update the visited grid and push the visited neighbor onto the stack
        visited[next_y][next_x] = True
        stack.append((next_x, next_y))

    return grid
