/* Billy Rhoades
 * 4/10/16
 * CS5201
 * CRTP Lecture Example
 * 
 * Driver to demonstrate our coordinate and shape classes.
 */

#include <iostream>

#include "consts.h"
#include "coordinates/cartesian.h"
#include "coordinates/polar.h"

#include "shapes/polygon.h"

#include "../common/reader.h"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
  if(argc != 3)
  {
    cout << "Driver requires two arguments." << endl
         << "A file containing 2-d coordinates as vertices of a shape. Each "
         << "adjacent pair must be equidistant and clockwise in order. They "
         << "must form a regular polygon." << endl
         << "The points in the second file will be checked if they are in the "
         << "shape defined above." << endl;
    return 0;
  }

  CoordReader<double,Cartesian> reader;

  vector<Cartesian<double>> vertices = reader(argv[1]);
  vector<Cartesian<double>> testers = reader(argv[2]);
  cout << "CRTP: Processing a " << vertices.size()
       << "-sided polygon with " << testers.size() << " test points." << endl;

  #ifndef USE_REAL_TYPE
  Polygon<double,CoordinateI> shape;

  // We must use our interface for both types or -O2/-O3 will compile it out.
  Polar<double> z(3, 2);
  Coordinate<double, Polar>& x = z;
  CoordinateI<double>& y = x;
  y.distance(z);
  #else
  // This is significantly faster, but not comparable to standard
  Polygon<double,Cartesian> shape;

  // We must use our "interface" here or we won't instantiate it and -O2/-O3
  // get zealous.
  Polar<double> x(3, 2);
  Coordinate<double, Polar>& y = x;
  y.distance(x);
  #endif

  for(auto& p: vertices)
    shape.addVertex(p);

  for(auto& p: testers)
  {
    #ifdef OUTPUT
      cout << p << ": " << shape.isInShape(p) << endl;
    #else
      shape.isInShape(p);
    #endif
  }

  return 0;
}
