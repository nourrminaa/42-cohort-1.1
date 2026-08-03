from typing import List, Tuple

from ex0 import AquaFactory, CreatureFactory, FlameFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import (
    AggressiveStrategy,
    BattleStrategy,
    DefensiveStrategy,
    InvalidStrategyError,
    NormalStrategy,
)

Opponent = Tuple[CreatureFactory, BattleStrategy]


def strategy_label(strategy: BattleStrategy) -> str:
    return type(strategy).__name__.replace("Strategy", "").lower()


def battle(opponents: List[Opponent]) -> None:
    creatures = []
    for factory, strategy in opponents:
        creatures.append((factory.create_base(), strategy))

    creature_a, strategy_a = creatures[0]
    creature_b, strategy_b = creatures[1]

    print("* Battle *")
    print(creature_a.describe())
    print(" vs.")
    print(creature_b.describe())
    print(" now fight!")

    for creature, strategy in creatures:
        if not strategy.is_valid(creature):
            raise InvalidStrategyError(
                f"Invalid Creature '{creature.name}' for this "
                f"{strategy_label(strategy)} strategy"
            )
        print(strategy.act(creature))


def run_tournament(
    label: str, description: str, opponents: List[Opponent]
) -> None:
    print(label)
    print(description)
    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved")
    try:
        print()
        battle(opponents)
    except InvalidStrategyError as error:
        print(f"Battle error, aborting tournament: {error}")


def main() -> None:
    run_tournament(
        "Tournament 0 (basic)",
        "[ (Flameling+Normal), (Healing+Defensive) ]",
        [
            (FlameFactory(), NormalStrategy()),
            (HealingCreatureFactory(), DefensiveStrategy()),
        ],
    )
    print()
    run_tournament(
        "Tournament 1 (error)",
        "[ (Flameling+Aggressive), (Healing+Defensive) ]",
        [
            (FlameFactory(), AggressiveStrategy()),
            (HealingCreatureFactory(), DefensiveStrategy()),
        ],
    )
    print()
    run_tournament(
        "Tournament 2 (multiple)",
        "[ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ]",
        [
            (AquaFactory(), NormalStrategy()),
            (HealingCreatureFactory(), DefensiveStrategy()),
            (TransformCreatureFactory(), AggressiveStrategy()),
        ],
    )


if __name__ == "__main__":
    main()
