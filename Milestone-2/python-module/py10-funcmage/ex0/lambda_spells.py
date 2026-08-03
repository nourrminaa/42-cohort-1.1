def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    return sorted(
        artifacts,
        key=lambda artifact: artifact['power'],
        reverse=True
    )


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    return list(
        filter(lambda mage: mage['power'] >= min_power, mages)
    )


def spell_transformer(spells: list[str]) -> list[str]:
    return list(
        map(lambda spell: "* " + spell + " *", spells)
    )


def mage_stats(mages: list[dict]) -> dict:
    if not mages:
        return {
            'max_power': None,
            'min_power': None,
            'avg_power': 0.0
        }

    return {
        'max_power': max(
            mages,
            key=lambda mage: mage['power']
        )['power'],

        'min_power': min(
            mages,
            key=lambda mage: mage['power']
        )['power'],

        'avg_power': round(
            sum(map(lambda mage: mage['power'], mages)) / len(mages),
            2
        )
    }


def main() -> None:
    print("Testing artifact sorter...")

    artifacts = [
        {
            "name": "Crystal Orb",
            "power": 85,
            "type": "artifact"
        },
        {
            "name": "Fire Staff",
            "power": 92,
            "type": "weapon"
        }
    ]

    sorted_artifacts = artifact_sorter(artifacts)

    for artifact in sorted_artifacts:
        print(
            f"{artifact['name']} ({artifact['power']} power)"
        )

    print("\nTesting spell transformer...")

    spells = ["fireball", "heal", "shield"]

    transformed = spell_transformer(spells)

    print(" ".join(transformed))

    print("\nTesting power filter...")

    mages = [
        {
            "name": "Merlin",
            "power": 100,
            "element": "arcane"
        },
        {
            "name": "Luna",
            "power": 70,
            "element": "water"
        },
        {
            "name": "Kai",
            "power": 85,
            "element": "fire"
        }
    ]

    powerful_mages = power_filter(mages, 80)

    print(powerful_mages)

    print("\nTesting mage stats...")

    print(mage_stats(mages))


if __name__ == "__main__":
    main()
