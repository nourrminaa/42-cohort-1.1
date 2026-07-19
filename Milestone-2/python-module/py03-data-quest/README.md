_This project has been created as part of the 42 curriculum by nmina._

# Python Module 03: Data Quest - Mastering Python Collections

## Data Structures Cheat Sheet

| Type    | Ordered | Mutable | Duplicates | Literal           |
| ------- | ------- | ------- | ---------- | ----------------- |
| `list`  | Yes     | Yes     | Allowed    | `[]`              |
| `tuple` | Yes     | No      | Allowed    | `()`              |
| `set`   | No      | Yes     | No         | `{1,2}` / `set()` |
| `dict`  | Yes\*   | Yes     | No (keys)  | `{}`              |

\*Insertion order preserved since Python 3.7, but not semantically "ordered" like a list.

## Exercises Overview

| Exercise | File                            | Concept                                  |
| -------- | ------------------------------- | ---------------------------------------- |
| 0        | `ex0/ft_command_quest.py`       | `sys.argv`, list basics                  |
| 1        | `ex1/ft_score_analytics.py`     | Lists + try/except on invalid input      |
| 2        | `ex2/ft_coordinate_system.py`   | Tuples, immutability, Euclidean distance |
| 3        | `ex3/ft_achievement_tracker.py` | Sets, union/intersection/difference      |
| 4        | `ex4/ft_inventory_system.py`    | Dictionaries, key-value parsing          |
| 5        | `ex5/ft_data_stream.py`         | Generators, `yield`, infinite streams    |
| 6        | `ex6/ft_data_alchemist.py`      | List/dict comprehensions                 |

## Key Concepts Per Exercise

**Ex0 — Command Quest**
`sys.argv` is a list; `sys.argv[0]` is always the script name, `sys.argv[1:]` are the actual arguments. There's no `argc` in Python — use `len(sys.argv)`.
Alternate ways to skip index 0: slicing (`sys.argv[1:]`), `range(1, len(sys.argv))`, or `sys.argv.pop(0)` (mutates the list — be ready to justify the choice at defense).

**Ex1 — Score Cruncher**
Wrap `int()` conversion in try/except to filter invalid parameters instead of crashing. Discard invalid entries, keep valid ones, only exit if none remain. Use built-ins (`sum`, `max`, `min`) for stats instead of manual loops.

**Ex2 — Position Tracker**
Tuples model coordinates because they're fixed once created — "data written in stone." Use `input().split(',')` to parse `x,y,z`, cast each to `float`, catch `ValueError` per-element to report exactly which token failed. Euclidean distance: `math.sqrt((x2-x1)**2 + (y2-y1)**2 + (z2-z1)**2)` — the 3D extension of Pythagoras.

**Ex3 — Achievement Hunter**
`random.randint(3, len(achievements) // 2)` bounds the per-player achievement count: minimum 3 so `difference()` results aren't trivially empty, maximum half the pool so unique/complement sets stay non-empty too. `random.sample(list, k)` picks `k` unique items without mutating the source, then wrap in `set(...)`.
Set ops used: `union` (all distinct achievements), `intersection` (common to all), `difference` (unique to one player, and what's missing from the full set).
Empty sets print as `set()`, not `{}` — `{}` is already reserved for an empty dict literal, so Python needs an unambiguous constructor call for the empty set case. `{1, 2, 3}` is fine as a non-empty set literal since the colon (`:`) is what actually disambiguates dict syntax.

**Ex4 — Inventory Master**
Parse `name:quantity` tokens from `sys.argv`; the shell already splits on whitespace, so each token arrives as one string to split on `:`. Reject malformed tokens (no colon, non-int quantity) and duplicate keys with explicit error messages before touching the dict.
`dict.update({'magic_item': 1})` inserts a new key or overwrites an existing one — same call handles both add and update.
Percentages: `quantity / total * 100`. Most/least abundant: iterate and track running max/min, keeping first-seen order to break ties by command-line order (not by re-sorting the dict).

**Ex5 — Stream Wizard**
A generator is a function that computes values lazily via `yield` instead of returning them all at once — it suspends and resumes state between calls. `next(gen)` manually advances it one step; a `for` loop calls `next()` implicitly until exhaustion.
`gen_event()` needs `while True:` internally — without it the function runs once and returns, defeating the "endless stream" requirement.
Type hint `Generator[int, None, None]` (or here, `Generator[tuple[str, str], None, None]`) reads as `[YieldType, SendType, ReturnType]`: what the generator yields, what `.send()` can push in (unused here → `None`), and what it returns on completion via `return` (also `None`, since it never returns normally).
`consume_event` must randomly pop items until the list is empty and be driven with `for item in consume_event(...)`, not manual `next()` calls — note `random.sample()` returns a list, not a single tuple, so a single random pick still needs `random.choice()` or indexing after sampling.

**Ex6 — Data Alchemist**
List comprehension = concise replacement for "build empty list, loop, append." Runs closer to C speed since it skips repeated Python-level method lookups (`.append()` calls) and lets the interpreter better predict the final allocation size.
`[name.capitalize() for name in players]` — transform.
`[name for name in players if name.istitle()]` — filter.
Dict comprehension swaps `[]` for `{}` and produces `key: value` pairs instead of single items; duplicate keys overwrite rather than duplicate, unlike list comprehensions which keep every element.
Comprehensions trade a small readability cost for speed and memory efficiency — worth it only while the line stays readable; past that, fall back to a plain loop.

## Resources

- [Command Line Arguments in Python - GeeksforGeeks](https://www.geeksforgeeks.org/python/command-line-arguments-in-python/)
- [Python Tuples - W3Schools](https://www.w3schools.com/python/python_tuples.asp)
- [Set difference() - W3Schools](https://www.w3schools.com/PYTHON/ref_set_difference.asp)
- [Python Dictionaries - W3Schools](https://www.w3schools.com/python/python_dictionaries.asp)

### AI Usage

AI (Claude) was used during this project for the following:

- **README writing**: Generating structured notes based on my understanding built during development

All code was written and understood by me. AI was not used to generate final solutions directly.
