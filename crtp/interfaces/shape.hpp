template <class T, template <class T> class System, // T, System<T>
          template <class T, template <class T> class System> class Derived> // Shape<T, Cartesian<T>>
#ifndef USE_REAL_TYPE
bool Shape<T, System, Derived>::isInShape(const CoordinateI<T>& p) const
#else
bool Shape<T, System, Derived>::isInShape(const Coordinate<T, System>& p) const
#endif
{
  bool ret = false;

  for(size_t i=0, j=numSides()-1; i<numSides(); j=i++)
  {
    #ifndef USE_REAL_TYPE
    // being an interface, they should be castable to cartesian (a nonvirt base).
    const CoordinateI<T>& verti = *operator[](i);
    const CoordinateI<T>& vertj = *operator[](j);
    #else
    const System<T>& verti = *operator[](i);
    const System<T>& vertj = *operator[](j);
    #endif

    if((verti.y()>p.y()) != (vertj.y()>p.y()) && 
       (p.x() < (vertj.x() - verti.x()) * (p.y()-verti.y()) / (vertj.y()-verti.y()) + verti.x()))
      ret = !ret;
  }

  return ret;
}
