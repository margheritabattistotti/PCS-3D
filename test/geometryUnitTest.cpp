#include "geometryUnitTest.hpp"
#include "Eigen"
#include "Output.hpp"

#include "Polygon.hpp"
#include "Polyhedron.hpp"
#include "ConcaveToConvex.hpp"

using namespace std;
using namespace MainApplication;

namespace GeDiM
{
  namespace UnitTest
  {
    namespace Geometry
    {
      // ***************************************************************************
      void UnitTest::RunAllTests()
      {
        RunPolygonTests();
        RunPolyhedronTests();
      }
      // ***************************************************************************
      void UnitTest::RunPolygonTests()
      {
        Output::PrintLine('-');
        Output::PrintGenericMessage("Polygon tests", true);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestOne();
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestTwo();
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestThree();
      }
      // ***************************************************************************
      void UnitTest::RunPolyhedronTests()
      {
        Output::PrintLine('-');
        Output::PrintGenericMessage("Polyhedron tests", true);
        Output::PrintLine('-');
        ConcavePolyhedronUnitTest::TestOne();
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::CreatePolygonTestOne(IPolygon& concavePolygon)
      {
        unsigned int numVertices = 9, numSegments = 9;

        concavePolygon.Initialize(numVertices, numSegments);

        vector<Vertex> vertices;
        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.9239e+00, 1.3827e+00));
        vertices.push_back(Vertex(1.3827e+00, 1.9239e+00));
        vertices.push_back(Vertex(6.1732e-01, 1.9239e+00));
        vertices.push_back(Vertex(7.6120e-02, 1.3827e+00));
        vertices.push_back(Vertex(1.3827e+00, 6.1732e-01));
        vertices.push_back(Vertex(7.6120e-02, 6.1732e-01));
        vertices.push_back(Vertex(6.1732e-01, 7.6120e-02));
        vertices.push_back(Vertex(1.3827e+00, 7.6120e-02));
        vertices.push_back(Vertex(1.9239e+00, 6.1732e-01));

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolygon.AddVertex(vertices[s]);

        vector<Segment> segments;
        segments.reserve(numSegments);

        for (unsigned int v = 0; v < numVertices; v++)
        {
          segments.push_back(Segment(v + 1));

          ISegment& segment = segments[v];
          const Vertex& origin = vertices[v];
          const Vertex& end = vertices[(v + 1) % numVertices];
          segment.Initialize(origin, end);
        }

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolygon.AddSegment(segments[s]);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::CreatePolygonTestTwo(IPolygon& concavePolygon)
      {
        unsigned int numVertices = 10, numSegments = 10;

        concavePolygon.Initialize(numVertices, numSegments);

        vector<Vertex> vertices;
        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.0000e+00, 2.0000e+00));
        vertices.push_back(Vertex(7.6489e-01, 1.3236e+00));
        vertices.push_back(Vertex(4.8943e-02, 1.3090e+00));
        vertices.push_back(Vertex(6.1958e-01, 8.7639e-01));
        vertices.push_back(Vertex(4.1221e-01, 1.9098e-01));
        vertices.push_back(Vertex(1.0000e+00, 6.0000e-01));
        vertices.push_back(Vertex(1.5878e+00, 1.9098e-01));
        vertices.push_back(Vertex(1.3804e+00, 8.7639e-01));
        vertices.push_back(Vertex(1.9511e+00, 1.3090e+00));
        vertices.push_back(Vertex(1.2351e+00, 1.3236e+00));

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolygon.AddVertex(vertices[s]);

        vector<Segment> segments;
        segments.reserve(numSegments);

        for (unsigned int v = 0; v < numVertices; v++)
        {
          segments.push_back(Segment(v + 1));

          ISegment& segment = segments[v];
          const Vertex& origin = vertices[v];
          const Vertex& end = vertices[(v + 1) % numVertices];
          segment.Initialize(origin, end);
        }

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolygon.AddSegment(segments[s]);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::CreatePolygonTestThree(IPolygon& concavePolygon)
      {
        unsigned int numVertices = 8, numSegments = 8;

        concavePolygon.Initialize(numVertices, numSegments);

        vector<Vertex> vertices;
        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.9239e+00, 1.3827e+00));
        vertices.push_back(Vertex(1.3827e+00, 1.9239e+00));
        vertices.push_back(Vertex(6.1732e-01, 1.9239e+00));
        vertices.push_back(Vertex(7.6120e-02, 1.3827e+00));
        vertices.push_back(Vertex(7.6120e-02, 6.1732e-01));
        vertices.push_back(Vertex(6.1732e-01, 7.6120e-02));
        vertices.push_back(Vertex(1.3827e+00, 7.6120e-02));
        vertices.push_back(Vertex(1.9239e+00, 6.1732e-01));

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolygon.AddVertex(vertices[s]);

        vector<Segment> segments;
        segments.reserve(numSegments);

        for (unsigned int v = 0; v < numVertices; v++)
        {
          segments.push_back(Segment(v + 1));

          ISegment& segment = segments[v];
          const Vertex& origin = vertices[v];
          const Vertex& end = vertices[(v + 1) % numVertices];
          segment.Initialize(origin, end);
        }

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolygon.AddSegment(segments[s]);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestOne()
      {
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestOne(concavePolygon);

        list<IPolygon*> ConvexPolygons;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolygon(concavePolygon, ConvexPolygons), "%s: Test", __func__);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestTwo()
      {
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestTwo(concavePolygon);

        list<IPolygon*> ConvexPolygons;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolygon(concavePolygon, ConvexPolygons), "%s: Test", __func__);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestThree()
      {
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestThree(concavePolygon);

        list<IPolygon*> ConvexPolygons;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolygon(concavePolygon, ConvexPolygons), "%s: Test", __func__);
      }
      // ***************************************************************************
      void ConcavePolyhedronUnitTest::CreatePolyhedronTestOne(IPolyhedron& concavePolyhedron)
      {
        unsigned int numVertices = 5, numSegments = 10, numFaces = 6;

        concavePolyhedron.Initialize(numVertices, numSegments, numFaces);

        vector<Vertex> vertices;
        vertices.reserve(numVertices);

        vertices.push_back(Vertex(1.6462e+00, 2.0335e+00, 2.0229e+00)); // 0
        vertices.push_back(Vertex(1.1764e+00, 6.6632e-01, 1.7380e+00)); // 1
        vertices.push_back(Vertex(4.2294e-01, 3.1275e+00, 2.4979e-01)); // 2
        vertices.push_back(Vertex(2.5080e+00, 2.3502e+00, 1.7143e+00)); // 3
        vertices.push_back(Vertex(2.2820e+00, 1.7009e+00, 1.1686e+00)); // 4

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolyhedron.AddVertex(vertices[s]);

        vector<Segment> segments;
        segments.resize(numSegments);

        segments[0].Initialize(vertices[1], vertices[4]);
        segments[1].Initialize(vertices[4], vertices[3]);
        segments[2].Initialize(vertices[3], vertices[0]);
        segments[3].Initialize(vertices[0], vertices[1]);
        segments[4].Initialize(vertices[0], vertices[4]);
        segments[5].Initialize(vertices[0], vertices[2]);
        segments[6].Initialize(vertices[1], vertices[2]);
        segments[7].Initialize(vertices[3], vertices[2]);
        segments[8].Initialize(vertices[4], vertices[2]);

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolyhedron.AddSegment(segments[s]);

        vector<Polygon> faces;
        faces.resize(numFaces);

        for (unsigned int f = 0; f < numFaces; f++)
          faces[f].Initialize(3, 3);

        faces[0].AddVertex(vertices[1]);
        faces[0].AddVertex(vertices[2]);
        faces[0].AddVertex(vertices[4]);
        faces[0].AddSegment(segments[6]);
        faces[0].AddSegment(segments[8]);
        faces[0].AddSegment(segments[0]);
        faces[1].AddVertex(vertices[4]);
        faces[1].AddVertex(vertices[2]);
        faces[1].AddVertex(vertices[3]);
        faces[1].AddSegment(segments[8]);
        faces[1].AddSegment(segments[7]);
        faces[1].AddSegment(segments[1]);
        faces[2].AddVertex(vertices[1]);
        faces[2].AddVertex(vertices[2]);
        faces[2].AddVertex(vertices[0]);
        faces[2].AddSegment(segments[6]);
        faces[2].AddSegment(segments[5]);
        faces[2].AddSegment(segments[3]);
        faces[3].AddVertex(vertices[0]);
        faces[3].AddVertex(vertices[2]);
        faces[3].AddVertex(vertices[3]);
        faces[3].AddSegment(segments[5]);
        faces[3].AddSegment(segments[7]);
        faces[3].AddSegment(segments[2]);
        faces[4].AddVertex(vertices[1]);
        faces[4].AddVertex(vertices[4]);
        faces[4].AddVertex(vertices[0]);
        faces[4].AddSegment(segments[0]);
        faces[4].AddSegment(segments[4]);
        faces[4].AddSegment(segments[3]);
        faces[5].AddVertex(vertices[4]);
        faces[5].AddVertex(vertices[3]);
        faces[5].AddVertex(vertices[0]);
        faces[5].AddSegment(segments[1]);
        faces[5].AddSegment(segments[2]);
        faces[5].AddSegment(segments[4]);

        for (unsigned int f = 0; f < numFaces; f++)
          concavePolyhedron.AddFace(faces[f]);
      }
      // ***************************************************************************
      void ConcavePolyhedronUnitTest::TestOne()
      {
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestOne(concavePolyhedron);

        list<IPolyhedron*> ConvexPolyhedra;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolyhedron(concavePolyhedron, ConvexPolyhedra), "%s: Test", __func__);
      }
      // ***************************************************************************
    }
  }
}
