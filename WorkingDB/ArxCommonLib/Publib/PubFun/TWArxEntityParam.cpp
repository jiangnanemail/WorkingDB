#include "StdAfx.h"
#include "TWArxEntityParam.h"
#include "TWArxGeCommonFun.h"
#pragma region TWArxEntityParam
TWArxEntityParam::TWArxEntityParam()
{
	m_nColor    = 256;
	m_strLayer  = _T("0");
}

TWArxEntityParam::~TWArxEntityParam()
{

}

BOOL TWArxEntityParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	if( pEnt == NULL ) return FALSE;

	TCHAR* chLayer = pEnt->layer();
	if( chLayer == NULL )
		return FALSE;
	m_strLayer = chLayer;

	acutDelString( chLayer );
	chLayer = NULL;

	m_nColor = pEnt->colorIndex();

	return TRUE;
}

BOOL TWArxEntityParam::SetEntityParam( IN OUT AcDbEntity* pEnt ) const
{
	if( pEnt == NULL ) return FALSE;
	pEnt->setLayer( m_strLayer );
	pEnt->setColorIndex( m_nColor );
	return TRUE;
}

AcDbEntity* TWArxEntityParam::CreateEntity() const
{
	return NULL;
}

BOOL TWArxEntityParam::SetCommonEntityProperty( IN AcDbEntity* pEnt ) const
{
	if( pEnt == NULL ) return FALSE;
	pEnt->setLayer( m_strLayer );
	pEnt->setColorIndex( m_nColor );

	return TRUE;
}

#pragma endregion TWArxEntityParam



#pragma region TWArxTextParam
TWArxTextParam::TWArxTextParam()
{
	m_strCon       = _T("");      
	m_IdStyle      = AcDbObjectId::kNull;    
	m_dTextHei     = 0;    
	m_dWidthFactor = 0.7;
	m_HorMode      = AcDb::kTextLeft;     
	m_VerMode      = AcDb::kTextBase;     
	m_PtAln        = AcGePoint3d::kOrigin; 
	m_PtPos        = AcGePoint3d::kOrigin; 
	m_dRot         = 0.0;        
	m_dObl         = 0.0;        

}

TWArxTextParam::~TWArxTextParam()
{

}

BOOL TWArxTextParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	return TRUE;
}

BOOL TWArxTextParam::SetEntityParam( IN OUT AcDbEntity* pEnt ) const
{
	return TRUE;
}

AcDbEntity* TWArxTextParam::CreateEntity() const
{
	AcDbText* pText = new AcDbText;
	SetCommonEntityProperty( pText );
	pText->setTextString( m_strCon );
	pText->setHeight( m_dTextHei );
	pText->setWidthFactor( m_dWidthFactor );
	pText->setTextStyle( m_IdStyle );
	pText->setHorizontalMode( m_HorMode );
	pText->setVerticalMode( m_VerMode );
	pText->setPosition( m_PtPos );
	pText->setAlignmentPoint( m_PtAln );
	pText->setRotation( m_dRot );

	return pText;

}

#pragma endregion TWArxTextParam



#pragma region TWArxAttributedefParam

TWArxAttributedefParam::TWArxAttributedefParam()
:TWArxTextParam()
{

}

TWArxAttributedefParam::~TWArxAttributedefParam()
{

}

BOOL TWArxAttributedefParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	return FALSE;
}

BOOL TWArxAttributedefParam::SetEntityParam( IN OUT AcDbEntity* pEnt ) const
{
	return FALSE;
}

AcDbEntity* TWArxAttributedefParam::CreateEntity() const
{
	AcDbAttributeDefinition* pDef = new AcDbAttributeDefinition;
	SetCommonEntityProperty( pDef );
	pDef->setTextString( m_strCon );
	pDef->setHeight( m_dTextHei );
	pDef->setWidthFactor( m_dWidthFactor );
	pDef->setTextStyle( m_IdStyle );
	pDef->setHorizontalMode( m_HorMode );
	pDef->setVerticalMode( m_VerMode );
	pDef->setPosition( m_PtPos );
	pDef->setAlignmentPoint( m_PtAln );
	pDef->setTag( m_strTag );
	pDef->setPrompt( m_strPormpt );

	return pDef;
}

#pragma endregion TWArxAttributedefParam


#pragma region TWArxLineParam
TWArxLineParam::TWArxLineParam()
{

}

TWArxLineParam::~TWArxLineParam()
{

}

BOOL TWArxLineParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	return TRUE;
}

BOOL TWArxLineParam::SetEntityParam( IN OUT AcDbEntity* pEnt ) const
{
	return TRUE;
}

AcDbEntity* TWArxLineParam::CreateEntity() const
{
	AcDbLine* pLine = new AcDbLine;
	SetCommonEntityProperty( pLine );
	pLine->setStartPoint( m_PtStart );
	pLine->setEndPoint( m_PtEnd );

	return pLine;
}

#pragma endregion TWArxLineParam



#pragma region TWArxPolylineParam
TWArxPolylineParam::TWArxPolylineParam()
:TWArxEntityParam()
{
	m_dLineWidth = 0;
	m_bIsClosed  = false;
}

TWArxPolylineParam::~TWArxPolylineParam()
{

}

BOOL TWArxPolylineParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	AcDbPolyline* pPoly = AcDbPolyline::cast( pEnt );
	if( pPoly == NULL ) return FALSE;

	TWArxEntityParam::GetEntityParam( pEnt );

	m_bIsClosed = pPoly->isClosed();
	pPoly->getConstantWidth( m_dLineWidth );
	
	m_PtVertexAry.removeAll();
	int nSize = pPoly->numVerts();
	for ( int i = 0; i < nSize; i++ )
	{
		AcGePoint2d Pt;
		pPoly->getPointAt( i, Pt );
		m_PtVertexAry.append( Pt );
	}

	return TRUE;
}

BOOL TWArxPolylineParam::SetEntityParam( IN OUT AcDbEntity* pEnt ) const
{
	return TRUE;
}

AcDbEntity* TWArxPolylineParam::CreateEntity() const
{
	AcDbPolyline* pPol = new AcDbPolyline;
	SetCommonEntityProperty( pPol );
	int nSize = m_PtVertexAry.length();
	for ( int i = 0; i < nSize; i++ )
	{
		pPol->addVertexAt( i, m_PtVertexAry[i] );
	}

	pPol->setClosed( m_bIsClosed );
	pPol->setConstantWidth( m_dLineWidth );

	return pPol;
}

void TWArxPolylineParam::SetPointAry( IN const AcGePoint3dArray& PtAry )
{
	m_PtVertexAry.removeAll();
	TWArxGeCommonFun::ToPoint2dArray( PtAry, m_PtVertexAry );
}

#pragma endregion TWArxPolylineParam



#pragma region TWArxAcDb3dPolylineParam
TWArxAcDb3dPolylineParam::TWArxAcDb3dPolylineParam()
{
	m_TypeP3D = AcDb::k3dSimplePoly;
	m_bIsClosed = false;
}

TWArxAcDb3dPolylineParam::~TWArxAcDb3dPolylineParam()
{

}

BOOL TWArxAcDb3dPolylineParam::SetEntityParam( IN OUT AcDbEntity* pEnt ) const
{
	if( FALSE == TWArxEntityParam::SetEntityParam(pEnt) ) return FALSE;

	AcDb3dPolyline* pPoly = AcDb3dPolyline::cast( pEnt );
	if( pPoly == NULL ) return FALSE;

	
	//删除原有的节点
	AcDbObjectIterator* pIte = pPoly->vertexIterator();
	if( pIte == NULL ) return FALSE;

	for (  pIte->start(); !pIte->done(); pIte->step() )
	{
		AcDb3dPolylineVertex* pVertex = NULL;
		acdbOpenObject(  pVertex, pIte->objectId(), AcDb::kForWrite );
		if(  pVertex == NULL ) continue;
		pVertex->erase();
		pVertex->close();
	}
	
	TWFreePtr( pIte );

	//基本属性
	if( m_bIsClosed ) pPoly->makeClosed();
	else              pPoly->makeOpen();
	pPoly->setPolyType( m_TypeP3D );

	//设置新节点
	int nLen = m_Vertex.length();
	for ( int i = 0; i < nLen; i++ )
		pPoly->appendVertex( new AcDb3dPolylineVertex( m_Vertex[i]) );

	return TRUE;
}

BOOL TWArxAcDb3dPolylineParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	if( !TWArxEntityParam::GetEntityParam(pEnt) ) return FALSE;

	AcDb3dPolyline* pLine = AcDb3dPolyline::cast( pEnt );
	if(  pLine == NULL ) return FALSE;

	m_bIsClosed = pLine->isClosed();
	m_TypeP3D   = pLine->polyType();

   AcDbObjectIterator* pIte = pLine->vertexIterator();
   if( pIte == NULL ) return FALSE;
   m_Vertex.removeAll();

   for (  pIte->start(); !pIte->done(); pIte->step() )
   {
	   AcDb3dPolylineVertex* pVertex = NULL;
	   acdbOpenObject(  pVertex, pIte->objectId(), AcDb::kForRead );
	   if(  pVertex == NULL ) continue;

	   pVertex->close();

	   m_Vertex.append( pVertex->position() );
   }

   TWFreePtr( pIte );

	return TRUE;
}

AcDbEntity* TWArxAcDb3dPolylineParam::CreateEntity() const
{
	AcDb3dPolyline* pLine = new AcDb3dPolyline;
	SetCommonEntityProperty( pLine );
	
	int nLen = m_Vertex.length();
	for ( int i = 0; i < nLen; i++ )
	{
		AcDb3dPolylineVertex* pVertex = new AcDb3dPolylineVertex( m_Vertex[i] );
		if( Acad::eOk != pLine->appendVertex(pVertex) )
		{
			TWFreePtr( pVertex );
		}
	}
	pLine->setPolyType( m_TypeP3D );
	if( m_bIsClosed ) pLine->makeClosed();
	else              pLine->makeOpen();

	return pLine;
}

void TWArxAcDb3dPolylineParam::SetVertex( IN const vector<AcGePoint3d>& vVertex )
{
	int nSize = vVertex.size();
	m_Vertex.removeAll();
	for ( int i = 0; i < nSize; i++ )
	{
		m_Vertex.append( vVertex[i] );
	}
}

#pragma endregion TWArxAcDb3dPolylineParam



#pragma region TWArxAcDb3dPolylineNDRParam
BOOL TWArxAcDb3dPolylineNDRParam::GetEntityParam( IN const AcDbEntity* pEnt )
{
	if( !TWArxEntityParam::GetEntityParam(pEnt) ) return FALSE;

	AcDb3dPolyline* pLine = AcDb3dPolyline::cast( pEnt );
	if(  pLine == NULL ) return FALSE;

	m_bIsClosed = pLine->isClosed();
	m_TypeP3D   = pLine->polyType();

	AcDbObjectIterator* pIte = pLine->vertexIterator();
	if( pIte == NULL ) return FALSE;
	m_Vertex.removeAll();

	for (  pIte->start(); !pIte->done(); pIte->step() )
	{
		AcDb3dPolylineVertex* pVertex = (AcDb3dPolylineVertex*)pIte->entity();
		if(  pVertex == NULL ) continue;
		m_Vertex.append( pVertex->position() );
	}

	TWFreePtr( pIte );

	return TRUE;




}
#pragma endregion TWArxAcDb3dPolylineNDRParam