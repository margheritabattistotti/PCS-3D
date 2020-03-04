#ifndef CONCAVETOCONVEX_H
#define CONCAVETOCONVEX_H

#include "Output.hpp"
#include "IPolygon.hpp"
#include "IPolyhedron.hpp"

using namespace MainApplication;

namespace GeDiM
{
  class ConcaveToConvex;

  class ConcaveToConvex
  {
    public:
      /// Check if a polygon is convex
      /// @param[in] polygon - the polygon
      /// @return true if the input polygon is convex
      static bool IsPolygonConvex(const IPolygon& polygon, const double& tolerance);

      /// Function to convert a concave polygon to a list of Convex polygons
      /// @param[in] concavePolygon - the concave polygon
      /// @param[out] convexPolygons - the list of convex polygons
      static Output::ExitCodes ConcaveToConvexPolygon(const IPolygon& concavePolygon, list<IPolygon*>& convexPolygons);

      /// Check if a polyhedron is convex
      /// @param[in] polyhedron - the polyhedron
      /// @return true if the input polyhedron is convex
      static bool IsPolyhedronConvex(const IPolyhedron& polyhedron, const double& tolerance);

      /// Function to convert a concave polyhedron to a list of Convex polyhedra
      /// @param[in] concavePolyhedron - the concave polyhedron
      /// @param[out] convexPolyhedra - the list of convex polyhedra
      static Output::ExitCodes ConcaveToConvexPolyhedron(const IPolyhedron& concavePolyhedron, list<IPolyhedron*>& convexPolyhedra);
  };
}

#endif // CONCAVETOCONVEX_H
