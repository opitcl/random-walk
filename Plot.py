'''
Author: Olivia Pitcl
Random walk - plotting code
'''

import numpy as np
import matplotlib.pyplot as plt
from scipy import stats as st

def histogram(values, dimension, num, border, bound, legend3):
    # Load in info from csv file, space-separated
    # These are the number of events it took for one iteration of the
    # random walk problem to return to the origin
    fig, ax = plt.subplots()
    maximum = np.max(values)
    if maximum > 150:
        maximum = 150
    minimum = np.min(values)

    # Create histogram of the number of events in bins appropriate to min
    # and max values
    # If the iteration timed out or the program went beyond the boundary,
    # the data will be filled with -1

    bins = np.linspace(minimum, maximum, 101, endpoint=True)
    ax.hist(values, bins=bins, color='b', density=True)
    
    ax.set_xlabel('Steps to return')
    ax.set_ylabel('Count')
    
    ax.set_title(dimension)
    legend = num
    legend2 = border
    mode = st.mode(values)
    mode = mode[1] / len(values)
    print(mode)
    plt.text((maximum - 70), (mode - 0.2), legend)
    plt.text((maximum - 70), (mode - 0.25), legend2)
    plt.text((maximum - 70), (mode - 0.3), legend3)
    plt.savefig(dimension + ".png")
    plt.clf()
    plt.close()

def main():
    filenames = ['random-walk-1D.csv', 'random-walk-2D.csv', 'random-walk-3D.csv']
    for filename in filenames:
        file = open(filename, "r")
	
	# Read first 3 lines
        num = file.readline().strip()
        boundary = file.readline().strip()
        bound = boundary.split()
        bound = bound[len(bound) - 1]
        bound = int(bound)
        print(bound)
        file.readline()

        elems = file.readline().strip().split(" ")
        values = []
        # If contains -1, remove
        # Maximum is boundary*10 because we will have large outlying data
        for elem in elems:
            elem = int(elem)
            if elem != -1:
                values.append(elem)

        values = np.array(values)
        dimension = filename.strip(".csv")
        ratio = "Completed / unfinished: " + str( len(values) / len(elems))
        histogram(values, dimension, num, boundary, bound, ratio)


main()
