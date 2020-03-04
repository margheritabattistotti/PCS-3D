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
          static void RunAllTests();
          static void RunPolygonTests();
          static void RunPolyhedronTests();
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
          static void TestPolygon(const IPolygon& concavePolygon, const string& fatherFunctionName);

        public:
          static void TestOne();
          static void TestTwo();
          static void TestThree();
      };

      class ConcavePolyhedronUnitTest
      {
        protected:
          /// Create Polyhedron for test one
          static void CreatePolyhedronTestOne(IPolyhedron& concavePolyhedron);
          /// Test the Polygon
          static void TestPolyhedron(const IPolyhedron& concavePolyhedron, const string& fatherFunctionName);

        public:
          static void TestOne();
      };
    }
  }
}

#endif // GEOMETRYUNITTEST_H
