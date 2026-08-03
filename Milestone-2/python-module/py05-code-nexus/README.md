_This project has been created as part of the 42 curriculum by nmina._

# Python Module 05: Data Pipeline - Abstract Classes & Polymorphism

## Core Concepts

```python
from abc import ABC, abstractmethod

class Vehicle(ABC):
    @abstractmethod
    def start_engine(self):
        pass

    def honk(self):
        return "Beep Beep!"
```

- **Abstract class**: cannot be instantiated (`Vehicle()` → `TypeError`), inherits from `ABC`.
- **Abstract method**: `@abstractmethod`, no implementation, must be overridden by subclasses.
- **Concrete method**: fully implemented in the abstract class, inherited as-is — no need to override.

## Exercises Overview

| Exercise | Concept                                           |
| -------- | ------------------------------------------------- |
| 0        | Abstract base processor, type validation          |
| 1        | Polymorphism via `DataStream`                     |
| 2        | Structural typing (`Protocol`) for export plugins |

## Key Concepts Per Exercise

**Ex0 — Abstract Processor Architecture**

- `isinstance()` over `type(var) == int` — correctly handles subclasses (e.g. `bool`).
- Edge case: `isinstance(True, int)` is `True` (bool is an int subclass). `validate(True)` silently passes. Not tested, but a grader could exploit it.
- Wrapping non-list input for uniform iteration:

```python
if isinstance(data, list):
    entries = data
else:
    entries = [data]
```

**Ex1 — Polymorphism in `DataStream`**

- `DataStream` only calls `proc.validate(elem)` / `proc.ingest(elem)` — never `isinstance(proc, NumericProcessor)`, never branches on type.
- Trusts the abstract contract; each subclass owns its own type logic.
- Benefits:
  - **Open/closed** — new processor types plug in without touching `DataStream`.
  - **Decoupling** — routing logic stays separate from type-specific validation.
  - **Testability** — mock/stub processors can be registered to test `DataStream` in isolation.

**Ex2 — Structural Typing with `Protocol`**

```python
class ExportPlugin(typing.Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...
```

- `Protocol` = duck typing for static analysis. Any class with a matching method signature satisfies it — no inheritance required.
- Not enforced at runtime, unlike `ABC`. Purely for `mypy`.

`CSVExportPlugin` — comma-joins values, discards rank:

```python
for i in range(len(data)):
    _, value = data[i]
    if i > 0:
        line += ","
    line += value
```

`JSONExportPlugin` — hand-builds a JSON object string, uses rank as key:

```python
for i in range(len(data)):
    rank, value = data[i]
    if i > 0:
        line += ", "
    line += f'"item_{rank}": "{value}"'
print(f"JSON Output: {{{line}}}")
```

- No `import json` — manual construction required by the subject.
- F-string brace escaping: `{{` and `}}` print literal `{` `}`; `{line}` interpolates normally. `{{{line}}}` = literal `{` + value of `line` + literal `}`.
- Pitfall: miscount the braces and you either leak `{{` into output or hit `ValueError: Single '{' encountered`.

## Resources

- [Python `abc` module — official docs](https://docs.python.org/3/library/abc.html)
- [`typing.Protocol` — official docs](https://docs.python.org/3/library/typing.html#typing.Protocol)

### AI Usage

AI (Claude) was used during this project for the following:

- **README writing**: Generating structured notes based on my understanding built during development

All code was written and understood by me. AI was not used to generate final solutions directly.
