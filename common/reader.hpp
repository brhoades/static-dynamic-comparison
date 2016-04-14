/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Reads coordinates from a file.
 */

template <class T, template <class T> class System>
System<T>* CoordReader<T, System>::operator()(const char* fname)
{
  fstream fs(fname);

  if(fs.bad())
  {
    cout << "Failed to read " << fname << "." << endl;
    exit(1);
  }

  m_size = 0;
  while(!fs.eof() and fs.good())
  {
    fs.ignore(numeric_limits<streamsize>::max(), '\n');
    m_size++;
  }
  fs.clear();
  fs.seekg(0, ios::beg);

  if(m_size == 0)
    throw out_of_range("Files passed to reader must have at least one line.");

  System<T>* ret = new System<T>[m_size];
  size_t i = 0;

  while(!fs.eof() and fs.good())
  {
    cout << "Filling in " << i << endl;
    fs >> ret[i][0]  >>ret[i][1];
    i++;
  }

  return ret;
}
