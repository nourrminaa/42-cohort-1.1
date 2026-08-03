"""app.display package.

Handles terminal rendering of a maze. Currently only an ASCII renderer
is implemented, but this package can accommodate additional display
options in the future.
"""

from app.display.ascii_renderer import (
    animate_generation,
    clear_screen,
    render_maze,
)
from app.display.design_configs import WALL_PALETTE

__all__ = ["render_maze", "animate_generation", "clear_screen", "WALL_PALETTE"]
