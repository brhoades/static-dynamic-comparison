template <class T>
bool Shape<T>::isInShape(const Coordinate<T>& p) const
{
  bool ret = false;

  for(size_t i=0, j=numSides()-1; i<numSides(); j=i++)
  {
    const Coordinate<T>& verti = operator[](i);
    const Coordinate<T>& vertj = operator[](j);

    if((verti.y()>p.y()) != (vertj.y()>p.y()) && 
       (p.x() < (vertj.x() - verti.x()) * (p.y()-verti.y()) / (vertj.y()-verti.y()) + verti.x()))
      ret = !ret;
  }

  return ret;
}
