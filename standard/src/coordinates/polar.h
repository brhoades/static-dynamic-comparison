/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Polar Coordinate
 */
#pragma once

#include <iostream>

#include "../interfaces/coordinate.h"

template <class T>
class Polar;

template <class T>
ostream& operator<<(ostream&, const Polar<T>&);

template <class T>
class Polar: public Coordinate<T>
{
  public:
    Polar();
    Polar(const T& r, const T& theta);
    virtual ~Polar()                                                 = default;

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
    virtual Cartesian<T> asCartesian() const;
    virtual void fromCartesian(const Cartesian<T>&);

    virtual T& r() {return m_r;}
    virtual T r() const {return m_r;}

    virtual T& theta() {return m_theta;}
    virtual T theta() const {return m_theta;}

  protected:
    T m_r, m_theta;
};

#include "polar.hpp"
