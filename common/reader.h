/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Reads coordinates from a file.
 */
#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <class T, template <class T> class System>
struct CoordReader
{
   vector<System<T>> operator()(const char* fname) const;
};

#include "reader.hpp"
