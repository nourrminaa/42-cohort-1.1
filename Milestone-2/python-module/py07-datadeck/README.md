_This project has been created as part of the 42 curriculum by nmina._

# DataDeck — Abstract Card Architecture

Python 3.10+ implementation of a creature-card system built around three
design patterns: Abstract Factory (ex0), capability mixins via multiple
inheritance (ex1), and Strategy (ex2).

## Project Structure

```
datadeck/
├── ex0/
│   ├── __init__.py      # exposes CreatureFactory, FlameFactory, AquaFactory
│   ├── creatures.py      # Creature (ABC), Flameling, Pyrodon, Aquabub, Torragon
│   └── factories.py      # CreatureFactory (ABC), FlameFactory, AquaFactory
├── ex1/
│   ├── __init__.py       # exposes HealingCreatureFactory, TransformCreatureFactory
│   ├── capabilities.py   # HealCapability (ABC), TransformCapability (ABC)
│   ├── creatures.py      # Sproutling, Bloomelle, Shiftling, Morphagon
│   └── factories.py      # HealingCreatureFactory, TransformCreatureFactory
├── ex2/
│   ├── __init__.py       # exposes BattleStrategy family + InvalidStrategyError
│   ├── exceptions.py      # InvalidStrategyError
│   └── strategies.py      # BattleStrategy (ABC), Normal/Aggressive/Defensive
├── battle.py              # root test script for ex0
├── capacitor.py           # root test script for ex1
└── tournament.py          # root test script for ex2
```

## Cheat Sheet

| Concept                                   | Where used                                                                               | Purpose                                                                                                                                                            |
| ----------------------------------------- | ---------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `ABC` + `@abstractmethod`                 | `Creature`, `CreatureFactory`, `HealCapability`, `TransformCapability`, `BattleStrategy` | Forbid instantiation until every abstract method is overridden                                                                                                     |
| Abstract Factory                          | `ex0`, `ex1`                                                                             | Caller depends only on `CreatureFactory`; concrete Creature classes never leave the package                                                                        |
| Multiple inheritance (mixin)              | `Sproutling(Creature, HealCapability)` etc.                                              | Compose orthogonal behavior without forcing capabilities into the `Creature` hierarchy                                                                             |
| Covariant return types                    | `FlameFactory.create_base() -> Flameling`                                                | Narrows the abstract `-> Creature` signature so mypy exposes the concrete API to callers typed against the specific factory                                        |
| Strategy                                  | `ex2`                                                                                    | Decouples "how a turn plays out" from the tournament loop; no `isinstance` branching in `battle()`                                                                 |
| `isinstance()` capability check           | `AggressiveStrategy.is_valid`, `DefensiveStrategy.is_valid`                              | Runtime duck-typing gate; a Creature qualifies by having the capability, not by family                                                                             |
| Custom exception (`InvalidStrategyError`) | `ex2/exceptions.py`                                                                      | Lets callers `except InvalidStrategyError` specifically instead of a bare `except Exception`                                                                       |
| `...` (Ellipsis) vs `pass`                | abstract method bodies use `...`; `InvalidStrategyError` body uses `pass`                | Both are no-op placeholders; `...` is the idiomatic stub marker for abstract/interface bodies, `pass` is the idiomatic marker for a genuinely empty concrete block |
| `type_` (trailing underscore)             | `Creature.__init__(self, name, type_)`                                                   | Avoids shadowing the `type` builtin inside the constructor's scope; PEP 8-sanctioned pattern (also `class_`, `id_`)                                                |

## Exercise Table

| Exercise | Files                   | Pattern                              | Key Classes                                                                                           |
| -------- | ----------------------- | ------------------------------------ | ----------------------------------------------------------------------------------------------------- |
| ex0      | `battle.py`, `ex0/`     | Abstract Factory                     | `Creature`, `CreatureFactory`, `FlameFactory`, `AquaFactory`                                          |
| ex1      | `capacitor.py`, `ex1/`  | Mixin composition + Abstract Factory | `HealCapability`, `TransformCapability`, `HealingCreatureFactory`, `TransformCreatureFactory`         |
| ex2      | `tournament.py`, `ex2/` | Strategy                             | `BattleStrategy`, `NormalStrategy`, `AggressiveStrategy`, `DefensiveStrategy`, `InvalidStrategyError` |

## Per-Exercise Gotchas

### ex0 — Abstract Factory

- The package must never expose concrete Creature classes — only `CreatureFactory`
  subclasses. This is enforced by what `ex0/__init__.py` imports, not by any
  runtime guard; submodule access (`ex0.creatures.Flameling`) still works if
  someone reaches for it directly.
- `describe()` is concrete on `Creature`, not abstract — it doesn't need to be
  reimplemented per subclass, and it calls `self.name` / `self.type`
  polymorphically regardless of which concrete class `self` actually is.

### ex1 — Capabilities via mixin

- `HealCapability` and `TransformCapability` do **not** inherit from `Creature`.
  Mixing them in (`class Sproutling(Creature, HealCapability)`) keeps
  capabilities reusable outside the Creature hierarchy.
- `TransformCapability.__init__` sets `self.transformed = False`. Because
  `Creature.__init__` and `TransformCapability.__init__` have different
  signatures, they're called explicitly by class name
  (`Creature.__init__(self, ...)` then `TransformCapability.__init__(self)`)
  rather than relying on a single cooperative `super()` chain.
- `attack()` on `Shiftling`/`Morphagon` branches on `self.transformed` — same
  method, different output depending on mutable state set by `transform()` /
  `revert()`.
- Factory return types are narrowed to the concrete class (e.g.
  `HealingCreatureFactory.create_base() -> Sproutling`, not `-> Creature`).
  Without this, `capacitor.py` calling `base.heal()` would fail `mypy --strict`,
  since `heal()` isn't part of the `Creature` interface.

### ex2 — Strategy

- `is_valid()` uses `isinstance(creature, TransformCapability)` /
  `isinstance(creature, HealCapability)` — validity is about which capability
  a Creature has, not which family/factory it came from.
- `act()` re-checks `is_valid()` internally and raises `InvalidStrategyError`
  on failure rather than letting an `AttributeError` propagate from calling
  `.transform()` on a Creature that doesn't have it.
- `assert isinstance(...)` statements after the validity check exist purely to
  satisfy `mypy --strict` (narrowing `creature: Creature` down to a type that
  actually has `.heal()` / `.transform()`); they carry no runtime behavior
  beyond that narrowing.
- `tournament.py` catches `InvalidStrategyError` per-fight so one bad
  factory/strategy pairing doesn't abort the whole round-robin.

## Validation

```
$ python3 -m flake8 --max-line-length=79 .
$ python3 -m mypy --strict battle.py capacitor.py tournament.py
Success: no issues found in 3 source files
```

All three root scripts (`battle.py`, `capacitor.py`, `tournament.py`) run
without exceptions and match the sample output given in the assignment.

## AI Usage Disclosure

Claude (Anthropic) was used to design and implement this module, including
architecture decisions (splitting capabilities out of the `Creature`
hierarchy, narrowing factory return types for `mypy --strict` compliance),
full code for all three exercises, and validation via `flake8` and `mypy`
run in a sandboxed environment. All design choices were reviewed and
explained on request before code generation.
