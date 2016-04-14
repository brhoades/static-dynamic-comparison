/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Coordinate interface (crtp).
 *
 * Documentation for interface functions are within derived classes.
 */
#pragma once

#include <cstdlib>
#include <iostream>

#include "coordinateI.h"

using namespace std;

template <class T, template <class T> class Derived>
class Coordinate;

template <class T>
class Cartesian;

template <class T, template <class T> class Derived>
ostream& operator<<(ostream& os, const CoordinateI<T>& rhs);

template <class T, template <class T> class Derived>
class Coordinate: public CoordinateI<T>
{
  public:
    virtual CoordinateI<T>& operator=(const CoordinateI<T>& rhs)
    {
      return static_cast<Derived<T>&>(*this).operator=(
          static_cast<const Coordinate<T, Derived>&>(rhs));
    }

    // Arithmetic
    virtual CoordinateI<T>& operator+=(const CoordinateI<T>& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator+=(rhs);
    }
    virtual CoordinateI<T>& operator-=(const CoordinateI<T>& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator-=(rhs);
    }

    // Transformation
    virtual CoordinateI<T>& operator/=(const T& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator/=(rhs);
    }
    virtual CoordinateI<T>& operator*=(const T& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator*=(rhs);
    }

    // Coordinate comparison
    virtual bool operator==(const CoordinateI<T>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->operator==(rhs);
    }
    virtual bool operator!=(const CoordinateI<T>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->operator!=(rhs);
    }

    // Accesss member values
    virtual T& operator[](const size_t index)
    {
      return static_cast<Derived<T>*>(this)->operator[](index);
    }
    virtual T operator[](const size_t index) const
    {
      return static_cast<const Derived<T>*>(this)->operator[](index);
    }

    virtual T distance(const Cartesian<T>& other) const
    {
      return static_cast<const Derived<T>*>(this)->distance(other);
    }

    // Convert to cartesian
    virtual operator Cartesian<T>() const
    {
      return static_cast<const Cartesian<T>>(*static_cast<const Derived<T>*>(this));
    }

    virtual void fromCartesian(const Cartesian<T>& other)
    {
      return static_cast<Derived<T>*>(this)->fromCartesian(other);
    }

    virtual T x() const
    {
      return static_cast<const Derived<T>*>(this)->x();
    }

    virtual T y() const
    {
      return static_cast<const Derived<T>*>(this)->y();
    }
};

#include "coordinate.hpp"
