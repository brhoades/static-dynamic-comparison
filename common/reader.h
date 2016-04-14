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
#include <limits>

using namespace std;

template <class T, template <class T> class System>
struct CoordReader
{
   System<T>* operator()(const char* fname);
   size_t m_size;
};

#include "reader.hpp"
