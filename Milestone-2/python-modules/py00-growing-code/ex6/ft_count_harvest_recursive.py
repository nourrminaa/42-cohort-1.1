def helper_print(days):
    if days < 1:
        return
    helper_print(days - 1)
    print(f"Day {days}")


def ft_count_harvest_recursive():
    days = int(input("Days until harvest: "))
    helper_print(days)
    print("Harvest time!")
