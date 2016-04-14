/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (crtp).
 */

template <class T,template <class T> class System>
Polygon<T,System>::Polygon()
{
}

template <class T,template <class T> class System>
Polygon<T,System>::Polygon(const Polygon<T,System>& other): Polygon()
{
  for(auto& p: other.m_vertices)
    m_vertices.push_back(new System<T>(p));
}

template <class T,template <class T> class System>
Polygon<T,System>::~Polygon()
{
  for(auto& p: m_vertices)
    delete p;
}

// Accesss member points
template <class T,template <class T> class System>
#ifndef USE_REAL_TYPE
CoordinateI<T>* Polygon<T,System>::operator[](const size_t index)
#else
System<T>* Polygon<T,System>::operator[](const size_t index)
#endif
{
  if(m_vertices.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return m_vertices[index];
}
template <class T,template <class T> class System>
#ifndef USE_REAL_TYPE
const CoordinateI<T>* Polygon<T,System>::operator[](const size_t index) const
#else
const System<T>* Polygon<T,System>::operator[](const size_t index) const
#endif
{
  if(m_vertices.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return m_vertices[index];
}

// Polygon comparison
template <class T,template <class T> class System>
bool Polygon<T,System>::operator==(const Shape<T,System,Polygon>& rhs) const
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
template <class T,template <class T> class System>
bool Polygon<T,System>::operator!=(const Shape<T,System,Polygon>& rhs) const
{
  return !operator==(rhs);
}

// Area differences between shapes.
template <class T,template <class T> class System>
T Polygon<T,System>::operator+(const Shape<T,System,Polygon>& rhs) const
{
  return area() + rhs.area();
}
template <class T,template <class T> class System>
T Polygon<T,System>::operator-(const Shape<T,System,Polygon>& rhs) const
{
  return area() - rhs.area();
}

template <class T,template <class T> class System>
size_t Polygon<T,System>::numSides() const
{
  return m_vertices.size();
}

template <class T,template <class T> class System>
void Polygon<T,System>::addVertex(const Cartesian<T>& coord)
{
  // really forcing this interface
  #ifndef USE_REAL_TYPE
  m_vertices.push_back(new Cartesian<T>(coord));
  #else
  m_vertices.push_back(new System<T>(coord));
  #endif
}

template <class T,template <class T> class System>
T Polygon<T,System>::area() const
{
  // get average of any two points (first two will do)
  System<T>& midpoint = *m_vertices[0];
  midpoint += *m_vertices[1] /= 2;

  // 1/2 apothom * perimeter
  return((1/2.f) * center().distance(midpoint)*perimeter());
}

template <class T,template <class T> class System>
T Polygon<T,System>::sideLength() const
{
  // grab first two points and return the distance
  return m_vertices[0]->distance((*this)[1]);
}

// Get coordinates for corners (noncircle).
template <class T,template <class T> class System>
#ifndef USE_REAL_TYPE
CoordinateI<T>** Polygon<T,System>::getPoints()
#else
System<T>** Polygon<T,System>::getPoints()
#endif
{
  return m_vertices.data();
}

template <class T,template <class T> class System>
Cartesian<T> Polygon<T,System>::center() const
{
  // get our first point
  Cartesian<T> sum;

  for(auto i=0u; i<m_vertices.size(); i++)
    sum += (*this)[i];

  return sum /= m_vertices.size();
}

template <class T,template <class T> class System>
T Polygon<T,System>::perimeter() const
{
  return sideLength()*m_vertices.size();
}
