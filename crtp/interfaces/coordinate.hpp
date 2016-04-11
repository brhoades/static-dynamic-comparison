/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Coordinate interface (non-crtp).
 */

template <class T, template <class T> class Derived>
ostream& operator<<(ostream& os, const Coordinate<T, Derived>& rhs)
{
  os << "(" << rhs[0] << ", " << rhs[1] << ")";

  return os;
}
