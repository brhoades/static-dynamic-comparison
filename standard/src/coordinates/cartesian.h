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
class Cartesian: public Coordinate<T>
{
  public:
    Cartesian();
    Cartesian(const T& x, const T& y);
    virtual ~Cartesian()                                             = default;

    virtual bool operator==(const Coordinate<T>&) const;
    virtual bool operator!=(const Coordinate<T>&) const;

    virtual T& operator[](const size_t index);
    virtual T operator[](const size_t index) const;

    virtual T distance(const Coordinate<T>&) const;

    virtual operator Cartesian<T>() const;

    virtual T& x() {return m_x;}
    virtual T x() const {return m_x;}

    virtual T& y() {return m_y;}
    virtual T y() const {return m_y;}

  protected:
    T m_x, m_y;
};

#include "cartesian.hpp"
