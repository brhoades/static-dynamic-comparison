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

#include "coordinates.h"

template <class T>
class Shape
{
  public:
    Shape()                                                     = default;
    virtual ~Shape()                                            = default;

    // Accesss member points
    virtual T& operator[](const size_t index)                   = nullptr;
    virtual T operator[](const size_t index)                    = nullptr;

    // Shape comparison
    virtual bool operator==(const Shape&) const                 = nullptr;
    virtual bool operator!=(const Shape&) const                 = nullptr;

    // Area differences between shapes.
    virtual T operator+(const Shape&) const                     = nullptr;
    virtual T operator-(const Shape&) const                     = nullptr;
    
    virtual T area() const                                      = nullptr;
    virtual T sideLength() const                                = nullptr;

    // Get coordinates for corners (noncircle) center (circle)
    virtual Array<Coordinate&> getPoints()                      = nullptr;
    virtual Coordinate& center()                                = nullptr;

    // Transform points
    //Shape& transform(~lambda~);
};
