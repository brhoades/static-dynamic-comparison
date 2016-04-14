/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Cartesian Coordinate
 */
#pragma once

template <class T>
class Cartesian;

#include <iostream>

#include "../interfaces/coordinate.h"

template <class T>
ostream& operator<<(ostream&, const Cartesian<T>&);

template <class T>
class Cartesian: public Coordinate<T>
{
  public:
    Cartesian();
    Cartesian(const T& x, const T& y);
    Cartesian(const Cartesian<T>& other);
    virtual ~Cartesian()                                             = default;

    virtual Coordinate<T>& operator=(const Coordinate<T>&);

    // Arithmetic
    virtual Coordinate<T>& operator+=(const Coordinate<T>&);
    virtual Coordinate<T>& operator-=(const Coordinate<T>&);

    // Transformation
    virtual Coordinate<T>& operator/=(const T&);

    virtual Coordinate<T>& operator*=(const T&);

    virtual bool operator==(const Coordinate<T>&) const;
    virtual bool operator!=(const Coordinate<T>&) const;

    virtual T& operator[](const size_t index);
    virtual T operator[](const size_t index) const;

    virtual T distance(const Coordinate<T>&) const;

    virtual operator Cartesian<T>() const;

    // As cartesian
    virtual void fromCartesian(const Cartesian<T>&);

    virtual T& x() {return m_x;}
    virtual T x() const {return m_x;}

    virtual T& y() {return m_y;}
    virtual T y() const {return m_y;}

  protected:
    T m_x, m_y;
};

#include "cartesian.hpp"
