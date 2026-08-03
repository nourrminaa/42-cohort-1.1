_This project was developed as part of the 42 curriculum by nmina\__

# FuncMage

Functional programming in Python: lambdas, higher-order functions, closures, `functools`, and decorators.

## Cheat Sheet

| Concept               | One-liner                                                              |
| --------------------- | ---------------------------------------------------------------------- |
| Lambda                | Anonymous, single-expression function — use for short, throwaway logic |
| `map()`               | Transform every element → lazy iterator                                |
| `filter()`            | Keep elements matching a predicate → lazy iterator                     |
| `sorted()`            | New sorted list, `key=` picks comparison value                         |
| First-class functions | Functions can be assigned, passed, returned, stored                    |
| Higher-order function | Takes and/or returns a function                                        |
| `Callable`            | Type hint for "this is callable"                                       |
| `callable()`          | Built-in, runtime check if an object is callable                       |
| Closure               | Inner function retains access to outer scope after outer returns       |
| `nonlocal`            | Mutate an enclosing (non-global) variable from a closure               |
| `reduce()`            | Fold an iterable down to one value                                     |
| `partial()`           | Pre-fill arguments to create a specialized function                    |
| `lru_cache()`         | Memoize return values by argument signature                            |
| `singledispatch()`    | Pick implementation by type of first argument                          |
| Decorator             | Function that wraps another to add behavior, returns a wrapper         |
| `@wraps`              | Preserves `__name__`/`__doc__`/annotations of the wrapped function     |
| Decorator factory     | A function that returns a decorator (lets the decorator take args)     |
| `@staticmethod`       | No `self`, no instance access, callable on the class directly          |

## Exercises

| #   | Name            | Core Concepts                                                                  |
| --- | --------------- | ------------------------------------------------------------------------------ |
| 00  | Lambda Sanctum  | lambdas, `map`, `filter`, `sorted`                                             |
| 01  | Higher Realm    | first-class functions, higher-order functions, `Callable`                      |
| 02  | Memory Depths   | closures, lexical scoping, `nonlocal`                                          |
| 03  | Ancient Library | `functools`: `reduce`, `partial`, `lru_cache`, `singledispatch`                |
| 04  | Master's Tower  | decorators, `*args`/`**kwargs`, `@wraps`, decorator factories, `@staticmethod` |

## Gotchas Per Exercise

**00 — Lambda Sanctum**

- `filter()` returns a lazy iterator — wrap in `list()` if the exercise wants a list.
- Lambdas aren't faster than `def` — same performance, just more concise for one-liners.
- `sorted()` returns a new list; `list.sort()` mutates in place and only works on lists.

**01 — Higher Realm**

- `Callable` (capital C, typing) is a type hint. `callable()` (lowercase, builtin) is a runtime check. Don't confuse them.
- A function is "higher-order" if it takes a function arg OR returns one — doesn't need both.

**02 — Memory Depths**

- Without `nonlocal`, assigning to an enclosing variable inside a nested function creates a new local instead of mutating the outer one.
- Closures are how you get encapsulation without a class — the enclosing scope acts as private state.

**03 — Ancient Library**

- `lru_cache()` only helps if the function is pure (same input → same output); don't use it on functions with side effects or mutable default args.
- `partial()` binds positional args left to right — order matters when defining the specialized function.
- `singledispatch()` dispatches on the type of the _first_ argument only.

**04 — Master's Tower**

- `@decorator` sugar is literally `func = decorator(func)` — know this equivalence cold, it's a common eval question.
- Forgetting `*args, **kwargs` in the wrapper breaks the decorator for any function with a different signature.
- Skipping `@wraps` silently corrupts `__name__`/`__doc__` on the decorated function — easy eval flag.
- Decorator factories add a third layer: `factory(arg) -> decorator -> wrapper`. Trace the call order before debugging.

## AI Disclosure

This README was generated with AI assistance (Claude) based on personal study notes and 42 Beirut peer-evaluation prep.

---
