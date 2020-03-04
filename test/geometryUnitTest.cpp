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
      void UnitTest::RunAllTests(const double& tolerance)
      {
        RunPolygonTests(tolerance);
        RunPolyhedronTests(tolerance);
      }
      // ***************************************************************************
      void UnitTest::RunPolygonTests(const double& tolerance)
      {
        Output::PrintLine('-');
        Output::PrintGenericMessage("Polygon tests", true);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestOne(tolerance);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestTwo(tolerance);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestThree(tolerance);
      }
      // ***************************************************************************
      void UnitTest::RunPolyhedronTests(const double& tolerance)
      {
        Output::PrintLine('-');
        Output::PrintGenericMessage("Polyhedron tests", true);
        Output::PrintLine('-');
        ConcavePolyhedronUnitTest::TestOne(tolerance);
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
      void ConcavePolygonUnitTest::TestPolygon(const IPolygon& concavePolygon, const double& tolerance, const string& fatherFunctionName)
      {
        list<IPolygon*> convexPolygons;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolygon(concavePolygon, convexPolygons, tolerance), "%s: ConcaveToConvexPolygon", fatherFunctionName.c_str());

        unsigned int counter = 1;
        for (list<IPolygon*>::iterator it = convexPolygons.begin(); it != convexPolygons.end(); it++)
        {
          if (*it == NULL)
          {
            Output::PrintErrorMessage("Polygon %d is NULL", true, counter);
            continue;
          }

          const IPolygon& convexPolygon = **it;
          Output::Assert(ConcaveToConvex::IsPolygonConvex(convexPolygon, tolerance), "%s: IsPolygonConvex %d", fatherFunctionName.c_str(), counter);

          counter++;
        }
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestOne(const double& tolerance)
      {
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestOne(concavePolygon);
        ConcavePolygonUnitTest::TestPolygon(concavePolygon, tolerance, __func__);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestTwo(const double& tolerance)
      {
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestTwo(concavePolygon);
        ConcavePolygonUnitTest::TestPolygon(concavePolygon, tolerance, __func__);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestThree(const double& tolerance)
      {
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestThree(concavePolygon);
        ConcavePolygonUnitTest::TestPolygon(concavePolygon, tolerance, __func__);
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
      void ConcavePolyhedronUnitTest::TestPolyhedron(const IPolyhedron& concavePolyhedron, const double& tolerance, const string& fatherFunctionName)
      {
        list<IPolyhedron*> convexPolyhedra;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolyhedron(concavePolyhedron, convexPolyhedra, tolerance), "%s: ConcaveToConvexPolyhedron", fatherFunctionName.c_str());

        unsigned int counter = 1;
        for (list<IPolyhedron*>::iterator it = convexPolyhedra.begin(); it != convexPolyhedra.end(); it++)
        {
          if (*it == NULL)
          {
            Output::PrintErrorMessage("Polyhedron %d is NULL", true, counter);
            continue;
          }

          const IPolyhedron& convexPolyhedron = **it;
          Output::Assert(ConcaveToConvex::IsPolyhedronConvex(convexPolyhedron, tolerance), "%s: IsPolyhedronConvex %d", fatherFunctionName.c_str(), counter);

          counter++;
        }
      }
      // ***************************************************************************
      void ConcavePolyhedronUnitTest::TestOne(const double& tolerance)
      {
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestOne(concavePolyhedron);
        ConcavePolyhedronUnitTest::TestPolyhedron(concavePolyhedron, tolerance, __func__);
      }
      // ***************************************************************************
    }
  }
}
