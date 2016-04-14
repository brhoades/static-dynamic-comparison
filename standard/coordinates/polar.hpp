/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Polar Coordinate
 */

#include <exception>
#include <cmath>

template <class T>
Polar<T>::Polar(): m_r(0), m_theta(0)
{
}

template <class T>
Polar<T>::Polar(const T& r, const T& theta): m_r(r), m_theta(theta)
{
}

template <class T>
Coordinate<T>& Polar<T>::operator=(const Coordinate<T>& rhs)
{
  fromCartesian(static_cast<const Cartesian<T>&>(rhs));

  return *this;
}

// Arithmetic
template <class T>
Coordinate<T>& Polar<T>::operator+=(const Coordinate<T>& rhs)
{
  fromCartesian(static_cast<Cartesian<T>>(*this) += rhs);

  return *this;
}

template <class T>
Coordinate<T>& Polar<T>::operator-=(const Coordinate<T>& rhs)
{
  fromCartesian(static_cast<Cartesian<T>>(*this) -= rhs);

  return *this;
}

// Transformation
template <class T>
Coordinate<T>& Polar<T>::operator/=(const T& rhs)
{
  fromCartesian(static_cast<Cartesian<T>>(*this) /= rhs);

  return *this;
}

template <class T>
Coordinate<T>& Polar<T>::operator*=(const T& rhs)
{
  fromCartesian(static_cast<Cartesian<T>>(*this) *= rhs);

  return *this;
}

template <class T>
bool Polar<T>::operator==(const Coordinate<T>& other) const
{
  return distance(other) == 0;
}

template <class T>
bool Polar<T>::operator!=(const Coordinate<T>& other) const
{
  return !operator==(other);
}

template <class T>
T& Polar<T>::operator[](const size_t index)
{
  if(index > 1)
    throw out_of_range("Coordinate index is not within a polar pair.");

  if(index == 1)
    return m_theta;

  return m_r;
}

template <class T>
T Polar<T>::operator[](const size_t index) const
{
  if(index > 1)
    throw out_of_range("Coordinate index is not within a polar pair.");

  if(index == 1)
    return m_theta;

  return m_r;
}

template <class T>
T Polar<T>::distance(const Coordinate<T>& other) const
{
  const Cartesian<T>& this_cartesian = static_cast<Cartesian<T>>(*this);
  const Cartesian<T>& other_cartesian = static_cast<Cartesian<T>>(other);
  T x = this_cartesian.x() - other_cartesian.x(),
    y = this_cartesian.y() - other_cartesian.y();

  return sqrt(x*x + y*y);
}

template <class T>
void Polar<T>::fromCartesian(const Cartesian<T>& rhs)
{
  m_r = sqrt(rhs.x()*rhs.x() + rhs.y()*rhs.y());

  if(rhs.x() == 0)
    m_theta = 0;
  else
    m_theta = atan(rhs.y()/rhs.x());
}

template <class T>
Polar<T>::operator Cartesian<T>() const
{
  Cartesian<T> ret(x(), y());

  return ret;
}

template <class T>
T Polar<T>::x() const
{
  return m_r*cos(m_theta);
}

template <class T>
T Polar<T>::y() const
{
  return m_r*sin(m_theta);
}

/* Global Functions */
template <class T>
ostream& operator<<(ostream& os, const Polar<T>& rhs)
{
  os << "(" << rhs.r() << ", " << rhs.theta() << "㎭)";

  return os;
}
