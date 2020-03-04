#include "Eigen"
#include "Input.hpp"
#include "EigenExtension.hpp"

#include "geometryUnitTest.hpp"
#include "UnitTestSummary.hpp"

using namespace std;
using namespace Eigen;
using namespace GeDiM;
using namespace UnitTest;

int main()
{
  /// RUN UNIT TESTS
  Geometry::UnitTest::RunPolyhedronTests();
  Output::PrintLine('*');

  /// PRINT SUMMARY
  UnitTestSummary::PrintSummary();
  Output::PrintLine('*');
}
