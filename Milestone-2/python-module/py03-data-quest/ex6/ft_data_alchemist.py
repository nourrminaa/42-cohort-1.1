import random


def main() -> None:

    players = ['Alice', 'bob', 'Charlie', 'dylan', 'Emma',
               'Gregory', 'john', 'kevin', 'Liam ']
    capitalized = [name.strip().capitalize() for name in players]
    capitalized_only = [name for name in players if name == name.capitalize()]
    scores = {name: random.randint(0, 999) for name in capitalized}
    average = sum(scores.values()) / len(scores)
    high_scores = {
        name: score for name, score in scores.items() if score > average
    }

    print("=== Game Data Alchemist ===")
    print(f"\nInitial list of players: {players}")
    print(f"New list with all names capitalized: {capitalized}")
    print(f"New list of capitalized names only: {capitalized_only}")
    print(f"\nScore dict: {scores}")
    print(f"Score average is {round(average, 2)}")
    print(f"High scores: {high_scores}")


if __name__ == "__main__":
    main()
