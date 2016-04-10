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

template <class T>
class Cartesian;

using namespace std;

template <class T>
class Coordinate
{
  public:
    virtual ~Coordinate()                                            = default;

    virtual Coordinate<T>& operator=(const Coordinate<T>&)                 = 0;

    // Arithmetic
    virtual Coordinate<T>& operator+=(const Coordinate<T>&)                = 0;
    virtual Coordinate<T>& operator-=(const Coordinate<T>&)                = 0;

    // Transformation
    virtual Coordinate<T>& operator/=(const T&)                            = 0;
    virtual Coordinate<T>& operator*=(const T&)                            = 0;

    // Coordinate comparison
    virtual bool operator==(const Coordinate<T>&) const                    = 0;
    virtual bool operator!=(const Coordinate<T>&) const                    = 0;

    // Accesss member values
    virtual T& operator[](const size_t index)                              = 0;
    virtual T operator[](const size_t index) const                         = 0;

    virtual T distance(const Coordinate<T>&) const                         = 0;

    // Convert to cartesian
    virtual operator Cartesian<T>() const                                  = 0;

    // As cartesian
    virtual Cartesian<T> asCartesian() const                               = 0;
    virtual void fromCartesian(const Cartesian<T>&)                        = 0;

    // Transform points
    //Coordinate& transform(~lambda~);
};
