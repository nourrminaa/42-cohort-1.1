import sys


def fill_inventory() -> dict:
    inventory = {}
    for i in range(1, len(sys.argv)):
        arg = sys.argv[i]
        parts = arg.split(':')
        if len(parts) != 2:
            print(f"Error - invalid parameter '{arg}'")
            continue
        name, quantity = parts[0], parts[1]
        if name in inventory:
            print(f"Redundant item '{name}' - discarding")
            continue
        try:
            inventory[name] = int(quantity)
        except ValueError as e:
            print(f"Quantity error for '{name}': {e}")
    return inventory


def display_inventory(inventory: dict) -> None:
    print(f"Got inventory: {inventory}")
    print(f"Item list: {list(inventory.keys())}")


def display_stats(inventory: dict) -> None:
    total = sum(inventory.values())
    print(f"Total quantity of the {len(inventory)} items: {total}")
    for item in inventory.keys():
        pct = round(inventory[item] / total * 100, 1)
        print(f"Item {item} represents {pct}%")


def display_abundance(inventory: dict) -> None:
    most = list(inventory.keys())[0]
    least = list(inventory.keys())[0]
    for item in inventory.keys():
        if inventory[item] > inventory[most]:
            most = item
        if inventory[item] < inventory[least]:
            least = item
    print(f"Item most abundant: {most} with quantity {inventory[most]}")
    print(f"Item least abundant: {least} with quantity {inventory[least]}")


def main() -> None:
    if len(sys.argv) == 1:
        print("No parameters provided. Each parameter "
              "must follow this format: <item_name>:<quantity>")
        return
    print("=== Inventory System Analysis ===")
    inventory = fill_inventory()
    if not inventory:
        print("No valid items provided.")
        return
    display_inventory(inventory)
    display_stats(inventory)
    display_abundance(inventory)
    inventory.update({'magic_item': 1})
    print(f"Updated inventory: {inventory}")


if __name__ == "__main__":
    main()
