#include "StdAfx.h"
#include "ArxEntityOperation.h"

#pragma region CArxEntityFun
Acad::ErrorStatus CArxEntityFun::PostModelSpace( AcDbEntity* pEnt, AcDbObjectId& IdRes, BOOL bAutoCLose /*= TRUE*/, BOOL bAutoDel /*= TRUE */, IN BOOL bUseTran /*= FALSE*/ )
{
	if( pEnt == NULL ) return Acad::eNullEntityPointer;

	if(  pEnt->objectId() != AcDbObjectId::kNull )
	{
		if( bAutoCLose )
			pEnt->close();
		return Acad::eOk;
	}

	AcDbBlockTablePointer pBt( acdbCurDwg()->blockTableId(), AcDb::kForRead );
	if( pBt.openStatus() != Acad::eOk ) 
	{
		if( bAutoDel )
		{
			FreePtr( pEnt );
		}
		return pBt.openStatus();
	}

	AcDbObjectId IdBtr;
	Acad::ErrorStatus es = pBt->getAt( ACDB_MODEL_SPACE, IdBtr );
	if( es != eOk )
	{
		if( bAutoDel )
		{
			FreePtr( pEnt );
		}
		return es;
	}

	AcDbBlockTableRecordPointer pBtr( IdBtr, AcDb::kForWrite );
	if( pBtr.openStatus() != Acad::eOk )
	{
		if( bAutoDel )
		{
			FreePtr( pEnt );
		}
		return pBtr.openStatus();
	}

	es = pBtr->appendAcDbEntity( IdRes, pEnt );
	if( es == Acad::eOk )
	{
		if( bUseTran )
			acTransactionManagerPtr()->addNewlyCreatedDBRObject( pEnt );

		if( bAutoCLose )
			pEnt->close();
	}
	else
	{
		if( bAutoDel )
		{
			FreePtr( pEnt );
		}
	}

	return es;

}

Acad::ErrorStatus CArxEntityFun::PostModelSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose /*= TRUE*/, IN BOOL bAutoDel /*= TRUE*/ )
{
	AcDbBlockTablePointer pBt( acdbCurDwg()->blockTableId(), AcDb::kForRead );
	if( pBt.openStatus() != Acad::eOk ) 
	{
		if( bAutoDel )
		{
			for_each( EntAry.begin(), EntAry.end(), For_each_Delete() );
		}
		return pBt.openStatus();
	}

	AcDbObjectId IdBtr;
	Acad::ErrorStatus es = pBt->getAt( ACDB_MODEL_SPACE, IdBtr );
	if( es != eOk )
	{
		if( bAutoDel )
		{
			for_each( EntAry.begin(), EntAry.end(), For_each_Delete() );
		}
		return es;
	}

	AcDbBlockTableRecordPointer pBtr( IdBtr, AcDb::kForWrite );
	if( pBtr.openStatus() != Acad::eOk )
	{
		if( bAutoDel )
		{
			for_each( EntAry.begin(), EntAry.end(), For_each_Delete() );
		}
		return pBtr.openStatus();
	}

	For_each_AppendEnt2TableRecor FunObj1;
	FunObj1.m_pBtr = pBtr.object();

	For_each_AppendEnt2TableRecor FunObj = for_each( EntAry.begin(), EntAry.end(), FunObj1 );

	if( bAutoDel )
		for_each( FunObj.m_vFalsEnt.begin(), FunObj.m_vFalsEnt.end(), For_each_Delete() );

	if( bAutoCLose )
		for_each( FunObj.m_vSuccEnt.begin(), FunObj.m_vSuccEnt.end(), For_each_Close() );

	IdAry.assign( FunObj.m_vSuccObjIds.begin(), FunObj.m_vSuccObjIds.end() );

	return Acad::eOk;
}

Acad::ErrorStatus CArxEntityFun::PostModelSpace( IN vector<AcDbEntity*>& EntAry, IN BOOL bAutoCLose /*= TRUE*/, IN BOOL bAutoDel /*= TRUE */ )
{
	vector<AcDbObjectId> vIds;
	return PostModelSpace( EntAry, vIds, bAutoCLose, bAutoDel );
}


Acad::ErrorStatus CArxEntityFun::GetHandString( IN const AcDbObjectId& Id, OUT _TCHAR* chHandle )
{
	Acad::ErrorStatus es;
	AcDbEntity* pEnt = NULL;
	es = acdbOpenObject( pEnt, Id, AcDb::kForRead );
	if( pEnt == NULL ) return es;
	pEnt->close();

	AcDbHandle hand;
	pEnt->getAcDbHandle( hand );
	hand.getIntoAsciiBuffer( chHandle );
	return es;
}

void CArxEntityFun::DeleteSS( ads_name ss )
{
	acedCommand( RTSTR, _T("erase"), RTPICKS, ss, RTSTR, _T(""), 0 );
}

void CArxEntityFun::TransformBy( vector<AcDbEntity*> vEnt, IN const AcGeMatrix3d& Mat )
{
	int nLen = vEnt.size();
	for ( int i = 0; i < nLen; i++ )
		vEnt[i]->transformBy( Mat );
}

Acad::ErrorStatus CArxEntityFun::CreateExtendDictionary( IN AcDbObject* pObj, OUT AcDbObjectId& IdExtDic )
{
	if( pObj == NULL ) return Acad::eNullPtr;

	IdExtDic = pObj->extensionDictionary();

	if( !IdExtDic.isNull() ) 	return Acad::eOk;

	if( !pObj->isWriteEnabled() ) return Acad::eNotOpenForWrite;

	Acad::ErrorStatus es = pObj->createExtensionDictionary();

	if( es == Acad::eOk )
		IdExtDic = pObj->extensionDictionary();

	return es;

}

Acad::ErrorStatus CArxEntityFun::CreateExtendDictionary( IN const AcDbObjectId& IdObj, OUT AcDbObjectId& IdExtDic )
{
	AcDbObject* pObj = NULL;
	Acad::ErrorStatus es = acdbOpenObject( pObj, IdObj, AcDb::kForWrite );
	if( pObj == NULL )  return es;
	es =  CreateExtendDictionary( pObj, IdExtDic );
	pObj->close();
	return es;
}

BOOL CArxEntityFun::IsA( IN ads_name ent, IN AcRxClass* pClass )
{
	AcDbObjectId Id;
	acdbGetObjectId( Id, ent );
	return IsA( Id, pClass );
}

BOOL CArxEntityFun::IsA( IN const AcDbObjectId& Id, IN AcRxClass* pClass )
{
	AcDbEntityPointer pEnt( Id, AcDb::kForRead );
	if( pEnt.openStatus() == Acad::eOk && pEnt->isA() == pClass ) return TRUE;
	return FALSE;
}

void CArxEntityFun::GetGeometryExtend( IN const vector<AcDbEntity*> vEnt, OUT AcDbExtents& Ext )
{
	int nSize = vEnt.size();
	for ( int i = 0; i < nSize; i++ )
	{
		AcDbExtents extTem;
		vEnt[i]->getGeomExtents( extTem );
		Ext.addExt( extTem );
	}
}

void CArxEntityFun::Free( AcDbVoidPtrArray& vPtr )
{
	int nLen = vPtr.length();
	for ( int i = 0; i < nLen; i++ )
	{
		void* p = vPtr[i];
		if( p != NULL )
		{
			AcDbEntity* pEnt = (AcDbEntity*)p;
			if( pEnt != NULL )
				delete pEnt;
		}
	}
}

void CArxEntityFun::For_each_AppendEnt2TableRecor::operator()( AcDbEntity* pEnt )
{
	if( m_pBtr == NULL )
	{
		m_vFalsEnt.push_back( pEnt );
		return ;
	}

	AcDbObjectId IdRes;
	Acad::ErrorStatus es;
	if( (es = m_pBtr->appendAcDbEntity(IdRes, pEnt)) == Acad::eOk )
	{
		m_vSuccEnt.push_back( pEnt );
		m_vSuccObjIds.push_back( IdRes );
	}
	else
		m_vFalsEnt.push_back( pEnt );

}
void CArxEntityFun::For_each_Close::operator()( AcDbEntity* pEnt )
{
	if( pEnt != NULL ) pEnt->close();
}

void CArxEntityFun::For_each_Delete::operator()( AcDbEntity* pEnt )
{
	FreePtr( pEnt );
}

#pragma endregion CArxEntityFun