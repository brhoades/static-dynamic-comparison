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

using namespace std;

template <class T>
class Cartesian;

template <class T>
ostream& operator<<(ostream&, const Cartesian<T>&);

#include "../interfaces/coordinate.h"

template <class T>
class Cartesian: public Coordinate<T, Cartesian>
{
  public:
    Cartesian();
    Cartesian(const T& x, const T& y);
    Cartesian(const Cartesian<T>& other);
    ~Cartesian()                                                     = default;

    Coordinate<T, Cartesian>& operator=(const Coordinate<T, Cartesian>&);

    // Arithmetic
    Coordinate<T, Cartesian>& operator+=(const Coordinate<T, Cartesian>&);
    Coordinate<T, Cartesian>& operator-=(const Coordinate<T, Cartesian>&);

    // Transformation
    Coordinate<T, Cartesian>& operator/=(const T&);

    Coordinate<T, Cartesian>& operator*=(const T&);

    bool operator==(const Coordinate<T, Cartesian>&) const;
    bool operator!=(const Coordinate<T, Cartesian>&) const;

    T& operator[](const size_t index);
    T operator[](const size_t index) const;

    T distance(const Coordinate<T, Cartesian>&) const;

    operator Cartesian<T>() const;

    // As cartesian
    Cartesian<T> asCartesian() const;
    void fromCartesian(const Cartesian<T>&);

    T& x() {return m_x;}
    T x() const {return m_x;}

    T& y() {return m_y;}
    T y() const {return m_y;}

  protected:
    T m_x, m_y;
};

#include "cartesian.hpp"
