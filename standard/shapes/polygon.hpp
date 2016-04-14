/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (non-crtp).
 */

template <class T>
Polygon<T>::Polygon()
{
  m_sides = 0;
  m_vertices = nullptr;
}

template <class T>
Polygon<T>::Polygon(size_t size)
{
  m_sides = size;
  m_vertices = nullptr;
}

template <class T>
Polygon<T>::Polygon(const Polygon<T>& other): Polygon()
{
  m_sides = other.m_sides;
  m_vertices = new Coordinate<T>[m_sides];

  for(auto i=0u; i<m_sides; i++)
    m_vertices[i] = other.m_vertices[i];
}

template <class T>
Polygon<T>::~Polygon()
{
  for(auto i=0u; i<m_sides; i++)
    delete m_vertices[i];

  delete[] m_vertices;
  m_vertices = nullptr;
  m_sides = 0;
}

// Accesss member points
template <class T>
Coordinate<T>& Polygon<T>::operator[](const size_t index)
{
  if(index >= m_sides)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return *m_vertices[index];
}
template <class T>
const Coordinate<T>& Polygon<T>::operator[](const size_t index) const
{
  if(index >= m_sides)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return *m_vertices[index];
}

// Polygon comparison
template <class T>
bool Polygon<T>::operator==(const Shape<T>& rhs) const
{
  if(rhs.numSides() != numSides())
    return false;

  for(auto i=0u; i<numSides(); i++)
  {
    if(rhs[i] != *m_vertices[i])
      return false;
  }

  return true;
}
template <class T>
bool Polygon<T>::operator!=(const Shape<T>& rhs) const
{
  return !operator==(rhs);
}

// Area differences between shapes.
template <class T>
T Polygon<T>::operator+(const Shape<T>& rhs) const
{
  return area() + rhs.area();
}
template <class T>
T Polygon<T>::operator-(const Shape<T>& rhs) const
{
  return area() - rhs.area();
}

template <class T>
size_t Polygon<T>::numSides() const
{
  return m_sides;
}

template <class T>
T Polygon<T>::area() const
{
  // abuse our interface here for maximum slow.

  // get average of any two points (first two will do)
  Cartesian<T> midpoint = *m_vertices[0];
  midpoint += *m_vertices[1] /= 2;

  // 1/2 apothom * perimeter
  return((1/2.f) * center().distance(midpoint)*perimeter());
}

template <class T>
T Polygon<T>::sideLength() const
{
  // grab first two points and return the distance
  return m_vertices[0]->distance(*m_vertices[1]);
}

template <class T>
Cartesian<T> Polygon<T>::center() const
{
  // get our first point
  Cartesian<T> sum;

  for(auto i=0u; i<m_sides; i++)
    sum += *m_vertices[i];

  return sum /= m_sides;
}

template <class T>
T Polygon<T>::perimeter() const
{
  return sideLength()*m_sides;
}
