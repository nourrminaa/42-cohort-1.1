from collections.abc import Callable


def spell(target: str, power: int) -> str:
    return f"{target} is hit with a spell of power {power}!"


def heal(target: str, power: int) -> str:
    return f"Heal restores {target} for {power} HP"


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:
    def combined_spell(target: str, power: int) -> tuple[str, str]:
        return (
            spell1(target, power),
            spell2(target, power)
        )

    return combined_spell


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:
    def amplified_spell(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)

    return amplified_spell


def conditional_caster(condition: Callable, spell: Callable) -> Callable:
    def conditional_spell(target: str, power: int) -> str:
        if condition(target, power):
            return spell(target, power)
        return "Spell fizzled"

    return conditional_spell


def spell_sequence(spells: list[Callable]) -> Callable:
    def sequence_spell(target: str, power: int) -> list[str]:
        return [spell(target, power) for spell in spells]

    return sequence_spell


def is_powerful(target: str, power: int) -> bool:
    return power >= 20


def main() -> None:
    print("Testing spell combiner...")
    combined = spell_combiner(spell, heal)
    result1, result2 = combined("Dragon", 10)
    print(f"Combined spell result: {result1}, {result2}")

    print("\nTesting power amplifier...")
    original_power = 10

    multiplier = 3
    mega_spell = power_amplifier(spell, multiplier)
    mega_spell("Dragon", original_power)
    print(
        f"Original: {original_power}, "
        f"Amplified: {original_power * multiplier}"
    )

    print("\nTesting conditional caster...")
    conditional_spell = conditional_caster(is_powerful, spell)

    print(conditional_spell("Goblin", 10))
    print(conditional_spell("Goblin", 25))

    print("\nTesting spell sequence...")
    sequence = spell_sequence([spell, heal])

    for result in sequence("Knight", 15):
        print(result)


if __name__ == "__main__":
    main()
