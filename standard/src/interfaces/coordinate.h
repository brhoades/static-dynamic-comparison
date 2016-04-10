/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Coordinate interface (non-crtp).
 *
 * Documentation for interface functions are within derived classes.
 */
#pragma once

template <class T>
class Coordinate
{
  public:
    Coordinate()                                                     = default;
    virtual ~Coordinate()                                            = default;

    // Coordinate comparison
    virtual bool operator==(const Coordinate&) const                 = nullptr;
    virtual bool operator!=(const Coordinate&) const                 = nullptr;

    // Accesss member values
    virtual T& operator[](const size_t index)                        = nullptr;
    virtual T operator[](const size_t index)                         = nullptr;


    virtual T distance(const Coordinate&) const                      = nullptr;

    // Transform points
    //Coordinate& transform(~lambda~);
};
