/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Polar Coordinate
 */
#pragma once

#include <iostream>

#include "../interfaces/coordinate.h"

template <class T>
class Polar;

template <class T>
ostream& operator<<(ostream&, const Polar<T>&);

template <class T>
class Polar: public Coordinate<T, Polar>
{
  public:
    Polar();
    Polar(const T& r, const T& theta);
    ~Polar()                                                 = default;

    template <template <class> class System>
    Coordinate<T, Polar>& operator=(const Coordinate<T, System>&);

    // Arithmetic
    template <template <class> class System>
    Coordinate<T, Polar>& operator+=(const Coordinate<T, System>&);
    template <template <class> class System>
    Coordinate<T, Polar>& operator-=(const Coordinate<T, System>&);

    // Transformation
    Coordinate<T, Polar>& operator/=(const T&);

    Coordinate<T, Polar>& operator*=(const T&);

    template <template <class> class System>
    bool operator==(const Coordinate<T, System>&) const;
    template <template <class> class System>
    bool operator!=(const Coordinate<T, System>&) const;

    T& operator[](const size_t index);
    T operator[](const size_t index) const;

    T distance(const Coordinate<T, Polar>&) const;

    operator Cartesian<T>() const;
    void fromCartesian(const Cartesian<T>&);

    T& r() {return m_r;}
    T r() const {return m_r;}

    T& theta() {return m_theta;}
    T theta() const {return m_theta;}

    T x() const;
    T y() const;

  protected:
    T m_r, m_theta;
};

#include "polar.hpp"
