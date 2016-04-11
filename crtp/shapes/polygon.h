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

template <class T,size_t size, template <class T> class System>
ostream& operator<<(ostream&, const Shape<T,System>&);

template <class T,size_t size, template <class T> class System>
class Polygon: Shape<T,System>
{
  public:
    Polygon();
    Polygon(const Polygon<T,size, System>& other);
    virtual ~Polygon();

    // Accesss member points
    virtual Coordinate<T,System>& operator[](const size_t index);
    virtual const Coordinate<T,System>& operator[](const size_t index) const;

    // Polygon comparison
    virtual bool operator==(const Shape<T,System>&) const;
    virtual bool operator!=(const Shape<T,System>&) const;

    // Area differences between shapes.
    virtual T operator+(const Shape<T,System>&) const;
    virtual T operator-(const Shape<T,System>&) const;

    virtual size_t numSides() const;

    void setVertex(const size_t, const Cartesian<T>&);
    
    virtual T area() const;
    virtual T sideLength() const;
    virtual T perimeter() const;

    // Get coordinates for corners (noncircle).
    virtual Coordinate<T,System>** getPoints();
    virtual Cartesian<T> center() const;

    // Bounding functions
    virtual bool isInShape(const Coordinate<T,System>&) const;
  private:
    array<Coordinate<T,System>*, size> m_verticies;
};

#include "polygon.hpp"
