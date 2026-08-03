class GardenError(Exception):
    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)


class PlantError(GardenError):
    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


class WaterError(GardenError):
    def __init__(self, message: str = "Unknown water error") -> None:
        super().__init__(message)


class Plant:
    def __init__(self, name: str, age: int) -> None:
        self.name = name
        self.age = age

    def check_health(self) -> None:
        if self.age > 10:
            raise PlantError(f"The {self.name} is wilting!")


def check_tank(liters: int) -> None:
    if liters < 10:
        raise WaterError("Not enough water in the tank!")
    if liters == 42000000:
        raise WaterError()


def test_custom_errors() -> None:
    print("=== Custom Garden Errors Demo ===")

    tomato = Plant("tomato", age=15)

    print("\nTesting PlantError...")
    try:
        tomato.check_health()
    except PlantError as e:
        print(f"Caught PlantError: {e}")

    print("\nTesting WaterError...")
    try:
        check_tank(5)
    except WaterError as e:
        print(f"Caught WaterError: {e}")

    print("\nTesting catching all garden errors...")
    try:
        tomato.check_health()
    except GardenError as e:
        print(f"Caught GardenError: {e}")

    try:
        check_tank(2)
    except GardenError as e:
        print(f"Caught GardenError: {e}")

    try:
        check_tank(42000000)
    except GardenError as e:
        print(f"Caught GardenError: {e}")

    print("\nAll custom error types work correctly!")


if __name__ == "__main__":
    test_custom_errors()
