"""
AOC 2018, Day 8
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"


def get_next_data(read_data):
    # NOTE: TIL: Python doesn't have an equivalent of a static variable.
    # This is ugly and not pythonic. Need to figure out a better way to handle this.
    if 'i' not in get_next_data.__dict__:
        get_next_data.i = 0
    get_next_data.i += 1
    return(read_data[get_next_data.i-1])


def parse_input(read_data):
    children = []
    metadata = []
    total_children = get_next_data(read_data)
    total_meta = get_next_data(read_data)

    #print ("children: ", total_children, ", total_meta: ", total_meta)

    # The trick to recursion here is to get the children out first.
    # Don't remove the last metadata values (read_data[:meta]) until you remove the children.
    # Thanks to https://www.reddit.com/r/adventofcode/comments/a47ubw/2018_day_8_solutions/ for the hints.
    # I kind of based this solution to a solution by u/jonathan_paulson and it was a good
    # learning especially for the C implementation.
    for c in range(0, total_children):
        print ("Before recursion children = ", children)
        children.append(parse_input(read_data))
        print ("After recursion children = ", children)
    # The recursion above will go on till it reaches this point for the last child.
    # Now we capture the meta from the last child.
    for m in range(0, total_meta):
        metadata.append(get_next_data(read_data))
    # Now the recursion will return this data to the previous child.
    # For the last child, children field will be empty.
    #print (children, metadata)
    return children, metadata


def get_meta_sum(node):
    total = 0
    # Split the children from metadata now.
    # Read note on why we don't split them earlier - it makes the recursion hell.
    (children, metadata) = node
    for m in metadata:
        total += m
    for c in children:
        total += get_meta_sum(c)
    return total


def get_value(node):
    # Split the children from metadata now.
    # Read note on why we don't split them earlier - it makes the recursion hell.
    (children, metadata) = node
    # If no children then value should be sum of metadata
    if not children:
        return sum(metadata)
    else:
        total = 0
        total_ignored = 0
        # If children present - check if child at index metadata is present.
        for m in metadata:
            try:
                total += get_value(children[m-1])
            except:
                total_ignored += 1
        #print ("Total ignored: ", total_ignored)
        return total


def main():
    """Day eight of AOC 2018"""
    with open ("test.txt", 'r') as f:
        read_data = f.readline()

    read_data = read_data.strip()
    read_data = [int(x) for x in read_data.split()]

    #print("Input is = ", read_data)
    root = parse_input(read_data)
    #print ("Root is: ", root)
    total = get_meta_sum(root)
    print ("Sum is: ", total)
    value = get_value(root)
    print ("Value is: ", value)

if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
