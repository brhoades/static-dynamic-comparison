template <class T, template <class T> class System, // T, System<T>
          template <class T, template <class T> class System> class Derived> // Shape<T, Cartesian<T>>
bool Shape<T, System, Derived>::isInShape(const Coordinate<T, System>& p) const
{
  const auto p_xy = p.asCartesian();
  bool ret = false;

  for(int i=0, j=static_cast<long>(numSides())-1; i<numSides(); j=i++)
  {
    const auto& verti = (*this)[i];
    const auto& vertj = (*this)[j];


    if((verti.y()>p_xy.y()) != (vertj.y()>p_xy.y()) && 
       (p_xy.x() < (vertj.x() - verti.x()) * (p_xy.y()-verti.y()) / (vertj.y()-verti.y()) + verti.x()))
      ret = !ret;
  }

  return ret;
}
