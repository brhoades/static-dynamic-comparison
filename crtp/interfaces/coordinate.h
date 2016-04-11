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
#include <iostream>

using namespace std;

template <class T, template <class T> class Derived>
class Coordinate;

template <class T>
class Cartesian;

template <class T, template <class T> class Derived>
ostream& operator<<(ostream& os, const Coordinate<T, Derived>& rhs);

template <class T, template <class T> class Derived>
class Coordinate
{
  public:
    Coordinate<T, Derived>& operator=(const Coordinate<T, Derived>& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator=(rhs);
    }

    // Arithmetic
    Coordinate<T, Derived>& operator+=(const Coordinate<T, Derived>& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator+=(rhs);
    }
    Coordinate<T, Derived>& operator-=(const Coordinate<T, Derived>& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator-=(rhs);
    }

    // Transformation
    Coordinate<T, Derived>& operator/=(const T& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator/=(rhs);
    }
    Coordinate<T, Derived>& operator*=(const T& rhs)
    {
      return static_cast<Derived<T>*>(this)->operator*=(rhs);
    }

    // Coordinate comparison
    bool operator==(const Coordinate<T, Derived>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->operator==(rhs);
    }
    bool operator!=(const Coordinate<T, Derived>& rhs) const
    {
      return static_cast<const Derived<T>*>(this)->operator!=(rhs);
    }

    // Accesss member values
    T& operator[](const size_t index)
    {
      return static_cast<Derived<T>*>(this)->operator[](index);
    }
    T operator[](const size_t index) const
    {
      return static_cast<const Derived<T>*>(this)->operator[](index);
    }

    T distance(const Coordinate<T, Cartesian>& other) const
    {
      return static_cast<const Derived<T>*>(this)->distance(other);
    }

    // Convert to cartesian
    operator Cartesian<T>() const
    {
      return static_cast<const Cartesian<T>>(*static_cast<const Derived<T>*>(this));
    }

    // As cartesian
    Cartesian<T> asCartesian() const
    {
      return static_cast<const Derived<T>*>(this)->asCartesian();
    }
    void fromCartesian(const Cartesian<T>& other)
    {
      return static_cast<Derived<T>*>(this)->fromCartesian(other);
    }
};

#include "coordinate.hpp"
