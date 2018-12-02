"""
AOC 2018, Day 1
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"


def main():
    """ Determine final frequency based on the input values """
    with open ("input.txt", 'r') as f:
        read_data = f.readlines()

    frequency = 0;
    seen_frequency = set()
    duplicate_found = False
    while not duplicate_found:
        for delta in read_data:
            if delta[0] == '+':
                frequency = frequency + int(delta[1:])
            else:
                frequency = frequency - int(delta[1:])

            if frequency in seen_frequency:
                print (frequency)
                duplicate_found = True
                break
            else:
                seen_frequency.add(frequency)


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
