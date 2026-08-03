*This project has been created as part of the 42 curriculum by szaarour, nmina.*

# A-Maze-ing

## Description

**A-Maze-ing** is an interactive maze generator and solver written in **Python**. The application generates random mazes that can be displayed directly in the terminal using colored ASCII graphics. Every generated maze is guaranteed to be solvable, and the program can compute and display the shortest path between the maze entry and exit.

The project is divided into two main parts:

* A reusable **maze generation package** (`mazegen`).
* An interactive application (`a_maze_ing.py`) responsible for configuration parsing, visualization, user interaction, and exporting the generated maze.

Features include:

* Random maze generation
* Perfect and imperfect maze support
* Seed-based reproducible mazes
* Shortest-path computation
* Colored terminal rendering
* Interactive menu
* Export of the generated maze to a text file
* Embedded **42** logo pattern inside sufficiently large mazes

---

# Instructions

## Requirements

* Python 3.12+
* A virtual environment (recommended)

## Installation

Create and activate a virtual environment:

```bash
make install
```

## Running the project

Run the application with a configuration file:

```bash
make run
```

---

## Interactive Menu

Once the maze is displayed, the following options are available:

1. Generate a new random maze
2. Show or hide the shortest path
3. Change wall colors
4. Quit the application

---

# Configuration File

The application is configured using a text configuration file.

Each line follows the format:

```text
KEY=VALUE
```

Comments begin with:

```text
#
```

Example:

```text
WIDTH=25
HEIGHT=15
ENTRY=0,0
EXIT=24,14
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=42
ALGORITHM=BACKTRACKER
```

## Configuration Keys

| Key         | Description                                                             |
| ----------- | ----------------------------------------------------------------------- |
| WIDTH       | Maze width                                                              |
| HEIGHT      | Maze height                                                             |
| ENTRY       | Entry coordinates (x,y)                                                 |
| EXIT        | Exit coordinates (x,y)                                                  |
| OUTPUT_FILE | File where the generated maze is saved                                  |
| PERFECT     | True or False. Determines whether the maze is perfect (single solution) |
| SEED        | Optional integer used for reproducible maze generation                  |
| ALGORITHM   | Optional maze generation algorithm                                      |

Mandatory keys:

* WIDTH
* HEIGHT
* ENTRY
* EXIT
* OUTPUT_FILE
* PERFECT

Optional keys:

* SEED
* ALGORITHM

---

# Maze Generation Algorithm

This project uses the **Recursive Backtracker** algorithm (randomized depth-first search).

The algorithm starts from the entry cell and repeatedly:

1. Visits a random unvisited neighboring cell.
2. Removes the wall between the two cells.
3. Continues recursively until no unvisited neighbors remain.
4. Backtracks until every reachable cell has been visited.

When `PERFECT=True`, the result is a **perfect maze**, meaning:

* Every cell is reachable.
* There is exactly one unique path between any two cells.
* No loops exist.

When `PERFECT=False`, extra passages are opened to introduce loops while preserving maze validity.

---

# Why Recursive Backtracker?

We selected the Recursive Backtracker algorithm because it:

* Produces high-quality perfect mazes.
* Is relatively simple to implement and understand.
* Has excellent performance for medium and large mazes.
* Naturally creates long corridors and interesting maze layouts.
* Works well with deterministic random seeds for reproducible results.

Its simplicity also made it an excellent candidate for packaging as a reusable module.

---

# Maze Generator Reusable Module

The reusable package is named **mazegen**.

It exposes the `MazeGenerator` class, which is responsible for:

* Maze generation
* Pattern creation
* Perfect/imperfect maze handling
* Shortest path computation
* Returning the generated maze grid

Typical usage:(after `uv add .whl` & `uv sync` & `uv run file`:)
```python
from mazegen import MazeGenerator

maze = MazeGenerator(
    width=20,
    height=15,
    entry_coords=(0,0),
    exit_coords=(19,14),
    seed=42
)

maze.generate()
grid = maze.get_grid()
solution = maze.get_solution()
```

The package can be rebuilt and installed independently of the application, making it reusable in other Python projects.

---

# Output File

Each generated maze is written to the configured output file.

The file contains:

* The maze representation
* An empty line
* Entry coordinates
* Exit coordinates
* The shortest path represented using the letters:

```
N
E
S
W
```

---

# Team and Project Management

## Team Roles

### szaarour

* Maze generation algorithm
* Maze solver
* Reusable package implementation
* Output writer

### nmina

* Configuration parser
* Terminal rendering
* Interactive menu
* Testing and integration

---

## Planning

Initial planning focused on dividing the project into independent modules:

1. Configuration parsing
2. Maze generation
3. Solver
4. Display
5. Output generation
6. Integration

During development, additional time was spent improving:

* Error handling
* Documentation
* Modularity
* Code quality
* Package reusability

The modular design made integration significantly easier than expected.

---

## What Worked Well

* Clear module separation
* Early interface definition
* Continuous integration between modules
* Independent testing of each component
* Reusable package architecture

---

## What Could Be Improved

* Support for multiple maze generation algorithms
* Animated maze construction
* More customization options
* Graphical interface
* Additional color themes
* Performance optimizations for extremely large mazes

---

## Tools Used

* Python
* Git
* Virtual environments (`venv`)
* mypy
* PEP Google style docstrings
* 42 output validator

---

# Resources

The following resources were consulted during development:

* Python packaging documentation
* Breadth-First Search (BFS) documentation and algorithm references
* Recursive Backtracker (Randomized DFS) maze generation references
* 42 project subject and provided validator

These resources were used only as references to understand algorithms, packaging, and standard Python APIs. All implementation code was written specifically for this project.

---

# Authors

* **szaarour**
* **nmina**
