"""mazegen package: top-level entry point for maze generation."""

from mazegen.errors import MazeError
from mazegen.generator import MazeGenerator
from mazegen.cell import (
    DIRECTIONS,
    NORTH,
    EAST,
    SOUTH,
    WEST,
    ALL_WALLS,
    OPPOSITE_WALL
)

__all__ = ["MazeError", "MazeGenerator",
           "DIRECTIONS", "NORTH", "EAST",
           "SOUTH", "WEST", "ALL_WALLS",
           "OPPOSITE_WALL"]
