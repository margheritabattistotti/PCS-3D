#ifndef GEOMETRYUNITTEST_H
#define GEOMETRYUNITTEST_H

#include "Output.hpp"
#include "IPolygon.hpp"
#include "IPolyhedron.hpp"

using namespace MainApplication;

namespace GeDiM
{
  namespace UnitTest
  {
    namespace Geometry
    {
      class UnitTest;

      class UnitTest
      {
        public:
          static void RunAllTests(const double& tolerance);
          static void RunPolygonTests(const double& tolerance);
          static void RunPolyhedronTests(const double& tolerance);
      };

      class ConcavePolygonUnitTest
      {
        protected:
          /// Create Polygon for test one
          static void CreatePolygonTestOne(IPolygon& concavePolygon);
          /// Create Polygon for test two
          static void CreatePolygonTestTwo(IPolygon& concavePolygon);
          /// Create Polygon for test three
          static void CreatePolygonTestThree(IPolygon& concavePolygon);
          /// Test the Polygon
          static void TestPolygon(const IPolygon& concavePolygon, const double& tolerance, const string& fatherFunctionName);

        public:
          static void TestOne(const double& tolerance);
          static void TestTwo(const double& tolerance);
          static void TestThree(const double& tolerance);
      };

      class ConcavePolyhedronUnitTest
      {
        protected:
          /// Create Polyhedron for test one
          static void CreatePolyhedronTestOne(IPolyhedron& concavePolyhedron);
          /// Test the Polygon
          static void TestPolyhedron(const IPolyhedron& concavePolyhedron, const double& tolerance, const string& fatherFunctionName);

        public:
          static void TestOne(const double& tolerance);
      };
    }
  }
}

#endif // GEOMETRYUNITTEST_H
