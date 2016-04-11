/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (crtp).
 */
#pragma once

#include <vector>

#include "../interfaces/shape.h"

template <class T, template <class T> class System>
class Polygon;

template <class T, template <class T> class System>
ostream& operator<<(ostream&, const Shape<T,System,Polygon>&);

template <class T, template <class T> class System>
class Polygon: public Shape<T,System,Polygon>
{
  public:
    Polygon();
    Polygon(const Polygon<T,System>& other);
    ~Polygon();

    // Accesss member points
    Coordinate<T,System>& operator[](const size_t index);
    const Coordinate<T,System>& operator[](const size_t index) const;

    // Polygon comparison
    bool operator==(const Shape<T,System,Polygon>&) const;
    bool operator!=(const Shape<T,System,Polygon>&) const;

    // Area differences between shapes.
    T operator+(const Shape<T,System,Polygon>&) const;
    T operator-(const Shape<T,System,Polygon>&) const;

    size_t numSides() const;

    void addVertex(const Cartesian<T>&);
    
    T area() const;
    T sideLength() const;
    T perimeter() const;

    // Get coordinates for corners (noncircle).
    Coordinate<T,System>** getPoints();
    Cartesian<T> center() const;
  private:
    vector<Coordinate<T,System>*> m_vertices;
};

#include "polygon.hpp"
