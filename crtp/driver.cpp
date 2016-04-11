#include "interfaces/coordinate.h"
#include "coordinates/cartesian.h"

int main()
{
  Cartesian<double> a(0, 0), b(0, 4), c(4, 0);
  Cartesian<double> d(1, 1), e(0, 0), f(5, 5), g(-1, -20);

  cout << "Distance from a to b." << endl;
  cout << a.distance(b) << endl << endl;

  cout << "a" << endl;
  cout << a << endl << endl;

  cout << "a -= b" << endl;
  cout << (a -= b) << endl << endl;

  cout << "a += b" << endl;
  cout << (a += b) << endl << endl;

  return 0;
}
