#include "StdAfx.h"
#include "TWDTM.h"
const double sqrt3 = 1.732050808;
#pragma region CTwVertex

CTwVertex::CTwVertex() : m_Pnt(0.0, 0.0,0 )
{

}

CTwVertex::CTwVertex( const CTwVertex& v ) : m_Pnt(v.m_Pnt)
{

}

CTwVertex::CTwVertex( const AcGePoint3d& pnt ) : m_Pnt(pnt)
{

}

CTwVertex::CTwVertex( double x, double y, double z ) : m_Pnt(x, y, z )
{

}

bool CTwVertex::operator<( const CTwVertex& v ) const
{
	if ( TWArxMathCommonFun::IsZero(m_Pnt.x, v.m_Pnt.x) ) return m_Pnt.x < v.m_Pnt.x;
	return m_Pnt.x < v.m_Pnt.x;
}

bool CTwVertex::operator==( const CTwVertex& v ) const
{
	return m_Pnt == v.m_Pnt;
}

double CTwVertex::GetX() const
{
	return m_Pnt.x;
}

double CTwVertex::GetY() const
{
	return m_Pnt.y;
}

double CTwVertex::GetZ() const
{
	return m_Pnt.z;
}

void CTwVertex::SetX( double x )
{
	m_Pnt.x = x;
}

void CTwVertex::SetY( double y )
{
	m_Pnt.y = y;
}

void CTwVertex::SetZ( double z )
{
	m_Pnt.z = z;
}

const AcGePoint3d& CTwVertex::GetPoint() const
{
	return m_Pnt;
}

#pragma endregion CTwVertex




#pragma region CTwTriangle

CTwTriangle::CTwTriangle( const CTwTriangle& tri )
: m_Center(tri.m_Center), m_R(tri.m_R), m_R2(tri.m_R2)
{
	for (int i = 0; i < 3; i++) m_Vertices[i] = tri.m_Vertices[i];
}

CTwTriangle::CTwTriangle( const CTwVertex* p0, const CTwVertex* p1, const CTwVertex* p2 )
{
	m_Vertices[0] = p0;
	m_Vertices[1] = p1;
	m_Vertices[2] = p2;
	SetCircumCircle();
}

CTwTriangle::CTwTriangle( const CTwVertex * pV )
{
	for (int i = 0; i < 3; i++) m_Vertices[i] = pV++;
	SetCircumCircle();
}

bool CTwTriangle::operator<( const CTwTriangle& tri ) const
{
	if ( m_Center.x == tri.m_Center.x) return m_Center.y < tri.m_Center.y;
	return m_Center.x < tri.m_Center.x;
}

const CTwVertex * CTwTriangle::GetVertex( int i ) const
{
	ASSERT(i >= 0);
	ASSERT(i < 3);
	return m_Vertices[i];
}

bool CTwTriangle::IsLeftOf( cvIterator itVertex ) const
{
	// returns true if * itVertex is to the right of the CTwTriangle's circumcircle
	return itVertex->GetPoint().x > (m_Center.x + m_R);
}

bool CTwTriangle::CCEncompasses( cvIterator itVertex ) const
{
	AcGeVector3d dist = itVertex->GetPoint() - m_Center;		// the distance between v and the circle center
	double dist2 = dist.x * dist.x + dist.y * dist.y;		    // squared
	return dist2 <= m_R2;								        // compare with squared radius
}

void CTwTriangle::SetCircumCircle()
{
	double x0 = m_Vertices[0]->GetX();
	double y0 = m_Vertices[0]->GetY();

	double x1 = m_Vertices[1]->GetX();
	double y1 = m_Vertices[1]->GetY();

	double x2 = m_Vertices[2]->GetX();
	double y2 = m_Vertices[2]->GetY();

	double y10 = y1 - y0;
	double y21 = y2 - y1;

	bool b21zero = TWArxMathCommonFun::IsZero( y21 );

	if (TWArxMathCommonFun::IsZero( y10 ))
	{
		if (b21zero)	// All three vertices are on one horizontal line.
		{
			if (x1 > x0)
			{
				if (x2 > x1) x1 = x2;
			}
			else
			{
				if (x2 < x0) x0 = x2;
			}
			m_Center.x = (x0 + x1) * .5F;
			m_Center.y = y0;
		}
		else	// m_Vertices[0] and m_Vertices[1] are on one horizontal line.
		{
			double m1 = - (x2 - x1) / y21;

			double mx1 = (x1 + x2) * .5F;
			double my1 = (y1 + y2) * .5F;

			m_Center.x = (x0 + x1) * .5F;
			m_Center.y = m1 * (m_Center.x - mx1) + my1;
		}
	}
	else if (b21zero)	// m_Vertices[1] and m_Vertices[2] are on one horizontal line.
	{
		double m0 = - (x1 - x0) / y10;

		double mx0 = (x0 + x1) * .5F;
		double my0 = (y0 + y1) * .5F;

		m_Center.x = (x1 + x2) * .5F;
		m_Center.y = m0 * (m_Center.x - mx0) + my0;
	}
	else	// 'Common' cases, no multiple vertices are on one horizontal line.
	{
		double m0 = - (x1 - x0) / y10;
		double m1 = - (x2 - x1) / y21;

		double mx0 = (x0 + x1) * .5F;
		double my0 = (y0 + y1) * .5F;

		double mx1 = (x1 + x2) * .5F;
		double my1 = (y1 + y2) * .5F;

		m_Center.x = (m0 * mx0 - m1 * mx1 + my1 - my0) / (m0 - m1);
		m_Center.y = m0 * (m_Center.x - mx0) + my0;
	}

	double dx = x0 - m_Center.x;
	double dy = y0 - m_Center.y;

	m_R2 = dx * dx + dy * dy;	// the radius of the circumcircle, squared
	m_R = (double) sqrt(m_R2);	// the proper radius
	m_R2 *= 1.000001f;
}

#pragma endregion CTwTriangle




#pragma region CTwEdge

CTwEdge::CTwEdge( const CTwEdge& e ) 
: m_pV0(e.m_pV0), m_pV1(e.m_pV1)
{

}

CTwEdge::CTwEdge( const CTwVertex * pV0, const CTwVertex * pV1 )
: m_pV0(pV0), m_pV1(pV1)
{

}

bool CTwEdge::operator<( const CTwEdge& e ) const
{
	if (m_pV0 == e.m_pV0) return * m_pV1 < * e.m_pV1;
	return * m_pV0 < * e.m_pV0;
}

#pragma endregion CTwEdge

// Function object to check whether a triangle has one of the vertices in SuperTriangle.
// operator() returns true if it does.
class triangleHasVertex
{
public:
	triangleHasVertex(const CTwVertex SuperTriangle[3]) : m_pSuperTriangle(SuperTriangle)	{}
	bool operator()(const CTwTriangle& tri) const
	{
		for (int i = 0; i < 3; i++)
		{
			const CTwVertex * p = tri.GetVertex(i);
			if (p >= m_pSuperTriangle && p < (m_pSuperTriangle + 3)) return true;
		}
		return false;
	}
protected:
	const CTwVertex * m_pSuperTriangle;
};

// Function object to check whether a triangle is 'completed', i.e. doesn't need to be checked
// again in the algorithm, i.e. it won't be changed anymore.
// Therefore it can be removed from the workset.
// A triangle is completed if the circumcircle is completely to the left of the current vertex.
// If a triangle is completed, it will be inserted in the output set, unless one or more of it's vertices
// belong to the 'super triangle'.
class triangleIsCompleted
{
public:
	triangleIsCompleted(cvIterator itVertex, triangleSet& output, const CTwVertex SuperTriangle[3])
		: m_itVertex(itVertex)
		, m_Output(output)
		, m_pSuperTriangle(SuperTriangle)
	{}
	bool operator()(const CTwTriangle& tri) const
	{
		bool b = tri.IsLeftOf(m_itVertex);

		if (b)
		{
			triangleHasVertex thv(m_pSuperTriangle);
			if (! thv(tri)) m_Output.insert(tri);
		}
		return b;
	}

protected:
	cvIterator m_itVertex;
	triangleSet& m_Output;
	const CTwVertex * m_pSuperTriangle;
};

// Function object to check whether vertex is in circumcircle of triangle.
// operator() returns true if it does.
// The edges of a 'hot' triangle are stored in the edgeSet edges.
class vertexIsInCircumCircle
{
public:
	vertexIsInCircumCircle(cvIterator itVertex, edgeSet& edges) : m_itVertex(itVertex), m_Edges(edges)	{}
	bool operator()(const CTwTriangle& tri) const
	{
		bool b = tri.CCEncompasses(m_itVertex);

		if (b)
		{
			HandleEdge(tri.GetVertex(0), tri.GetVertex(1));
			HandleEdge(tri.GetVertex(1), tri.GetVertex(2));
			HandleEdge(tri.GetVertex(2), tri.GetVertex(0));
		}
		return b;
	}
protected:
	void HandleEdge(const CTwVertex * p0, const CTwVertex * p1) const
	{
		const CTwVertex * pVertex0(NULL);
		const CTwVertex * pVertex1(NULL);

		// Create a normalized edge, in which the smallest vertex comes first.
		if ( *p0 < *p1 )
		{
			pVertex0 = p0;
			pVertex1 = p1;
		}
		else
		{
			pVertex0 = p1;
			pVertex1 = p0;
		}

		CTwEdge e(pVertex0, pVertex1);

		// Check if this edge is already in the buffer
		edgeIterator found = m_Edges.find(e);

		if (found == m_Edges.end()) m_Edges.insert(e);		// no, it isn't, so insert
		else m_Edges.erase(found);							// yes, it is, so erase it to eliminate double edges
	}

	cvIterator    m_itVertex;
	edgeSet&      m_Edges;
};




#pragma region CTwDelaunay

void CTwDelaunay::Triangulate( const vertexSet& vertices, triangleSet& output )
{
	if (vertices.size() < 3) return;	// nothing to handle

	// Determine the bounding box.
	cvIterator itVertex = vertices.begin();

	double xMin = itVertex->GetX();
	double yMin = itVertex->GetY();
	double xMax = xMin;
	double yMax = yMin;

	++itVertex;		// If we're here, we know that vertices is not empty.
	for (; itVertex != vertices.end(); itVertex++)
	{
		xMax = itVertex->GetX();	// Vertices are sorted along the x-axis, so the last one stored will be the biggest.
		double y = itVertex->GetY();
		if (y < yMin) yMin = y;
		if (y > yMax) yMax = y;
	}

	double dx = xMax - xMin;
	double dy = yMax - yMin;

	// Make the bounding box slightly bigger, just to feel safe.
	double ddx = dx * 0.01F;
	double ddy = dy * 0.01F;

	xMin -= ddx;
	xMax += ddx;
	dx += 2 * ddx;

	yMin -= ddy;
	yMax += ddy;
	dy += 2 * ddy;

	// Create a 'super triangle', encompassing all the vertices. We choose an equilateral triangle with horizontal base.
	// We could have made the 'super triangle' simply very big. However, the algorithm is quite sensitive to
	// rounding errors, so it's better to make the 'super triangle' just big enough, like we do here.
	CTwVertex vSuper[3];

	vSuper[0] = CTwVertex(xMin - dy * sqrt3 / 3.0F, yMin);	// Simple highschool geometry, believe me.
	vSuper[1] = CTwVertex(xMax + dy * sqrt3 / 3.0F, yMin);
	vSuper[2] = CTwVertex((xMin + xMax) * 0.5F, yMax + dx * sqrt3 * 0.5F);

	triangleSet workset;
	workset.insert(CTwTriangle(vSuper));

	for (itVertex = vertices.begin(); itVertex != vertices.end(); itVertex++)
	{
		// First, remove all 'completed' triangles from the workset.
		// A triangle is 'completed' if its circumcircle is entirely to the left of the current vertex.
		// Vertices are sorted in x-direction (the set container does this automagically).
		// Unless they are part of the 'super triangle', copy the 'completed' triangles to the output.
		// The algorithm also works without this step, but it is an important optimalization for bigger numbers of vertices.
		// It makes the algorithm about five times faster for 2000 vertices, and for 10000 vertices,
		// it's thirty times faster. For smaller numbers, the difference is negligible.
		tIterator itEnd = remove_if(workset.begin(), workset.end(), triangleIsCompleted(itVertex, output, vSuper));

		edgeSet edges;

		// A triangle is 'hot' if the current vertex v is inside the circumcircle.
		// Remove all hot triangles, but keep their edges.
		itEnd = remove_if(workset.begin(), itEnd, vertexIsInCircumCircle(itVertex, edges));
		workset.erase(itEnd, workset.end());	// remove_if doesn't actually remove; we have to do this explicitly.

		// Create new triangles from the edges and the current vertex.
		for (edgeIterator it = edges.begin(); it != edges.end(); it++)
			workset.insert(CTwTriangle(it->m_pV0, it->m_pV1, & (* itVertex)));
	}

	// Finally, remove all the triangles belonging to the 'super triangle' and move the remaining
	// triangles tot the output; remove_copy_if lets us do that in one go.
	tIterator where = output.begin();
	remove_copy_if(workset.begin(), workset.end(), inserter(output, where), triangleHasVertex(vSuper));
}

void CTwDelaunay::TrianglesToEdges( const triangleSet& triangles, edgeSet& edges )
{
	for (ctIterator it = triangles.begin(); it != triangles.end(); ++it)
	{
		HandleEdge(it->GetVertex(0), it->GetVertex(1), edges);
		HandleEdge(it->GetVertex(1), it->GetVertex(2), edges);
		HandleEdge(it->GetVertex(2), it->GetVertex(0), edges);
	}
}

void CTwDelaunay::HandleEdge( const CTwVertex * p0, const CTwVertex * p1, edgeSet& edges )
{
	const CTwVertex * pV0(NULL);
	const CTwVertex * pV1(NULL);

	if (* p0 < * p1)
	{
		pV0 = p0;
		pV1 = p1;
	}
	else
	{
		pV0 = p1;
		pV1 = p0;
	}

	// Insert a normalized edge. If it's already in edges, insertion will fail,
	// thus leaving only unique edges.
	edges.insert(CTwEdge(pV0, pV1));
}

#pragma endregion CTwDelaunay
