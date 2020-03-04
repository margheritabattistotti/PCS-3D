#include "Intersector2D2D.hpp"

namespace GeDiM
{
    // ***************************************************************************
    Intersector2D2D::Intersector2D2D()
    {
        toleranceParallelism = 1.0e-07;
        toleranceIntersection = 1.0e-07;

        intersectionType = Intersector2D2D::NoInteresection;
        rightHandSide.setZero();
    }


    Intersector2D2D::~Intersector2D2D()
    {

    }
    // ***************************************************************************
    const Output::ExitCodes Intersector2D2D::SetFirstPlane(const Vector3d& planeNormal, const double& planeTranslation)
    {
        matrixNomalVector.row(0) = planeNormal;

        rightHandSide(0) = planeTranslation;

        return Output::Success;
    }

    // ***************************************************************************
    const Output::ExitCodes Intersector2D2D::SetSecondPlane(const Vector3d& planeNormal, const double& planeTranslation)
    {
        matrixNomalVector.row(1) = planeNormal;

        rightHandSide(1) = planeTranslation;

        return Output::Success;
    }

    // ***************************************************************************
    const Output::ExitCodes Intersector2D2D::ComputeIntersection()
    {
        tangentLine = matrixNomalVector.row(0).cross(matrixNomalVector.row(1));
        if(tangentLine.squaredNorm() < toleranceParallelism * toleranceParallelism)
        {
            if(abs(rightHandSide(0) - rightHandSide(1)) < toleranceIntersection)
            {
                intersectionType = Intersector2D2D::Coplanar;
                Output::PrintGenericMessage("Coplanar domains", true);
                return Output::Success;
            }
            else
            {
                intersectionType = Intersector2D2D::NoInteresection;
                Output::PrintDebugMessage("Skew normal vector", true);
                return Output::Success;
            }
        }

        matrixNomalVector.row(2) = tangentLine.normalized();
        pointLine = matrixNomalVector.colPivHouseholderQr().solve(rightHandSide);
        intersectionType = Intersector2D2D::LineIntersection;
        return Output::Success;
    }

    // ***************************************************************************
}
