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

#include "coordinate.h"

template <class T>
class Shape
{
  public:
    Shape()                                                          = default;
    virtual ~Shape()                                                 = default;

    // Accesss member points
    virtual Coordinate<T>& operator[](const size_t index)                  = 0;
    virtual Coordinate<T> operator[](const size_t index) const             = 0;

    // Shape comparison
    virtual bool operator==(const Shape<T>&) const                         = 0;
    virtual bool operator!=(const Shape<T>&) const                         = 0;

    // Area differences between shapes.
    virtual T operator+(const Shape<T>&) const                             = 0;
    virtual T operator-(const Shape<T>&) const                             = 0;

    virtual size_t numSides() const                                        = 0;
    
    virtual T area() const                                                 = 0;
    virtual T sideLength() const                                           = 0;
    virtual T perimeter() const                                            = 0;

    // Get coordinates for corners (noncircle), center (circle).
    virtual Coordinate<T>* getPoints()                                     = 0;
    virtual Cartesian<T> center() const                                    = 0;

    // Transform points
    //Shape& transform(~lambda~);
};
