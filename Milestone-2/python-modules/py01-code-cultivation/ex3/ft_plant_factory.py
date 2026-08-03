class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self.height = height
        self.age_days = age

    def show(self) -> None:
        print(f"{self.name.capitalize()}: {self.height}cm,\
               {self.age_days} days old")

    def grow(self, height_growth_value: float) -> None:
        self.height = round(self.height + height_growth_value, 1)

    def age(self) -> None:
        self.age_days += 1


def main() -> None:
    plants = [
        Plant("Rose", 25.0, 30),
        Plant("Oak", 200.0, 365),
        Plant("Cactus", 5.0, 90),
        Plant("Sunflower", 80.0, 45),
        Plant("fern", 15.0, 120),
    ]

    for plant in plants:
        print("Created: ", end="")
        plant.show()


if __name__ == "__main__":
    main()
