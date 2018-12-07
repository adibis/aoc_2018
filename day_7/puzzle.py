"""
AOC 2018, Day 7
"""

__author__ = "adibis"
__version__ = "0.1.0"
__license__ = "MIT"

def resolve_dependencies(arg):
    d = dict((k, set(arg[k])) for k in arg)
    resolved = []
    while d:
        # for v in values:
        #   for each i in values: {since there can be multiple values per key}
        #       return i
        # subtract the keys from i
        # This gives all the values which are not a key (or don't have a dependency)
        free_tasks=set(i for v in sorted(d.values()) for i in v)-set(d.keys())
        # Once dependency is completed, we remove values from keys (dependencies)
        # Get a list of all such keys which don't have a dependency (okay to proceed)
        free_tasks.update(k for k, v in d.items() if not v)
        # Remove all elements from the initial dependency tree since they can be started.
        # They are not waiting on any step to complete.
        # Only pick up one task at a time because of the program definition
        next_task = set(sorted(free_tasks)[0])
        resolved += list(next_task)
        # Remove the items which have started form the list of remaining items
        d = dict(((k, v-next_task) for k, v in sorted(d.items()) if v))
    return (''.join(resolved))

def execute_task(dispatch_queue, time, workers):
    # Keep asigning tasks until all workers are occupied or queue is empty.
    while len(workers) < 5 and dispatch_queue:
        # Pick up the next task to schedule.
        next_task = min(dispatch_queue, key=str)
        # Remove that task from the queue.
        dispatch_queue.remove(next_task)
        print ("Starting ", next_task, " at time ", time)
        # Assign a worker to the task.
        workers.append((time+61+ord(next_task) - ord('A'), next_task))
        print("Workers are engaged in ", workers)

def dispatch_tasks(arg):
    d = dict((k, set(arg[k])) for k in arg)
    time = 0
    dispatch_queue=[]
    dispatched = []
    workers = []
    while d or dispatch_queue:
        # for v in values:
        #   for each i in values: {since there can be multiple values per key}
        #       return i
        # subtract the keys from i
        # This gives all the values which are not a key (or don't have a dependency)
        free_tasks = set(i for v in sorted(d.values()) for i in v)-set(d.keys())
        # Once dependency is completed, we remove values from keys (dependencies)
        # Get a list of all such keys which don't have a dependency (okay to proceed)
        free_tasks.update(k for k, v in d.items() if not v)
        # Remove all elements from the initial dependency tree since they can be started.
        # They are not waiting on any step to complete.
        task_list = list(free_tasks)
        # Keep a track of what has been dispatched already.
        # We don't want to dispatch the same task again while it's currently running.
        dispatch_queue = dispatch_queue + [i for i in task_list if i not in dispatched]
        dispatched = dispatched + task_list
        print("Okay to start with the following tasks: ", task_list)
        # NOTE: Suppose we had more tasks to schedule than workers. Take example of 6 tasks.
        # First 5 of them will start. 6th will remain pending.
        # The first of those 5 to complete will be removed from the queue.
        # REPEAT: On next iteration the dependencies of the completed queue will be unlocked.
        # Now we dispatch unlocked dependencies + 6th original task.
        # That is again sorted and first one will start on the free worker.
        # We also remove the next task to complete and go back to step REPEAT
        if workers or dispatch_queue:
            # Execute a task from the queue.
            execute_task(dispatch_queue, time, workers)
            # Get the first item to complete (smallest time).
            time, task = min(workers)
            # Remove this task from current list of active tasks.
            workers.remove(min(workers))
            print ("Completed task ", task, " at time ", time)

            # Now remove only the task which was completed and removed from the workers.
            # Don't remove others since they are still going on.
            d = dict(((k, v-set(task)) for k, v in sorted(d.items()) if v))
    return time

def main():
    """Day seven of AOC 2018"""
    with open ("input.txt", 'r') as f:
        read_data = f.readlines()

    dependencies = dict()

    # No point calculating distance for all random points.
    # Capture the bounds and use them alone.
    for code in read_data:
        step = code.split(' ')[1]
        dependency = code.split(' ')[7]
        if dependency not in dependencies:
            dependencies[dependency] = set()
        dependencies[dependency].add(step)

    print ("Initial status of depedency tree: ", dependencies)
    first_order = resolve_dependencies(dependencies)
    final_time = dispatch_tasks(dependencies)

    print ("PART A: Order: ", first_order)
    print ("PART B: Final Time: ", final_time)

if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
