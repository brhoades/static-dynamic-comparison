template <class T>
bool Shape<T>::isInShape(const Coordinate<T>& p) const
{
  const auto p_xy = static_cast<const Cartesian<T>&>(p);
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
