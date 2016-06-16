#include "StdAfx.h"
#include "TWArxTool.h"
#include "TWArxCommonFun.h"
#pragma region TWBlockRefenceTool

TWBlockRefenceTool::TWBlockRefenceTool()
:m_IdblockRef()
{

}

TWBlockRefenceTool::~TWBlockRefenceTool()
{

}

BOOL TWBlockRefenceTool::IsValid() const
{
	if( m_IdblockRef.isNull() || !m_IdblockRef.isValid() ) return FALSE;
	return TRUE;
}

BOOL TWBlockRefenceTool::Insert( IN const CString& strBlockName, IN const AcGePoint3d& PtIns, IN double dScale, IN double dRat, AcDbDatabase* pDb /*= NULL */ )
{
	/*
		使用简单的实现方法
	*/
	ads_name entPre = { 0, 0 };
	ads_entlast( entPre );

	resbuf rbOld;
	resbuf rbNew;
	rbNew.restype = RTSHORT;
	rbNew.resval.rint = 0;
	acedGetVar( _T("ATTREQ"), &rbOld );
	acedSetVar( _T("ATTREQ"), &rbNew );

	ads_command( RTSTR, _T("insert"), RTSTR, strBlockName, RT3DPOINT, asDblArray(PtIns), RTREAL, 1.0, RTSTR, _T(""), RTREAL, 0.0, 0 );

	acedSetVar( _T("ATTREQ"), &rbOld );

	ads_name ent = { 0 ,0 };
	ads_entlast( ent );

	//判定是否正确生成块参照
	if( ads_name_equal(ent, entPre) )
		return FALSE;

	acdbGetObjectId( m_IdblockRef, ent );
	return IsValid();
}

AcDbObjectId TWBlockRefenceTool::GetBlockRefId() const
{
	return m_IdblockRef;
}

AcDbBlockReference* TWBlockRefenceTool::CreateBlockRefence( IN const CString& strBlockName, IN const AcGePoint3d& PtIns, IN double dScale, IN double dRat, AcDbDatabase* pDb /*= NULL */ )
{
	AcDbObjectId IdBd;

	if( !TWArxBlokTableFun::HasBlockTableRecord(strBlockName, IdBd, pDb) ) return NULL;

	AcDbBlockReference* pBrf = new AcDbBlockReference( PtIns, IdBd );
	pBrf->setScaleFactors( AcGeScale3d(dScale, dScale, dScale) );
	pBrf->setRotation( dRat );

	return pBrf;
}

#pragma endregion TWBlockRefenceTool



#pragma region TWArxLayer

TWArxLayer::TWArxLayer()
:TWWorkingDatabase()
{
	m_strName.Empty();  
	m_nColor    = 256;   
	m_bIsFrozen = false;
	m_bIsLocked = false;
	m_bIsOff    = false;  

}

TWArxLayer::~TWArxLayer()
{

}

BOOL TWArxLayer::IsExist() const
{
	AcDbDatabase* pDB = GetWorkingDB();

	TWArxLayerMan layerMan;
	layerMan.SetWrokingDB( pDB );

	AcDbObjectId Id;
	if( layerMan.Init() != Acad::eOk ) return FALSE;

	if( Acad::eOk == layerMan.GetLayerId( m_strName, Id ) ) return TRUE;
	return FALSE;
}

Acad::ErrorStatus TWArxLayer::Init( IN const AcDbObjectId IdLayer )
{
	Acad::ErrorStatus           es = Acad::eOk;
	AcDbLayerTableRecordPointer pRc( IdLayer, AcDb::kForRead );
	if( pRc.openStatus() != Acad::eOk ) return pRc.openStatus();
	
	AcString strName;
	pRc->getName( strName );
	m_strName = strName.kTCharPtr();
	m_nColor = pRc->color().colorIndex();
	m_bIsFrozen = pRc->isFrozen();
	m_bIsLocked = pRc->isLocked();
	m_bIsOff    = pRc->isOff();

	return es;
}

void TWArxLayer::SetName( IN const CString& strName )
{
	m_strName = strName;
}

Acad::ErrorStatus TWArxLayer::Create( OUT AcDbObjectId& IdLayer ) const
{
	if( m_strName.IsEmpty() ) return Acad::eInvalidInput;

	AcDbDatabase* pDb = GetWorkingDB();

	Acad::ErrorStatus es = Acad::eKeyNotFound;

	AcDbLayerTable* pLayerTb = NULL;
	es = pDb->getLayerTable( pLayerTb,AcDb::kForRead );
	if( pLayerTb == NULL ) return es;
	
	es = pLayerTb->getAt( m_strName, IdLayer );
	if( es == Acad::eOk )
	{
		pLayerTb->close();
		return es;
	}

	es = pLayerTb->upgradeOpen();

	AcDbLayerTableRecord* pLtr = new AcDbLayerTableRecord;
	pLtr->setName( m_strName );
	pLtr->setIsFrozen( m_bIsFrozen );
	pLtr->setIsLocked( m_bIsLocked );
	pLtr->setIsOff( m_bIsOff );

	es = pLayerTb->add( IdLayer, pLtr );
	pLayerTb->close();

	if( es == Acad::eOk )
	{
		pLtr->close();
		return es;
	}

	TWFreePtr( pLtr );
	return es;
}

#pragma endregion TWArxLayer




#pragma region TWArxLayerMan

TWArxLayerMan::TWArxLayerMan()
:TWWorkingDatabase(), m_vLayers()
{

}

TWArxLayerMan::~TWArxLayerMan()
{

}

Acad::ErrorStatus TWArxLayerMan::Init()
{
	AcDbDatabase* pDb = GetWorkingDB();

	Acad::ErrorStatus es = Acad::eOk;

	AcDbLayerTable* pLayerTb = NULL;
	es = pDb->getLayerTable( pLayerTb,AcDb::kForRead );
	if( pLayerTb == NULL ) return es;
	pLayerTb->close();

	AcDbLayerTableIterator* pIte = NULL;
	es = pLayerTb->newIterator( pIte );
	if( pIte == NULL ) return es;

	m_vLayers.clear();
	for ( pIte->start(); !pIte->done(); pIte->step())
	{
		AcDbObjectId Id;
		es = pIte->getRecordId( Id );
		if( es != Acad::eOk ) continue;

		m_vLayers.push_back( Id );
	}

	TWFreePtr( pIte );
	return es;
}

int TWArxLayerMan::GetLayerNames( OUT vector<CString>& vLayerNames ) const
{
	int nSize = m_vLayers.size();
	for ( int i = 0; i < nSize; i++ )
	{
		CString strName;
		if( Acad::eOk == GetLayerName(m_vLayers[i], strName) )
			vLayerNames.push_back( strName );
	}

	return vLayerNames.size();
}

Acad::ErrorStatus TWArxLayerMan::GetLayerName( IN const AcDbObjectId& Id , OUT CString& strName ) const
{
	AcDbLayerTableRecordPointer pRc( Id, AcDb::kForRead );
	if( pRc.openStatus() != Acad::eOk  ) return pRc.openStatus();

	AcString          acName;
	Acad::ErrorStatus es = Acad::eOk;
	if( Acad::eOk == (es = pRc->getName(acName)) )
		strName = acName.kTCharPtr();

	return es;
}

Acad::ErrorStatus TWArxLayerMan::GetLayerId( IN const CString& strLayerName, OUT AcDbObjectId& IdLayer ) const
{
	int               nSize = m_vLayers.size();
	Acad::ErrorStatus es    = Acad::eRecordNotInTable;
	for ( int i = 0; i < nSize; i++ )
	{
		CString strName;
		if( Acad::eOk == GetLayerName(m_vLayers[i], strName) )
		{
			if( strLayerName.CompareNoCase(strName) == 0 )
			{
				IdLayer = m_vLayers[i];
				return Acad::eOk;
			}
		}
	}
	
// 	vector< TWArxLayer> v, v2;
// 	GetLayer( v );
	return es;
}

int TWArxLayerMan::GetLayer( OUT TWAutoFreeVector<TWArxLayer>& vLayer ) const
{
	int nSize = m_vLayers.size();
	for ( int i = 0; i < nSize; i++ )
	{
		TWArxLayer LayerItem;
		if( Acad::eOk == LayerItem.Init(m_vLayers[i]) );
			//vLayer.push_back( LayerItem );
	}

	return vLayer.size();
}

#pragma endregion TWArxLayerMan





#pragma region CTwArxDictionary

CTwArxDictionary::CTwArxDictionary()
{

}

CTwArxDictionary::~CTwArxDictionary()
{

}

Acad::ErrorStatus CTwArxDictionary::GetSubDictionaryID( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObjectId& IdSub, AcDbDatabase* pCurDB ) const
{
	Acad::ErrorStatus es = Acad::eOk;
	AcDbDictionary* pDicRoot = NULL;
	AcDbDatabase* pWdb = pCurDB;
	if( pWdb == NULL )
		pWdb = acdbCurDwg();
	if( IdRoot.isNull() )
		es = pWdb->getNamedObjectsDictionary( pDicRoot, AcDb::kForRead );
	else
		es = acdbOpenObject( pDicRoot, IdRoot, AcDb::kForRead );
	if( pDicRoot == NULL ) return es;
	pDicRoot->close();
	
	es = pDicRoot->getAt( strKey, IdSub );

	return es;

}

Acad::ErrorStatus CTwArxDictionary::OpenSubObject( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObject*& pObj, AcDb::OpenMode os ) const
{
	AcDbObjectId Id;
	Acad::ErrorStatus es = GetSubDictionaryID( IdRoot, strKey, Id );
	if( es != eOk) return es;

	pObj = NULL;
	es = acdbOpenObject( pObj, Id, os );
	return es;
}

Acad::ErrorStatus CTwArxDictionary::OpenSubDictionary( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbDictionary*& pDic, AcDb::OpenMode os ) const
{
	return OpenSubObject( IdRoot, strKey, (AcDbObject*&)pDic, os );
}

Acad::ErrorStatus CTwArxDictionary::OpenXrecord( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbXrecord*& pXrecord, AcDb::OpenMode os ) const
{
	return OpenSubObject( IdRoot, strKey, (AcDbObject*&)pXrecord, os );
}

Acad::ErrorStatus CTwArxDictionary::GetXrecordObject( IN const AcDbObjectId& IdRoot, IN const vector<CString>& vDicPath, IN const CString& strXrecordName, OUT AcDbXrecord*& pXrecord, IN AcDb::OpenMode os, AcDbDatabase* pCurDB ) const
{
	AcDbObjectId IdCur   = IdRoot;
	int          nLen    = vDicPath.size();
	Acad::ErrorStatus es = Acad::eOk;
	for ( int i = 0; i < nLen; i++ )
	{
		es = GetSubDictionaryID( IdCur, vDicPath[i], IdCur, pCurDB );
		if( es != Acad::eOk ) return es;
	}

	return OpenXrecord( IdCur, strXrecordName, pXrecord, os );
}

Acad::ErrorStatus CTwArxDictionary::CreateXrecord( IN const AcDbObjectId& IdRoot, IN const vector<CString>& vDicPath, IN const CString& strXrecordName, OUT AcDbObjectId& IdRes ) const
{
	AcDbObjectId IdCur   = IdRoot;
	int          nLen    = vDicPath.size();
	Acad::ErrorStatus es = Acad::eOk;
	for ( int i = 0; i < nLen; i++ )
	{
		es = CreateSubDictionary( IdCur, vDicPath[i], IdCur );
		if( es != Acad::eOk ) return es;
	}

	return CreateXRecord( IdCur, strXrecordName, IdRes );
}

Acad::ErrorStatus CTwArxDictionary::CreateSubDictionary( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObjectId& IdSubDic ) const
{
	return CreateSubDictionaryID( IdRoot, strKey, IdSubDic );
	
}

Acad::ErrorStatus CTwArxDictionary::CreateXRecord( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObjectId& IdSubDic ) const
{
	return CreateSubDictionaryID( IdRoot, strKey, IdSubDic, AcDbXrecord::desc() );
}

Acad::ErrorStatus CTwArxDictionary::CreateSubDictionaryID( IN const AcDbObjectId& IdRoot, IN const CString& strKey, OUT AcDbObjectId& IdSubDic, IN AcRxClass* pRxObjType /*= AcDbDictionary::desc() */ ) const
{
	if( pRxObjType == NULL ) return Acad::eNullObjectPointer;

	Acad::ErrorStatus es = Acad::eOk;
	AcDbDictionary* pDicRoot = NULL;
	AcDbDatabase* pWdb = acdbCurDwg();

	if( IdRoot.isNull() )
		es = pWdb->getNamedObjectsDictionary( pDicRoot, AcDb::kForRead );
	else
		es = acdbOpenObject( pDicRoot, IdRoot, AcDb::kForRead );

	if( es != Acad::eOk ) return es;

	if( pDicRoot->has(strKey) )
	{
		pDicRoot->getAt( strKey, IdSubDic );
		pDicRoot->close();
		return es;
	}

	pDicRoot->upgradeOpen();
	AcDbObject* pObj = (AcDbObject*)pRxObjType->create();
	es = pDicRoot->setAt( strKey, pObj, IdSubDic );
	pObj->close();
	pDicRoot->close();

	return es;
}

#pragma endregion CTwArxDictionary




#pragma region CTwAutoRedraw
CTwAutoRedraw::CTwAutoRedraw()
{
	ads_name_clear( m_ss );
	acedSSAdd( NULL, NULL, m_ss );
}

CTwAutoRedraw::~CTwAutoRedraw()
{
	Remove();
}

void CTwAutoRedraw::Remove()
{
	long Len = 0;
	ads_sslength( m_ss, &Len );
	for ( int i = 0; i < Len; i++ )
	{
		ads_name ent;
		ads_ssname( m_ss, i, ent );
		ads_redraw( ent, 4 );
	}

	ads_ssfree( m_ss );
	ads_name_clear( m_ss );
}

void CTwAutoRedraw::Highlight( IN ads_name ent )
{
	ads_redraw( ent, 3 );
	ads_ssadd( ent, m_ss, m_ss );
}

#pragma endregion CTwAutoRedraw
