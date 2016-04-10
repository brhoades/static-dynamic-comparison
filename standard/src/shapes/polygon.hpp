/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Regular Polygon (non-crtp).
 */

template <class T, size_t size>
Polygon<T, size>::Polygon(): m_data(nullptr)
{
}

// Accesss member points
template <class T, size_t size>
Coordinate<T>& Polygon<T, size>::operator[](const size_t index)
{

}
template <class T, size_t size>
Coordinate<T> Polygon<T, size>::operator[](const size_t index) const
{

}

// Polygon comparison
template <class T, size_t size>
bool Polygon<T, size>::operator==(const Shape<T>&) const
{

}
template <class T, size_t size>
bool Polygon<T, size>::operator!=(const Shape<T>&) const
{

}

// Area differences between shapes.
template <class T, size_t size>
T Polygon<T, size>::operator+(const Shape<T>&) const
{

}
template <class T, size_t size>
T Polygon<T, size>::operator-(const Shape<T>&) const
{

}
    
template <class T, size_t size>
T Polygon<T, size>::area() const
{

}
template <class T, size_t size>
T Polygon<T, size>::sideLength() const
{

}

    // Get coordinates for corners (noncircle).
template <class T, size_t size>
Coordinate<T>* Polygon<T, size>::getPoints()
{

}
template <class T, size_t size>
Coordinate<T> Polygon<T, size>::center() const
{

}
