/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Coordinate interface (non-crtp).
 *
 * Documentation for interface functions are within derived classes.
 */
#pragma once

#include <cstdlib>

using namespace std;

template <class T>
class Coordinate
{
  public:
    Coordinate()                                                     = default;
    virtual ~Coordinate()                                            = default;

    // Coordinate comparison
    virtual bool operator==(const Coordinate<T>&) const              = 0;
    virtual bool operator!=(const Coordinate<T>&) const              = 0;

    // Accesss member values
    virtual T& operator[](const size_t index)                        = 0;
    virtual T operator[](const size_t index) const                   = 0;

    virtual T distance(const Coordinate<T>&) const                   = 0;

    // Transform points
    //Coordinate& transform(~lambda~);
};
