/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Cartesian Coordinate
 */

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
Cartesian<T>::Cartesian(const Cartesian<T>& other): Cartesian(other.m_x,
  other.m_y)
{
}

// If you weren't lazy, you could specialize for Coordinate <T, Polar> to avoid
// additional calls to static_cast. -O2 may take care of this for you.
template <class T>
template <template <class> class System>
Coordinate<T, Cartesian>& Cartesian<T>::operator=(const Coordinate<T, System>& rhs)
{
  const auto& rhs_xy = static_cast<const Cartesian<T>&>(rhs);
  fromCartesian(rhs_xy);

  return *this;
}

// Arithmetic
template <class T>
template <template <class> class System>
Coordinate<T, Cartesian>& Cartesian<T>::operator+=(const Coordinate<T, System>& rhs)
{
  const auto& rhs_xy = static_cast<const Cartesian<T>&>(rhs);

  for(auto i=0; i<2; i++)
    (*this)[i] += rhs_xy[i];

  return *this;
}

template <class T>
template <template <class> class System>
Coordinate<T, Cartesian>& Cartesian<T>::operator-=(const Coordinate<T, System>& rhs)
{
  const auto& rhs_xy = static_cast<const Cartesian<T>&>(rhs);

  for(auto i=0; i<2; i++)
    (*this)[i] -= rhs_xy[i];

  return *this;
}

// Transformation
template <class T>
Coordinate<T, Cartesian>& Cartesian<T>::operator/=(const T& rhs)
{
  for(auto i=0; i<2; i++)
    (*this)[i] /= rhs;

  return *this;
}

template <class T>
Coordinate<T, Cartesian>& Cartesian<T>::operator*=(const T& rhs)
{
  for(auto i=0; i<2; i++)
    (*this)[i] *= rhs;

  return *this;
}

template <class T>
template <template <class> class System>
bool Cartesian<T>::operator==(const Coordinate<T, System>& other) const
{
  return distance(other) == 0;
}

template <class T>
template <template <class> class System>
bool Cartesian<T>::operator!=(const Coordinate<T, System>& other) const
{
  return !operator==(other);
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
template <template <class> class System>
T Cartesian<T>::distance(const Coordinate<T, System>& other) const
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

template <class T>
void Cartesian<T>::fromCartesian(const Cartesian<T>& rhs)
{
  m_x = rhs.m_x;
  m_y = rhs.m_y;
}

/* Global Functions */
template <class T>
ostream& operator<<(ostream& os, const Cartesian<T>& rhs)
{
  os << "(" << rhs.x() << ", " << rhs.y() << ")";

  return os;
}
