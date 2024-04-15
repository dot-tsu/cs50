def main():
    while True:
        try:
            pyramidHeight = int(
                input("How tall do you want the pyramids to be? (from 1 to 8): ")
            )
            if 1 <= pyramidHeight <= 8:
                break
            else:
                print("Please enter a number between 1 and 8.")
        except ValueError:
            print("Please enter a valid integer.")

    makePyramid(pyramidHeight)


def makePyramid(pyramidHeight):
    leadingSpaces = pyramidHeight
    for pyramidFloor in range(pyramidHeight):
        leadingSpaces -= 1
        # Print leading spaces
        print(" " * leadingSpaces, end="")

        # Print left-side blocks
        printHashes(pyramidFloor)

        # Print the gap between blocks
        print("  ", end="")

        # Print right-side blocks
        printHashes(pyramidFloor)

        # Go to the next floor
        print()


def printHashes(floor):
    for blocks in range(floor + 1):
        print("#", end="")


main()
