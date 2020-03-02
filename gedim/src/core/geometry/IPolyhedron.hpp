#ifndef IPOLYHEDRON_HPP
#define IPOLYHEDRON_HPP

#include "IGeometricObject.hpp"
#include "ISegment.hpp"
#include "IPolygon.hpp"

namespace GeDiM
{
  class IPolyhedron : virtual public IGeometricObject
  {
    public:
      virtual ~IPolyhedron() {}

      /// Initialize the polygon with number of vertices segments and faces
      virtual void Initialize(const unsigned int& numberOfVertices, const unsigned int& numberOfSegments, const unsigned int& numberOfFaces) = 0;

      /// Initialize the vertices of the geometric object
      virtual void InitializeVertices(const unsigned int& numberOfVertices) = 0;
      /// Add a single vertex to the geometric object
      virtual void AddVertex(const Vertex& vertex) = 0;
      /// Add a list of vertices to the geometric object
      virtual void AddVertices(const vector<const Vertex*>& _vertices) = 0;

      /// Add a new segment in the polyhedron
      virtual void AddSegment(const ISegment& segment) = 0;
      /// @return The number of segments of the polyhedron
      virtual unsigned int NumberOfSegments() const = 0;
      /// @return The segment at position p of the geometric object
      virtual const ISegment& GetSegment(const unsigned int& position) const = 0;
      /// @return The list of segments of the geometric object
      virtual const vector<const ISegment*>& Segments() const = 0;

      /// Add a new faces in the polyhedron
      virtual void AddFace(const IPolygon& face) = 0;
      /// @return The number of faces of the polyhedron
      virtual unsigned int NumberOfFaces() const = 0;
      /// @return The face at position p of the polyhedron
      virtual const IPolygon& GetFace(const unsigned int& position) const = 0;
      /// @return The list of faces of the polyhedron
      virtual const vector<const IPolygon*>& Faces() const = 0;
  };
}

#endif // IPOLYHEDRON_HPP
