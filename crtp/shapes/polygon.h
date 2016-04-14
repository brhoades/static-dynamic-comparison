/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (crtp).
 */
#pragma once

// Huge speed change here.
#include <vector>

#include "../consts.h"
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
    #ifndef USE_REAL_TYPE
    CoordinateI<T>* operator[](const size_t index);
    const CoordinateI<T>* operator[](const size_t index) const;
    #else
    System<T>* operator[](const size_t index);
    const System<T>* operator[](const size_t index) const;
    #endif

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

    Cartesian<T> center() const;

    // Get coordinates for corners (noncircle).
    #ifndef USE_REAL_TYPE
    CoordinateI<T>** getPoints();
    #else
    System<T>** getPoints();
    #endif
  private:
    #ifndef USE_REAL_TYPE
    vector<CoordinateI<T>*> m_vertices;
    #else
    vector<System<T>*> m_vertices;
    #endif
};

#include "polygon.hpp"
