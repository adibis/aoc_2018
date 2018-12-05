"""
AOC 2018, Day 5
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"

# Remove poles (which are back to back letters of opposite case)
def remove_poles(read_data):
    was_reduced = True
    while was_reduced == True:
        was_reduced = False
        for i in range(len(read_data) - 1, -1, -1):
            if i == (len(read_data) - 1):
                continue
            else:
                # Check if letters differ in ASCII code by 32. If yes it's a matching pair.
                # Keep repeating until we have at least one reduction possible.
                if abs(ord(read_data[i]) - ord(read_data[i+1])) == 32:
                    del read_data[i+1]
                    del read_data[i]
                    was_reduced = True

    return read_data

def main():
    """Day five of AOC 2018"""
    with open ("input.txt", 'r') as f:
        read_data = f.read()


    # Save the read data for reuse later.
    golden_read_data = read_data

    # Part 1: Reduce the list as much as possible. Find the final size of it.
    read_data = list(read_data.strip())
    read_data = remove_poles(read_data)

    print ("PART 1: Length of Final String = ", len(read_data))

    # Part 2: Again, use the ascii code of letters to delete them from the string in a loop.
    small_letter = 65
    caps_letter = 97
    smallest_length = len(read_data)

    for alpha in range(0, 25):
        # Reset the input, delete letters one by one.
        # Then repeat the code above to see if it was reduced or not.
        read_data = golden_read_data
        read_data = read_data.replace(chr(small_letter+alpha), "")
        read_data = read_data.replace(chr(caps_letter+alpha), "")
        read_data = list(read_data.strip())
        read_data = remove_poles(read_data)

        if smallest_length > len(read_data):
            smallest_length = len(read_data)

    print ("PART 2: Length of Smallest String = ", smallest_length)


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
