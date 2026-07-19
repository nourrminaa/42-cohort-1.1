import math


def get_player_pos() -> tuple:
    while True:
        input_val = input(
            "Enter new coordinates as floats in format 'x,y,z': "
        )
        parts = input_val.split(',')
        if len(parts) != 3:
            print("Invalid syntax")
            continue
        valid = True
        coords = []
        for part in parts:
            try:
                coords.append(float(part.strip()))
            except ValueError as e:
                print(f"Error on parameter '{part}': {e}")
                valid = False
                break
        if valid:
            return tuple(coords)


def main() -> None:
    print("=== Game Coordinate System ===")

    print("\nGet a first set of coordinates")
    pos1 = get_player_pos()
    print(f"Got a first tuple: {pos1}")
    print(f"It includes: X={pos1[0]}, Y={pos1[1]}, Z={pos1[2]}")
    dist_origin = round(
        math.sqrt(pos1[0]**2 + pos1[1]**2 + pos1[2]**2), 4
    )
    print(f"Distance to center: {dist_origin}")

    print("\nGet a second set of coordinates")
    pos2 = get_player_pos()
    dist = round(
        math.sqrt(
            (pos2[0]-pos1[0])**2 +
            (pos2[1]-pos1[1])**2 +
            (pos2[2]-pos1[2])**2
        ), 4
    )
    print(f"Distance between the 2 sets of coordinates: {dist}")


if __name__ == "__main__":
    main()
