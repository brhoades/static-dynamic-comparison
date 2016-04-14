/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Coordinate interface (crtp).
 *
 * Documentation for interface functions are within derived classes.
 */
#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class Cartesian;

template <class T>
class CoordinateI
{
  public:
    virtual ~CoordinateI() {};

    virtual CoordinateI<T>& operator=(const CoordinateI<T>& rhs) = 0;

    // Arithmetic
    virtual CoordinateI<T>& operator+=(const CoordinateI<T>& rhs) = 0;
    virtual CoordinateI<T>& operator-=(const CoordinateI<T>& rhs) = 0;

    // Transformation
    virtual CoordinateI<T>& operator/=(const T& rhs) = 0;
    virtual CoordinateI<T>& operator*=(const T& rhs) = 0;

    // Coordinate comparison
    virtual bool operator==(const CoordinateI<T>& rhs) const = 0;
    virtual bool operator!=(const CoordinateI<T>& rhs) const = 0;

    // Accesss member values
    virtual T& operator[](const size_t index) = 0;
    virtual T operator[](const size_t index) const = 0;

    virtual T distance(const Cartesian<T>& other) const = 0;

    // Convert to cartesian
    virtual operator Cartesian<T>() const = 0;

    // As cartesian
    virtual void fromCartesian(const Cartesian<T>& other) = 0;

    virtual T x() const = 0;
    virtual T y() const = 0;
};
