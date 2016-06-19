#pragma once
#include <set>
/*
	三角地面高程生成类
*/

//对高程点的封装，高程点三维，但是在
//建立三角网时使用的平面属性。
#pragma region CTwVertex
class CTwVertex
{
public:
	CTwVertex();
	CTwVertex(const CTwVertex& v);
	CTwVertex(const AcGePoint3d& pnt);
	CTwVertex(double x, double y, double z=0);
	//CTwVertex(int x, int y)		: m_Pnt((double) x, (double) y)	{}

	bool operator<(const CTwVertex& v) const;

	bool operator==(const CTwVertex& v) const;

public:

	double GetX() const;
	double GetY() const;
	double GetZ() const;

	void SetX(double x);
	void SetY(double y);
	void SetZ( double z );

	const AcGePoint3d& GetPoint() const;
protected:
	AcGePoint3d	m_Pnt;
};

typedef set<CTwVertex>                   vertexSet;
typedef set<CTwVertex>::iterator         vIterator;
typedef set<CTwVertex>::const_iterator   cvIterator;

#pragma endregion CTwVertex


//不规则三角形
#pragma region CTwTriangle
class CTwTriangle
{
public:
	CTwTriangle(const CTwTriangle& tri);
	CTwTriangle(const CTwVertex* p0, const CTwVertex* p1, const CTwVertex* p2);
	CTwTriangle(const CTwVertex * pV);

	bool operator<(const CTwTriangle& tri) const;

	const CTwVertex * GetVertex(int i) const;

	bool IsLeftOf(cvIterator itVertex) const;

	bool CCEncompasses(cvIterator itVertex) const;
protected:
	const CTwVertex* m_Vertices[3];	                                                              // 三角形三个顶点。
	AcGePoint3d m_Center;				                                                          // 三角形圆心
	double  m_R;			                                                                      // 外接圆半径
	double  m_R2;			                                                                      // 外接圆半径平方

	void SetCircumCircle();
};

typedef multiset<CTwTriangle>                  triangleSet;
typedef multiset<CTwTriangle>::iterator        tIterator;
typedef multiset<CTwTriangle>::const_iterator  ctIterator;

#pragma endregion CTwTriangle



//边
#pragma region CTwEdge
class CTwEdge
{
public:
	CTwEdge(const CTwEdge& e);
	CTwEdge(const CTwVertex * pV0, const CTwVertex * pV1);

	bool operator<(const CTwEdge& e) const;

	const CTwVertex * m_pV0;
	const CTwVertex * m_pV1;
};

typedef set<CTwEdge>                          edgeSet;
typedef set<CTwEdge>::iterator                edgeIterator;
typedef set<CTwEdge>::const_iterator          cedgeIterator;
#pragma endregion CTwEdge



#pragma region CTwDelaunay
class CTwDelaunay
{
public:
	// Calculate the Delaunay triangulation for the given set of vertices.
	void Triangulate(const vertexSet& vertices, triangleSet& output);

	// Put the edges of the triangles in an edgeSet, eliminating double edges.
	// This comes in useful for drawing the triangulation.
	void TrianglesToEdges(const triangleSet& triangles, edgeSet& edges);
protected:
	void HandleEdge(const CTwVertex * p0, const CTwVertex * p1, edgeSet& edges);
};
#pragma endregion CTwDelaunay