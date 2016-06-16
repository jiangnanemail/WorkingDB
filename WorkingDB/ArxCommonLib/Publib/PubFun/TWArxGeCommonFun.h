#pragma once

/*
	������ط�������ѧ�����ȡ�
*/

class ArxCommonLib_CLASS TWArxGeCommonFun
{
public:
	//����:3d 2d��ת����
	//����:
	//���:
	//����:
	//˵��:
	static AcGePoint2d ToPoint2d( IN const AcGePoint3d& Pt3d );
	static AcGePoint3d ToPoint3d( IN const AcGePoint2d& Pt2d );
	static AcGeVector2d ToVector2d( IN const AcGeVector3d& v );
	static AcGePoint3d Z2Zero( IN const AcGePoint3d& Pt3d );
	static void ToPoint2dArray( IN const AcGePoint3dArray& Pt3dAry, OUT AcGePoint2dArray& Pt2dAry );
	static void Point3dAryTransform( IN const AcGeMatrix3d& Mat, IN OUT AcGePoint3dArray& Pt3dAry );
	static void PointdVecto3PointrAry( IN const vector<AcGePoint3d> vPoints, OUT AcGePoint3dArray& Pt3dAry );
	static void Point3dAry2Point3dVector( IN const AcGePoint3dArray& Pt3dAry, OUT vector<AcGePoint3d> vPoints );

	//����:�����ĵ����У������ ָ��λ�õĵ�������С�
	//����:bX ʹ��x ����Y ���֡�
	//���:
	//����:
	//˵��:PtAry����Ҫ��bxһ�µ�������PtMin��PtMaxҪ���� bX��������
	static BOOL GetSubPtAry( IN const AcGePoint3dArray& PtAry, IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, OUT AcGePoint3dArray& PtResAry, IN BOOL bX = TRUE );

	//����:ʹ�ø����ĵ㽫һ�������з�Ϊ�����֡�
	//����:bX ʹ��x ����Y ���֡�
	//���:
	//����:
	//˵��:PtAry����Ҫ��bxһ�µ�������
	static BOOL SplitePtAry( IN const AcGePoint3dArray& PtAry, IN const AcGePoint3d& Pt,OUT AcGePoint3dArray& PtResFrontAry, OUT AcGePoint3dArray& PtResBackAry, IN BOOL bX = TRUE );

	//����:������Ե��Ƿ��ڶ�����ڡ�
	//����:
	//���:
	//����:
	//˵��:
	static BOOL PointInPolygon( IN const AcGePoint3d& PtTest, IN vector<AcGePoint3d>& Polygon );

	//����:�ж�curve�Ƿ��������Χ�н�����
	//����:
	//���:
	//����:
	//˵��:
	static BOOL CurveInsectWithFrame( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, IN const AcGeLineSeg3d& Ln );
	static BOOL CurveInsectWithFrame( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, IN const AcGeCircArc3d& Arc );

	//����:�ж�����ֱ�߶ε�λ�ù�ϵ��
	//����:
	//���:
	//����:1��2�ң�3�ϣ�4���ߡ�����Ϊ����
	//˵��:ֱ�߷��� ln.end - ln.start.
	static int Relation( IN const AcGeLineSeg2d& Ln, IN const AcGePoint2d& Pt );
	static int Relation( IN const AcGePoint2d& ptFrom, IN const AcGePoint2d& ptTo, IN const AcGePoint2d& pt );

};



class ArxCommonLib_CLASS TWArxMathCommonFun
{
public:

	//����:�����������ְ������ľ��������
	//����:nM Ϊָ���ľ���
	//���:
	//����:
	//˵��:nM > 0.
	static double GetDecN( IN double dValue , IN int nM = 10 );

	//����:�������������Ƿ���ȡ�
	//����:
	//���:
	//����:
	//˵��:
	static BOOL IsEquql( IN double d1, IN double d2, double dTol = TW_TOL );

	//����:d1���ڵ���d2.
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GEqual( IN double d1, IN double d2, double dTol = TW_TOL );

	//����:�Ƿ�Ϊ��
	//����:
	//���:
	//����:
	//˵��:
	static BOOL IsZero( IN double d , double dTol  = TW_TOL );

	//����:��->����
	//����:
	//���:
	//����:
	//˵��:
	static double D2R( IN double dDegree );

	//����:�ȷ���->����
	//����:
	//���:
	//����:
	//˵��:
	static double DMS2R( IN const CString& strDFM );

	//����:��ά������ˡ�
	//����:
	//���:
	//����:
	//˵��:
	static double crossProduct( IN const AcGeVector2d& v1, IN const AcGeVector2d& v2 );


	//����:double�Ƚ϶���
	//����:
	//���:
	//����:
	//˵��:
	class CTwRealEqual
	{
	public:
		CTwRealEqual( IN double dTol = TW_TOL );


	bool operator()( IN double d1, IN double d2 ) const;
	protected:

		double     m_dTol;
	};
};


//�������߷���
class ArxCommonLib_CLASS TWArxGeCurveFun
{
public:
	//����:����Ln ��CompCurve�Ľ���
	//����:
	//���:
	//����:
	//˵��:���ص�����ʽ��ֻ������CompCurveȫ��ֱ����ɵġ�
	static BOOL IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeLinearEnt3d& Ln, OUT vector<AcGePoint3d>& vPtIns );
	static BOOL IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeLinearEnt3d& Ln, OUT AcGePoint3d& PtIns );
	static BOOL IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeCircArc3d& Arc, OUT vector<AcGePoint3d>& vPtIns );


	//����:�����������ߡ�
	//����:
	//���:
	//����:
	//˵��:PtAry�ĵ�Ҫ���� ����ComCurve����Ҫ��һ��
	static BOOL GetCompositeCurve( IN const AcGePoint3dArray& PtAry, OUT AcGeCompositeCurve3d& ComCurve );
	static BOOL GetCompositePtAry( IN const AcGeCompositeCurve3d& ComCurve, OUT AcGePoint3dArray& PtAry );

	//����:������������
	//����:vId �켣���ʵ�壻ComCurve �������ߡ�
	//���:
	//����:
	//˵��:��ϵĹ켣ʵ��Ӧ���� polyline��lineʵ�塢arcʵ��
	static BOOL GetCompositeCurve( IN const vector<AcDbObjectId>& vId, OUT AcGeCompositeCurve3d& ComCurve );

	//����:���߽���top�ṹ
	//����:
	//���:
	//����:
	//˵��:ʵ������ polyline��lineʵ�塢arcʵ�塣���ص�ʵ��˳��Ϊʵ������˳��
	//ǰ��˳�����������յ�����ȷ����
	static BOOL GetTopLogic( IN OUT vector<AcDbObjectId>& vId );

	//����:��ֱ��ln1��ln2�ϸ���һ�㣬�Ҿ���Ϊ dv��
	//����:
	//���:
	//����:
	//˵��:
	static BOOL LineInterpolation( IN const AcGePoint3d& Ln1Start, IN const AcGePoint3d& Ln1End, IN const AcGePoint3d& Ln2Start, IN const AcGePoint3d& Ln2End, IN double dv, OUT AcGePoint3d& Ln1Res, OUT AcGePoint3d& Ln2Res );

	//����:������ֱ�߽��㡣
	//����:
	//���:
	//����:
	//˵��:
	static BOOL LineIntersectWith( IN const AcGePoint3d& Pt1, IN const AcGeVector3d& v1, IN const AcGePoint3d& Pt2, IN const AcGeVector3d& v2, OUT AcGePoint3d& PtRes );

	//����:db����ʵ��ת��Ϊge����
	//����:bProject:�Ƿ� pCompCurve ͶӰ��XY-��0��0��0��ƽ�档
	//���:
	//����:
	//˵��:
	static BOOL AcdbCurve2AcGeCurve( IN const AcDbPolyline* pPolyLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE );
	static BOOL AcdbCurve2AcGeCurve( IN const AcDb2dPolyline* pPolyLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE, IN int nStep = 1 );
	static BOOL AcdbCurve2AcGeCurve( IN const AcDbSpline* pSpLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE, IN int nStep = 1 );
	static BOOL AcdbCurve2AcGeCurveEx( IN const AcDbSpline* pSpLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject = FALSE, IN int nStep = 1 );

	//����:����pComCurve��Ptstd�ϵķ�������
	//����:bRight ����ǰ������� ��ƫ ������ƫ��
	//���:
	//����:
	//˵��:
	static BOOL GetCompositeNormal( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, OUT AcGeVector3d& vNormal, BOOL bRight = TRUE );
	
	//����:����pComCurve��Ptstd�ϵķ�������
	//����:
	//���:
	//����:
	//˵��:�˷��������pComCurve�ķ���
	static BOOL GetCompositeDir( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, OUT AcGeVector3d& vDir );
// 	static BOOL GetCompositeNormal( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, IN double dArcLen, IN AcGePoint3d ptBase,  OUT AcGeVector3d& vNormal, BOOL bRight = TRUE );

	//����:��arc��ɢ�ɵ�ļ��ϡ�
	//����:dStep ��ɢ��Ĳ��ࡣ
	//���:
	//����:
	//˵��:
	static BOOL DiscreteArc( IN const AcGeCircArc3d* pArc, OUT vector<AcGePoint3d>& vPts, IN double dStep = 1 );
};

//����δ������
class ArxCommonLib_CLASS CTwPolygon2d
{
public:
	CTwPolygon2d();
	virtual ~CTwPolygon2d();

public:

	//����:���������
	//����:
	//���:
	//����:
	//˵��:
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

	//����:�������ġ�
	//����:
	//���:
	//����:
	//˵��:������͹�Ļ򰼵ļ򵥶����.
	BOOL Center( OUT AcGePoint3d& PtCen ) const;

	//����:�Ƿ�Ϊ͹����Ρ�
	//����:
	//���:
	//����:
	//˵��:����ε����������˳or��ʱ�롣
	BOOL IsConvex() const;

	//����:ʹ�õ㼯������͹�ǡ�
	//����:
	//���:
	//����:
	//˵��:���ص�͹�ǵ㼯���ź���
	static BOOL ConvexHull( IN const vector<AcGePoint3d>& vPts, OUT vector<AcGePoint3d>& vRes );
	BOOL ConvexHull(  IN const vector<AcGePoint3d>& vPts);
	BOOL ConvexHull(  IN const vector<AcGePoint2d>& vPts);

	//����:�Ƿ���
	//����:
	//���:
	//����:
	//˵��:
	BOOL IsLinear() const;

	//����:�жϵ�ǰ�Ƿ���һ����Ч�Ķ����
	//����:
	//���:
	//����:
	//˵��:�ж����� ���������ǵ㣬�����е㲻���ߡ�
	BOOL Valid() const;

	//����:�жϵ�p�Ƿ��ڼ򵥶����poly�ڡ�  
	//����:
	//���:
	//����:
	//˵��:����ο�����͹�Ļ򰼵ģ�����ζ˵��Ѿ�����
	BOOL IsInner( IN const AcGePoint2d& Pt, IN BOOL bBorder = FALSE ) const;

	//����:����
	//����:
	//���:
	//����:
	//˵��:Ӧ����һ��͹����Ρ�
	BOOL Sort( IN BOOL bClockwise = FALSE );
	static BOOL Sort( vector<AcGePoint2d>& vPts, IN BOOL bClockwise = FALSE );

	//����:���㵱ǰ���������ε��в�����
	//����:����͵�ǰ�����Ӧ��͹����Ρ�
	//���:
	//����:
	//˵��:����ֵ��һ����͹����Ρ�
	BOOL Union( IN const CTwPolygon2d& Polygon, OUT CTwPolygon2d& Unioned ) const;

	//����:�󽻼�
	//����:����͵�ǰ�����Ӧ��͹����Ρ�
	//���:
	//����:
	//˵��:����ֵ��һ����͹����Ρ�
	BOOL Intersection( IN const CTwPolygon2d& Polygon, OUT CTwPolygon2d& Inters );

protected:

	//���ڼ���͹�����еĵ�ṹ��atom1�㣬atom2��ǰ�㵽����ļ��ǣ�atom3��ǰ�㵽����ľ��롣
	typedef  TWTripleObjAtom<AcGePoint3d, double, double>        ConvexHullVertex;
	
protected:

	//����
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

	//͹�Ƕ�������
	class _Sort_Compare_ConvexHull
	{
	public:
		bool operator()( IN const ConvexHullVertex& pt1, IN const ConvexHullVertex& pt2 ) const;
	};

protected:
	vector<AcGePoint2d>       m_vPts;                                                              //����εı߽��
};

class CTwRectangle : public CTwPolygon2d
{
public:
	CTwRectangle();
	~CTwRectangle();

public:

	//����:���þ���
	//����:PtMin��PtMaxΪ���ε���С������,kYAxis�˾��εķ���������ֱ�ھ��ο�ߡ�
	//���:
	//����:
	//˵��:vNormal ����[0 ~ PI]
	void Set( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax );


};



//�����ڽ�����
//֧�ֵ�ʵ������ polyline��lineʵ�塢arcʵ�塣
class ArxCommonLib_CLASS CTwCurveAdjustSort
{
public:
	//���������ڽӹ�ϵ
	//��ǰ�ڵ�����һ���ڵ�����ӹ�ϵ��
	enum CTwEnumAdjustJoinType { eNoJoin = 0, eStart_Start, eStart_End, eEnd_Start, eEnd_eEnd };

	//����:�ڽ�����
	//����:
	//���:
	//����:vId��vJoinType����һ�£���λ��һһ��Ӧ��
	//˵��:
	BOOL DoIt( IN OUT vector<AcDbObjectId>& vId, OUT vector<CTwEnumAdjustJoinType>& vJoinType );

protected:

	//����ڵ����ݽṹ
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

	//�����������
	//��ָ������β������½ڵ�
	void Append( Node* pList, Node* pNode ) const;
	//ͷ�����
	void Pushhead( Node* pList, Node* pNode ) const;
	//ָ���ڵ�λ�õĺ�����ӽڵ�
	void Insert( Node* pList, Node* pPos, Node* pNode ) const;
	//�ͷ��ڴ�
	void Free(  Node* pList ) const;


};