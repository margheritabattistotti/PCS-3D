#include "IntersectorPolygonLine.hpp"

namespace GeDiM
{

	// ***************************************************************************
	IntersectorPolygonLine::IntersectorPolygonLine()
	{
		domainPointer = NULL;
		cellPointer = NULL;
		startPointPointer = NULL;
		tangentPointer = NULL;
		toleranceParallelism = 1.0e-07;
		toleranceIntersection = 1.0e-07;
		indexEdges.reserve(2);
		indexVertices.reserve(2);
		parametricCoordinates.resize(2, 0.0);
		positionBoundaryEdge = -1;
	}

	IntersectorPolygonLine::~IntersectorPolygonLine()
	{

	}

	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::ComputeIntersection()
	{
		if(domainPointer == NULL && cellPointer == NULL)
		{
			Output::PrintErrorMessage("Set a polygon in Intersector ", false);
			return Output::GenericError;
		}

		if(domainPointer == NULL)
		{
			return ComputeIntersectionGenericCell();
		}
		return ComputeIntersectionGenericDomain();
	}
	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::ComputeIntersectionGenericDomain()
	{
		Vector3d tangentVectorEdge, tangentVectorDifference;
		Intersector1D1D intersect;
		unsigned int counterIntersection = 0;
		bool continueIter = true;
		double toll = toleranceIntersection * toleranceIntersection;
		const GenericDomain& domain = *domainPointer;
		const Vector3d& tangentVectorSegment = *tangentPointer;
		const Vector3d& startPoint = *startPointPointer;

		intersect.SetFirstTangentVector(tangentVectorSegment);
		vector<bool> checkEdges(domain.NumberEdges(), false);
		for(unsigned int numPnt = 0; (numPnt < domain.NumberEdges() && continueIter); numPnt++)
		{
			if(checkEdges[numPnt])
				continue;

			const unsigned int& indexFirstVert = domain.EdgeOriginIndex(numPnt);
			const unsigned int& indexSecondVert = domain.EdgeEndIndex(numPnt);
			const Vector3d& firstVert = domain.RotatedVertex(indexFirstVert);
			const Vector3d& secondVert = domain.RotatedVertex(indexSecondVert);

			tangentVectorEdge = secondVert - firstVert;
			tangentVectorDifference = firstVert - startPoint;
			intersect.SetSecondTangentVector(tangentVectorEdge);
			intersect.ComputeIntersectionEdges(tangentVectorSegment, tangentVectorEdge, tangentVectorDifference);

			double normVectorSegment = 1.0/tangentVectorSegment.norm();
			const unsigned int& type = intersect.TypeIntersection();
			checkEdges[numPnt] = true;
			switch(type)
			{
				case Intersector1D1D::IntersectionParallelOnLine:
				case Intersector1D1D::IntersectionParallelOnSegment:
					parametricCoordinates[0] = intersect.FirstParametricCoordinate();
					parametricCoordinates[1] = intersect.SecondParametricCoordinate();
					indexEdges.clear();
					indexVertices.clear();
					indexEdges.push_back(numPnt);
					indexVertices.push_back(indexFirstVert);
					indexVertices.push_back(indexSecondVert);
					intersectionType = TypeIntersection::Boundary;
					continueIter = false;
					counterIntersection = 2;
					break;

				case Intersector1D1D::IntersectionOnLine:
				case Intersector1D1D::IntersectionOnSegment:
					switch(intersect.PositionIntersectionInSecondEdge())
					{
						case Intersector1D1D::Inner:
							parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
							indexEdges.push_back(numPnt);
							intersectionType = TypeIntersection::Inside;
							break;
						case Intersector1D1D::Begin:
						{
							if(counterIntersection)
							{
								parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
								indexEdges.push_back(numPnt);
								indexVertices.push_back(indexFirstVert);
								continueIter = false;
							}
							else
							{
								unsigned int numEdgPrevious = (numPnt == 0)? domain.NumberEdges() - 1 : numPnt -1;
								const unsigned int& indexFirstVertPrev = domain.EdgeOriginIndex(numEdgPrevious);
								const unsigned int& indexSecondVertPrev = domain.EdgeEndIndex(numEdgPrevious);
								const Vector3d& firstVertPrev = domain.RotatedVertex(indexFirstVertPrev);
								const Vector3d& secondVertPrev = domain.RotatedVertex(indexSecondVertPrev);
								Vector3d tangentVectorEdgePrev = firstVertPrev - secondVertPrev;
								Vector3d tangentVectorSegment2(tangentVectorSegment);
								if(tangentVectorSegment2(1) < toll)
									tangentVectorSegment2 = -tangentVectorSegment2;

								double scalar1 = tangentVectorEdge.dot(tangentVectorEdgePrev / tangentVectorEdgePrev.norm());
								double scalar2 = tangentVectorEdge.dot(tangentVectorSegment2 * normVectorSegment);

								if( abs(scalar1 - scalar2) < toll || abs(scalar1 + scalar2) < toll)
								{
									double scalar3 = abs(tangentVectorEdgePrev.dot(tangentVectorSegment));
									indexVertices.push_back(indexFirstVert);
									if(scalar3 > toll)
									{
										parametricCoordinates[0] = 0.0;
										parametricCoordinates[1] = 1.0;
										indexVertices.push_back(indexFirstVertPrev);
									}
									else
									{
										parametricCoordinates[0] = 0.0;
										indexVertices.push_back(indexSecondVertPrev);
									}
									indexEdges.push_back(numEdgPrevious);
									positionIntersection = IntersectorPolygonLine::VertexVertex;
									intersectionType = TypeIntersection::Boundary;
									continueIter = false;
									counterIntersection = 2;
								}
								else if( scalar1 < scalar2)
								{
									parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
									indexEdges.push_back(numPnt);
									indexVertices.push_back(indexFirstVert);
									intersectionType = TypeIntersection::Inside;
								}
								checkEdges[numEdgPrevious] = true;
							}
						}
							break;
						default:
							break;
					}
			}

			if(intersectionType == TypeIntersection::Boundary && counterIntersection == 2)
			{
				positionBoundaryEdge = numPnt;
			}
		}

		if(counterIntersection == 2)
		{
			if(indexVertices.size() == 2)
			{
				if(indexVertices[0] == indexVertices[1])
				{
					intersectionType = TypeIntersection::Tangent;
					positionIntersection = IntersectorPolygonLine::Vertex;
				}
				else
					positionIntersection = IntersectorPolygonLine::VertexVertex;
			}
			else if(indexEdges.size() == 2)
			{
				if(indexVertices.size() == 1)
					positionIntersection = IntersectorPolygonLine::EdgeVertex;
				else
					positionIntersection = IntersectorPolygonLine::EdgeEdge;
			}

			if(parametricCoordinates[0] > parametricCoordinates[1])
			{
				double temp = parametricCoordinates[0];
				parametricCoordinates[0] = parametricCoordinates[1];
				parametricCoordinates[1] = temp;
			}
		}
		else
		{
			intersectionType = TypeIntersection::Tangent;
			positionIntersection = IntersectorPolygonLine::Vertex;
		}
		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::ComputeIntersectionGenericCell()
	{
		Vector3d tangentVectorEdge, tangentVectorDifference;
		Intersector1D1D intersect;
		unsigned int counterIntersection = 0;
		bool continueIter = true;
		double toll = 1.0e-14;
		const GenericCell& cell = *cellPointer;
		const Vector3d& tangentVectorSegment = *tangentPointer;
		const Vector3d& startPoint = *startPointPointer;

		intersect.SetFirstTangentVector(tangentVectorSegment);
		vector<bool> checkEdges(cell.NumberOfPoints(), false);
		for(unsigned int numPnt = 0; (numPnt < cell.NumberOfPoints() && continueIter); numPnt++)
		{
			if(checkEdges[numPnt])
				continue;

			const unsigned int& indexFirstVert = numPnt;
			const unsigned int& indexSecondVert = (numPnt+1)%cell.NumberOfPoints();
			const Vector3d& firstVert = cell.Point(indexFirstVert)->Coordinates();
			const Vector3d& secondVert = cell.Point(indexSecondVert)->Coordinates();

			tangentVectorEdge = secondVert - firstVert;
			tangentVectorDifference = firstVert - startPoint;
			intersect.SetSecondTangentVector(tangentVectorEdge);
			intersect.ComputeIntersectionEdges(tangentVectorSegment, tangentVectorEdge, tangentVectorDifference);

			const unsigned int& type = intersect.TypeIntersection();
			checkEdges[numPnt] = true;
			switch(type)
			{
				case Intersector1D1D::IntersectionParallelOnLine:
				case Intersector1D1D::IntersectionParallelOnSegment:
					parametricCoordinates[0] = intersect.FirstParametricCoordinate();
					parametricCoordinates[1] = intersect.SecondParametricCoordinate();
					indexEdges.clear();
					indexVertices.clear();
					indexEdges.push_back(numPnt);
					indexVertices.push_back(indexFirstVert);
					indexVertices.push_back(indexSecondVert);
					intersectionType = TypeIntersection::Boundary;
					continueIter = false;
					counterIntersection = 2;
					break;

				case Intersector1D1D::IntersectionOnLine:
				case Intersector1D1D::IntersectionOnSegment:
					switch(intersect.PositionIntersectionInSecondEdge())
					{
						case Intersector1D1D::Inner:
						{
							parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
							indexEdges.push_back(numPnt);
							intersectionType = TypeIntersection::Inside;
							break;
						}
						case Intersector1D1D::Begin:
						{
							if(counterIntersection)
							{
								parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
								indexEdges.push_back(numPnt);
								indexVertices.push_back(indexFirstVert);
								continueIter = false;
							}
							else
							{
								const unsigned int& indexVertPrev = (numPnt == 0)? cell.NumberOfPoints() - 1 : numPnt -1;;
								const Vector3d& firstVertPrev = cell.Point(indexVertPrev)->Coordinates();
								const Vector3d& secondVertPrev = cell.Point(numPnt)->Coordinates();
								Vector3d tangentVectorEdgePrev = firstVertPrev - secondVertPrev;
								Vector3d tangentVectorSegment2(tangentVectorSegment);
								if(tangentVectorSegment2(1) < toll)
									tangentVectorSegment2 = -tangentVectorSegment2;

								double scalar1 = tangentVectorEdge.dot(tangentVectorEdgePrev/tangentVectorEdgePrev.norm());
								double scalar2 = tangentVectorEdge.dot(tangentVectorSegment2/tangentVectorSegment2.norm());

								if( abs(scalar1 - scalar2) < toll || abs(scalar1 + scalar2) < toll)
								{
									double scalar3 = abs(tangentVectorEdgePrev.dot(tangentVectorSegment));
									indexVertices.push_back(indexFirstVert);
									if(scalar3 > toll)
									{
										parametricCoordinates[0] = 0.0;
										parametricCoordinates[1] = 1.0;
										indexVertices.push_back(indexVertPrev);
									}
									else
									{
										parametricCoordinates[0] = 0.0;
										indexVertices.push_back(numPnt);
									}
									indexEdges.push_back(indexVertPrev);
									positionIntersection = IntersectorPolygonLine::VertexVertex;
									intersectionType = TypeIntersection::Boundary;
									continueIter = false;
									counterIntersection = 2;
								}
								else if( scalar1 < scalar2)
								{
									parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
									indexEdges.push_back(numPnt);
									indexVertices.push_back(indexFirstVert);
									intersectionType = TypeIntersection::Inside;
								}
								checkEdges[indexVertPrev] = true;
							}
						}
							break;

						default:

							break;
					}
			}
			if(intersectionType == TypeIntersection::Boundary && counterIntersection == 2)
			{
				positionBoundaryEdge = numPnt;
			}
		}

		if(counterIntersection == 2)
		{
			if(indexVertices.size() == 2)
			{
				if(indexVertices[0] == indexVertices[1])
				{
					intersectionType = TypeIntersection::Tangent;
					positionIntersection = IntersectorPolygonLine::Vertex;
				}
				else
					positionIntersection = IntersectorPolygonLine::VertexVertex;
			}
			else if(indexEdges.size() == 2)
			{
				if(indexVertices.size() == 1)
					positionIntersection = IntersectorPolygonLine::EdgeVertex;
				else
					positionIntersection = IntersectorPolygonLine::EdgeEdge;
			}

			if(parametricCoordinates[0] > parametricCoordinates[1])
			{
				double temp = parametricCoordinates[0];
				parametricCoordinates[0] = parametricCoordinates[1];
				parametricCoordinates[1] = temp;
			}
		}
		else
		{
			intersectionType = TypeIntersection::Tangent;
			positionIntersection = IntersectorPolygonLine::Vertex;
		}
		return Output::Success;
	}

	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::Reset()
	{
		parametricCoordinates[0] = 0.0;
		parametricCoordinates[1] = 0.0;
		indexEdges.clear();
		indexVertices.clear();
		intersectionType = NoIntersection;
		positionIntersection = NoPosition;
		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::SetLine(const Vector3d& startPoint, const Vector3d& tangent)
	{
		Reset();
		startPointPointer = &startPoint;
		tangentPointer = &tangent;
		return Output::Success;
	}

	// ***************************************************************************
}
