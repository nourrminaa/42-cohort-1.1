_This project has been created as part of the 42 curriculum by nmina._

# module-06 — The Codex: Mastering Python's Import Mysteries

Python import system deep-dive: package initialization, absolute vs.
relative imports, nested cross-module imports, and circular dependency
resolution.

## Structure

```
.
├── alchemy/
│   ├── __init__.py
│   ├── elements.py
│   ├── potions.py
│   ├── grimoire/
│   │   ├── __init__.py
│   │   ├── light_spellbook.py
│   │   ├── light_validator.py
│   │   ├── dark_spellbook.py
│   │   └── dark_validator.py
│   └── transmutation/
│       ├── __init__.py
│       └── recipes.py
├── elements.py
├── ft_alembic_0.py .. ft_alembic_5.py
├── ft_distillation_0.py, ft_distillation_1.py
├── ft_transmutation_0.py .. ft_transmutation_2.py
└── ft_kaboom_0.py, ft_kaboom_1.py
```

## Cheat sheet

| Concept                | Syntax                                    | Notes                                                     |
| ---------------------- | ----------------------------------------- | --------------------------------------------------------- |
| Absolute import        | `import alchemy.elements`                 | Full path from project root                               |
| Absolute from-import   | `from alchemy.elements import create_air` | Binds name directly                                       |
| Relative import        | `from .elements import create_air`        | `.` = same package                                        |
| Parent-relative import | `from ..elements import create_air`       | `..` = parent package                                     |
| Module-only import     | `from . import light_validator`           | Import module object, not a name — avoids circular import |
| Package re-export      | `__init__.py` + `__all__`                 | Controls what `import alchemy` exposes                    |

**Circular import fix used here:** import the _module_, not a _name_ from
it (`from . import light_validator`, then call
`light_validator.validate_ingredients(...)`). At import time, Python only
needs the module object to exist in `sys.modules` — it doesn't need the
target function to be defined yet. Deferred/lazy imports (import inside a
function body) are the other common fix, but doing that made
`ft_kaboom_1` fail to reproduce the intended circular import error, so it
was reverted to a top-level import.

## Exercise table

| Part | Script                  | Import style                                                    | Target                              | Result                                                                  |
| ---- | ----------------------- | --------------------------------------------------------------- | ----------------------------------- | ----------------------------------------------------------------------- |
| I    | `ft_alembic_0.py`       | `import elements`                                               | `create_fire()`                     | success                                                                 |
| I    | `ft_alembic_1.py`       | `from elements import create_water`                             | `create_water()`                    | success                                                                 |
| I    | `ft_alembic_2.py`       | `import alchemy.elements`                                       | `create_earth()`                    | success                                                                 |
| I    | `ft_alembic_3.py`       | `from alchemy.elements import create_air`                       | `create_air()`                      | success                                                                 |
| I    | `ft_alembic_4.py`       | `import alchemy`                                                | `create_earth()`                    | **raises `AttributeError`** (on purpose — not exposed in `__init__.py`) |
| I    | `ft_alembic_5.py`       | `from alchemy import create_air`                                | `create_air()`                      | success                                                                 |
| II   | `ft_distillation_0.py`  | `from alchemy.potions import ...`                               | potions                             | success                                                                 |
| II   | `ft_distillation_1.py`  | `import alchemy`                                                | `strength_potion()`, `heal()` alias | success                                                                 |
| III  | `ft_transmutation_0.py` | `import alchemy.transmutation.recipes`                          | `lead_to_gold()`                    | success                                                                 |
| III  | `ft_transmutation_1.py` | `import alchemy.transmutation`                                  | `lead_to_gold()`                    | success                                                                 |
| III  | `ft_transmutation_2.py` | `import alchemy`                                                | `lead_to_gold()`                    | success                                                                 |
| IV   | `ft_kaboom_0.py`        | `from alchemy.grimoire import light_spell_record`               | light spell                         | success (cycle avoided)                                                 |
| IV   | `ft_kaboom_1.py`        | `from alchemy.grimoire.dark_spellbook import dark_spell_record` | dark spell                          | **raises `ImportError`** (on purpose — real circular import)            |

## Gotchas per part

- **Part I (`ft_alembic_4`):** `import alchemy` only exposes what
  `__init__.py` explicitly imports/re-exports. `create_earth` is never
  imported there, so `alchemy.create_earth()` raises `AttributeError`
  even though the function exists in `alchemy/elements.py`. mypy also
  flags this at `--strict` — expected, not a bug.
- **Part II:** `alchemy/potions.py` needs create*fire/create_water from
  the \_top-level* `elements.py` (absolute import) and create_air/create_earth
  from `alchemy/elements.py` (relative import) — both element sources are
  used deliberately to exercise both import styles in one file.
- **Part III:** `alchemy/transmutation/recipes.py` mixes an absolute
  import (`from elements import create_fire`, top-level file) with two
  relative imports (`from ..elements import create_air`,
  `from ..potions import strength_potion`) — demonstrates when each is
  necessary based on how "far" the target module is from the importer.
- **Part IV:** the light/dark spellbook-validator pairs are structurally
  identical except for one thing: light imports the _module_
  (`from . import light_validator`), dark imports a _name_ from the module
  at the top level (`from .dark_validator import validate_ingredients`).
  That one difference is what makes light survive and dark explode.
  `dark_spellbook.py`'s import **must** stay at the top of the file, not
  inside `dark_spell_record()` — a deferred import there defeats the
  circular-dependency demonstration entirely (confirmed by testing: it
  silently "fixes" the cycle instead of exploding).
- **flake8:** watch for `F541` (f-string with no placeholders) on prints
  that don't actually interpolate anything.
- **mypy --strict:** the project should show exactly one error total
  (`ft_alembic_4.py`, `attr-defined` on `create_earth`) — anything else
  is a real bug.

## AI usage disclosure

AI (Claude) was used to review this project's compliance with the subject
(flake8, mypy --strict, expected script outputs and exceptions)
