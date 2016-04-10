/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (non-crtp).
 */
#pragma once

#include <array>

#include "../interfaces/shape.h"

template <class T, size_t size>
class Polygon: Shape<T>
{
  public:
    Polygon();
    virtual ~Polygon()                                               = default;

    // Accesss member points
    virtual Coordinate<T>& operator[](const size_t index);
    virtual Coordinate<T> operator[](const size_t index) const;

    // Polygon comparison
    virtual bool operator==(const Shape<T>&) const;
    virtual bool operator!=(const Shape<T>&) const;

    // Area differences between shapes.
    virtual T operator+(const Shape<T>&) const;
    virtual T operator-(const Shape<T>&) const;
    
    virtual T area() const;
    virtual T sideLength() const;

    // Get coordinates for corners (noncircle).
    virtual Coordinate<T>* getPoints();
    virtual Coordinate<T> center() const;

  private:
    array<Coordinate<T>, size> m_data;
};

#include "polygon.hpp"
