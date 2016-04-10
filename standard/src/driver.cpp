/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Driver to demonstrate our coordinate and shape classes.
 */

#include <iostream>

#include "coordinates/cartesian.h"
#include "coordinates/polar.h"

#include "shapes/polygon.h"

using namespace std;

int main(int argc, char** argv)
{
  Cartesian<double> a(1, 2);
  Polar<double> b(2, 3);

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
