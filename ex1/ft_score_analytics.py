import sys


def main() -> None:
    print("=== Player Score Analytics ===")

    scores = []
    for i in range(1, len(sys.argv)):
        try:
            scores.append(int(sys.argv[i]))
        except ValueError:
            print(f"Invalid parameter: '{sys.argv[i]}'")

    if len(scores) == 0:
        print("No scores provided.")
        print(f"Usage: python3 {sys.argv[0]} <score1> <score2> ...")
        return

    total = sum(scores)
    average = total / len(scores)
    high = max(scores)
    low = min(scores)

    print(f"Scores processed: {scores}")
    print(f"Total players: {len(scores)}")
    print(f"Total score: {total}")
    print(f"Average score: {average}")
    print(f"High score: {high}")
    print(f"Low score: {low}")
    print(f"Score range: {high - low}")


if __name__ == "__main__":
    main()
