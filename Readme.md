Static vs Dynamic Polymorphism in C++
--------------------------------------

The plot-speed.py script and the two codebases are used together to graph
speed differences between the CRTP and standard dynamic polymorphism in C++.

This example accompanies a presentation:
  https://docs.google.com/presentation/d/167VVaQhar1Shfgj_NX0fiZjJUz4gp_ZLcdF8sFXTrOM/edit?usp=sharing

Usage
-----

Install the requirements listed in requirements.txt. You can then create graphs
with the following:

> python plot-speed.py 10000 --title "Plot title" --start 100

This will generate a graph of the two implementation's performance in time versus
sides of a polygon. It goes up to 10,000 sides with 10,000 test points. The graph
starts at 100 and has the title of "Plot title".

More information can be found:

> python plot-speed.py --help

Example Implementations
-----------------------

There are two included example implementations. One uses the CRTP (crtp) and the
other uses dynamic polymorphism (standard). By removing or adding the constant 
in crtp/consts.h, it will disable or enable a dynamic/static hybrid implementation versus
a pure static implementation.

Both code perform identically. Their driver takes two files. The first file
defines verticies for a regular polygon. The vertices must be cartesian and the
file must list them like so::

```
  0 0
  1 1
  2 2
```

Where coordinates above are (0, 0), (1, 1), and (2, 2). The second file contains
coordinates for testing. The program will check if the shape defined from the first
file contains the points in the second file within its area.

