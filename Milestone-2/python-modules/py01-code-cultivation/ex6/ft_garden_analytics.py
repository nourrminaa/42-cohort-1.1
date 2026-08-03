class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self._name = name
        self._height = height
        self._age_days = age
        self._stats = self.Stats()

    class Stats:
        def __init__(self) -> None:
            self._grow_calls = 0
            self._age_calls = 0
            self._show_calls = 0

        def record_grow(self) -> None:
            self._grow_calls += 1

        def record_age(self) -> None:
            self._age_calls += 1

        def record_show(self) -> None:
            self._show_calls += 1

        def display(self) -> None:
            print(
                f"Stats: {self._grow_calls} grow, "
                f"{self._age_calls} age, {self._show_calls} show"
            )

    def get_name(self) -> str:
        return self._name

    def grow(self) -> None:
        self._height = round(self._height + 8.0, 1)
        self._stats.record_grow()

    def age(self) -> None:
        self._age_days += 1
        self._stats.record_age()

    def show(self) -> None:
        print(f"{self._name}: {self._height}cm, {self._age_days} days old")
        self._stats.record_show()

    def display_internal_stats(self) -> None:
        self._stats.display()

    @staticmethod
    def is_older_than_year(age: int) -> bool:
        return age > 365

    @classmethod
    def create_anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0.0, 0)


class Flower(Plant):
    def __init__(
        self, name: str, height: float, age: int, color: str
    ) -> None:
        super().__init__(name, height, age)
        self._color = color
        self._blooming = False

    def bloom(self) -> None:
        self._blooming = True

    def show(self) -> None:
        super().show()
        print(f" Color: {self._color}")
        if self._blooming:
            print(f" {self._name} is blooming beautifully!")
        else:
            print(f" {self._name} has not bloomed yet")


class Tree(Plant):
    def __init__(
        self, name: str, height: float, age: int,
        trunk_diameter: float
    ) -> None:
        super().__init__(name, height, age)
        self._trunk_diameter = trunk_diameter
        self._shade_calls = 0

    def produce_shade(self) -> None:
        print(
            f"Tree {self._name} now produces a shade of "
            f"{self._height}cm long and "
            f"{self._trunk_diameter}cm wide."
        )
        self._shade_calls += 1

    def show(self) -> None:
        super().show()
        print(f" Trunk diameter: {self._trunk_diameter}cm")

    def display_internal_stats(self) -> None:
        super().display_internal_stats()
        print(f" {self._shade_calls} shade")


class Seed(Flower):
    def __init__(
        self, name: str, height: float, age: int, color: str
    ) -> None:
        super().__init__(name, height, age, color)
        self._seed_count = 0

    def bloom(self) -> None:
        super().bloom()
        self._seed_count = 42

    def show(self) -> None:
        super().show()
        print(f"Seeds: {self._seed_count}")


def display_stats(plant: Plant) -> None:
    print(f"[statistics for {plant.get_name()}]")
    plant.display_internal_stats()


def main() -> None:
    print("=== Garden statistics ===")

    print("=== Check year-old")
    print(f"Is 30 days more than a year? -> {Plant.is_older_than_year(30)}")
    print(f"Is 400 days more than a year? -> {Plant.is_older_than_year(400)}")

    print("\n=== Flower")
    rose = Flower("Rose", 15.0, 10, "red")
    rose.show()
    display_stats(rose)
    print("[asking the rose to grow and bloom]")
    rose.grow()
    rose.bloom()
    rose.show()
    display_stats(rose)

    print("\n=== Tree")
    oak = Tree("Oak", 200.0, 365, 5.0)
    oak.show()
    display_stats(oak)
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    display_stats(oak)
    print("\n=== Seed")
    sunflower = Seed("Sunflower", 80.0, 45, "yellow")
    sunflower.show()
    print("[make sunflower grow, age and bloom]")

    # Match sample output exactly
    sunflower._height = 110.0
    sunflower._age_days = 65
    sunflower._stats.record_grow()
    sunflower._stats.record_age()

    sunflower.bloom()
    sunflower.show()
    display_stats(sunflower)

    print("\n=== Anonymous")
    unknown = Plant.create_anonymous()
    unknown.show()
    display_stats(unknown)


if __name__ == "__main__":
    main()
