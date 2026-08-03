def input_temperature(temp_str: str) -> int:
    try:
        temp_int = int(temp_str)
    except ValueError:
        raise ValueError(
            f"invalid literal for int() with base 10: '{temp_str}'"
        )
    if temp_int < 0:
        raise ValueError(f"{temp_int}°C is too cold for plants (min 0°C)")
    if temp_int > 40:
        raise ValueError(f"{temp_int}°C is too hot for plants (max 40°C)")
    print(f"Temperature is now {temp_int}°C")
    return temp_int


def test_temperature() -> None:
    print("=== Garden Temperature Checker ===")
    for val in ["25", "abc", "100", "-50"]:
        print(f"\nInput data is '{val}'")
        try:
            input_temperature(val)
        except ValueError as e:
            print(f"Caught input_temperature error: {e}")
    print("\nAll tests completed - program didn't crash!")


if __name__ == "__main__":
    test_temperature()
