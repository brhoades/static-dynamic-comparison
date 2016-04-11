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

  Polygon<double, 3, Cartesian> triangle;
  triangle.setVertex(0, a);
  triangle.setVertex(1, b);
  triangle.setVertex(2, c);

  cout << triangle.isInShape(d) << endl;
  cout << triangle.isInShape(e) << endl;
  cout << triangle.isInShape(f) << endl;
  cout << triangle.isInShape(g) << endl;
  cout << triangle.isInShape(g) << endl;

  return 0;
}
