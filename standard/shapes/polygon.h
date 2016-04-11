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

template <class T>
ostream& operator<<(ostream&, const Shape<T>&);

template <class T, size_t size>
class Polygon: Shape<T>
{
  public:
    Polygon();
    Polygon(const Polygon<T, size>& other);
    virtual ~Polygon();

    // Accesss member points
    virtual Coordinate<T>& operator[](const size_t index);
    virtual const Coordinate<T>& operator[](const size_t index) const;

    // Polygon comparison
    virtual bool operator==(const Shape<T>&) const;
    virtual bool operator!=(const Shape<T>&) const;

    // Area differences between shapes.
    virtual T operator+(const Shape<T>&) const;
    virtual T operator-(const Shape<T>&) const;

    virtual size_t numSides() const;

    void setVertex(const size_t, const Cartesian<T>&);
    
    virtual T area() const;
    virtual T sideLength() const;
    virtual T perimeter() const;

    // Get coordinates for corners (noncircle).
    virtual Coordinate<T>** getPoints();
    virtual Cartesian<T> center() const;

    // Bounding functions
    virtual bool isInShape(const Coordinate<T>&) const;
  private:
    array<Coordinate<T>*, size> m_verticies;
};

#include "polygon.hpp"
