/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (non-crtp).
 */

template <class T,size_t size,template <class T> class System>
Polygon<T,size,System>::Polygon()
{
  if(size <= 1)
    throw domain_error("A regular polygon needs at least 3 sides.");

  for(auto*& p: m_verticies)
    p = nullptr;
}

template <class T,size_t size,template <class T> class System>
Polygon<T,size,System>::Polygon(const Polygon<T,size,System>& other): Polygon()
{
  for(auto i=0u; i<size; i++)
    m_verticies[i] = new Coordinate<T,System>(other[i]);
}

template <class T,size_t size,template <class T> class System>
Polygon<T,size,System>::~Polygon()
{
  for(auto i=0u; i<size; i++)
    delete m_verticies[i];
}

// Accesss member points
template <class T,size_t size,template <class T> class System>
Coordinate<T,System>& Polygon<T,size,System>::operator[](const size_t index)
{
  if(m_verticies.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return *m_verticies[index];
}
template <class T,size_t size,template <class T> class System>
const Coordinate<T,System>& Polygon<T,size,System>::operator[](const size_t index) const
{
  if(m_verticies.size() <= index)
    throw out_of_range("Provided index is out of bounds for this shape.");

  return *m_verticies[index];
}

// Polygon comparison
template <class T,size_t size,template <class T> class System>
bool Polygon<T,size,System>::operator==(const Shape<T,System>& rhs) const
{
  if(rhs.numSides() != numSides())
    return false;

  for(auto i=0u; i<numSides(); i++)
  {
    if(rhs[i] != *m_verticies[i])
      return false;
  }

  return true;
}
template <class T,size_t size,template <class T> class System>
bool Polygon<T,size,System>::operator!=(const Shape<T,System>& rhs) const
{
  return !operator==(rhs);
}

// Area differences between shapes.
template <class T,size_t size,template <class T> class System>
T Polygon<T,size,System>::operator+(const Shape<T,System>& rhs) const
{
  return area() + rhs.area();
}
template <class T,size_t size,template <class T> class System>
T Polygon<T,size,System>::operator-(const Shape<T,System>& rhs) const
{
  return area() - rhs.area();
}

template <class T,size_t size,template <class T> class System>
size_t Polygon<T,size,System>::numSides() const
{
  return size;
}


template <class T,size_t size,template <class T> class System>
void Polygon<T,size,System>::setVertex(const size_t index, const Cartesian<T>& coord)
{
  delete m_verticies[index];

  // really forcing this interface
  m_verticies[index] = new Cartesian<T>(coord);
}

template <class T,size_t size,template <class T> class System>
T Polygon<T,size,System>::area() const
{
  // abuse our interface here for maximum slow.

  // get average of any two points (first two will do)
  Cartesian<T> midpoint = *m_verticies[0];
  midpoint += *m_verticies[1] /= 2;

  // 1/2 apothom * perimeter
  return((1/2.f) * this->center().distance(midpoint)*perimeter());
}

template <class T,size_t size,template <class T> class System>
T Polygon<T,size,System>::sideLength() const
{
  // grab first two points and return the distance
  return m_verticies[0]->distance((*this)[1]);
}

// Get coordinates for corners (noncircle).
template <class T,size_t size,template <class T> class System>
Coordinate<T,System>** Polygon<T,size,System>::getPoints()
{
  return m_verticies.data();
}

template <class T,size_t size,template <class T> class System>
Cartesian<T> Polygon<T,size,System>::center() const
{
  // get our first point
  Cartesian<T> sum;

  for(auto i=0u; i<size; i++)
    sum += (*this)[i];

  return sum /= size;
}

template <class T,size_t size,template <class T> class System>
T Polygon<T,size,System>::perimeter() const
{
  return sideLength()*size;
}

template <class T,size_t size,template <class T> class System>
bool Polygon<T,size,System>::isInShape(const Coordinate<T,System>& p) const
{
  auto p_xy = p.asCartesian();
  const Coordinate<T,System>* right = m_verticies[0];
  const Coordinate<T,System>* left = m_verticies[1];

  // A freeform shape won't have this... TODO
  T side = sideLength() / 2;

  // Create triangles with every pair of coordinates near each other and the
  // passed point.
  for(auto i=0u; i<size; i++)
  {
    left = m_verticies[i];

    if(i < size - 1)
      right = m_verticies[i+1];
    else // wrap around back to first.
      right = m_verticies[0];

    T right_distance = p.distance(*right), left_distance = p.distance(*left);

    T sum = 0;

    // law of cosines
    sum += acos((right_distance*right_distance + left_distance*left_distance - side*side)
                /(2*right_distance*left_distance));
    sum += acos((side*side + left_distance*left_distance - right_distance*right_distance)
                /(2*side*left_distance));
    sum += acos((side*side + right_distance*right_distance - left_distance*left_distance)
                /(2*side*right_distance));

    // If the sum of these angles is PI, it's inside (continue). If zero, false.
    if(sum == 0)
      return false;
    else if(isnan(sum))
      return false;
    else if(abs(sum - M_PI) > 0.0000001)
    {
      cerr << sum << endl;
      throw domain_error("When determining side of point on a shape, the result wasn't 0 or PI.");
    }
  }

  return true;
}
