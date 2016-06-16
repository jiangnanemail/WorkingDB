#pragma once

/*
	几何相关方法、数学方法等。
*/

class ArxCommonLib_CLASS TWArxGeCommonFun
{
public:
	//功能:3d 2d点转换。
	//输入:
	//输出:
	//返回:
	//说明:
	static AcGePoint2d ToPoint2d( IN const AcGePoint3d& Pt3d );
	static AcGePoint3d ToPoint3d( IN const AcGePoint2d& Pt2d );
	static AcGeVector2d ToVector2d( IN const AcGeVector3d& v );
	static AcGePoint3d Z2Zero( IN const AcGePoint3d& Pt3d );
	static void ToPoint2dArray( IN const AcGePoint3dArray& Pt3dAry, OUT AcGePoint2dArray& Pt2dAry );
	static void Point3dAryTransform( IN const AcGeMatrix3d& Mat, IN OUT AcGePoint3dArray& Pt3dAry );
	static void PointdVecto3PointrAry( IN const vector<AcGePoint3d> vPoints, OUT AcGePoint3dArray& Pt3dAry );
	static void Point3dAry2Point3dVector( IN const AcGePoint3dArray& Pt3dAry, OUT vector<AcGePoint3d> vPoints );

	//功能:给定的点序列，获得在 指定位置的点的子序列。
	//输入:bX 使用x 或者Y 划分。
	//输出:
	//返回:
	//说明:PtAry排序要与bx一致递增排序。PtMin和PtMax要依据 bX递增排序。
	static BOOL GetSubPtAry( IN const AcGePoint3dArray& PtAry, IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, OUT AcGePoint3dArray& PtResAry, IN BOOL bX = TRUE );

	//功能:使用给定的点将一个点序列分为两部分。
	//输入:bX 使用x 或者Y 划分。
	//输出:
	//返回:
	//说明:PtAry排序要与bx一致递增排序。
	static BOOL SplitePtAry( IN const AcGePoint3dArray& PtAry, IN const AcGePoint3d& Pt,OUT AcGePoint3dArray& PtResFrontAry, OUT AcGePoint3dArray& PtResBackAry, IN BOOL bX = TRUE );

	//功能:计算测试点是否在多边形内。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL PointInPolygon( IN const AcGePoint3d& PtTest, IN vector<AcGePoint3d>& Polygon );

	//功能:判定curve是否与给定范围有交集。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL CurveInsectWithFrame( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, IN const AcGeLineSeg3d& Ln );
	static BOOL CurveInsectWithFrame( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, IN const AcGeCircArc3d& Arc );

	//功能:判定点与直线段的位置关系。
	//输入:
	//输出:
	//返回:1左；2右；3上；4共线。其他为错误。
	//说明:直线方向 ln.end - ln.start.
	static int Relation( IN const AcGeLineSeg2d& Ln, IN const AcGePoint2d& Pt );
	static int Relation( IN const AcGePoint2d& ptFrom, IN const AcGePoint2d& ptTo, IN const AcGePoint2d& pt );

};



class ArxCommonLib_CLASS TWArxMathCommonFun
{
public:

	//功能:将给定的数字按给定的精度输出。
	//输入:nM 为指定的精度
	//输出:
	//返回:
	//说明:nM > 0.
	static double GetDecN( IN double dValue , IN int nM = 10 );

	//功能:测试两个数字是否相等。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL IsEquql( IN double d1, IN double d2, double dTol = TW_TOL );

	//功能:d1大于等于d2.
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GEqual( IN double d1, IN double d2, double dTol = TW_TOL );

	//功能:是否为零
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL IsZero( IN double d , double dTol  = TW_TOL );

	//功能:度->弧度
	//输入:
	//输出:
	//返回:
	//说明:
	static double D2R( IN double dDegree );

	//功能:度分秒->弧度
	//输入:
	//输出:
	//返回:
	//说明:
	static double DMS2R( IN const CString& strDFM );

	//功能:二维向量叉乘。
	//输入:
	//输出:
	//返回:
	//说明:
	static double crossProduct( IN const AcGeVector2d& v1, IN const AcGeVector2d& v2 );


	//功能:double比较对象。
	//输入:
	//输出:
	//返回:
	//说明:
	class CTwRealEqual
	{
	public:
		CTwRealEqual( IN double dTol = TW_TOL );


	bool operator()( IN double d1, IN double d2 ) const;
	protected:

		double     m_dTol;
	};
};


//几何曲线方法
class ArxCommonLib_CLASS TWArxGeCurveFun
{
public:
	//功能:计算Ln 与CompCurve的交点
	//输入:
	//输出:
	//返回:
	//说明:返回单点形式的只适用于CompCurve全是直线组成的。
	static BOOL IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeLinearEnt3d& Ln, OUT vector<AcGePoint3d>& vPtIns );
	static BOOL IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeLinearEnt3d& Ln, OUT AcGePoint3d& PtIns );
	static BOOL IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeCircArc3d& Arc, OUT vector<AcGePoint3d>& vPtIns );


	//功能:创建复合曲线。
	//输入:
	//输出:
	//返回:
	//说明:PtAry的点要求与 创建ComCurve所需要求一致
	static BOOL GetCompositeCurve( IN const AcGePoint3dArray& PtAry, OUT AcGeCompositeCurve3d& ComCurve );
	static BOOL GetCompositePtAry( IN const AcGeCompositeCurve3d& ComCurve, OUT AcGePoint3dArray& PtAry );

	//功能:创建复合曲线
	//输入:vId 轨迹组合实体；ComCurve 复合曲线。
	//输出:
	//返回:
	//说明:组合的轨迹实体应当是 polyline、line实体、arc实体
	static BOOL GetCompositeCurve( IN const vector<AcDbObjectId>& vId, OUT AcGeCompositeCurve3d& ComCurve );

	//功能:曲线建立top结构
	//输入:
	//输出:
	//返回:
	//说明:实体类型 polyline、line实体、arc实体。返回的实体顺序为实体拓扑顺序。
	//前后顺序按照曲线起终点属性确定。
	static BOOL GetTopLogic( IN OUT vector<AcDbObjectId>& vId );

	//功能:在直线ln1和ln2上各找一点，且距离为 dv。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL LineInterpolation( IN const AcGePoint3d& Ln1Start, IN const AcGePoint3d& Ln1End, IN const AcGePoint3d& Ln2Start, IN const AcGePoint3d& Ln2End, IN double dv, OUT AcGePoint3d& Ln1Res, OUT AcGePoint3d& Ln2Res );

	//功能:求两条直线交点。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL LineIntersectWith( IN const AcGePoint3d& Pt1, IN const AcGeVector3d& v1, IN const AcGePoint3d& Pt2, IN const AcGeVector3d& v2, OUT AcGePoint3d& PtRes );

	//功能:db曲线实体转换为ge对象
	//输入:bProject:是否将 pCompCurve 投影到XY-（0，0，0）平面。
	//输出:
	//返回:
	//说明:
	static BOOL AcdbCurve2AcGeCurve( IN const AcDbPolyline* pPolyLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE );
	static BOOL AcdbCurve2AcGeCurve( IN const AcDb2dPolyline* pPolyLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE, IN int nStep = 1 );
	static BOOL AcdbCurve2AcGeCurve( IN const AcDbSpline* pSpLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE, IN int nStep = 1 );
	static BOOL AcdbCurve2AcGeCurveEx( IN const AcDbSpline* pSpLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE, IN int nStep = 1 );

	//功能:计算pComCurve在Ptstd上的法向量。
	//输入:bRight 曲线前进方向的 右偏 或者左偏。
	//输出:
	//返回:
	//说明:
	static BOOL GetCompositeNormal( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, OUT AcGeVector3d& vNormal, BOOL bRight = TRUE );
	
	//功能:计算pComCurve在Ptstd上的方向向量
	//输入:
	//输出:
	//返回:
	//说明:此方向相对于pComCurve的方向
	static BOOL GetCompositeDir( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, OUT AcGeVector3d& vDir );
// 	static BOOL GetCompositeNormal( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, IN double dArcLen, IN AcGePoint3d ptBase,  OUT AcGeVector3d& vNormal, BOOL bRight = TRUE );

	//功能:将arc离散成点的集合。
	//输入:dStep 离散点的步距。
	//输出:
	//返回:
	//说明:
	static BOOL DiscreteArc( IN const AcGeCircArc3d* pArc, OUT vector<AcGePoint3d>& vPts, IN double dStep = 1 );
};

//多边形处理对象
class ArxCommonLib_CLASS CTwPolygon2d
{
public:
	CTwPolygon2d();
	virtual ~CTwPolygon2d();

public:

	//功能:创建多边形
	//输入:
	//输出:
	//返回:
	//说明:
	void Set( IN const AcGePoint3dArray& vPts );
	void Set( IN const AcGePoint2dArray& vPts );
	void Set( IN const vector<AcGePoint3d> vPts );
	void Set( IN const vector<AcGePoint2d> vPts );
	void Add( IN const AcGePoint2d& Pt );
	void Add( IN const AcGePoint3d& Pt );

	void Get( OUT AcGePoint3dArray& vPts );
	void Get( OUT AcGePoint2dArray& vPts );
	void Get( OUT vector<AcGePoint3d> vPts );
	void Get( OUT vector<AcGePoint2d> vPts );

public:

	//功能:计算形心。
	//输入:
	//输出:
	//返回:
	//说明:适用于凸的或凹的简单多边形.
	BOOL Center( OUT AcGePoint3d& PtCen ) const;

	//功能:是否为凸多边形。
	//输入:
	//输出:
	//返回:
	//说明:多边形点有序的无论顺or逆时针。
	BOOL IsConvex() const;

	//功能:使用点集，创建凸壳。
	//输入:
	//输出:
	//返回:
	//说明:返回点凸壳点集已排好序。
	static BOOL ConvexHull( IN const vector<AcGePoint3d>& vPts, OUT vector<AcGePoint3d>& vRes );
	BOOL ConvexHull(  IN const vector<AcGePoint3d>& vPts);
	BOOL ConvexHull(  IN const vector<AcGePoint2d>& vPts);

	//功能:是否共线
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL IsLinear() const;

	//功能:判断当前是否是一个有效的多边形
	//输入:
	//输出:
	//返回:
	//说明:判定条件 大于三个角点，且所有点不共线。
	BOOL Valid() const;

	//功能:判断点p是否在简单多边形poly内。  
	//输入:
	//输出:
	//返回:
	//说明:多边形可以是凸的或凹的，多边形端点已经排序。
	BOOL IsInner( IN const AcGePoint2d& Pt, IN BOOL bBorder = FALSE ) const;

	//功能:排序
	//输入:
	//输出:
	//返回:
	//说明:应当是一个凸多边形。
	BOOL Sort( IN BOOL bClockwise = FALSE );
	static BOOL Sort( vector<AcGePoint2d>& vPts, IN BOOL bClockwise = FALSE );

	//功能:计算当前与输入多边形的有并集。
	//输入:输入和当前多边形应当凸多边形。
	//输出:
	//返回:
	//说明:返回值不一定是凸多边形。
	BOOL Union( IN const CTwPolygon2d& Polygon, OUT CTwPolygon2d& Unioned ) const;

	//功能:求交集
	//输入:输入和当前多边形应当凸多边形。
	//输出:
	//返回:
	//说明:返回值不一定是凸多边形。
	BOOL Intersection( IN const CTwPolygon2d& Polygon, OUT CTwPolygon2d& Inters );

protected:

	//用于计算凸壳所有的点结构：atom1点，atom2当前点到极点的极角，atom3当前点到基点的距离。
	typedef  TWTripleObjAtom<AcGePoint3d, double, double>        ConvexHullVertex;
	
protected:

	//排序
	class _Sort_Compare
	{
	public:
		_Sort_Compare( IN const AcGePoint2d& PtOri, IN BOOL bClockwise = FALSE );
		~_Sort_Compare();

	public:
		bool operator()( IN const AcGePoint2d& pt1, IN const AcGePoint2d& pt2 ) const;

	protected:
		AcGePoint2d   m_PtOri;
		BOOL          m_bClockwise;
	};

	//凸壳顶点排序
	class _Sort_Compare_ConvexHull
	{
	public:
		bool operator()( IN const ConvexHullVertex& pt1, IN const ConvexHullVertex& pt2 ) const;
	};

protected:
	vector<AcGePoint2d>       m_vPts;                                                              //多边形的边界点
};

class CTwRectangle : public CTwPolygon2d
{
public:
	CTwRectangle();
	~CTwRectangle();

public:

	//功能:设置矩形
	//输入:PtMin，PtMax为矩形的最小和最大点,kYAxis此矩形的法向量，垂直于矩形宽边。
	//输出:
	//返回:
	//说明:vNormal 方向[0 ~ PI]
	void Set( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax );


};



//曲线邻接排序
//支持的实体类型 polyline、line实体、arc实体。
class ArxCommonLib_CLASS CTwCurveAdjustSort
{
public:
	//相邻曲线邻接关系
	//当前节点与下一个节点的连接关系。
	enum CTwEnumAdjustJoinType { eNoJoin = 0, eStart_Start, eStart_End, eEnd_Start, eEnd_eEnd };

	//功能:邻接排序
	//输入:
	//输出:
	//返回:vId与vJoinType数量一致，按位置一一对应。
	//说明:
	BOOL DoIt( IN OUT vector<AcDbObjectId>& vId, OUT vector<CTwEnumAdjustJoinType>& vJoinType );

protected:

	//定义节点数据结构
	struct Node
	{
		AcDbCurve*                  m_pCurve;
		CTwEnumAdjustJoinType       m_JoinType;
		Node*                       m_pNext;

		Node()
		{
			m_pCurve   = NULL;
			m_pNext    = NULL;
			m_JoinType = eNoJoin;
		}
	};

	//定义链表操作
	//在指定链表尾部添加新节点
	void Append( Node* pList, Node* pNode ) const;
	//头部添加
	void Pushhead( Node* pList, Node* pNode ) const;
	//指定节点位置的后面添加节点
	void Insert( Node* pList, Node* pPos, Node* pNode ) const;
	//释放内存
	void Free(  Node* pList ) const;


};