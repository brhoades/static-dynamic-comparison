/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Reads coordinates from a file.
 */

#include <cstring>

template <class T, template <class T> class System>
vector<System<T>> CoordReader<T, System>::operator()(const char* fname) const
{
  vector<System<T>> ret;
  fstream fs(fname);

  if(!fs.bad())
  {
    cout << "Failed to read " << fname << "." << endl;
    exit(1);
  }

  char first[10], second[10];
  while(!fs.eof())
  {
    fs >> first >> second;
    
    System<T> tmp(atof(first), atof(second));
    ret.push_back(tmp);
  }

  return ret;
}
