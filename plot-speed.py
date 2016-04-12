# Billy Rhoades
# 4/12/16
# This script plots the speed differences between static/dynamic polymorphism.

import os
import random
import math
import tempfile
import datetime

from subprocess import call
from shapely.geometry.polygon import Polygon


def build(folder):
    """
    Builds a provided directory with make.
    """
    folder = os.path.join(os.path.dirname(__file__), folder)

    # build
    call(["make", "-C", folder])


def create_ngon_files(n):
    """
    Creates and returns two file names. The first one is a coordinate file
    for a n-sided polygon. It has n coordinates separated by new lines.

    The second file is a test file. It has 2*n coordinates to test the
    polygon with. n coordinates are inside the polygon, n coordinates are
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
    for i in range(n):
        # create a random point inside our bounds
        testpoints.append((ru(bounds[0], bounds[2]), ru(bounds[1], bounds[3])))

    for i in range(n):
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

    for sides in range(3, 10, 10):
        sideslist.append(sides)
        vfile, tfile = create_ngon_files(sides)

        di = 0
        for driver in drivers:
            start = datetime.datetime.now()
            call([driver, vfile.name, tfile.name])
            times[di].append((datetime.datetime.now() - start).total_seconds())
            di += 1


if __name__ == "__main__":
    TYPES = ["standard", "crtp"]
    graph(TYPES)
