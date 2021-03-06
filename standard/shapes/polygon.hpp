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
}

template <class T>
Polygon<T>::Polygon(const Polygon<T>& other): Polygon()
{
  for(auto& p: other.m_vertices)
    m_vertices.push_back(p);
}

template <class T>
Polygon<T>::~Polygon()
{
  for(auto i=0u; i<m_vertices.size(); i++)
    delete m_vertices[i];
}

// Accesss member points
template <class T>
Coordinate<T>& Polygon<T>::operator[](const size_t index)
{
  if(m_vertices.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return *m_vertices[index];
}
template <class T>
const Coordinate<T>& Polygon<T>::operator[](const size_t index) const
{
  if(m_vertices.size() <= index)
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
  return m_vertices.size();
}

template <class T>
void Polygon<T>::addVertex(const Cartesian<T>& coord)
{
  // really forcing this interface
  m_vertices.push_back(new Cartesian<T>(coord));
}

template <class T>
T Polygon<T>::area() const
{
  // abuse our interface here for maximum slow.

  // get average of any two points (first two will do)
  Cartesian<T> midpoint = *m_vertices[0];
  midpoint += *m_vertices[1] /= 2;

  // 1/2 apothom * perimeter
  return((1/2.f) * this->center().distance(midpoint)*perimeter());
}

template <class T>
T Polygon<T>::sideLength() const
{
  // grab first two points and return the distance
  return m_vertices[0]->distance((*this)[1]);
}

// Get coordinates for corners (noncircle).
template <class T>
Coordinate<T>** Polygon<T>::getPoints()
{
  return m_vertices.data();
}

template <class T>
Cartesian<T> Polygon<T>::center() const
{
  // get our first point
  Cartesian<T> sum;

  for(auto i=0u; i<m_vertices.size(); i++)
    sum += (*this)[i];

  return sum /= m_vertices.size();
}

template <class T>
T Polygon<T>::perimeter() const
{
  return sideLength()*m_vertices.size();
}
