template <class T, template <class T> class System, // T, System<T>
          template <class T, template <class T> class System> class Derived> // Shape<T, Cartesian<T>>
bool Shape<T, System, Derived>::isInShape(const Coordinate<T, System>& p) const
{
  // A freeform shape won't have this... TODO
  T side, right_distance, left_distance, rsquared, lsquared, ssquared;

  // Create triangles with every pair of coordinates near each other and the
  // passed point.
  for(auto i=0u; i<numSides(); i++)
  {
    const Coordinate<T, System>& right = (*this)[(i+1)%numSides()];
    const Coordinate<T, System>& left = (*this)[i];

    side = left.distance(right);
    ssquared = side*side;
    right_distance = right.distance(p);
    left_distance = left.distance(p);
    rsquared = right_distance * right_distance;
    lsquared = left_distance * left_distance;

    T sum = 0;

    // law of cosines
    sum += acos((rsquared + lsquared - ssquared)/(2*right_distance*left_distance));
    sum += acos((ssquared + lsquared -rsquared)/(2*side*left_distance));
    sum += acos((ssquared + rsquared - lsquared)/(2*side*right_distance));

    // If the sum of these angles is PI, it's inside (continue). If zero, false.
    if(sum == 0)
      return false;
  }

  return true;
}
