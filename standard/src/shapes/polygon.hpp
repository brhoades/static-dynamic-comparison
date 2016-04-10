/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (non-crtp).
 */

template <class T, size_t size>
Polygon<T, size>::Polygon()
{
  if(size <= 1)
    throw domain_error("A regular polygon needs at least 3 sides.");
}

template <class T, size_t size>
Polygon<T, size>::Polygon(const Polygon<T, size>& other): Polygon()
{
  for(auto i=0u; i<size; i++)
    m_data[i] = other[i];
}

// Accesss member points
template <class T, size_t size>
Coordinate<T>& Polygon<T, size>::operator[](const size_t index)
{
  if(m_data.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return m_data[index];
}
template <class T, size_t size>
Coordinate<T> Polygon<T, size>::operator[](const size_t index) const
{
  if(m_data.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return m_data[index];
}

// Polygon comparison
template <class T, size_t size>
bool Polygon<T, size>::operator==(const Shape<T>& rhs) const
{
  if(rhs.numSides() != numSides())
    return false;

  for(auto i=0u; i<numSides(); i++)
  {
    if(rhs[i] != this[i])
      return false;
  }

  return true;
}
template <class T, size_t size>
bool Polygon<T, size>::operator!=(const Shape<T>& rhs) const
{
  return !operator==(rhs);
}

// Area differences between shapes.
template <class T, size_t size>
T Polygon<T, size>::operator+(const Shape<T>& rhs) const
{
  return area() + rhs.area();
}
template <class T, size_t size>
T Polygon<T, size>::operator-(const Shape<T>& rhs) const
{
  return area() - rhs.area();
}

template <class T, size_t size>
size_t Polygon<T, size>::numSides() const
{
  return size;
}

template <class T, size_t size>
T Polygon<T, size>::area() const
{
  // abuse our interface here for maximum slow.

  // get average of any two points (first two will do)
  Cartesian<T> midpoint = (std::copy(m_data[0]) += m_data[1]) /= 2;

  // 1/2 apothom * perimeter
  return (1/2.f)*this->center.distance(midpoint)*perimeter();
}

template <class T, size_t size>
T Polygon<T, size>::sideLength() const
{
  // grab first two points and return the distance
  return m_data[0].distance(m_data[1]);
}

// Get coordinates for corners (noncircle).
template <class T, size_t size>
Coordinate<T>* Polygon<T, size>::getPoints()
{
  return m_data.data();
}

template <class T, size_t size>
Cartesian<T> Polygon<T, size>::center() const
{
  // get our first point
  Cartesian<T> sum;

  for(auto i=0u; i<size; i++)
    sum += (*this)[i];

  return sum /= size;
}
