# PCS Project - 3D

## 3D Problem

Create a C++ function which given an input concave polyhedron it returns the list of convex polyhedra.  

The C++ function to be implemented is the following
```c++
/// Function to convert a concave polyhedron to a list of convex polyhedra
/// @param[in] concavePolyhedron - the concave polyhedron
/// @param[out] convexPolyhedra - the list of convex polyhedra
static Output::ExitCodes ConcaveToConvexPolyhedron(const IPolyhedron& concavePolyhedron, list<IPolyhedron*>& convexPolyhedra);
```

## Tests

### Test One

The following image shows the first 3D test:

![3DTestOne](Images/PolyhedronTestOne.jpg)

## Solution Example

The results is not unique, it depends from the algorithm implemented.

A possible solution of the Test One is reported in the following image:

![3DTestTwo](Images/PolygonTestOne_Result.jpg)

## Class Diagrams

The following class diagrams shows the classes to be used.

### Vertex

![Vertex](Images/ClassDiagramVertex.png)

### Segment

![Segment](Images/ClassDiagramSegment.png)

### Polygon

![Polygon](Images/ClassDiagramPolygon.png)

### Polyhedron

![Polyhedron](Images/ClassDiagramPolyhedron.png)

## Hints

The input / output of the C++ program can be mixed with MATLAB software.
The following hints shows are to be used in MATLAB.

### Generate Other Tests

The following code generates a 3D random polyhedron.

```matlab
npts = 5;
pts = randn(npts, 3);
```

### Show Results

Given a list of points `pts`, it is possible to show them on a plot using the following code:

```matlab
shp = alphaShape(pts);
plot(shp,  'facealpha', 0.5);
```