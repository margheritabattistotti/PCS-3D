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
      /// Function to convert a concave polygon to a list of Convex polygons
      /// @param[in] concavePolygon - the concave polygon
      /// @param[out] convexPolygons - the list of convex polygons
      static Output::ExitCodes ConcaveToConvexPolygon(const IPolygon& concavePolygon, list<IPolygon*>& convexPolygons);

      /// Function to convert a concave polyhedron to a list of Convex polyhedra
      /// @param[in] concavePolyhedron - the concave polyhedron
      /// @param[out] convexPolyhedra - the list of convex polyhedra
      static Output::ExitCodes ConcaveToConvexPolyhedron(const IPolyhedron& concavePolyhedron, list<IPolyhedron*>& convexPolyhedra);
  };
}

#endif // CONCAVETOCONVEX_H
