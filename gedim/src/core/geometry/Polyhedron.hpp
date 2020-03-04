#ifndef POLYHEDRON_HPP
#define POLYHEDRON_HPP

#include "GeometricObject.hpp"
#include "IPolyhedron.hpp"

using namespace std;
using namespace Eigen;
using namespace MainApplication;

namespace GeDiM
{
  class Polyhedron : public GeometricObject, public IPolyhedron
  {
    protected:
      vector<const Vertex*> vertices; ///< Array of domain vertices
			vector< const ISegment* > segments; ///< list of the segments in the polygon
			vector< const IPolygon* > faces; ///< list of the faces in the polygon

    public:
			Polyhedron();
      Polyhedron(const unsigned int& _id) : Polyhedron() { globalId = _id; id = _id;}
			virtual ~Polyhedron();

      inline void Initialize(const unsigned int& numberOfVertices, const unsigned int& numberOfSegments, const unsigned int& numberOfFaces) { }
      inline IPolyhedron* Clone() const { return new Polyhedron(); }
      inline void InitializeVertices(const unsigned int& numberOfVertices) { vertices.reserve(numberOfVertices); }

			inline void AddVertex(const Vertex& vertex) { vertices.push_back(&vertex); }
      inline void AddVertices(const vector<const Vertex*>& _vertices) { vertices = _vertices; }

      inline unsigned int NumberOfVertices() const { return vertices.size(); }
      inline const Vertex& GetVertex(const unsigned int& position) const { return *vertices[position]; }
      inline const vector<const Vertex*>& Vertices() const { return vertices; }

      /// Add a new segment in the polyhedron
      virtual void AddSegment(const ISegment& segment) { }
      /// @return The number of segments of the polyhedron
      virtual unsigned int NumberOfSegments() const { }
      /// @return The segment at position p of the polygon
      virtual const ISegment& GetSegment(const unsigned int& position) const { }
      /// @return The list of segments of the polygon
      virtual const vector<const ISegment*>& Segments() const { }


      /// Add a new faces in the polyhedron
      virtual void AddFace(const IPolygon& face) { }
      /// @return The number of faces of the polyhedron
      virtual unsigned int NumberOfFaces() const { }
      /// @return The face at position p of the polyhedron
      virtual const IPolygon& GetFace(const unsigned int& position) const { }
      /// @return The list of faces of the polyhedron
      virtual const vector<const IPolygon*>& Faces() const { }

      inline unsigned int Dimension() const { return 3; }

      inline Output::ExitCodes ComputeBarycenter() { if(barycenter == NULL) barycenter = new Vertex(); return ComputeBarycenter(*barycenter); }
			Output::ExitCodes ComputeBarycenter(Vertex& _barycenter) const { return Output::UnimplementedMethod; }

      ///Compute Centroid
      /// \brief Compute the centroid of the polygon and save inside the object
      inline Output::ExitCodes ComputeCentroid() { if(centroid == NULL) centroid = new Vertex(); return ComputeCentroid(*centroid); }
      Output::ExitCodes ComputeCentroid(Vertex& _centroid) const { return Output::UnimplementedMethod; }

      ///Compute Measure
      /// \brief Compute the length of the edge and save inside the object
      inline Output::ExitCodes ComputeMeasure() { return ComputeMeasure(measure); }
      Output::ExitCodes ComputeMeasure(double& _measure) const { return Output::UnimplementedMethod; }

      ///Compute radius
      /// \brief Compute the radius of the edge and save inside the object
      inline Output::ExitCodes ComputeRadius() { return ComputeRadius(radius); }
      Output::ExitCodes ComputeRadius(double& _radius) const { return Output::UnimplementedMethod; }

      ///Compute squared radius
      /// \brief Compute the squared radius of the edge and save inside the object
      inline Output::ExitCodes ComputeSquaredRadius() { return ComputeSquaredRadius(squaredRadius); }
      Output::ExitCodes ComputeSquaredRadius(double& _radiusSquared) const { return Output::UnimplementedMethod; }
  };
}
#endif //POLYHEDRON_HPP
