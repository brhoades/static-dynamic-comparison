/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Cartesian Coordinate
 */
#pragma once

template <class T>
class Cartesian;

#include <iostream>

using namespace std;

template <class T>
class Cartesian;

template <class T>
ostream& operator<<(ostream&, const Cartesian<T>&);

#include "../interfaces/coordinate.h"
#include "../interfaces/coordinate.h"

template <class T>
class Cartesian: public Coordinate<T, Cartesian>
{
  public:
    Cartesian();
    Cartesian(const T& x, const T& y);
    Cartesian(const Cartesian<T>& other);
    ~Cartesian()                                                     = default;

    template <template <class> class System>
    Coordinate<T, Cartesian>& operator=(const Coordinate<T, System>&);

    // Arithmetic
    template <template <class> class System>
    Coordinate<T, Cartesian>& operator+=(const Coordinate<T, System>&);
    template <template <class> class System>
    Coordinate<T, Cartesian>& operator-=(const Coordinate<T, System>&);

    // Transformation
    Coordinate<T, Cartesian>& operator/=(const T&);
    Coordinate<T, Cartesian>& operator*=(const T&);
    
    template <template <class> class System>
    bool operator==(const Coordinate<T, System>&) const;
    template <template <class> class System>
    bool operator!=(const Coordinate<T, System>&) const;

    T& operator[](const size_t index);
    T operator[](const size_t index) const;

    template <template <class> class System>
    T distance(const Coordinate<T, System>&) const;

    operator Cartesian<T>() const;

    // From a cartesian point
    void fromCartesian(const Cartesian<T>&);

    T& x() {return m_x;}
    T x() const {return m_x;}

    T& y() {return m_y;}
    T y() const {return m_y;}

  protected:
    T m_x, m_y;
};

#include "cartesian.hpp"
