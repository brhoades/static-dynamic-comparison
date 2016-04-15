# Billy Rhoades
# 4/12/16
# This script plots the speed differences between static/dynamic polymorphism.

import os
import random
import math
import tempfile
import datetime
import argparse
import numpy as np

import scipy.interpolate as interpolate
from subprocess import call
from shapely.geometry.polygon import Polygon
from matplotlib import pyplot as plt

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('--start', type=int, dest='start',
                    help='number of sides to start with',
                    default=100, action='store')
parser.add_argument('end', type=int,
                    help='number of sides to end with')
parser.add_argument('--title', dest='title', action='store')
parser.add_argument('--smooth', dest='smooth', action='store',
                    default=0.2)

args = parser.parse_args()

# The number of tests we do per size (to average)
NUMBER_OF_TEST_ITERATIONS = 5

# How much smoothing we do to our graph
SPLINE_SMOOTH = args.smooth


def build(folder):
    """
    Builds a provided directory with make.
    """
    folder = os.path.join(os.path.dirname(__file__), folder)

    # build
    call(["make", "-C", folder, "clean"])
    call(["make", "-C", folder])


def create_ngon_files(n):
    """
    Creates and returns two file names. The first one is a coordinate file
    for a n-sided polygon. It has n coordinates separated by new lines.

    The second file is a test file. It has n coordinates to test the
    polygon with. n/2 coordinates are inside the polygon, n/2 coordinates are
    outside.
    """
    vertices = []
    testpoints = []
    vertfile = tempfile.NamedTemporaryFile("w")
    testfile = tempfile.NamedTemporaryFile("w")

    vertices = list(create_polygon(n))

    # assists in creating points inside and outside.
    p = Polygon(vertices)
    bounds = p.bounds
    ru = random.uniform
    for i in range(n//2):
        # create a random point inside our bounds
        testpoints.append((ru(bounds[0], bounds[2]), ru(bounds[1], bounds[3])))

    for i in range(n//2):
        # create a random point outside our bounds
        x = None
        y = None

        # x above or below bounds
        if random.choice([True, False]):
            # x above
            x = ru(bounds[2], 100000)
        else:
            # x below
            x = ru(-100000,  bounds[0])

        # y above / below
        if random.choice([True, False]):
            # y above
            y = ru(bounds[3], 100000)
        else:
            # y below
            y = ru(-100000,  bounds[1])
        testpoints.append((x, y))

    vertfile.write("\n".join(["{} {}".format(x, y) for x, y in vertices]))
    testfile.write("\n".join(["{} {}".format(x, y) for x, y in testpoints]))

    return vertfile, testfile


def create_polygon(n):
    """
    Generator

    Creates a regular polygon with n sides and a random center with a random
    center and an uniform side length. Yields coordinate tuples.
    """
    centerx, centery = random.uniform(-1000, 1000), random.uniform(-1000, 1000)

    # circumference
    r = random.uniform(1, 10)

    # Side length
    a = 2*r*math.tan(math.pi/n)

    # interior angle
    alpha = (n-2)*math.pi

    # circumradius
    R = (1/2)*a*(1/math.sin(math.pi/n))

    # Go clockwise around our center. Increment our angle by alpha/n.
    for sideoffset in range(n):
        angle = alpha+2*math.pi*sideoffset/n
        yield (centerx + R*math.cos(angle), centery + R*math.sin(angle))


def spline_data(x, y):
    """
    Smooths out a passed list of data.

    Returns a x, y where x now contains 100x the resolution and y is splined
    to match.
    """
    x_sm = np.array(x)

    x_smooth = np.linspace(x_sm.min(), x_sm.max(), len(x)*100)
    ysp = interpolate.UnivariateSpline(x, y)
    ysp.set_smoothing_factor(SPLINE_SMOOTH)

    return x_smooth, ysp(x_smooth)


def graph(types):
    """
    Gathers information about passed types (folders in this directory),
    runs their makefiles, then records their times. Graphs with pyplot.
    """
    for type in types:
        build(type)

    times = [[] for x in types]
    sideslist = []
    drivers = [os.path.join(type, "driver") for type in types]

    for sides in range(args.start, args.end, 100):
        sideslist.append(sides)
        vfile, tfile = create_ngon_files(sides)

        for di, driver in enumerate(drivers):
            testtimes = []
            for i in range(NUMBER_OF_TEST_ITERATIONS):
                start = datetime.datetime.now()
                call([driver, vfile.name, tfile.name])
                (testtimes.append((datetime.datetime.now() - start)
                 .total_seconds()))
            times[di].append(sum(testtimes)/len(testtimes))

    plt.style.use('ggplot')
    # Drop our times on our plot. Sides count is our x, time y.
    for type in types:
        x_sm, y_sm = spline_data(sideslist, times[types.index(type)])
        plt.plot(x_sm, y_sm, label=type, linewidth=3)

    # Give us a legend on the top right, on the graph a bit.
    plt.legend(bbox_to_anchor=(0.8, 1), loc=2, borderaxespad=0.)
    plt.xlabel("Number of sides and test points")
    plt.ylabel("Time elapsed (seconds)")
    plt.title(args.title)
    plt.savefig("{}_{}.png".format(args.title.lower().replace(" ", "_"),
                                   args.end),
                format="png")
    plt.show()


if __name__ == "__main__":
    TYPES = ["standard", "crtp", "crtp-nodynamic"]
    graph(TYPES)
