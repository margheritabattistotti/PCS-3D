#ifndef GEOMETRICOBJECT_HPP
#define GEOMETRICOBJECT_HPP

#include <vector>
#include "Eigen"
#include "Output.hpp"
#include "Vertex.hpp"
#include "IGeometricObject.hpp"

using namespace std;
using namespace Eigen;
using namespace MainApplication;

namespace GeDiM
{
  class GeometricObject : virtual public IGeometricObject
	{
		protected:
			unsigned int id;
			unsigned int globalId;

			Vertex* centroid; ///< Centroid of the domain
			Vertex* barycenter; ///< Barycenter of the domain

			double measure; ///< Measure of the domain
			double squaredRadius; ///< Squared radius of the domain (squared max distance between centroid and vertices)
			double radius; ///< Radius of the domain (max distance between centroid and vertices)
		public:
			virtual ~GeometricObject() {}

      void SetGlobalId(const unsigned int& _globalId) override { globalId = _globalId; }
      void SetId(const unsigned int& _id) override { id = _id; }

      const unsigned int& GlobalId() override { return globalId; }
      const unsigned int& Id() override { return id; }

      inline const double& Measure() const override { return measure; }
      inline const Vertex& Centroid() const override { return *centroid; }
      inline const double& Radius() const override { return radius; }
      inline const double& SquaredRadius() const override { return squaredRadius; }
      inline const Vertex& Barycenter() const override { return *barycenter; }
	};
}






#endif // GENERICOBJECT_HPP
