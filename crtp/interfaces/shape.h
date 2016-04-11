/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Shape interface (non-crtp).
 *
 * Documentation for interface functions are within derived classes.
 */
#pragma once

#include "coordinate.h"

template <class T, template <class T> class System, // T, System<T>
          template <class T, template <class T> class System> class Derived> // Shape<T, Cartesian<T>>
class Shape
{
  public:
    // Access member points
    Coordinate<T,System>& operator[](const size_t index)
    {
      return static_cast<Derived<T, System>*>(this)->operator[](index);
    }
    const Coordinate<T,System>& operator[](const size_t index) const
    {
      return static_cast<const Derived<T, System>*>(this)->operator[](index);
    }

    // Shape comparison
    bool operator==(const Shape<T,System,Derived>& rhs) const
    {
      return static_cast<const Derived<T, System>*>(this)->operator==(rhs);
    }
    bool operator!=(const Shape<T,System,Derived>& rhs) const
    {
      return static_cast<const Derived<T, System>*>(this)->operator!=(rhs);
    }

    // Area differences between shapes.
    T operator+(const Shape<T,System,Derived>& rhs) const
    {
      return static_cast<const Derived<T, System>*>(this)->operator+(rhs);
    }
    T operator-(const Shape<T,System,Derived>& rhs) const
    {
      return static_cast<const Derived<T, System>*>(this)->operator-(rhs);
    }

    size_t numSides() const
    {
      return static_cast<const Derived<T, System>*>(this)->numSides();
    }
    
    T area() const
    {
      return static_cast<const Derived<T, System>*>(this)->area();
    }
    T sideLength() const
    {
      return static_cast<const Derived<T, System>*>(this)->sideLength();
    }
    T perimeter() const
    {
      return static_cast<const Derived<T, System>*>(this)->perimeter();
    }

    // Get coordinates for corners (noncircle), center (circle).
    Coordinate<T,System>** getPoints()
    {
      return static_cast<Derived<T, System>*>(this)->getPoints();
    }
    Cartesian<T> center() const
    {
      return static_cast<const Derived<T, System>*>(this)->center();
    }

    // Bounding checks
    bool isInShape(const Coordinate<T,System>& p) const;
};

#include "shape.hpp"
