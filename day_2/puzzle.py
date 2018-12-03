"""
AOC 2018, Day 2
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"

def gen_characters(code):
    characters = dict()
    for letter in code:
        if letter in characters:
            characters[letter] += 1
        else:
            characters[letter] = 1

    return characters

def has_n_letters(code, n):
    characters = gen_characters(code)
    for key in characters:
        if characters[key] == n:
            return True
    return False

def get_code(code_1, code_2):
    diff = ""
    key = ""
    for a, b in zip(code_1, code_2):
        if a != b:
            diff += a+b
        else:
            key += a
    if len(diff) == 2:
        return key
    else:
        return False

def main():
    """Find the checksum of boxes and find two boxes which differ by 1"""
    with open ("input.txt", 'r') as f:
        read_data = f.readlines()

    two_letters = 0
    three_letters = 0
    checksum = 0
    key_found = False

    for code in read_data:
        if has_n_letters(code, 2):
            two_letters += 1
        if has_n_letters(code, 3):
            three_letters += 1

    checksum = two_letters * three_letters
    print("Final checksum: " + str(checksum))

    for code_1 in read_data:
        for code_2 in read_data:
            key = get_code(code_1, code_2)
            if key:
                print ("Matching Boxes: " + key )
                key_found = True
                break
        if key_found:
            break


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
