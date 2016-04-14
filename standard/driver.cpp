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

  // We must use our interface for both types or -O2/-O3 will compile it out.
  Polar<double> x(3, 2);
  Coordinate<double>& y = x;

  y.distance(x);

  Polar<float> a(3, 2);
  Coordinate<float>& b = a;

  b.distance(a);
  CoordReader<double,Cartesian> reader;

  vector<Cartesian<double>> vertices = reader(argv[1]);
  vector<Cartesian<double>> testers = reader(argv[2]);
  cout << "Standard: Processing a " << vertices.size()
       << "-sided polygon with " << testers.size() << " test points." << endl;

  Polygon<double> shape;

  for(auto& p: vertices)
    shape.addVertex(p);

  for(auto& p: testers)
    shape.isInShape(p);

  return 0;
}
