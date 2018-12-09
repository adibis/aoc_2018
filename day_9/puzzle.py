"""
AOC 2018, Day 9
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"


# NOTE: This is the in-efficient version of the solution that uses lists.
# The part 2 for this has 100x the input size. It ran on my machine for 40 minutes and din't complete.
# This is a great example of what using correct structures with least complexity can provide.
# I am using a deque in the optimized solution that finishes in 5 seconds. Please check that.
def main():
    """Day nine of AOC 2018"""
    starting_board = [0, 2, 1, 3]
    total_players = 473
    player_scores = 473 * [0]
    total_marbles = 70904

    new_index = 4
    for i in range(4, total_marbles+1):
        new_index = new_index + 2
        if (new_index > (len(starting_board) + 1)):
                new_index = (new_index) % len(starting_board)
        if ((i % 23) != 0):
            starting_board = starting_board[:new_index-1] + [i] + starting_board[new_index-1:]
        else:
            player_scores[i%total_players] += i
            remove_index = new_index-9
            #print ("I = ", i, " New Index = ", new_index, " Board len = ", len(starting_board))
            #print ("Removing ", starting_board[remove_index-1], " at index ", remove_index)
            player_scores[i%total_players] += starting_board[remove_index-1]
            starting_board = starting_board[:remove_index-1] + starting_board[remove_index:]
            if (remove_index < 0):
                new_index = len(starting_board) + remove_index + 1
                #print ("Resetting new index to ", new_index)
            else:
                new_index = remove_index
        #print(starting_board)

    print (max(player_scores))

if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
