_This project has been created as part of the 42 curriculum by nmina._

# Python Module 02: Garden Guardian - Exception Handling for Smart Agriculture

## Exception Handling Syntax

```python
try:
    # risky code
except SomeException as e:
    # handle error
else:
    # runs only if no exception
finally:
    # always runs, even on return
```

## Exception Cheat Sheet

| Exception           | Trigger                   | Example             |
| ------------------- | ------------------------- | ------------------- |
| `ValueError`        | Right type, wrong content | `int("abc")`        |
| `TypeError`         | Wrong type for operation  | `"a" + 1`           |
| `ZeroDivisionError` | Divide by zero            | `5 / 0`             |
| `FileNotFoundError` | File doesn't exist        | `open("ghost.txt")` |
| `Exception`         | Catch-all (last resort)   | —                   |

## Exercises Overview

| Exercise | File                         | Concept                                       |
| -------- | ---------------------------- | --------------------------------------------- |
| 0        | `ex0/ft_first_exception.py`  | Basic try/except, catching ValueError         |
| 1        | `ex1/ft_raise_exception.py`  | Raising exceptions, propagation up call stack |
| 2        | `ex2/ft_different_errors.py` | Multiple exception types, tuple catch         |
| 3        | `ex3/ft_custom_errors.py`    | Custom exception classes, inheritance         |
| 4        | `ex4/ft_finally_block.py`    | finally block, resource cleanup               |

## Key Concepts Per Exercise

**Ex0** — catch inside the function, print the error there directly.

**Ex1** — `input_temperature` raises, `test_temperature` catches and prints. `raise` propagates the exception up to whoever called the function.

**Ex2** — single `try` block catches multiple types via tuple:

```python
except (ValueError, TypeError, ZeroDivisionError, FileNotFoundError) as e:
    print(f"Caught {type(e).__name__}: {e}")
```

`type(e).__name__` prints the exception class name without using `type()` on the input.
Add `# type: ignore` to silence mypy on intentional TypeError.

**Ex3** — custom exceptions with default messages:

```python
class GardenError(Exception):
    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)
```

`pass` version gives no default message. `__init__` version sets a fallback.
Catching `GardenError` automatically catches `PlantError` and `WaterError` due to inheritance.

**Ex4** — `finally` always runs, even on `return`. That is what guarantees cleanup.
Cleanup means closing whatever you opened: files, DB connections, sockets. Here it is just a print simulating the concept.

## Resources

- [Python Exception Handling - GeeksforGeeks](https://www.geeksforgeeks.org/python/python-exception-handling/)

### AI Usage

AI (Claude) was used during this project for the following:

- **README writing**: Generating structured notes based on my understanding built during development

All code was written and understood by me. AI was not used to generate final solutions directly.
