#include "stdafx.h"
#include "TWMisc.h"
#include "TWArxGeCommonFun.h"
#include "TWArxEntityParam.h"

#pragma region CTwTimeRun

void CTwTimeRun::Start()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_timeFr );
	QueryPerformanceCounter( (LARGE_INTEGER*)&m_timeStart );
}

void CTwTimeRun::End()
{
	QueryPerformanceCounter( (LARGE_INTEGER*)&m_timeEnd );
}

void CTwTimeRun::ShowMsg() const
{
	CString str;
	str.Format(  _T("\nTime runing:%f"), (double)(m_timeEnd - m_timeStart) / (double)m_timeFr  );
	ads_prompt( str );
}

#pragma endregion CTwTimeRun

#pragma region CTwSmbolDrawToolKid

BOOL CTwSmbolDrawToolKid::Draw( OUT vector<AcDbEntity*>& vEnt ) const
{
	return TRUE;
}

BOOL CTwSmbolDrawToolKid::Draw( IN AcDbEntity* pSrcEnt, OUT vector<AcDbEntity*>& vEnt ) const
{
	return TRUE;
}


BOOL CTwSmbolDrawToolKid::DrawTriangle( IN const AcGePoint3d& PtBase, IN double dLen, OUT AcDbPolyline*& pPolyline )
{
	//
	AcGePoint3dArray PtAry;
	PtAry.append( PtBase );
	AcGeVector3d v = AcGeVector3d::kYAxis;
	v.rotateBy( TW_PI/6.0, AcGeVector3d::kZAxis );
	PtAry.append( PtBase + dLen*v );

	v.rotateBy( -TW_PI/3.0, AcGeVector3d::kZAxis );
	PtAry.append( PtBase + dLen*v );
	TWArxPolylineParam PolylineParam;
	PolylineParam.SetPointAry( PtAry );
	PolylineParam.m_bIsClosed = true;

	pPolyline = (AcDbPolyline*)PolylineParam.CreateEntity();

	return TRUE;

}
#pragma endregion CTwSmbolDrawToolKid




#pragma region CTwSmblolDrawTriangle

CTwSmblolDrawTriangle::CTwSmblolDrawTriangle()
{
	m_Ptbase   = AcGePoint3d::kOrigin;  
	m_vNormal  = AcGeVector3d::kYAxis; 
	m_dLen     = 1;;    

}

CTwSmblolDrawTriangle::~CTwSmblolDrawTriangle()
{

}

BOOL CTwSmblolDrawTriangle::Draw( vector<AcDbEntity*>& vEnt ) const
{
	AcGePoint3dArray PtAry;

	PtAry.append( m_Ptbase );
	AcGeVector3d v = m_vNormal;
	v.rotateBy( TW_PI/6.0, AcGeVector3d::kZAxis );
	PtAry.append( m_Ptbase + m_dLen*v );

	v.rotateBy( -TW_PI/3.0, AcGeVector3d::kZAxis );
	PtAry.append( m_Ptbase + m_dLen*v );
	TWArxPolylineParam PolylineParam;
	PolylineParam.SetPointAry( PtAry );
	PolylineParam.m_bIsClosed = true;

	vEnt.push_back( PolylineParam.CreateEntity() );
	return TRUE;
}

#pragma endregion CTwSmblolDrawTriangle




#pragma region CTwSmblolDrawElevation

CTwSmblolDrawElevation::CTwSmblolDrawElevation()
{
	m_vLeader    = AcGeVector3d::kXAxis;
	m_dTxtOff    = 1.0;
	m_dExt       = 1.0;   
	m_bUnderLine = TRUE;

}

CTwSmblolDrawElevation::~CTwSmblolDrawElevation()
{

}

AcDbText* CTwSmblolDrawElevation::CreateElevtionNote( IN const CString& strCon, IN double dTxtH, IN const AcDbObjectId& IdTxtStyle )
{
	TWArxTextParam TxtParam;
	TxtParam.m_strCon  = strCon;
	TxtParam.m_IdStyle = IdTxtStyle;
	TxtParam.m_dTextHei= dTxtH;
	TxtParam.m_HorMode  = AcDb::kTextCenter;
	TxtParam.m_VerMode  = AcDb::kTextBottom;
	return (AcDbText*)TxtParam.CreateEntity();
}

BOOL CTwSmblolDrawElevation::Draw( IN AcDbEntity* pSrcEnt, OUT vector<AcDbEntity*>& vEnt ) const
{
	if( !TWArxMathCommonFun::IsZero(m_vLeader.dotProduct(m_vNormal)) ) return FALSE;

	if( pSrcEnt->isA()!= AcDbText::desc() ) return FALSE;
	AcDbText* pTxt =( AcDbText*) pSrcEnt;

	//计算文字长、高
	AcDbExtents Ext;
	pTxt->getGeomExtents( Ext );
	double dTxtLen = Ext.maxPoint().x - Ext.minPoint().x;
	double dTxtH   = Ext.maxPoint().y - Ext.minPoint().y;

	//三角符号绘制
	AcGePoint3dArray PtAry;

	PtAry.append( m_Ptbase );
	AcGeVector3d v = m_vNormal;
	v.rotateBy( TW_PI/6.0, AcGeVector3d::kZAxis );
	PtAry.append( m_Ptbase + m_dLen*v );

	v.rotateBy( -TW_PI/3.0, AcGeVector3d::kZAxis );
	PtAry.append( m_Ptbase + m_dLen*v );

	TWArxPolylineParam PolylineParam;
	PolylineParam.SetPointAry( PtAry );
	PolylineParam.m_bIsClosed = true;

	vEnt.push_back( PolylineParam.CreateEntity() );

	//绘制引线
	AcGeVector3d vLeader = m_vLeader;
	vLeader.normalize();
	AcGeVector3d vTemp = PtAry[1] - PtAry[2];
	vTemp.normalize();
	TWArxLineParam LnParam;
	if( vLeader == vTemp )
		LnParam.m_PtStart = PtAry[1];
	else
		LnParam.m_PtStart = PtAry[2];

	//计算引线长度
	double dLeaderLen = dTxtLen + m_dExt * 2;
	//计算终点
	LnParam.m_PtEnd = LnParam.m_PtStart + vLeader*dLeaderLen;

	vEnt.push_back( LnParam.CreateEntity() );

	//文字位置同步
	//计算引线中点
	AcGePoint3d PtLeaderMid = LnParam.m_PtStart + (LnParam.m_PtEnd - LnParam.m_PtStart)/2.0;
	
	//计算最新文字位置
	AcGePoint3d PtTxtNewMid = PtLeaderMid + m_vNormal * ( m_dTxtOff );

	pTxt->setAlignmentPoint( PtTxtNewMid );

	return TRUE;

}

#pragma endregion CTwSmblolDrawElevation



#pragma region CTwSymbolDrawRectangle

CTwSymbolDrawRectangle::CTwSymbolDrawRectangle()
{
	m_dWidht = 0;
	m_dHeigh = 0;
}

CTwSymbolDrawRectangle::~CTwSymbolDrawRectangle()
{

}

BOOL CTwSymbolDrawRectangle::Draw( OUT vector<AcDbEntity*>& vEnt ) const
{
	return FALSE;
}

AcDbPolyline* CTwSymbolDrawRectangle::Draw_Cen( IN double dH, IN double dW, IN const AcGePoint3d& PtCen ,IN const AcGeVector3d& vNormal /*= AcGeVector3d::kYAxis */ )
{
	TWArxPolylineParam LnParam;

	AcGePoint2d Pt   = TWArxGeCommonFun::ToPoint2d( PtCen );

	AcGePoint2d PtLT = Pt;
	PtLT.y          += dH / 2.0;
	PtLT.x          -= dW / 2.0;
	LnParam.m_PtVertexAry.append( PtLT );

	AcGePoint2d PtRT = PtLT;
	PtRT.x           += dW;
	LnParam.m_PtVertexAry.append( PtRT );

	AcGePoint2d PtRB = PtRT;
	PtRB.y          -= dH;
	LnParam.m_PtVertexAry.append( PtRB );

	AcGePoint2d PtLB = PtLT;
	PtLB.y          -= dH;
	LnParam.m_PtVertexAry.append( PtLB );

	LnParam.m_bIsClosed = true;

	return (AcDbPolyline*)LnParam.CreateEntity();
}

AcDbPolyline* CTwSymbolDrawRectangle::Draw_Lb( IN double dH, IN double dW, IN const AcGePoint3d& PtLB ,IN const AcGeVector3d& vNormal /*= AcGeVector3d::kYAxis */ )
{
	return Draw_Cen( dH, dW, PtLB + AcGeVector3d( dW/2.0, dH/2.0, 0 ), vNormal );
}

#pragma endregion CTwSymbolDrawRectangle



#pragma region API

BOOL Index2String( IN int nRow, IN int nCol, OUT CString& strRes, IN int nRowOff /*= 0*/, IN int nColOff /*= 0*/ )
{
	nRow += nRowOff;
	nCol += nColOff;
	const short nStart = _T('A');
	
	if( nCol < 1 ) return FALSE;

	nCol -= 1;                                           //将其转化为0为开始索引
	
	CString strCol; 
	int nIndex = 0;
	while( 1 )
	{
		int n1 = nCol / 26; 
		if( n1 == 0 )
		{
			strCol = CString( _TCHAR(nCol+nStart) ) + strCol ;
			break;
		}
		else
		{
			int n = nCol - 26 * n1 ;
			strCol = CString( _TCHAR(n+nStart) ) + strCol;
			nCol = n1 - 1;
		}
	}

	strRes.Format( _T("%s%d"), strCol, nRow ) ;

	return TRUE;
}

BOOL GetIsoPapaerSize( IN const CString& strTZ, OUT double& dH, OUT double& dW )
{
	if( strTZ.Find(TTMB_PAPERFRAME_SIZE_A0) > -1 )
	{
		dH = 841;
		dW = 1184;
	}
	else if( strTZ.Find(TTMB_PAPERFRAME_SIZE_A1) > -1 )
	{
		dH = 594;
		dW = 841;
	}
	else if( strTZ.Find(TTMB_PAPERFRAME_SIZE_A2) > -1 )
	{
		dH = 420;
		dW = 594;
	}
	else if( strTZ.Find(TTMB_PAPERFRAME_SIZE_A3) > -1 )
	{
		dH = 297;
		dW = 420;
	}
	else if( strTZ.Find(TTMB_PAPERFRAME_SIZE_A4) > -1 )
	{
		dH = 210;
		dW = 297;
	}
	else
		return FALSE;

	return TRUE;
}

#pragma endregion API