template <class T, template <class T> class System, // T, System<T>
          template <class T, template <class T> class System> class Derived> // Shape<T, Cartesian<T>>
bool Shape<T, System, Derived>::isInShape(const CoordinateI<T>& p) const
{
  const auto p_xy = static_cast<const Cartesian<T>&>(p);
  bool ret = false;

  for(int i=0, j=static_cast<long>(numSides())-1; i<numSides(); j=i++)
  {
    // being an interface, they should be castable to cartesian (a nonvirt base).
    const Cartesian<T>& verti = static_cast<const Cartesian<T>&>(*operator[](i));
    const Cartesian<T>& vertj = static_cast<const Cartesian<T>&>(*operator[](j));


    if((verti.y()>p_xy.y()) != (vertj.y()>p_xy.y()) && 
       (p_xy.x() < (vertj.x() - verti.x()) * (p_xy.y()-verti.y()) / (vertj.y()-verti.y()) + verti.x()))
      ret = !ret;
  }

  return ret;
}
