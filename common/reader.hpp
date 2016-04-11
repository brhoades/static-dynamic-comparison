/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Reads coordinates from a file.
 */

template <class T, template <class T> class System>
vector<System<T>> CoordReader<T, System>::operator()(const char* fname) const
{
  vector<System<T>> ret;
  fstream fs(fname);

  if(fs.bad())
  {
    cout << "Failed to read " << fname << "." << endl;
    exit(1);
  }

  while(!fs.eof() and fs.good())
  {
    T first, second;
    fs >> first >> second;
    
    System<T> tmp(first, second);
    ret.push_back(tmp);
  }

  return ret;
}
