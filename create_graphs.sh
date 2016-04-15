#!/bin/bash
# These commands just run with the current makefile, you'd
# have to change their optimizations manually. This is here
# for demonstration purposes.
python create_plot.py --title "No Optimizations" --start 100 10000
python create_plot.py --title "-O2 Optimization" --start 100 20000
python create_plot.py --title "-O3 Optimization" --start 100 20000
