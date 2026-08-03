_This project has been created as part of the 42 curriculum by nmina._

# Python Module 00: Growing Code - Python Fundamentals Through Garden Data

## Description

This project introduces Python's core programming concepts through community garden scenarios.
Each exercise builds on the previous one, covering expressions, variables, functions, control flow, loops, recursion and type annotations.

The goal is to build a solid foundation in Python syntax and semantics, writing clean, readable functions that solve practical problems.

## Instructions

### Requirements

- Python 3.10+
- flake8 (for linting)
- mypy (for type checking)

### Install dependencies

```bash
pip3 install flake8
pip3 install mypy
```

### Run an exercise

Each exercise is a standalone Python file containing a single function. To test them, use the provided `main.py` helper:

```bash
python3 main.py
```

### Check code style

```bash
flake8 ex0/ft_hello_garden.py
# etc.
```

No output means your code is clean. flake8 checks but does **not** fix errors - you fix them yourself (just like norminette for C).

### Check type hints

```bash
mypy ex7/ft_seed_inventory.py
```

Type hints tell Python what type each parameter and return value should be (e.g. str, int, None). mypy checks that they are written correctly.

## Exercises Overview

| Exercise | File                                                                  | Concept                          |
| -------- | --------------------------------------------------------------------- | -------------------------------- |
| 0        | `ex0/ft_hello_garden.py`                                              | print(), basic output            |
| 1        | `ex1/ft_garden_name.py`                                               | input(), print(), string output  |
| 2        | `ex2/ft_plot_area.py`                                                 | input(), int(), arithmetic       |
| 3        | `ex3/ft_harvest_total.py`                                             | Variables, addition              |
| 4        | `ex4/ft_plant_age.py`                                                 | if/else conditionals             |
| 5        | `ex5/ft_water_reminder.py`                                            | Conditional logic                |
| 6        | `ex6/ft_count_harvest_iterative.py` & `ft_count_harvest_recursive.py` | Loops and recursion              |
| 7        | `ex7/ft_seed_inventory.py`                                            | Type annotations, string methods |

## Algorithm & Data Structure Choices

Each exercise uses the simplest appropriate structure:

- **Exercises 0–5**: Simple variables and conditionals.
- **Exercise 6 (iterative)**: A `for` loop with `range(1, n+1)` iterates from day 1 to n.
- **Exercise 7**: A simple `if/elif/else` chain maps unit strings to output formats.

## Resources

- [Python 3 Official Documentation](https://docs.python.org/3/)
- [flake8 medium article](https://medium.com/python-pandemonium/what-is-flake8-and-why-we-should-use-it-b89bd78073f2)

### AI Usage

AI (Claude) was used during this project for the following:

- **Debugging logic**: Describing unexpected output and asking what might be wrong
- **Linting help**: Understanding what flake8 error codes mean
- **README writing**: Generating a structured README template based on my project notes taken during development

All code was written and understood by the student. AI was not used to generate final solutions directly.
