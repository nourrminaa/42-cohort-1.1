# Python Module 01: Code Cultivation - Object-Oriented Garden Systems

## Description

This project builds a digital garden ecosystem while introducing Object-Oriented
Programming in Python: classes, inheritance, encapsulation, static/class methods,
and nested classes.

## Conventions

- Classes: `PascalCase` (e.g. `Plant`, `Flower`, `Seed`)
- Functions and variables: `snake_case` (e.g. `set_height`, `trunk_diameter`)
- All functions and methods include type hints, checked with `mypy`
- Code style checked with `flake8`

## Why `if __name__ == "__main__":` matters

When Python runs a file directly, it sets the special variable `__name__` to
`"__main__"`. When another file _imports_ that same file, `__name__` becomes the
module's filename instead. Guarding code with this check ensures it only runs when
the file is executed directly — not every time it gets imported.

**Without the guard:**

```python
# ft_garden_intro.py
print("I am running!")

def say_hello() -> None:
    print("Hello from garden!")
```

```python
# other_file.py
import ft_garden_intro
ft_garden_intro.say_hello()
```

Running `other_file.py` prints:

```
I am running!       # unwanted — triggered just by importing
Hello from garden!
```

**With the guard:**

```python
def say_hello() -> None:
    print("Hello from garden!")

if __name__ == "__main__":
    print("I am running!")
```

Now `other_file.py` only prints:

```
Hello from garden!
```

And running `ft_garden_intro.py` directly still prints `I am running!` as expected.

## What is the shebang line?

The first line of a script, e.g.:

```python
#!/usr/bin/env python3
```

It tells the terminal which interpreter to use to run the file. With it (and the
file marked executable), you can run the script directly instead of typing
`python3 script.py`:

```bash
chmod +x ft_garden_intro.py
./ft_garden_intro.py
```

"Shebang" comes from `#` ("sharp") + `!` ("bang") → sharp-bang → shebang.

## Design evolution across exercises

- **Ex1**: `Plant` is a bare class; attributes are set on instances manually after
  creation (`rose = Plant(); rose.name = "Rose"`). This works but doesn't scale —
  100 plants means 100 separate variables and a high risk of forgetting an attribute.
  Because attributes aren't declared in `__init__`, they're declared as class-level
  type annotations (`name: str`) so mypy can resolve them.
- **Ex2**: Behavior is added (`grow()`, `age()`), but objects are still built
  attribute-by-attribute. Same class-level annotation pattern used for mypy.
- **Ex3**: `__init__()` is introduced, so every plant is created fully formed in one
  line: `Plant("Rose", 25.0, 30)`. This guarantees consistency.
- **Ex4**: Encapsulation is added — attributes become protected (`_height`, `_age`),
  with `get_*`/`set_*` methods validating input before storage.
- **Ex5**: Inheritance — `Flower`, `Tree`, and `Vegetable` extend `Plant`, reusing
  shared logic via `super()` instead of duplicating it.
- **Ex6**: `Plant` gains a `staticmethod` (`is_older_than_year`) and a `classmethod`
  (`create_anonymous`). An internal `Stats` nested class tracks `grow()`/`age()`/
  `show()` call counts per instance, fully encapsulated and exposed only through a
  `display()` method. `Tree` extends this with a shade-call counter. `Seed` extends
  `Flower`, adding a seed count set when the flower blooms. A standalone function,
  `display_stats()`, prints stats for any `Plant` subclass — it relies on a
  `get_name()` accessor rather than touching protected attributes directly, keeping
  encapsulation intact across module boundaries.

A natural next step beyond this project: store plants in a list and loop over them
instead of one variable per plant.

```python
plants = [Plant("Rose", 25, 30), Plant("Oak", 200, 365)]
for plant in plants:
    plant.show()
```

## Notes on specific mechanics

- `round(self._height + 0.8, 1)` — `round()` takes the value and the number of
  decimal places to keep. Needed because floating-point math produces results like
  `25.0 + 0.8 = 25.799999999999997`; rounding cleans this to `25.8`.
- `range(1, 8)` generates `1, 2, ..., 7` (stop value excluded) — 7 numbers for a
  7-day week.
- `print(..., end="")` — `print()` appends a newline (`\n`) by default; `end=""`
  suppresses it so the next `print()` continues on the same line.
- **Nested class (ex6)**: `Plant.Stats` is defined inside `Plant` and instantiated
  in `__init__` as `self._stats`. It's accessed only through `Plant`'s own methods
  (`grow`, `age`, `show`, `display_internal_stats`), never directly from outside —
  this is the encapsulation the subject asks for.

## Exercises Overview

| Exercise | File                         | Concept                                        |
| -------- | ---------------------------- | ---------------------------------------------- |
| 0        | `ex0/ft_garden_intro.py`     | Program structure, `if __name__ == "__main__"` |
| 1        | `ex1/ft_garden_data.py`      | First class, attributes, `show()`              |
| 2        | `ex2/ft_plant_growth.py`     | Methods, state mutation (`grow`, `age`)        |
| 3        | `ex3/ft_plant_factory.py`    | `__init__`, object construction                |
| 4        | `ex4/ft_garden_security.py`  | Encapsulation, validation, getters/setters     |
| 5        | `ex5/ft_plant_types.py`      | Inheritance, `super()`                         |
| 6        | `ex6/ft_garden_analytics.py` | Static/class methods, nested classes, `Seed`   |

## AI Usage

AI (Claude) was used during this project for:

- Linting/typing help (interpreting flake8/mypy error output, fixing mypy
  `attr-defined` errors in ex1/ex2 via class-level type annotations)
- README writing: generating structured documentation from my own dev notes

All code was written and understood by the student. AI was not used to generate
final solutions directly.
