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
    inline CoordinateI<T>* operator[](const size_t index);
    inline const CoordinateI<T>* operator[](const size_t index) const;
    #else
    inline System<T>* operator[](const size_t index);
    inline const System<T>* operator[](const size_t index) const;
    #endif

    // Polygon comparison
    bool operator==(const Shape<T,System,Polygon>&) const;
    bool operator!=(const Shape<T,System,Polygon>&) const;

    // Area differences between shapes.
    T operator+(const Shape<T,System,Polygon>&) const;
    T operator-(const Shape<T,System,Polygon>&) const;

    inline size_t numSides() const;

    inline void addVertex(const Cartesian<T>&);
    
    inline T area() const;
    inline T sideLength() const;
    inline T perimeter() const;

    inline Cartesian<T> center() const;

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
