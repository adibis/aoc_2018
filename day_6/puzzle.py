"""
AOC 2018, Day 6
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"

def get_mhtn_dist(min_x, max_x, min_y, max_y, read_data, bounded_area):
    nodes = dict()
    bounded_region = 0

    # For all points on the canvas...
    for x in range(min_x, max_x):
        for y in range(min_y, max_y):
            min_dist = 999999
            eq_dist = False
            closest_node = ""
            total_dist = 0
            # For each node from the input list...
            for node in read_data:
                node = node.strip()
                node_x, node_y = node.split(',')
                node_x = int(node_x)
                node_y = int(node_y)
                # Calculate the distance of each node from each point on canvas
                this_dist = abs(node_x-x) + abs(node_y-y)
                # Keep storing total distance of this point from each node
                total_dist += this_dist

                if node not in nodes:
                    nodes[node] = 0
                # If the point is closer to a node than any previous node then it
                # needs to be marked properly. Keep checking this till you find the closest point.
                if(this_dist <= min_dist):
                    if(this_dist != min_dist):
                        min_dist = this_dist
                        eq_dist = False
                        closest_node = node
                    else:
                        eq_dist = True

            # Once you find the closest point then increase that point's influence by 1.
            # Our aim is to find point with max influence.
            if not eq_dist:
                nodes[closest_node] += 1

            # In the meantime, if a point is within a certain max_bound from each node then
            # add that point to the list of valid points.
            if total_dist < bounded_area:
                bounded_region += 1

    print (bounded_region)
    return nodes


def main():
    """Day six of AOC 2018"""
    with open ("input.txt", 'r') as f:
        read_data = f.readlines()

    # This is _NOT_ ideal. Python int being unbounded - use a value that works for this case.
    # It will not work for all cases, obviously.
    max_x = 0
    min_x = 10000
    max_y = 0
    min_y = 10000
    bounded_area = 10000

    # No point calculating distance for all random points.
    # Capture the bounds and use them alone.
    for code in read_data:
        x, y = code.split(',')
        x = int(x)
        y = int(y)
        if (x > max_x):
            max_x = x
        if (y > max_y):
            max_y = y
        if (x < min_x):
            min_x = x
        if (y < min_y):
            min_y = y

    dist_pass_one = get_mhtn_dist(min_x, max_x, min_y, max_y, read_data, bounded_area)
    dist_pass_two = get_mhtn_dist(min_x-1, max_x+1, min_y-1, max_y+1, read_data, bounded_area)

    # The unbounded points will change distance from a node if we increase the canvas size.
    # So - capture the distances on smallest canvas and smallest canvas + 1.
    # Find the distances that don't change between the two and that's the maximum.
    final_dict = dict()
    for key in dist_pass_one:
        if dist_pass_one[key] == dist_pass_two[key]:
            final_dict[key] = dist_pass_one[key]

    print (max(final_dict.values()))


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
