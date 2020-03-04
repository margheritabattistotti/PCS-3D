#include "ConcaveToConvex.hpp"

using namespace std;
using namespace MainApplication;

namespace GeDiM
{
  // ***************************************************************************
  bool ConcaveToConvex::IsPolygonConvex(const IPolygon& polygon, const double& tolerance)
  {
    return false;
  }
  // ***************************************************************************
  Output::ExitCodes ConcaveToConvex::ConcaveToConvexPolygon(const IPolygon& concavePolygon, list<IPolygon*>& convexPolygons, const double& tolerance)
  {
    convexPolygons.push_back(concavePolygon.Clone());

    return Output::UnimplementedMethod;
  }
  // ***************************************************************************
  bool ConcaveToConvex::IsPolyhedronConvex(const IPolyhedron& polyhedron, const double& tolerance)
  {
    return false;
  }
  // ***************************************************************************
  Output::ExitCodes ConcaveToConvex::ConcaveToConvexPolyhedron(const IPolyhedron& concavePolyhedron, list<IPolyhedron*>& convexPolyhedra, const double& tolerance)
  {
    convexPolyhedra.push_back(concavePolyhedron.Clone());

    return Output::UnimplementedMethod;
  }
  // ***************************************************************************

}
