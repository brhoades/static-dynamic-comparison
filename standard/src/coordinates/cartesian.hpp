/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Cartesian Coordinate
 */

#include <iostream>
#include <exception>
#include <cmath>

template <class T>
Cartesian<T>::Cartesian(): m_x(0), m_y(0)
{
}

template <class T>
Cartesian<T>::Cartesian(const T& x, const T& y): m_x(x), m_y(y)
{
}

template <class T>
bool Cartesian<T>::operator==(const Coordinate<T>& other) const
{
  return distance(other) == 0;
}

template <class T>
bool Cartesian<T>::operator!=(const Coordinate<T>& other) const
{
  return operator==(other);
}

template <class T>
T& Cartesian<T>::operator[](const size_t index)
{
  if(index > 1)
    throw out_of_range("Coordinate index is not within a cartesian pair.");

  if(index == 1)
    return m_y;

  return m_x;
}

template <class T>
T Cartesian<T>::operator[](const size_t index) const
{
  if(index > 1)
    throw out_of_range("Coordinate index is not within a cartesian pair.");

  if(index == 1)
    return m_y;

  return m_x;
}

template <class T>
T Cartesian<T>::distance(const Coordinate<T>& other) const
{
  const Cartesian<T>& other_cartesian = static_cast<const Cartesian<T>&>(other);
  T x = m_x - other_cartesian.m_x, y = m_y - other_cartesian.m_y;

  return sqrt(x*x + y*y);
}

template <class T>
Cartesian<T>::operator Cartesian<T>() const
{
  return *this;
}
