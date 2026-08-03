class Plant:
    name: str
    height: float
    age_days: int
    height_growth_value: float

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.age_days} days old")

    def grow(self) -> None:
        self.height = round(self.height + self.height_growth_value, 1)

    def age(self) -> None:
        self.age_days += 1


def main() -> None:
    print("=== Garden Plant Growth ===")
    rose = Plant()
    rose.name = "Rose"
    rose.height = 25.0
    rose.age_days = 30
    rose.height_growth_value = 0.8

    start_height = rose.height
    rose.show()

    for day in range(1, 8):
        print(f"=== Day {day} ===")
        rose.grow()
        rose.age()
        rose.show()

    print(f"Growth this week: {round(rose.height - start_height, 1)}cm")


if __name__ == "__main__":
    main()
