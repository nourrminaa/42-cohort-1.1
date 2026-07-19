import random


class Player:
    def __init__(self, name: str, ach_set: set) -> None:
        self.name = name
        self.ach_set = ach_set


def gen_player_achievements(achievements_list: list) -> set:
    count = random.randint(3, len(achievements_list) // 2)
    return set(random.sample(achievements_list, count))


def main() -> None:
    print("=== Achievement Tracker System ===")
    print()
    achievements_list = [
        'Crafting Genius', 'Strategist', 'World Savior', 'Speed Runner',
        'Survivor', 'Master Explorer', 'Treasure Hunter', 'Unstoppable',
        'First Steps', 'Collector Supreme', 'Untouchable', 'Sharp Mind',
        'Boss Slayer'
    ]
    all_achievements = set(achievements_list)

    player1 = Player("Alice", gen_player_achievements(achievements_list))
    player2 = Player("Bob", gen_player_achievements(achievements_list))
    player3 = Player("Charlie", gen_player_achievements(achievements_list))
    player4 = Player("Dylan", gen_player_achievements(achievements_list))

    for p in [player1, player2, player3, player4]:
        print(f"Player {p.name}: {p.ach_set}")

    p1, p2, p3, p4 = player1, player2, player3, player4

    print()
    all_distinct = p1.ach_set.union(p2.ach_set, p3.ach_set, p4.ach_set)
    print(f"All distinct achievements: {all_distinct}")

    common = p1.ach_set.intersection(p2.ach_set, p3.ach_set, p4.ach_set)
    print(f"\nCommon achievements: {common}")

    only1 = p1.ach_set.difference(p2.ach_set, p3.ach_set, p4.ach_set)
    only2 = p2.ach_set.difference(p1.ach_set, p3.ach_set, p4.ach_set)
    only3 = p3.ach_set.difference(p1.ach_set, p2.ach_set, p4.ach_set)
    only4 = p4.ach_set.difference(p1.ach_set, p2.ach_set, p3.ach_set)

    print(f"\nOnly {p1.name} has: {only1}")
    print(f"Only {p2.name} has: {only2}")
    print(f"Only {p3.name} has: {only3}")
    print(f"Only {p4.name} has: {only4}")

    print(f"\n{p1.name} is missing: {all_achievements.difference(p1.ach_set)}")
    print(f"{p2.name} is missing: {all_achievements.difference(p2.ach_set)}")
    print(f"{p3.name} is missing: {all_achievements.difference(p3.ach_set)}")
    print(f"{p4.name} is missing: {all_achievements.difference(p4.ach_set)}")


if __name__ == "__main__":
    main()
