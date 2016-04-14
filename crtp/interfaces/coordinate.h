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

#ifndef USE_REAL_TYPE
#include "coordinateI.h"
#endif
#include "../consts.h"

using namespace std;

#ifndef USE_REAL_TYPE
#define RTYPE CoordinateI<T>
#else
#define RTYPE Coordinate<T, Derived>
#endif

template <class T, template <class T> class Derived>
class Coordinate;

template <class T>
class Cartesian;

template <class T, template <class T> class Derived>
// Flip on and off using our interface.
#ifndef USE_REAL_TYPE
class Coordinate: public CoordinateI<T>
#else
class Coordinate
#endif
{
  public:
    virtual RTYPE& operator=(const RTYPE& rhs)
    {
      return static_cast<Derived<T>&>(*this).operator=(
          static_cast<const Coordinate<T, Derived>&>(rhs));
    }

    // Arithmetic
    virtual RTYPE& operator+=(const RTYPE& rhs)
    {
      // If we don't cast to Coordinate here, it tries to call our derived
      // class's == on CoordinateI.
      return static_cast<Coordinate<T,Derived>&>(*this) += rhs;
    }
    virtual RTYPE& operator-=(const RTYPE& rhs)
    {
      return static_cast<Coordinate<T,Derived>&>(*this) -= rhs;
    }

    // Transformation
    virtual RTYPE& operator/=(const T& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator/=(rhs);
    }
    virtual RTYPE& operator*=(const T& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator*=(rhs);
    }

    // Coordinate comparison
    virtual bool operator==(const RTYPE& rhs) const
    {
      return static_cast<const Coordinate<T, Derived>&>(*this) == rhs;
    }
    virtual bool operator!=(const RTYPE& rhs) const
    {
      return static_cast<const Coordinate<T, Derived>&>(*this) != rhs;
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
