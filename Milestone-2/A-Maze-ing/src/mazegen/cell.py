"""Wall-bitmask constants shared across the mazegen package."""

# helps us create the binary bitmask for each cell (each cell is a wall)
# 1 = 0001, 2 = 0010, 4 = 0100, 8 = 1000
# (that's how we know which walls are still there)
NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

# bitmask for all walls present (1111 if all walls are present))
# logical OR of all walls (0001 | 0010 | 0100 | 1000 = 1111 = 15 (F in hex))
ALL_WALLS = NORTH | EAST | SOUTH | WEST

# to remove walls on both cells, we need to know the opposite wall of each wall
OPPOSITE_WALL: dict[int, int] = {
    NORTH: SOUTH,
    SOUTH: NORTH,
    EAST: WEST,
    WEST: EAST,
}

# movement directions
DIRECTIONS: list[tuple[int, int, int, str]] = [
    (0, -1, NORTH, "N"),
    (1, 0, EAST, "E"),
    (0, 1, SOUTH, "S"),
    (-1, 0, WEST, "W"),
]
