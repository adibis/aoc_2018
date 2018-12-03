"""
AOC 2018, Day 3
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"

def split_code(code):
    coord = code.split(' ')[2]
    size = code.split(' ')[3]
    coord = coord.replace(':', '')
    coord_x, coord_y = coord.split(',')
    size_x, size_y = size.split('x')

    coord_x = int(coord_x)
    coord_y = int(coord_y)
    size_x = int(size_x)
    size_y = int(size_y)

    return(coord_x, coord_y, size_x, size_y)

def main():
    """Day three of AOC 2018"""
    with open ("input.txt", 'r') as f:
        read_data = f.readlines()

    graph = dict()
    overlap = 0

    for code in read_data:
        coord_x, coord_y, size_x, size_y = split_code(code)
        for x in range(0,size_x):
            if (coord_x+x) not in graph:
                graph[coord_x+x] = dict()
            for y in range(0, size_y):
                if (coord_y+y) in graph[coord_x+x]:
                    graph[coord_x+x][coord_y+y] += 1
                else:
                    graph[coord_x+x][coord_y+y] = 0


    # Find all the overlaps
    for coord_x in graph:
        for coord_y in graph[coord_x]:
            if graph[coord_x][coord_y] > 0:
                overlap += 1

    # Do second pass to check which fabric never overlapped.
    for code in read_data:
        coord_x, coord_y, size_x, size_y = split_code(code)
        good_fabric = True
        for x in range(0,size_x):
            for y in range(0, size_y):
                if graph[coord_x+x][coord_y+y] > 0:
                    good_fabric = False

        if good_fabric:
            print ("Good fabric ID is: ", code)

    print ("Final overlap is: ", overlap)


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
