/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Cartesian Coordinate
 */
#pragma once

#include "../interfaces/coordinate.h"

template <class T>
class Cartesian: Coordinate<T>
{
  public:
    Cartesian();
    Cartesian(const T& x, const T& y);
    virtual ~Cartesian()                                            = default;

    // Cartesian comparison
    virtual bool operator==(const Coordinate<T>&) const;
    virtual bool operator!=(const Coordinate<T>&) const;

    // Accesss member values
    virtual T& operator[](const size_t index);
    virtual T operator[](const size_t index) const;

    virtual T distance(const Coordinate<T>&) const;

  protected:
    T m_x, m_y;
};

#include "cartesian.hpp"
