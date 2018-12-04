"""
AOC 2018, Day 4
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"

def split_code(code):
    month = (code.split(' ')[0]).split('-')[1]
    date = (code.split(' ')[0]).split('-')[2]
    minute = (code.split(' ')[1]).split(':')[1]
    minute = minute[:-1]

    return month, date, minute

def main():
    """Day four of AOC 2018"""
    with open ("input.txt", 'r') as f:
        read_data = f.readlines()

    guards = dict()

    # Sort the data since we have to look at shifts.
    for code in sorted(read_data):
        month, date, minute = split_code(code)
        # The sleep/wake is based on most recent guard.
        # So we can just pick the guard first and then pick times.
        # This is limited by _very strict_ input validation.
        if ('Guard' in code):
            guard = (code.split('#')[1]).split(' ')[0]
            if guard not in guards:
                guards[guard] = 60 * [0]

        if ('sleep' in code):
            start_minute = minute

        if ('wakes' in code):
            stop_minute = minute
            for i in range(int(start_minute),int(stop_minute)):
                guards[guard][i] += 1

    # These variable names could be better.
    guard_max_slept = 0;
    max_slept_guard = 0;
    max_slept_min = 0;
    min_max_slept = 0;
    max_min_slept_guard = 0;

    for i in guards:
        if sum(guards[i]) > guard_max_slept:
            max_slept_guard = i;
            guard_max_slept = sum(guards[i])

        if max(guards[i]) > min_max_slept:
            max_min_slept_guard = i
            max_slept_min = guards[i].index(max(guards[i]))
            min_max_slept = max(guards[i])


    chosen_id_part_2 = int(max_min_slept_guard) * int(max_slept_min)
    max_slept_min = guards[max_slept_guard].index(max(guards[max_slept_guard]))
    chosen_id_part_1 = int(max_slept_guard) * int(max_slept_min)
    print ("PART 1: ID of chosen guard = ", chosen_id_part_1)
    print ("PART 2: ID of chosen guard = ", chosen_id_part_2)


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
