#include "StdAfx.h"
#include "TWArxGeCommonFun.h"
#include "TWStringPubFun.h"
#include "TWArxCommonFun.h"
#include "TWArxEntityParam.h"
#include <list>

#pragma region TWArxGeCommonFun

AcGePoint2d TWArxGeCommonFun::ToPoint2d( IN const AcGePoint3d& Pt3d )
{
	return AcGePoint2d( Pt3d.x, Pt3d.y );
}

AcGePoint3d TWArxGeCommonFun::ToPoint3d( IN const AcGePoint2d& Pt2d )
{
	return AcGePoint3d( Pt2d.x, Pt2d.y, 0 );
}

AcGeVector2d TWArxGeCommonFun::ToVector2d( IN const AcGeVector3d& v )
{
	return AcGeVector2d( v.x, v.y );
}

AcGePoint3d TWArxGeCommonFun::Z2Zero( IN const AcGePoint3d& Pt3d )
{
	return AcGePoint3d( Pt3d.x, Pt3d.y, 0 );
}

void TWArxGeCommonFun::ToPoint2dArray( IN const AcGePoint3dArray& Pt3dAry, OUT AcGePoint2dArray& Pt2dAry )
{
	int nSize = Pt3dAry.length();
	for ( int i = 0; i < nSize; i++ )
		Pt2dAry.append( ToPoint2d(Pt3dAry[i]) );
}

void TWArxGeCommonFun::Point3dAryTransform( IN const AcGeMatrix3d& Mat, IN OUT AcGePoint3dArray& Pt3dAry )
{
	int nSize = Pt3dAry.length();
	for ( int i = 0; i < nSize; i++ )
		Pt3dAry[i].transformBy( Mat );
}

void TWArxGeCommonFun::PointdVecto3PointrAry( IN const vector<AcGePoint3d> vPoints, OUT AcGePoint3dArray& Pt3dAry )
{
	int nSize = vPoints.size();
	for( int i = 0; i < nSize; i++ )
		Pt3dAry.append( vPoints[i] );
}

void TWArxGeCommonFun::Point3dAry2Point3dVector( IN const AcGePoint3dArray& Pt3dAry, OUT vector<AcGePoint3d> vPoints )
{
	
}


BOOL TWArxGeCommonFun::GetSubPtAry( IN const AcGePoint3dArray& PtAry, IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, OUT AcGePoint3dArray& PtResAry, IN BOOL bX /*= TRUE */ )
{
	AcGePoint3dArray PtAryPre, PtAryBack;
	if( !SplitePtAry(PtAry, PtMin, PtAryPre, PtAryBack, bX) ) return FALSE;

	if( !SplitePtAry( PtAryBack, PtMax, PtResAry, PtAryPre, bX) ) return FALSE;
	
	return TRUE;
}

BOOL TWArxGeCommonFun::SplitePtAry( IN const AcGePoint3dArray& PtAry, IN const AcGePoint3d& Pt,OUT AcGePoint3dArray& PtResFrontAry, OUT AcGePoint3dArray& PtResBackAry, IN BOOL bX /*= TRUE */ )
{
	int nLen = PtAry.length();
	if( nLen < 2 ) return FALSE;

	PtResFrontAry.removeAll();
	PtResBackAry.removeAll();

	AcGeLine3d Ln; 

	//两个端点特殊情况
	if( bX )
	{
		if( Pt.x <= PtAry.first().x )
		{
			PtResBackAry.append( PtAry );
			return TRUE;
		}
		else if( Pt.x >= PtAry.last() .x )
		{
			PtResFrontAry.append( PtAry );
			return TRUE;
		}

		Ln.set( Pt, AcGeVector3d::kYAxis );
	}
	else
	{
		if( Pt.y <= PtAry.first().y )
		{
			PtResBackAry.append( PtAry );
			return TRUE;
		}
		else if( Pt.y >= PtAry.last().y )
		{
			PtResFrontAry.append( PtAry );
			return TRUE;
		}

		Ln.set( Pt, AcGeVector3d::kXAxis);
	}

	AcGeCompositeCurve3d CompCurve;
	if( !TWArxGeCurveFun::GetCompositeCurve(PtAry, CompCurve) ) return FALSE;
    
	AcGePoint3d PtIns;
	if( !TWArxGeCurveFun::IntersectWith(CompCurve, Ln, PtIns) ) return FALSE;


	for ( int i = 0; i < nLen; i++ )
	{
		AcGePoint3d PtTemp = PtAry[i];
		if( bX )
		{
			if( PtTemp.x <= Pt.x )
				PtResFrontAry.append( PtTemp );
			else
				PtResBackAry.append( PtTemp );

		}
	}

	if( PtResFrontAry.last() != PtIns )
		PtResFrontAry.append( PtIns );
	if( PtResBackAry.first() != PtIns )
		PtResBackAry.insertAt( 0, PtIns );
	return TRUE;
}

BOOL TWArxGeCommonFun::CurveInsectWithFrame( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, IN const AcGeLineSeg3d& Ln )
{
	AcGePoint3d PtLB = PtMin;
	AcGePoint3d ptRT = PtMax;
	AcGePoint3d PtLT( PtLB.x, ptRT.y, 0 );
	AcGePoint3d PtRB( ptRT.x, PtLB.y, 0 );

	vector<AcGePoint3d> vPts;
	vPts.push_back( PtLT );
	vPts.push_back( ptRT );
	vPts.push_back( PtRB );
	vPts.push_back( PtLB );

// 	{
// 		for ( int i = 0; i < 4; i++ )
// 		{
// 			ads_point Pt;
// 			ads_getpoint( asDblArray(vPts[i]), NULL, Pt );
// 		}
// 	}
	
	BOOL bStart = PointInPolygon( Ln.startPoint(), vPts );
	BOOL bEnd   = PointInPolygon( Ln.endPoint(), vPts );

	//其中一个点在范围之内，则有交集。
	if( bStart == TRUE || bEnd == TRUE ) return TRUE;


	AcGePoint3d PtIns;
	AcGeLineSeg3d lnLeft( PtLB, PtLT );
	if( Adesk::kTrue == Ln.intersectWith(lnLeft, PtIns) ) return TRUE;

	AcGeLineSeg3d lnTop( PtLT, ptRT );
	if( Adesk::kTrue == Ln.intersectWith(lnTop, PtIns) ) return TRUE;

	AcGeLineSeg3d lnRight( PtRB, ptRT );
	if( Adesk::kTrue == Ln.intersectWith(lnRight, PtIns) ) return TRUE;

	AcGeLineSeg3d lnButtom( PtRB, PtLB );
	if( Adesk::kTrue == Ln.intersectWith(lnButtom, PtIns) ) return TRUE;

	return FALSE;
}

BOOL TWArxGeCommonFun::CurveInsectWithFrame( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax, IN const AcGeCircArc3d& Arc )
{
	AcGePoint3d PtLB = PtMin;
	AcGePoint3d ptRT = PtMax;
	AcGePoint3d PtLT( PtLB.x, ptRT.y, 0 );
	AcGePoint3d PtRB( ptRT.x, PtLB.y, 0 );

	vector<AcGePoint3d> vPts;
	vPts.push_back( PtLT );
	vPts.push_back( ptRT );
	vPts.push_back( PtRB );
	vPts.push_back( PtLB );

	BOOL bStart = PointInPolygon( Arc.startPoint(), vPts );
	BOOL bEnd   = PointInPolygon( Arc.endPoint(), vPts );

	//其中一个点在范围之内，则有交集。
	if( bStart == TRUE || bEnd == TRUE ) return TRUE;


	AcGePoint3d PtIns1, PtIns2;
	int nNum = 0;
	AcGeLineSeg3d lnLeft( PtLB, PtLT );
	if( Adesk::kTrue == Arc.intersectWith(lnLeft, nNum, PtIns1, PtIns2) ) return TRUE;

	AcGeLineSeg3d lnTop( PtLT, ptRT );
	if( Adesk::kTrue == Arc.intersectWith( lnTop, nNum, PtIns1, PtIns2) ) return TRUE;

	AcGeLineSeg3d lnRight( PtRB, ptRT );
	if( Adesk::kTrue == Arc.intersectWith(lnRight, nNum, PtIns1, PtIns2) ) return TRUE;

	AcGeLineSeg3d lnButtom( PtRB, PtLB );
	if( Adesk::kTrue == Arc.intersectWith(lnButtom, nNum, PtIns1, PtIns2) ) return TRUE;

	return FALSE;
}

BOOL TWArxGeCommonFun::PointInPolygon( IN const AcGePoint3d& PtTest, IN vector<AcGePoint3d>& Polygon )
{
	if( Polygon.size() < 3 ) return FALSE;

	int   i    = 0;
	int   j    = Polygon.size() - 1 ;
	BOOL  bRes = FALSE     ;

	for ( i = 0;i < Polygon.size(); i++ ) 
	{
		AcGePoint3d PtI = Polygon[i];
		AcGePoint3d PtJ = Polygon[j];

		if( (PtI.y < PtTest.y && PtJ.y >= PtTest.y || PtJ.y < PtTest.y &&PtI.y >= PtTest.y) && (PtI.x <= PtTest.x || PtJ.x <= PtTest.x) )
		{
				if( PtI.x+(PtTest.y-PtI.y)/(PtJ.y-PtI.y)*(PtJ.x-PtI.x) < PtTest.x )
					bRes = !bRes;

		}

		j=i;
	}

	return bRes; 
}

int TWArxGeCommonFun::Relation( IN const AcGeLineSeg2d& Ln, IN const AcGePoint2d& Pt )
{
// 	AcGePoint2d PtStart = Ln.startPoint();
// 	AcGePoint2d PtEnd   = Ln.endPoint();
// 	double dValue = ( Pt.x - PtStart.x ) * ( PtEnd.y - PtStart.y ) -( Pt.y - PtStart.y ) * ( PtEnd.x - PtStart.x );
// 	if( dValue < 0 )      return 1;                 //左
// 	else if( dValue > 0 ) return 2;                 //右
// 	else
// 	{
// 		if( TWArxMathCommonFun::IsEquql( PtStart.distanceTo(Pt)+Pt.distanceTo(PtEnd), PtStart.distanceTo(PtEnd)) )
// 			return  3;                              //线段上
// 		else return 4;                              //共线
// 	}
	return Relation( Ln.startPoint(), Ln.endPoint(), Pt );
}

int TWArxGeCommonFun::Relation( IN const AcGePoint2d& ptFrom, IN const AcGePoint2d& ptTo, IN const AcGePoint2d& Pt )
{
	AcGePoint2d PtStart = ptFrom;
	AcGePoint2d PtEnd   = ptTo;
	double dValue = ( Pt.x - PtStart.x ) * ( PtEnd.y - PtStart.y ) -( Pt.y - PtStart.y ) * ( PtEnd.x - PtStart.x );
	if( dValue < 0 )      return 1;                 //左
	else if( dValue > 0 ) return 2;                 //右
	else
	{
		if( TWArxMathCommonFun::IsEquql( PtStart.distanceTo(Pt)+Pt.distanceTo(PtEnd), PtStart.distanceTo(PtEnd)) )
			return  3;                              //线段上
		else return 4;                              //共线
	}
}

#pragma endregion TWArxGeCommonFun


#pragma region TWArxMathCommonFun
BOOL TWArxMathCommonFun::IsZero( IN double d , double dTol /*= TW_TOL */ )
{
	return IsEquql( d, 0, dTol );
}

BOOL TWArxMathCommonFun::IsEquql( IN double d1, IN double d2, double dTol /*= TW_TOL */ )
{
	if( fabs( d1 - d2 ) < dTol )
		return TRUE;
	return FALSE;
}


BOOL TWArxMathCommonFun::GEqual( IN double d1, IN double d2, double dTol /*= TW_TOL */ )
{
	if( IsEquql(d1, d2) ) return TRUE;
	return d1 > d2;
}


double TWArxMathCommonFun::GetDecN( IN double dValue , IN int nM /*= 10 */ )
{
	return (int(0.5 + dValue / nM)) * nM;
}

double TWArxMathCommonFun::D2R( IN double dDegree )
{
	return dDegree * TW_PI / 180;
}

double TWArxMathCommonFun::DMS2R( IN const CString& strDMS )
{
	CString strD = _T("°");
	CString strM = _T("\'");
	CString strS = _T("\"");
	vector<CString> vString;
	StringCommonFun::StringResolving( strDMS, strD,vString );
	if( vString.empty() ) return 0.0;

	//度
	if( vString.size() == 1 )
		return D2R( _tstof(vString[0]) );

	double dD = _tstof( vString[0] );

	//分
	CString str = vString[1];
	vString.clear();
	StringCommonFun::StringResolving( str, strM, vString );
	if( vString.empty() ) return dD;
	if( vString.size() == 1 )
		return D2R( dD + _tstof(vString[0])/60 );

	dD += _tstof(vString[0])/60;

	//秒
	str = vString[1];
	vString.clear();
	StringCommonFun::StringResolving( str, strS, vString );
	if( vString.empty() ) return dD;
	return D2R( dD + _tstof(vString[0])/3600 );
}

double TWArxMathCommonFun::crossProduct( IN const AcGeVector2d& v1, IN const AcGeVector2d& v2 )
{
	return (v1.x * v2.y - v2.x * v1.y);
}


TWArxMathCommonFun::CTwRealEqual::CTwRealEqual( IN double dTol /* = TW_TOL */ )
{
	m_dTol = dTol;
}

bool TWArxMathCommonFun::CTwRealEqual::operator()( IN double d1, IN double d2 ) const
{
	return IsEquql( d1, d2, m_dTol );
}

#pragma endregion TWArxMathCommonFun




#pragma region TWArxGeCurveFun

BOOL TWArxGeCurveFun::IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeLinearEnt3d& Ln, OUT vector<AcGePoint3d>& vPtIns )
{
	AcGeVoidPointerArray VoidPtrAry;
	CompCurve.getCurveList( VoidPtrAry );

	int nCount = VoidPtrAry.length();
	if( nCount < 1 ) return FALSE;

	for ( int i = 0; i < nCount; i++ )
	{
		AcGeCurve3d* pCur = (AcGeCurve3d*)( VoidPtrAry[i] );
		if( pCur == NULL ) continue;

		if( pCur->type() == AcGe::kLineSeg3d )
		{
			AcGePoint3d Pt;
			AcGeLineSeg3d* lnSeg = (AcGeLineSeg3d*)pCur;
			{
				AcGePoint3d PtSt, PtEnd;
				Ln.hasStartPoint( PtSt );
				Ln.hasEndPoint( PtEnd );
				if( lnSeg->isOn( PtSt) )
				{
					int a = 0;
				}
				if( lnSeg->isOn( PtEnd) )
				{
					int a = 0;
				}

				AcGeLine3d Lntem( PtSt, PtEnd );
				AcGePoint3d Pttt;
				if( Adesk::kTrue == lnSeg->intersectWith( Lntem, Pttt ) )
				{
					int ww  = 0;
				}
			}
			if( lnSeg->intersectWith( Ln, Pt) == Adesk::kTrue )
				vPtIns.push_back( Pt );
		}
		else if( pCur->type() == AcGe::kCircArc3d )
		{
			AcGeCircArc3d* pArc = ( AcGeCircArc3d* )pCur;
			int nNum = 0;
			AcGePoint3d Pt1, Pt2;
			if( pArc->intersectWith(Ln, nNum, Pt1, Pt2) == Adesk::kTrue )
			{
				if( nNum >= 1 ) vPtIns.push_back( Pt1 );
				if( nNum == 2 ) vPtIns.push_back( Pt2 );
			}
		}
	}

	return ( vPtIns.size() == 0 ) ? FALSE : TRUE;
}

BOOL TWArxGeCurveFun::IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeLinearEnt3d& Ln, OUT AcGePoint3d& PtIns )
{
	AcGeVoidPointerArray VoidPtrAry;
	CompCurve.getCurveList( VoidPtrAry );

	int nCount = VoidPtrAry.length();
	if( nCount < 1 ) return FALSE;

	for ( int i = 0; i < nCount; i++ )
	{
		AcGeCurve3d* pCur = (AcGeCurve3d*)( VoidPtrAry[i] );
		if( pCur == NULL ) continue;

		if( pCur->type() == AcGe::kLineSeg3d )
		{
			AcGeLineSeg3d* lnSeg = (AcGeLineSeg3d*)pCur;
// 			{
// 				AcGePoint3d Ptss = lnSeg->startPoint();
// 				AcGePoint3d PtEE = lnSeg->endPoint();
// 				int  aaaa = 0;
// 			}
			if( lnSeg->intersectWith( Ln, PtIns) == Adesk::kTrue )
				return TRUE;
		}
	}

	return FALSE;
}

BOOL TWArxGeCurveFun::IntersectWith( IN const AcGeCompositeCurve3d& CompCurve, IN const AcGeCircArc3d& Arc, OUT vector<AcGePoint3d>& vPtIns )
{
	AcGeVoidPointerArray VoidPtrAry;
	CompCurve.getCurveList( VoidPtrAry );

	int nCount = VoidPtrAry.length();
	if( nCount < 1 ) return FALSE;

	for ( int i = 0; i < nCount; i++ )
	{
		AcGeCurve3d* pCur = (AcGeCurve3d*)( VoidPtrAry[i] );
		if( pCur == NULL ) continue;

		if( pCur->type() == AcGe::kLineSeg3d )
		{
			
			AcGeLineSeg3d* lnSeg = (AcGeLineSeg3d*)pCur;
			int nNum = 0;
			AcGePoint3d Pt1, Pt2;
			if( Arc.intersectWith(*lnSeg, nNum, Pt1, Pt2) == Adesk::kTrue )
			{
				if( nNum >= 1 ) vPtIns.push_back( Pt1 );
				if( nNum == 2 ) vPtIns.push_back( Pt2 );
			}
		}
		else if( pCur->type() == AcGe::kCircArc3d )
		{
			AcGeCircArc3d* pArc = ( AcGeCircArc3d* )pCur;
			int nNum = 0;
			AcGePoint3d Pt1, Pt2;
			if( pArc->intersectWith(Arc, nNum, Pt1, Pt2) == Adesk::kTrue )
			{
				if( nNum >= 1 ) vPtIns.push_back( Pt1 );
				if( nNum == 2 ) vPtIns.push_back( Pt2 );
			}
		}
	}

	return ( vPtIns.size() == 0 ) ? FALSE : TRUE;
}
BOOL TWArxGeCurveFun::LineInterpolation( IN const AcGePoint3d& Ln1Start, IN const AcGePoint3d& Ln1End, IN const AcGePoint3d& Ln2Start, IN const AcGePoint3d& Ln2End, IN double dv, OUT AcGePoint3d& Ln1Res, OUT AcGePoint3d& Ln2Res )
{

// 	(y-y1)/(y2-y1)=(x-x1)/(x2-x1)
// 		(y-y1)(x2-x1)=(x-x1)(y2-y1)
// 		(y2-y1)x-(x2-x1)y-x1(y2-y1)+y1(x2-x1)=0
	double A1 = ( Ln1End.y - Ln1Start.y );
	double B1 = ( Ln1End.x - Ln1Start.x );
	double C1 = -Ln1Start.x*A1 +  Ln1Start.y * B1;

	double A2 = ( Ln2End.y - Ln2Start.y );
	double B2 = ( Ln2End.x - Ln2Start.x );
	double C2 = -Ln2Start.x*A2 +  Ln2Start.y * B2;

	double dX = ( B2 * C1 - B1 * C2 + dv * B1 * B2 ) / ( A2 * B1 - A1 * B2 );

	double dY = (A1* dX + C1) / B1;
	
	Ln1Res.set( dX, dY, 0 );
	Ln2Res.set( dX, dv + dY, 0 );

	return TRUE;
}

BOOL TWArxGeCurveFun::LineIntersectWith( IN const AcGePoint3d& Pt1, IN const AcGeVector3d& v1, IN const AcGePoint3d& Pt2, IN const AcGeVector3d& v2, OUT AcGePoint3d& PtRes )
{
	AcGeLine3d Ln1( Pt1, v1 );
	AcGeLine3d Ln2( Pt2, v2 );
	if( Ln2.intersectWith( Ln1, PtRes ) )
		return TRUE;
	return FALSE;
}

BOOL TWArxGeCurveFun::GetCompositeCurve( IN const AcGePoint3dArray& PtAry, OUT AcGeCompositeCurve3d& ComCurve )
{
	int nLen = PtAry.length();
	if( nLen < 2 ) return FALSE;

	AcGeIntArray         IntAry;
	AcGeVoidPointerArray GePtrAry;
	for ( int i = 1; i < nLen; i++ )
	{
		AcGePoint3d PtPre = PtAry[i-1];
		AcGePoint3d PtCur = PtAry[i];
		AcGeLineSeg3d* pLine = new AcGeLineSeg3d( PtPre, PtCur );
		GePtrAry.append( pLine );
		IntAry.append( 1 );
	}
	
	ComCurve.setCurveList( GePtrAry, IntAry );
	return TRUE;
}

// BOOL TWArxGeCurveFun::GetCompositeCurve( IN vector<AcDbObjectId>& vId, OUT AcGeCompositeCurve3d& ComCurve )
// {
// 	int nSize = vId.size();
// 	if( nSize == 0 ) return FALSE;
// 
// 	//计算邻接结构
// 	vector<AcDbCurve*> vDbCurve;
// 	for ( int i = 0; i < nSize; i++ )
// 	{
// 
// 	}
// 
// 	AcGeVoidPointerArray curveList;
// 	AcGeIntArray         isOwnerOfCurves;
// 	
// }

BOOL TWArxGeCurveFun::GetCompositePtAry( IN const AcGeCompositeCurve3d& ComCurve, OUT AcGePoint3dArray& PtAry )
{
	AcGeVoidPointerArray curveList;
	ComCurve.getCurveList( curveList );
	int nLen = curveList.length();
	if( nLen == 0 ) return FALSE;
	
	AcGeCurve3d* pCur = ( AcGeCurve3d*)curveList[0];
	AcGePoint3d Pt;
	if( pCur->hasStartPoint( Pt ) )
		PtAry.append( Pt );

	for ( int i = 0; i < nLen; i++ )
	{
		pCur = ( AcGeCurve3d*)curveList[i];
		if( pCur->hasEndPoint( Pt ) )
			PtAry.append( Pt );
	}

	return TRUE;
	
}

BOOL TWArxGeCurveFun::AcdbCurve2AcGeCurve( IN const AcDbPolyline* pPolyLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject /*= FALSE*/ )
{
	AcGeLineSeg3d *pLine = NULL;
	AcGeCircArc3d *pArc  = NULL;
	AcGeVoidPointerArray GeCurves;
	AcGeIntArray         IntAry;

	for( int i = 0; i < pPolyLine->numVerts(); i++ )
	{
		if( pPolyLine->segType(i) == AcDbPolyline::kLine )
		{
			pLine = new AcGeLineSeg3d;
			pPolyLine->getLineSegAt(i, *pLine);
			GeCurves.append(pLine);
			IntAry.append( 1 );
		}
		else if( pPolyLine->segType(i) == AcDbPolyline::kArc )
		{
			pArc = new AcGeCircArc3d;
			pPolyLine->getArcSegAt(i, *pArc);
			GeCurves.append(pArc);
			IntAry.append( 1 );
		}
	}
	if( GeCurves.length() != IntAry.length() || GeCurves.length() == 0 ) return FALSE;
	pCompCurve =  new AcGeCompositeCurve3d( GeCurves, IntAry );
	
	//需要投影
	if( bProject )
	{
		//如果标高为0就不用投影了。
		double dElev = pPolyLine->elevation();
		if( !TWArxMathCommonFun::IsZero(dElev) )
		{
			AcGePlane Plan( AcGePoint3d::kOrigin, AcGeVector3d::kZAxis );
			AcGeEntity3d* pEnt = pCompCurve->orthoProject( Plan );
			TWFreePtr( pCompCurve ); 

			if( pEnt->type() != AcGe::kCompositeCrv3d )
			{
				TWFreePtr( pEnt );
				return FALSE;
			}

			pCompCurve = (AcGeCompositeCurve3d*)pEnt;
		}
	}
	
	return TRUE;
}


BOOL TWArxGeCurveFun::AcdbCurve2AcGeCurve( IN const AcDb2dPolyline* pPolyLine, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject /*= FALSE*/, IN int nStep /*= 1 */ )
{
	if( pPolyLine == NULL ) return FALSE;

	AcDb::Poly2dType type = pPolyLine->polyType();
	AcDbPolyline * pLwpoly = NULL;
	Acad::ErrorStatus es;
	if ( (type==AcDb::k2dSimplePoly)||(type==AcDb::k2dFitCurvePoly) )
	{
		pLwpoly = new AcDbPolyline;
		es      = pLwpoly->convertFrom((AcDbEntity *&)pPolyLine,Adesk::kFalse);
		if ( es!=Acad::eOk )
		{
			delete pLwpoly;
			pLwpoly=NULL;
			return FALSE;
		}
		TWArxEntityFun::PostModelSpace( pLwpoly, AcDbObjectId() );
		BOOL bRet  = AcdbCurve2AcGeCurve( pLwpoly, pCompCurve, bProject );
		pLwpoly->close();
		return bRet;
	}
	else
	{
		AcGeVoidPointerArray GeCurves;
		AcGeIntArray intAry;
		AcGePoint3d pt1;
		AcGePoint3d pt2;
		double Param;
		pPolyLine->getEndParam(Param);
		AcGeLineSeg3d *pLine = NULL;
		for (int i= 0; i < (int)Param; i++ )
		{
			pPolyLine->getPointAtParam( i, pt1 );
			pPolyLine->getPointAtParam( i+1, pt2 );
			if( bProject )
				pt2.z = pt1.z = 0;

			intAry.append( 1 );
			pLine = new AcGeLineSeg3d( pt1, pt2 );
			GeCurves.append(pLine);
		}

		pCompCurve = new AcGeCompositeCurve3d( GeCurves, intAry );
	}
	return TRUE;
}

BOOL TWArxGeCurveFun::AcdbCurve2AcGeCurve( IN const AcDbSpline* pSpline, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject /*= FALSE*/, IN int nStep /*= 1 */ )
{
	if( pSpline == NULL ) return FALSE;

	AcGePoint3d PtEnd;
	pSpline->getEndPoint( PtEnd );
	double dLen = 0;
	
	if( pSpline->isClosed() )
	{
		double dParam = 0;
		pSpline->getEndParam( dParam );
		pSpline->getDistAtParam( dParam, dLen );

	}
	else
		pSpline->getDistAtPoint( PtEnd, dLen );

	AcGePoint3dArray PtAry;

	double dDist = 0;
	while( dDist < dLen )
	{
		AcGePoint3d Pt;
		if( Acad::eOk == pSpline->getPointAtDist( dDist, Pt ) )
		{
			if( bProject )
				Pt.z = 0;
			PtAry.append( Pt );
		}

		dDist += nStep;
	}

	if( !PtAry.isEmpty() && PtEnd != PtAry.last() )
	{
		if( bProject )
			PtEnd.z = 0;
		PtAry.append( PtEnd );
	}

	pCompCurve = new AcGeCompositeCurve3d;

	GetCompositeCurve( PtAry, *pCompCurve );

	return TRUE;
}

BOOL TWArxGeCurveFun::AcdbCurve2AcGeCurveEx( IN const AcDbSpline* pSpline, OUT AcGeCompositeCurve3d*& pCompCurve, BOOL bProject /*= FALSE*/, IN int nStep /*= 1 */ )
{
	if( pSpline == NULL ) return FALSE;
	AcGePoint3dArray PtAry;
	if( pSpline->hasFitData() )
	{
		int nSize = pSpline->numFitPoints();
		for ( int i = 0; i< nSize; i++ )
		{
			AcGePoint3d Pt;
			pSpline->getFitPointAt( i, Pt );
			if( bProject )
				Pt.z = 0;
			PtAry.append( Pt );
		}
	}
	else
	{
		int nNumCtr = pSpline->numControlPoints();
		for ( int i = 0; i< nNumCtr; i++ )
		{
			AcGePoint3d Pt;
			pSpline->getControlPointAt( i, Pt );
			if( bProject )
				Pt.z = 0;
			PtAry.append( Pt );
		}
	}
	
	pCompCurve = new AcGeCompositeCurve3d;

	GetCompositeCurve( PtAry, *pCompCurve );

	return TRUE;
}


BOOL TWArxGeCurveFun::DiscreteArc( IN const AcGeCircArc3d* pArc, OUT vector<AcGePoint3d>& vPts, IN double dStep /*= 1 */ )
{
	if( pArc == NULL ) return FALSE;

	AcGePoint3d PtStart = pArc->startPoint();
	AcGePoint3d PtEnd   = pArc->endPoint();
	double dParam = pArc->paramOf( PtStart );
	double dLen = pArc->length( dParam, pArc->paramOf(PtEnd) );
	double dTotalLen = 0;
	AcGePoint3d PtTem;
	vPts.push_back( PtStart );

	while( 1 )
	{
		if( dLen <= ( dTotalLen + dStep) )
		{
			dParam = pArc->paramAtLength( dParam, dLen - dTotalLen );
			PtTem = pArc->evalPoint( dParam );
			vPts.push_back( PtTem );
			break;;
		}
		
		dTotalLen += dStep;
		dParam = pArc->paramAtLength( dParam, dStep );
		PtTem = pArc->evalPoint( dParam );
		vPts.push_back( PtTem );
	}

	return TRUE;
}

BOOL TWArxGeCurveFun::GetCompositeNormal( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, OUT AcGeVector3d& vNormal, BOOL bRight /*= TRUE */ )
{
	double dParam = 0;

	if( pComCurve->isOn(PtStd, dParam) == Adesk::kFalse );
		//return FALSE;
	int nSeg = -1;
	dParam = pComCurve->globalToLocalParam( dParam, nSeg );

	AcGeVoidPointerArray  curveList;
	pComCurve->getCurveList( curveList );
	AcGeCurve3d* pCurve = (AcGeCurve3d*)curveList[nSeg];
	if( pCurve->type() == AcGe::kLineSeg3d )
	{
		AcGeLineSeg3d* pLn = ( AcGeLineSeg3d*)pCurve;

		AcGeVector3d vT = pLn->endPoint() - pLn->startPoint();
		vNormal = vT.rotateBy( bRight? -TW_PI/2:TW_PI/2, AcGeVector3d::kZAxis );
		vNormal.normalize();
		return TRUE;
	}
	else if ( pCurve->type() == AcGe::kCircArc3d )
	{
		AcGeCircArc3d* pArc = ( AcGeCircArc3d*)pCurve;

		AcGePoint3d PtCen = pArc->center();

		AcGeVector3d vArcNorm = pArc->normal();

		AcGeVector3d vT = PtStd - PtCen;
		vNormal = vT.normalize();
		if( vArcNorm == AcGeVector3d::kZAxis )                  
		{
			if( !bRight)
				vNormal =-1*vNormal;

			return TRUE;
		}
		else if( vArcNorm == -AcGeVector3d::kZAxis )
		{
			if( bRight )
				vNormal =-1*vNormal;

			return TRUE;
		}
	}

	return FALSE;

}



BOOL TWArxGeCurveFun::GetCompositeDir( IN const AcGeCompositeCurve3d* pComCurve, IN const AcGePoint3d& PtStd, OUT AcGeVector3d& vDir )
{
	double dParam = 0;

	if( pComCurve->isOn(PtStd, dParam) == Adesk::kFalse );
	//return FALSE;
	int nSeg = -1;
	dParam = pComCurve->globalToLocalParam( dParam, nSeg );

	AcGeVoidPointerArray  curveList;
	pComCurve->getCurveList( curveList );
	AcGeCurve3d* pCurve = (AcGeCurve3d*)curveList[nSeg];
	if( pCurve->type() == AcGe::kLineSeg3d )
	{
		AcGeLineSeg3d* pLn = ( AcGeLineSeg3d*)pCurve;

		vDir = pLn->endPoint() - pLn->startPoint();
		vDir.normalize();

		return TRUE;
	}
	else if ( pCurve->type() == AcGe::kCircArc3d )
	{
		AcGeCircArc3d* pArc = ( AcGeCircArc3d*)pCurve;

		AcGePoint3d PtCen = pArc->center();

		AcGeVector3d vArcNorm = pArc->normal();

		AcGeVector3d vT = PtStd - PtCen;
		vT.normalize();
		vDir = vArcNorm.crossProduct( vT );
		vDir.normalize();

		return TRUE;
	}

	return FALSE;
}




#pragma endregion TWArxGeCurveFun




#pragma region CTwCurveAdjustSort

BOOL CTwCurveAdjustSort::DoIt( IN OUT vector<AcDbObjectId>& vId, OUT vector<CTwEnumAdjustJoinType>& vJoinType )
{
	return FALSE;
	int nSize = vId.size();
	if( nSize == 0 ) return FALSE;

	//转换为实体指针
	list<AcDbCurve*> vCurves;
	for ( int i = 0; i < nSize; i++ )
	{
		AcDbCurve* pCurve = NULL;
		acdbOpenObject( pCurve, vId[i], AcDb::kForRead );
		if( pCurve == NULL ) continue;
		pCurve->close();
		vCurves.push_back( pCurve );
	}
	if( vCurves.empty() ) return FALSE;

	nSize = vCurves.size();
	for ( int i = 0; i < nSize; i++ )
	{
		//vCurves.po
	}
	

	
}


#pragma endregion CTwCurveAdjustSort




#pragma region CTwPolygon2d

CTwPolygon2d::CTwPolygon2d():m_vPts()
{

}

CTwPolygon2d::~CTwPolygon2d()
{
	m_vPts.clear();
}

void CTwPolygon2d::Set( IN const AcGePoint3dArray& vPts )
{
	m_vPts.clear();
	int nLen = vPts.length();
	for ( int i = 0; i < nLen; i++ )
	{
		m_vPts.push_back( TWArxGeCommonFun::ToPoint2d(vPts[i]) );
	}
}

void CTwPolygon2d::Set( IN const AcGePoint2dArray& vPts )
{
	m_vPts.clear();
	int nLen = vPts.length();
	for ( int i = 0; i < nLen; i++ )
	{
		m_vPts.push_back( vPts[i] );
	}
}

void CTwPolygon2d::Set( IN const vector<AcGePoint3d> vPts )
{
	m_vPts.clear();
	int nLen = vPts.size();
	for ( int i = 0; i < nLen; i++ )
	{
		m_vPts.push_back( TWArxGeCommonFun::ToPoint2d(vPts[i]) );
	}
}

void CTwPolygon2d::Set( IN const vector<AcGePoint2d> vPts )
{
	m_vPts.assign( vPts.begin(), vPts.end() );
}

void CTwPolygon2d::Add( IN const AcGePoint2d& Pt )
{
	m_vPts.push_back( Pt );
}

void CTwPolygon2d::Add( IN const AcGePoint3d& Pt )
{
	m_vPts.push_back( TWArxGeCommonFun::ToPoint2d(Pt) );
}

void CTwPolygon2d::Get( OUT AcGePoint2dArray& vPts )
{
	int nSize = m_vPts.size();
	for ( int i = 0; i < nSize; i++ )
		vPts.append( m_vPts[i] );
}

void CTwPolygon2d::Get( OUT AcGePoint3dArray& vPts )
{

}

void CTwPolygon2d::Get( OUT vector<AcGePoint3d> vPts )
{

}

void CTwPolygon2d::Get( OUT vector<AcGePoint2d> vPts )
{

}


BOOL CTwPolygon2d::Center( OUT AcGePoint3d& PtCen ) const
{
	int nSize = m_vPts.size();
	if( nSize < 2 ) return FALSE;

	double dTol = 0.000001;
	AcGePoint2d Pt, Pt0, Pt1, Pt2, Pt3;
	double dM  = 0;
	double dM0 = 0;
	Pt1 = m_vPts[0];
	Pt2 = m_vPts[1];

	for ( int i = 2; i < nSize; i++ )
	{
		Pt3 = m_vPts[i];
		Pt0.x = (Pt1.x + Pt2.x + Pt3.x ) / 3.0;
		Pt0.y = (Pt1.y + Pt2.y + Pt3.y ) / 3.0; 

		dM0 = Pt1.x * Pt2.y + Pt2.x * Pt3.y + Pt3.x* Pt1.y - Pt1.y * Pt2.x - Pt2.y * Pt3.x - Pt3.y * Pt1.x;
		if( TWArxMathCommonFun::IsZero(dM+ dM0) )
			dM0 += dTol;

		
		Pt.x = ( dM * Pt.x + dM0 * Pt0.x ) / ( dM + dM0 ); 
		Pt.y = ( dM * Pt.y + dM0 * Pt0.y ) / ( dM + dM0 ); 
		dM += dM0; 
		Pt2  = Pt3; 
	}

	PtCen = TWArxGeCommonFun::ToPoint3d( Pt );
	return TRUE;
}

BOOL CTwPolygon2d::IsConvex() const
{
// 	bool IsConvex(const Polygon& poly) // 判断多边形poly是否是凸的 
// 	{ 
// 		int i, n, rel; 
// 		Line side; 
// 
// 		n = poly.size(); 
// 		if (n < 3) return false; 
// 		side.p1 = poly[0]; 
// 		side.p2 = poly[1]; 
// 		rel = Relation(poly[2], side); 
// 		for (i = 1; i < n; i++) { 
// 			side.p1 = poly[i]; 
// 			side.p2 = poly[(i+1)%n]; 
// 			if (Relation(poly[(i+2)%n], side) != rel) return false; 
// 		} 
// 		return true; 
// 	} 

	int nSize = m_vPts.size();
	if( nSize < 3 ) return FALSE;
	int Rel = TWArxGeCommonFun::Relation( m_vPts[0], m_vPts[1], m_vPts[3] );                       //存在一个问题，如果共线怎么处理？
	for ( int i = 1; i < nSize; i++ )
	{
		if( TWArxGeCommonFun::Relation( m_vPts[i], m_vPts[(i+1)%nSize], m_vPts[(i+2)%nSize]) != Rel )
			return FALSE;
	}

	return TRUE;
}

BOOL CTwPolygon2d::Sort( IN BOOL bClockwise /*= FALSE */ )
{
	return Sort( m_vPts, bClockwise );
}

BOOL CTwPolygon2d::Sort( vector<AcGePoint2d>& vPts, IN BOOL bClockwise /*= FALSE */ )
{
	int nSize = vPts.size();
	if( nSize < 3 ) return FALSE;
	
	//计算点集最小的X和Y值
	double dX = 0;
	double dY = 0;
	for( int i = 0; i < nSize; i++ )
	{
		dX += vPts[i].x;
		dY += vPts[i].y;
	}

	dX = dX / nSize;
	dY = dY / nSize;
	std::sort( vPts.begin(), vPts.end(), _Sort_Compare(AcGePoint2d(dX, dY), bClockwise) );

	return TRUE;

	//测试
	AcGePoint2d PtOr( dX, dY );
	TWArxTextParam txtParm;
	txtParm.m_dTextHei = 20;
	vector<AcDbEntity*> vEnt;
	for( int i = 0; i < nSize; i++ )
	{
		double d = (vPts[i] - PtOr).angle();
		txtParm.m_PtAln = txtParm.m_PtPos = TWArxGeCommonFun::ToPoint3d(vPts[i]);
		txtParm.m_strCon.Format( _T("%d:%s"), i+1, StringCommonFun::Real2String(d) );
		vEnt.push_back( txtParm.CreateEntity() );
	}

	txtParm.m_PtAln = txtParm.m_PtPos = TWArxGeCommonFun::ToPoint3d(PtOr);
	txtParm.m_strCon.Format( _T("Origon Point") );
	vEnt.push_back( txtParm.CreateEntity() );

	TWArxEntityFun::PostCurSpace( vEnt, vector<AcDbObjectId>() );
	return TRUE;
}

BOOL CTwPolygon2d::Intersection( IN const CTwPolygon2d& Polygon, OUT CTwPolygon2d& Inters )
{
	if( !Valid() || !Polygon.Valid() ) return FALSE;

	vector<AcGePoint2d> vPtIns;

	//计算交点
	int nThisSize = m_vPts.size();
	int nParaSize = Polygon.m_vPts.size();
	for ( int i = 0; i < nThisSize; i++ )
	{
		int nThisNextId = ( i + 1 ) % nThisSize;
		for ( int j = 0; j < nParaSize; j++ )
		{
			int nParaNextId = ( j+1) % nParaSize;

			AcGeLineSeg2d LnThis( m_vPts[i], m_vPts[nThisNextId] );
			AcGeLineSeg2d LnPara( Polygon.m_vPts[j], Polygon.m_vPts[nParaNextId] );
			AcGePoint2d PtIns;
			if( LnThis.intersectWith( LnPara, PtIns) == Adesk::kTrue )
				vPtIns.push_back( PtIns );
		}
	}

	vector<AcGePoint2d> vThisInParam;
	for ( int i = 0; i < nThisSize; i++ )
	{
		if( Polygon.IsInner(m_vPts[i]) )
			vThisInParam.push_back( m_vPts[i] );
	}

	vector<AcGePoint2d> vParaInThis;
	for ( int i = 0; i < nParaSize; i++ )
	{
		if( IsInner(Polygon.m_vPts[i]) )
			vParaInThis.push_back( Polygon.m_vPts[i] );
	}

	Inters.Set( vPtIns );
	Inters.m_vPts.insert( Inters.m_vPts.end(), vThisInParam.begin(), vThisInParam.end() );
	Inters.m_vPts.insert( Inters.m_vPts.end(), vParaInThis.begin(), vParaInThis.end() );

	Inters.Sort();
	Inters.m_vPts.erase( unique(Inters.m_vPts.begin(), Inters.m_vPts.end()), Inters.m_vPts.end() );
	return TRUE;
}

BOOL CTwPolygon2d::IsLinear() const
{
	return FALSE;
}

BOOL CTwPolygon2d::Valid() const
{
	int nSize = m_vPts.size();
	if( nSize < 3 ) return  FALSE;
	
	return TRUE;

}

BOOL CTwPolygon2d::IsInner( IN const AcGePoint2d& Pt, IN BOOL bBorder /*= FALSE */ ) const
{
	int nCount = m_vPts.size();
	if( nCount < 3) return FALSE;

	AcGeRay2d Ray( Pt, AcGeVector2d::kXAxis );
	int nInsCount = 0;

	for ( int i = 0; i < nCount; i++ )
	{
		AcGePoint2d PtStart = m_vPts[i] ;
		AcGePoint2d PtEnd   = m_vPts[(i+1)%nCount];

		AcGeLineSeg2d LnSide( PtStart, PtEnd );

		if( 3 == TWArxGeCommonFun::Relation(LnSide, Pt) )                                          //在边界上
		{
			if( bBorder ) return TRUE;
			else return FALSE;
		}

		if( TWArxMathCommonFun::IsEquql(PtStart.y, PtEnd.y) ) continue;                            //平行于X轴

		if( Ray.isOn( PtStart) == Adesk::kTrue ) nInsCount++;                                      //扫描线穿过起点
		else if( Ray.isOn( PtEnd) == Adesk::kTrue ) nInsCount++;                                   //扫描线穿过终点
		else if( Ray.intersectWith(LnSide, AcGePoint2d()) == Adesk::kTrue ) nInsCount++;           //扫描线穿过边

	}
	
	return (nInsCount % 2 == 1) ? TRUE : FALSE;

	/*
	int i, n, count; 
	Line ray, side; 

	n = poly.size(); 
	count = 0;     
	ray.p1    = p; 
	ray.p2.y  = p.y; 
	ray.p2.x  = - INF; 

	for (i = 0; i < n; i++) {                 
		side.p1 = poly[i]; 
		side.p2 = poly[(i+1)%n]; 

		if( OnLineSeg(p, side) ) { 
			return BORDER; 
		} 
		// 如果side平行x轴则不作考虑 
		if ( EQ(side.p1.y, side.p2.y) ) { 
			continue; 
		} 
		if (OnLineSeg(side.p1, ray)) { 
			if (GT(side.p1.y, side.p2.y)) count++; 
		} else if (OnLineSeg(side.p2, ray)) { 
			if ( GT(side.p2.y, side.p1.y)) count++; 
		} else if (LineSegIntersect(ray, side)) { 
			count++; 
		} 
	}    
	return ((count % 2 == 1) ? INSIDE : OUTSIDE); */
}

BOOL CTwPolygon2d::ConvexHull( IN const vector<AcGePoint2d>& vPts )
{
	//int i, k, n; 
	//Point p; 

	//n = points.size(); 
	//result.clear(); 

	//if (n < 3) return; 

	//// 选取points中y坐标最小的点points[k]， 
	//// 如果这样的点有多个，则取最左边的一个 
	//k = 0; 
	//for (i = 1; i < n; i++ ) { 
	//	if (EQ(points[i].y, points[k].y)) { 
	//		if (points[i].x <= points[k].x) k = i; 
	//	} else if (points[i].y < points[k].y) { 
	//		k = i; 
	//	}        
	//} 
	//swap(points[0], points[k]); 

	//// 现在points中y坐标最小的点在points[0] 
	//// 计算每个点相对于points[0]的极角和距离 
	//for (i = 1; i < n; i++) { 
	//	points[i].angle = atan2(points[i].y - points[0].y, points[i].x - points[0].x); 
	//	points[i].dis   = Norm(points[i] - points[0]); 
	//} 

	//// 对顶点按照相对points[0]的极角从小到大进行排序 
	//// 对于极角相同的按照距points[0]的距离从小到大排序 
	//sort(points.begin() + 1, points.end(), GrahamComp); 

	//// 下面计算凸包 
	//result.push_back(points[0]); 

	//for (i = 1; i < n; i++) { 
	//	// 如果有极角相同的点，只取相对于points[0]最远的一个 
	//	if ((i + 1 < n) && EQ(points[i].angle, points[i+1].angle)) continue; 
	//	if (result.size() >= 3) { 
	//		p = result[result.size() - 2]; 
	//		while ( GEQ((points[i] - p)*(result.back() - p), 0) ) 
	//		{ 
	//			result.pop_back(); 
	//			p = result[result.size() - 2]; 
	//		} 
	//	} 
	//	result.push_back( points[i] );       
	//} 

	return FALSE;
}

BOOL CTwPolygon2d::ConvexHull( IN const vector<AcGePoint3d>& vSrc, OUT vector<AcGePoint3d>& vCHRes )
{
	int nSize = vSrc.size();
	if( nSize < 3 ) return FALSE;
	vCHRes.clear();

	vector<AcGePoint3d> vPts;
	vPts.assign( vSrc.begin(), vSrc.end() );

	// 选取points中y坐标最小的点vPts[k]， 
	// 如果这样的点有多个，则取最左边的一个 
	int nIndex = 0;
	for ( int i = 1; i < nSize; i++ )
	{
		if (TWArxMathCommonFun::IsEquql(vPts[i].y, vPts[nIndex].y) ) 
		{ 
			if (vPts[i].x <= vPts[nIndex].x) nIndex = i; 
		}
		else if (vPts[i].y < vPts[nIndex].y)  nIndex = i;       
	}
	swap( vPts[0], vPts[nIndex] ); 

	vector<ConvexHullVertex> vCHV;
	vector<ConvexHullVertex> vRes;

	//计算相对于左下角点的极角和距离。
	vCHV.push_back( ConvexHullVertex(vPts[0],0 , 0) );
	for ( int i = 1; i < nSize; i++ )
		vCHV.push_back( ConvexHullVertex( vPts[i], atan2(vPts[i].y - vPts[0].y, vPts[i].x - vPts[0].x), vPts[i].distanceTo(vPts[0]) ) );

	// 对顶点按照相对points[0]的极角从小到大进行排序 
	// 对于极角相同的按照距points[0]的距离从小到大排序 
	sort(vCHV.begin() + 1, vCHV.end(), _Sort_Compare_ConvexHull() ); 

	//计算凸包
	vRes.push_back( vCHV[0] );
	ConvexHullVertex p ;
	for ( int i = 1; i < nSize; i++ )
	{
		// 如果有极角相同的点，只取相对于vCHV[0]最远的一个 
		if ((i + 1 < nSize) && TWArxMathCommonFun::IsEquql(vCHV[i].GetAtom2() , vCHV[i+1].GetAtom2()) ) continue; 
		if ( vRes.size() >= 3 ) 
		{ 
			p = vRes[vRes.size() - 2]; 

			while ( TWArxMathCommonFun::GEqual( TWArxMathCommonFun::crossProduct(TWArxGeCommonFun::ToVector2d(vCHV[i].GetAtom1() - p.GetAtom1()) ,TWArxGeCommonFun::ToVector2d(vRes.back().GetAtom1() - p.GetAtom1())), 0) ) 
			{ 
				vRes.pop_back(); 
				p = vRes[vRes.size() - 2]; 
			} 
		} 
		vRes.push_back( vCHV[i] );       
	}

	nSize = vRes.size();
	for ( int i = 0; i < nSize; i++ )
		vCHRes.push_back( vRes[i].GetAtom1() );

	return TRUE;
}


CTwPolygon2d::_Sort_Compare::_Sort_Compare( IN const AcGePoint2d& PtOri, IN BOOL bClockwise /*= FALSE */ )
{
	m_PtOri      = PtOri;
	m_bClockwise = bClockwise;
}

CTwPolygon2d::_Sort_Compare::~_Sort_Compare()
{

}

bool CTwPolygon2d::_Sort_Compare::operator()( IN const AcGePoint2d& pt1, IN const AcGePoint2d& pt2 ) const
{
	double dAngel1 = ( pt1 - m_PtOri ).angle();
	double dAngel2 = ( pt2 - m_PtOri ).angle();

	if( TWArxMathCommonFun::IsEquql(dAngel2,dAngel1) )
	{
		if(m_PtOri.distanceTo(pt1) < m_PtOri.distanceTo(pt2) ) return TRUE;
		else return FALSE;
	}
	else if( dAngel1 < dAngel2 )
	{
		if( m_bClockwise ) return FALSE;
		else return TRUE;
	}
	else
	{
		if( m_bClockwise ) return TRUE;
		else return FALSE;
	}

}


bool CTwPolygon2d::_Sort_Compare_ConvexHull::operator()( IN const ConvexHullVertex& pt1, IN const ConvexHullVertex& pt2 ) const
{
	if (TWArxMathCommonFun::IsEquql(pt1.GetAtom2(), pt2.GetAtom2() )) 
		return (pt1.GetAtom3() < pt2.GetAtom3() ); 
	else 
		return (pt1.GetAtom2() < pt2.GetAtom2()); 
}

#pragma endregion CTwPolygon2d


#pragma region CTwRectangle
CTwRectangle::CTwRectangle()
:CTwPolygon2d()
{

}

CTwRectangle::~CTwRectangle()
{

}

void CTwRectangle::Set( IN const AcGePoint3d& PtMin, IN const AcGePoint3d& PtMax )
{
	//return FALSE;
}

#pragma endregion CTwRectangle
