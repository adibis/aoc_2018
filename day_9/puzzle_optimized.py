"""
AOC 2018, Day 9
"""

from collections import deque

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"


def play_game(players, marbles):

    starting_board = deque([0])
    total_players = players
    player_scores = players * [0]
    total_marbles = marbles

    for i in range(1, total_marbles+1):
        # First of all - the complicated algorithm to get the index of the next element
        # for the list solution is not required here. You can rotate the queue by one every time
        # and the second rotation is automatic (since we enter the new element there).
        # It keeps building the queue with the correct elements each time.
        if ((i % 23) != 0):
            starting_board.rotate(-1)
            starting_board.append(i)
        else:
            # Calculate the index to remove if this is the 23rd marble.
            # We rotate the queue by 7 so element to remove is at the end.
            # We pop it.
            #print("Before removal board: ", starting_board)
            # Before removal board:  deque([11, 1, 12, 6, 13, 3, 14, 7, 15, 0, 16, 8, 17, 4, 18, 9, 19, 2, 20, 10, 21, 5, 22])
            starting_board.rotate(7)
            #print("Removal board: ", starting_board)
            # Removal board:  deque([19, 2, 20, 10, 21, 5, 22, 11, 1, 12, 6, 13, 3, 14, 7, 15, 0, 16, 8, 17, 4, 18, 9])
            player_scores[i%total_players] += i
            player_scores[i%total_players] += starting_board.pop()
            # Now the new marble should be the one next to it on the right.
            # So rotate it by -1 to make it the right-most item.
            starting_board.rotate(-1)
            #print("Append board: ", starting_board)
            # Append board:  deque([2, 20, 10, 21, 5, 22, 11, 1, 12, 6, 13, 3, 14, 7, 15, 0, 16, 8, 17, 4, 18, 19])

    return (max(player_scores))

def main():
    """Day nine of AOC 2018"""

    print ("TEST: Solution: ", play_game(9,25))
    print ("PART A: Solution: ", play_game(473, 70904))
    print ("PART B: Solution: ", play_game(473, 7090400))


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
