"""Maze Generator Class."""

from random import Random

from .algorithms import backtracker
from .errors import MazeError
from .solver import solve
from .cell import (
    ALL_WALLS,
    NORTH,
    EAST,
    SOUTH,
    WEST,
)


class MazeGenerator:
    def __init__(
        self,
        width: int,
        height: int,
        entry_coords: tuple[int, int],
        exit_coords: tuple[int, int],
        seed: int | None = None,
        algorithm: str = "backtracker",
        perfect: bool = True,
    ) -> None:

        self.width = width
        self.height = height
        self.entry_coords = entry_coords
        self.exit_coords = exit_coords
        self.seed = seed
        self.algorithm = algorithm
        self.perfect = perfect
        self.random = Random(self.seed)

        self.grid: list[list[int]] = []
        self.solution: list[tuple[int, int]] = []
        self.pattern_cells: set[tuple[int, int]] = set()
        self.generation_steps: list[list[list[int]]] = []

        # # So we can increase it and get different mazes
        # # even with a fixed seed
        # self._generation_count = 0

    def generate(self) -> None:
        # the "42" must be computed BEFORE generation, so those
        # cells can be excluded from the walk and stay fully closed
        self.pattern_cells = self._generate_pattern_cells()

        max_attempts = 20
        for _ in range(max_attempts):
            if self.seed is not None:
                # run_seed = self.seed + self._generation_count + attempt
                run_seed = self.seed
            else:
                run_seed = self.random.randint(1, 100)

            if self.algorithm.upper() == "BACKTRACKER":
                self.grid = backtracker.generate(
                    width=self.width,
                    height=self.height,
                    random=self.random,
                    start=self.entry_coords,
                    blocked=self.pattern_cells,
                )
            else:
                raise MazeError(f"Unknown algorithm: {self.algorithm}")

            # Ensure all pattern cells explicitly retain all
            # 4 closed walls (15 / 0xF)
            for x, y in self.pattern_cells:
                if 0 <= x < self.width and 0 <= y < self.height:
                    self.grid[y][x] = ALL_WALLS

            if not self.perfect:
                self._add_loops(run_seed)

            try:
                moves = solve(
                    grid=self.grid,
                    width=self.width,
                    height=self.height,
                    start=self.entry_coords,
                    goal=self.exit_coords,
                )
                self._last_moves = moves
                self.solution = self._moves_to_coordinates(moves)
                # self._generation_count += attempt + 1
                return
            except MazeError:
                continue

        raise MazeError(
            f"Could not generate a solvable maze after "
            f"{max_attempts} attempts."
        )

    def _generate_pattern_cells(self) -> set[tuple[int, int]]:
        """returns coordinates forming the 42 logo"""

        center_x = self.width // 2
        center_y = self.height // 2

        offsets = [
            # 4
            (-4, -2), (-4, -1), (-4, 0),
            (-3, 0),
            (-2, -2), (-2, -1), (-2, 0), (-2, 1), (-2, 2),
            # 2
            (1, -2), (2, -2), (3, -2),
            (3, -1),
            (1, 0), (2, 0), (3, 0),
            (1, 1),
            (1, 2), (2, 2), (3, 2),
        ]

        # check the whole logo fits before drawing any of it, so we
        # never show a half-cut-off "42"
        min_dx = min(dx for dx, dy in offsets)
        max_dx = max(dx for dx, dy in offsets)
        min_dy = min(dy for dx, dy in offsets)
        max_dy = max(dy for dx, dy in offsets)

        left = center_x + min_dx
        right = center_x + max_dx
        top = center_y + min_dy
        bottom = center_y + max_dy

        if left < 0 or right >= self.width or top < 0 or bottom >= self.height:
            print(
                "WARNING: maze is too small to fit the '42' pattern. "
                "Skipping it."
            )
            return set()

        pattern = set()
        for dx, dy in offsets:
            x = center_x + dx
            y = center_y + dy
            pattern.add((x, y))

        if self.entry_coords in pattern or self.exit_coords in pattern:
            print(
                "WARNING: entry or exit falls inside the '42' pattern. "
                "Skipping it for this run."
            )
            return set()

        return pattern

    def _add_loops(self, seed: int | None) -> None:
        """Punch a few extra holes so the maze isn't a perfect tree.

        Skips any change that would create a fully-open 3x3 block.
        """

        attempts = max(1, int(0.08 * self.width * self.height))
        directions = [
            (0, -1, NORTH, SOUTH),
            (1, 0, EAST, WEST),
            (0, 1, SOUTH, NORTH),
            (-1, 0, WEST, EAST),
        ]

        for _ in range(attempts):
            x = self.random.randrange(self.width)
            y = self.random.randrange(self.height)
            if (x, y) in self.pattern_cells:
                continue

            dx, dy, wall, opposite = self.random.choice(directions)
            nx, ny = x + dx, y + dy
            if not (0 <= nx < self.width and 0 <= ny < self.height):
                continue
            if (nx, ny) in self.pattern_cells:
                continue
            if not (self.grid[y][x] & wall):
                continue  # already open, nothing to do

            self.grid[y][x] &= ~wall
            self.grid[ny][nx] &= ~opposite

            if self._has_3x3_open_area():
                # undo, this change opened too big an area
                self.grid[y][x] |= wall
                self.grid[ny][nx] |= opposite

    def _has_3x3_open_area(self) -> bool:
        for top in range(self.height - 2):
            for left in range(self.width - 2):
                if self._block_is_fully_open(top, left):
                    return True
        return False

    def _block_is_fully_open(self, top: int, left: int) -> bool:
        for row in range(top, top + 3):
            for col in range(left, left + 2):
                if self.grid[row][col] & EAST:
                    return False
        for row in range(top, top + 2):
            for col in range(left, left + 3):
                if self.grid[row][col] & SOUTH:
                    return False
        return True

    def _moves_to_coordinates(
        self,
        moves: str,
    ) -> list[tuple[int, int]]:
        """converts BFS directions into cell coordinates"""

        path = [self.entry_coords]
        x, y = self.entry_coords
        for move in moves:
            if move == "N":
                y -= 1
            elif move == "E":
                x += 1
            elif move == "S":
                y += 1
            elif move == "W":
                x -= 1
            path.append((x, y))

        return path

    def get_grid(self) -> list[list[int]]:
        return self.grid

    def get_solution(self) -> list[tuple[int, int]]:
        return self.solution

    def get_solution_letters(self) -> str:
        return getattr(self, "_last_moves", "")

    def get_pattern_cells(self) -> set[tuple[int, int]]:
        return self.pattern_cells
