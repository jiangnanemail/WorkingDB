#include "StdAfx.h"
#include "TWArxCommonFun.h"
#include "TWArxGeCommonFun.h"
#include "adsdef.h"

#pragma region TWArxLayerFun

Acad::ErrorStatus TWArxLayerFun::GetLayerNames( OUT vector<CString>& vLayerNames, IN AcDbDatabase* pCur /*= NULL */ )
{
	 AcDbDatabase* pDb = pCur;

	if( pDb == NULL )
		pDb = acdbCurDwg();

	if( pDb == NULL )
		return Acad::eNoDatabase;

	Acad::ErrorStatus es = Acad::eOk;

	AcDbLayerTable* pLayerTb = NULL;
	es = pDb->getLayerTable( pLayerTb,AcDb::kForRead );
	if( pLayerTb == NULL ) return es;
	pLayerTb->close();

	AcDbLayerTableIterator* pIte = NULL;
	es = pLayerTb->newIterator( pIte );
	if( pIte == NULL ) return es;

	vLayerNames.clear();
	for ( pIte->start(); !pIte->done(); pIte->step())
	{
		AcDbObjectId Id;
		es = pIte->getRecordId( Id );
		if( es != Acad::eOk ) continue;

		AcDbLayerTableRecordPointer pLayTr( Id, AcDb::kForRead );
		if( pLayTr.openStatus() != Acad::eOk ) continue;
		AcString strName;
		if( Acad::eOk == pLayTr->getName(strName) )
			vLayerNames.push_back( strName.kTCharPtr() );
	}

	TWFreePtr( pIte );
	return es;
}
#pragma endregion TWArxLayerFun



#pragma region TWArxTextStyleFun

Acad::ErrorStatus TWArxTextStyleFun::GetTextStyleNames( OUT vector<CString>& vTextStyleNames, IN AcDbDatabase* pCur /*= NULL */ )
{
	AcDbDatabase* pDb = pCur;

	if( pDb == NULL )
		pDb = acdbCurDwg();

	if( pDb == NULL )
		return Acad::eNoDatabase;

	Acad::ErrorStatus es = Acad::eOk;

	AcDbTextStyleTable* pTst = NULL;
	es = pDb->getTextStyleTable( pTst, AcDb::kForRead );
	if( pTst == NULL ) return es;
	pTst->close();

	AcDbTextStyleTableIterator* pIte = NULL;
	es = pTst->newIterator( pIte );
	if( pIte == NULL ) return es;

	for ( pIte->start(); !pIte->done(); pIte->step() )
	{
		AcDbObjectId Id;
		es = pIte->getRecordId( Id );
		if( es != Acad::eOk ) continue;

		AcDbTextStyleTableRecordPointer pTr( Id, AcDb::kForRead );
		if( pTr.openStatus() != Acad::eOk ) continue;
		AcString strName;
		if( Acad::eOk == pTr->getName(strName) )
			vTextStyleNames.push_back( strName.kTCharPtr() );
	}

	TWFreePtr( pIte );
	return es;
}

AcDbObjectId TWArxTextStyleFun::GetTextStyleId( IN const CString strStyleName, IN AcDbDatabase* pCur /*= NULL */ )
{
	AcDbDatabase* pDb = pCur;

	if( pDb == NULL )
		pDb = acdbCurDwg();

	if( pDb == NULL )
		return AcDbObjectId::kNull;

	Acad::ErrorStatus es = Acad::eOk;

	AcDbTextStyleTable* pTst = NULL;
	es = pDb->getTextStyleTable( pTst, AcDb::kForRead );
	if( pTst == NULL ) return AcDbObjectId::kNull;
	pTst->close();

	AcDbObjectId Id;
	pTst->getAt( strStyleName, Id );
	return Id;
}

Acad::ErrorStatus TWArxTextStyleFun::CreateTextStyle( IN const CString& strName, IN const CString& strSHXName, IN const CString& strBigFront, IN double dWidthFactor )
{
	Acad::ErrorStatus es = Acad::eOk;

	AcDbTextStyleTable *pTextTable = NULL;
	acdbCurDwg()->getTextStyleTable(pTextTable,AcDb::kForWrite);

	AcDbTextStyleTableRecord *pTextStyleblRec;
	pTextStyleblRec = new AcDbTextStyleTableRecord();
	pTextStyleblRec->setName(strName);
	pTextStyleblRec->setFileName(strSHXName);
	pTextStyleblRec->setBigFontFileName( strBigFront );

	pTextStyleblRec->setXScale(dWidthFactor);
	es = pTextTable->add(pTextStyleblRec);
	pTextStyleblRec->close();
	pTextTable->close();

	return es;
}

#pragma endregion TWArxTextStyleFun



#pragma region TWArxEntityFun


Acad::ErrorStatus TWArxEntityFun::PostModelSpace( AcDbEntity* pEnt, AcDbObjectId& IdRes, BOOL bAutoCLose /*= TRUE*/, BOOL bAutoDel /*= TRUE */, IN BOOL bUseTran /*= FALSE*/ )
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
			TWFreePtr( pEnt );
		}
		return pBt.openStatus();
	}

	AcDbObjectId IdBtr;
	Acad::ErrorStatus es = pBt->getAt( ACDB_MODEL_SPACE, IdBtr );
	if( es != eOk )
	{
		if( bAutoDel )
		{
			TWFreePtr( pEnt );
		}
		return es;
	}

	AcDbBlockTableRecordPointer pBtr( IdBtr, AcDb::kForWrite );
	if( pBtr.openStatus() != Acad::eOk )
	{
		if( bAutoDel )
		{
			TWFreePtr( pEnt );
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
			TWFreePtr( pEnt );
		}
	}

	return es;

}

Acad::ErrorStatus TWArxEntityFun::PostModelSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose /*= TRUE*/, IN BOOL bAutoDel /*= TRUE*/ )
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


Acad::ErrorStatus TWArxEntityFun::PostCurSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose /*= TRUE*/, IN BOOL bAutoDel /*= TRUE */ )
{
	AcDbObjectId IdBtr = acdbCurDwg()->currentSpaceId();
	if( IdBtr.isNull() || !IdBtr.isValid() )
	{
		if( bAutoDel )
		{
			for_each( EntAry.begin(), EntAry.end(), For_each_Delete() );
		}
		return Acad::eNullPtr;
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



Acad::ErrorStatus TWArxEntityFun::GetHandString( IN const AcDbObjectId& Id, OUT _TCHAR* chHandle )
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

void TWArxEntityFun::DeleteSS( ads_name ss )
{
	acedCommand( RTSTR, _T("erase"), RTPICKS, ss, RTSTR, _T(""), 0 );
}

void TWArxEntityFun::TransformBy( vector<AcDbEntity*> vEnt, IN const AcGeMatrix3d& Mat )
{
	int nLen = vEnt.size();
	for ( int i = 0; i < nLen; i++ )
		vEnt[i]->transformBy( Mat );
}

Acad::ErrorStatus TWArxEntityFun::CreateExtendDictionary( IN AcDbObject* pObj, OUT AcDbObjectId& IdExtDic )
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

Acad::ErrorStatus TWArxEntityFun::CreateExtendDictionary( IN const AcDbObjectId& IdObj, OUT AcDbObjectId& IdExtDic )
{
	AcDbObject* pObj = NULL;
	Acad::ErrorStatus es = acdbOpenObject( pObj, IdObj, AcDb::kForWrite );
	if( pObj == NULL )  return es;
	es =  CreateExtendDictionary( pObj, IdExtDic );
	pObj->close();
	return es;
}

BOOL TWArxEntityFun::IsA( IN ads_name ent, IN AcRxClass* pClass )
{
	AcDbObjectId Id;
	acdbGetObjectId( Id, ent );
	return IsA( Id, pClass );
}

BOOL TWArxEntityFun::IsA( IN const AcDbObjectId& Id, IN AcRxClass* pClass )
{
	AcDbEntityPointer pEnt( Id, AcDb::kForRead );
	if( pEnt.openStatus() == Acad::eOk && pEnt->isA() == pClass ) return TRUE;
	return FALSE;
}

void TWArxEntityFun::GetGeometryExtend( IN const vector<AcDbEntity*> vEnt, OUT AcDbExtents& Ext )
{
	int nSize = vEnt.size();
	for ( int i = 0; i < nSize; i++ )
	{
		AcDbExtents extTem;
		vEnt[i]->getGeomExtents( extTem );
		Ext.addExt( extTem );
	}
}

// BOOL TWArxEntityFun::GetTxtGeometryExtend( IN const AcDbText* pTxt, OUT AcDbExtents& Ext )
// {
// 	if( pTxt == NULL ) return FALSE;
// 	
// 	double dAngle = pTxt->rotation();
// 	//不用几何变换
// 	if( TWArxMathCommonFun::IsEquql(dAngle, TW_PI)     || 
// 		TWArxMathCommonFun::IsEquql(dAngle, 0)         ||
// 		TWArxMathCommonFun::IsEquql(dAngle, TW_PI/2.0) ||
// 		TWArxMathCommonFun::IsEquql(dAngle, 3.0*TW_PI)/2 )
// 		return ( pTxt->getGeomExtents( Ext)== Acad::eOk ) ? TRUE : FALSE;
// 
// 
// 	AcDbText* pClone = (AcDbText*)pTxt->clone();
// 	AcDbExtents ExtTemp;
// 	pClone->setRotation( 0 );
// 	pClone->getGeomExtents( ExtTemp );
// 	AcGeMatrix3d Mat;
// 	Mat.setToRotation( dAngle, AcGeVector3d::kZAxis, ExtTemp.minPoint() );
// 	ExtTemp.transformBy( Mat );
// 	Ext = ExtTemp;
// 
// 	TWFreePtr( pClone );
// 
// 	return TRUE;
// }

BOOL TWArxEntityFun::GetTxtGeometryExtend( IN const AcDbText* pTxt, OUT CTwRectangle* Rectangle )
{
	if( pTxt == NULL ) return FALSE;

	double dAngle = pTxt->rotation();
	//不用几何变换
	if( TWArxMathCommonFun::IsEquql(dAngle, TW_PI)     || 
		TWArxMathCommonFun::IsEquql(dAngle, 0)         ||
		TWArxMathCommonFun::IsEquql(dAngle, TW_PI/2.0) ||
		TWArxMathCommonFun::IsEquql(dAngle, 3.0*TW_PI)/2 )
	{
		AcDbExtents Ext;
		if( pTxt->getGeomExtents( Ext)!= Acad::eOk ) return FALSE;


	}


// 	AcDbText* pClone = (AcDbText*)pTxt->clone();
// 	AcDbExtents ExtTemp;
// 	pClone->setRotation( 0 );
// 	pClone->getGeomExtents( ExtTemp );
// 	AcGeMatrix3d Mat;
// 	Mat.setToRotation( dAngle, AcGeVector3d::kZAxis, ExtTemp.minPoint() );
// 	ExtTemp.transformBy( Mat );
// 	Ext = ExtTemp;

	//TWFreePtr( pClone );

	return TRUE;
}

void TWArxEntityFun::Free( AcDbVoidPtrArray& vPtr )
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

void TWArxEntityFun::For_each_AppendEnt2TableRecor::operator()( AcDbEntity* pEnt )
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
void TWArxEntityFun::For_each_Close::operator()( AcDbEntity* pEnt )
{
	if( pEnt != NULL ) pEnt->close();
}

void TWArxEntityFun::For_each_Delete::operator()( AcDbEntity* pEnt )
{
	TWFreePtr( pEnt );
}

#pragma endregion TWArxEntityFun



#pragma region TWArxBlokTableFun

BOOL TWArxBlokTableFun::HasBlockTableRecord( IN const CString& strName, OUT AcDbObjectId& IdRes, IN AcDbDatabase* pCur /*= NULL */ )
{
	AcDbDatabase* pDb = pCur;

	if( pDb == NULL )
		pDb = acdbCurDwg();

	if( pDb == NULL )
		return FALSE;

	AcDbObjectId IdBt =	pDb->blockTableId();
	AcDbBlockTablePointer pBt( IdBt, AcDb::kForRead );
	if( pBt.openStatus() != Acad::eOk )
		return FALSE;

	if( pBt->has( strName ) == true )
	{
		if( Acad::eOk == pBt->getAt(strName, IdRes) )
			return TRUE;
	}

	return FALSE;
}

Acad::ErrorStatus TWArxBlokTableFun::CreateBlockDef( IN const AcGePoint3d& PtOrigin, IN const CString& strName, OUT AcDbObjectId& IdRes, IN vector<AcDbEntity*>& vEnt, IN AcDbDatabase* pCur /*= NULL */ )
{
	AcDbDatabase* pDb = pCur;

	if( pDb == NULL )
		pDb = acdbCurDwg();

	if( pDb == NULL )
		return Acad::eNoDatabase;

	Acad::ErrorStatus es = Acad::eOk;

	AcDbObjectId IdBt =	pDb->blockTableId();
	AcDbBlockTablePointer pBt( IdBt, AcDb::kForWrite );
	if( pBt.openStatus() != Acad::eOk )
		return pBt.openStatus();

	//创建块定义
	AcDbBlockTableRecord* pBtr = new AcDbBlockTableRecord;
	pBtr->setName( strName );
	pBtr->setOrigin( PtOrigin );

	AcDbObjectId IdBtr;
	es = pBt->add( IdBtr, pBtr );
	if( Acad::eOk != es )
	{
		for_each(vEnt.begin(), vEnt.end(), TWArxEntityFun::For_each_Delete() );
		TWFreePtr( pBtr );
		return es;
	}
	pBtr->close();
	pBt.close();

	AcDbBlockTableRecordPointer pBTR( IdBtr, AcDb::kForWrite );
	if( pBTR.openStatus() != Acad::eOk  )
	{
		for_each(vEnt.begin(), vEnt.end(), TWArxEntityFun::For_each_Delete() );
		return pBTR.openStatus();
	}

	TWArxEntityFun::For_each_AppendEnt2TableRecor FunObj1;
	FunObj1.m_pBtr = pBTR.object() ;

	TWArxEntityFun::For_each_AppendEnt2TableRecor FunObj = for_each( vEnt.begin(), vEnt.end(), FunObj1 );

	for_each( FunObj.m_vFalsEnt.begin(), FunObj.m_vFalsEnt.end(), TWArxEntityFun::For_each_Delete() );

	for_each( FunObj.m_vSuccEnt.begin(), FunObj.m_vSuccEnt.end(), TWArxEntityFun::For_each_Close() );

	IdRes = IdBtr;
	return es;
}

BOOL TWArxBlokTableFun::GetBlockTableRecordIterator( IN const CString& strName, OUT AcDbBlockTableRecordIterator*& pIte, IN AcDbDatabase* pCur /*= NULL */ )
{
	AcDbObjectId Id ;
	if( HasBlockTableRecord(strName, Id, pCur) == FALSE ) return FALSE;

	AcDbBlockTableRecordPointer pBtr( Id, AcDb::kForRead );
	if( pBtr.openStatus() != Acad::eOk ) return FALSE;

	pIte = NULL;
	pBtr->newIterator( pIte );
	if( pIte == NULL ) return FALSE;

	return TRUE;
}

void TWArxBlokTableFun::LoadBlockDef( IN const CString& strExtDB, IN const vector<CString>& vBlockName, OUT vector<CString>& vNoMatchName )
{
	Acad::ErrorStatus es = Acad::eOk;
	vNoMatchName.clear();

	//读入外部图库dwg
	AcDbDatabase* pDbSrc = new AcDbDatabase( false/*, true*/ );
	es                   = pDbSrc->readDwgFile( strExtDB );
	if( es != Acad::eOk ) 
	{
		TWFreePtr( pDbSrc );
		vNoMatchName.assign( vNoMatchName.begin(), vNoMatchName.end() );
		CString strPrompt;
		strPrompt.Format( _T("\n%s文件读取失败！\n请确认此文件是否存在或者已经被打开!"), strExtDB );
		ads_prompt( strPrompt );
		return ;
	}

	//在外部dwg查找BlockName
	AcDbBlockTable* pBt = NULL;
	es = pDbSrc->getBlockTable( pBt, AcDb::kForRead );
	if( pBt == NULL )
	{
		TWFreePtr( pDbSrc ); 
		vNoMatchName.assign( vNoMatchName.begin(), vNoMatchName.end() );
		return;
	}
	pBt->close();

	AcDbObjectIdArray IdSrcAry;
	int               nLen = (int)vBlockName.size();
	for ( int i = 0; i < nLen; i++ )
	{
		CString str = vBlockName[i];
		if( pBt->has(str) == true )
		{
			AcDbObjectId Id;
			es = pBt->getAt( str, Id );
			IdSrcAry.append( Id );
		}
		else
			vNoMatchName.push_back( str );
	}

	//一个没找到
	if( nLen == vNoMatchName.size() )
	{
		TWFreePtr( pDbSrc ); 
		return;
	}

	//加载
	AcDbIdMapping Mapping;
	es = pDbSrc->wblockCloneObjects( IdSrcAry,acdbCurDwg()->blockTableId(), Mapping, AcDb::kDrcReplace  );
	TWFreePtr( pDbSrc );
}

int  TWArxBlokTableFun::InsertDwgToCurrDwgBlockTableRecord(TCHAR *pszBlockName,TCHAR *lpszFileName, AcDbObjectId &id)
{
	AcDbDatabase *pDatabaseCur;
	AcDbDatabase *pDatabaseDwg;
	Acad::ErrorStatus es;
	pDatabaseCur = acdbHostApplicationServices()->workingDatabase();

	AcDbBlockTable *pBlockTable;

	if ( pDatabaseCur -> getBlockTable ( pBlockTable, AcDb::kForRead ) != Acad::eOk )
		return -1;

	if ( pBlockTable -> has ( pszBlockName ) )
	{
		pBlockTable->getAt(pszBlockName,id);
		pBlockTable -> close ();
		return 1;
	}
	pBlockTable->close();

	pDatabaseDwg=new AcDbDatabase(Adesk::kFalse);
	es = pDatabaseDwg->readDwgFile(lpszFileName);
	if (es!=Acad::eOk)
	{
		delete pDatabaseDwg;
		return 0;
	}
	es = pDatabaseCur->insert(id,pszBlockName,pDatabaseDwg);
	if (es==Acad::eOk)
	{
		delete pDatabaseDwg;
		return 2;
	}
	else
	{
		delete pDatabaseDwg;
		return 0;
	}
}

int TWArxBlokTableFun::InsertDwgToCurrDwgBlockTableRecord( TCHAR *pszBlockName,AcDbDatabase* pExtDB, AcDbObjectId &id )
{
	if( pExtDB == NULL ) return 0;

	AcDbDatabase *pDatabaseCur;
	AcDbDatabase *pDatabaseDwg;
	Acad::ErrorStatus es;
	pDatabaseCur = acdbHostApplicationServices()->workingDatabase();

	AcDbBlockTable *pBlockTable;

	if ( pDatabaseCur -> getBlockTable ( pBlockTable, AcDb::kForRead ) != Acad::eOk )
		return -1;

	if ( pBlockTable -> has ( pszBlockName ) )
	{
		pBlockTable->getAt(pszBlockName,id);
		pBlockTable -> close ();
		return 1;
	}
	pBlockTable->close();

	pDatabaseDwg = pExtDB;
	es           = pDatabaseCur->insert(id,pszBlockName,pDatabaseDwg);
	if (es==Acad::eOk)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

#pragma endregion TWArxBlokTableFun




#pragma region TWArxViewPortFun

Acad::ErrorStatus TWArxViewPortFun::Zoom( const AcGePoint3d& cenPt,double width,double height,BOOL zflag )
{
	AcDbViewTableRecord view;
	struct resbuf rb;
	struct resbuf wcs, dcs, ccs;         // ads_trans coord system flags
	ads_point vpDir;
	ads_point wmin, wmax;             // min and max corners of the zoom window
	ads_point wdcsmax, wdcsmin;   // windows corners in device coords
	AcGeVector3d viewDir;

	ads_real    lenslength,
		viewtwist,
		frontz,
		backz;

	ads_point target;

	int viewmode,
		tilemode,
		cvport;

	// Get window to zoom to:
	wmax[X]=cenPt.x+width/2.0;
	wmin[X]=cenPt.x-width/2.0;
	wmax[Y]=cenPt.y+height/2.0;
	wmin[Y]=cenPt.y-height/2.0;


	wmax[Z] = 0.0;
	wmin[Z] = 0.0;

	wcs.restype         = RTSHORT;         // WORLD coord system flag
	wcs.resval.rint = 0;
	ccs.restype         = RTSHORT;         // CURRENT coord system flag
	ccs.resval.rint = 1;
	dcs.restype         = RTSHORT;         // DEVICE coord system flag
	dcs.resval.rint = 2;

	// Get the 'VPOINT' direction vector
	ads_getvar( _T("VIEWDIR"), &rb);
	ads_trans(rb.resval.rpoint, &ccs, &wcs, 0, vpDir);
	viewDir.set(vpDir[X], vpDir[Y], vpDir[Z]);


	if (!zflag)
	{
		double len=(width>height)?height:width;
		wmax[X]+=0.025*len;
		wmax[Y]+=0.025*len;
		wmin[X]-=0.025*len;
		wmin[Y]-=0.025*len;
	}
	// convert upper right window corner to DCS
	ads_trans(wmax, &ccs, &dcs, 0, wdcsmax);

	// convert lower left window corner to DCS
	ads_trans(wmin, &ccs, &dcs, 0, wdcsmin);
	// calculate and set view center point
	AcGePoint2d cenPt1(cenPt.x,cenPt.y);
	view.setCenterPoint(cenPt1);

	// set view height and width and direction
	view.setHeight(fabs(wdcsmax[Y] - wdcsmin[Y]));
	view.setWidth(fabs(wdcsmax[X] - wdcsmin[X]));
	view.setViewDirection(viewDir);

	// get and set other properties
	ads_getvar( _T( "LENSLENGTH"), &rb);
	lenslength = rb.resval.rreal;
	view.setLensLength(lenslength);

	ads_getvar( _T("VIEWTWIST"), &rb);
	viewtwist = rb.resval.rreal;
	view.setViewTwist(viewtwist);

	ads_getvar(_T("FRONTZ"), &rb);
	frontz = rb.resval.rreal;

	ads_getvar( _T("BACKZ"), &rb);
	backz = rb.resval.rreal;

	ads_getvar( _T("VIEWMODE"), &rb);
	viewmode = rb.resval.rint;

	view.setPerspectiveEnabled(viewmode & 1);
	view.setFrontClipEnabled(viewmode & 2);
	view.setBackClipEnabled(viewmode & 4);
	view.setFrontClipAtEye(!(viewmode & 16));

	ads_getvar( _T("TILEMODE"), &rb);
	tilemode = rb.resval.rint;
	ads_getvar( _T("CVPORT"), &rb);
	cvport = rb.resval.rint;

	// Paperspace flag
	Adesk::Boolean paperspace =
		((tilemode == 0) && (cvport == 1)) ? Adesk::kTrue:Adesk::kFalse;
	view.setIsPaperspaceView(paperspace);

	if (Adesk::kFalse == paperspace)
	{
		view.setFrontClipDistance(frontz);
		view.setBackClipDistance(backz);
	}
	else
	{
		view.setFrontClipDistance(0.0);
		view.setBackClipDistance(0.0);
	}

	ads_getvar( _T("TARGET"), &rb);
	ads_trans(rb.resval.rpoint, &ccs, &wcs, 0, target);
	view.setTarget(AcGePoint3d(target[X], target[Y], target[Z]));

	acedSetCurrentView( &view, NULL );

	
	return Acad::eOk;
}

Acad::ErrorStatus TWArxViewPortFun::GetCurrentViwe( AcDbViewTableRecord& pVtr )
{
	AcDbViewTableRecord view ;
	struct resbuf rb;
	struct resbuf wcs, dcs, ccs;         // ads_trans coord system flags
	ads_point vpDir;
	ads_point wmin, wmax;             // min and max corners of the zoom window
	ads_point wdcsmax, wdcsmin;   // windows corners in device coords
	AcGeVector3d viewDir;

	ads_real    lenslength,
		viewtwist,
		frontz,
		backz;

	ads_point target;

	int viewmode,
		tilemode,
		cvport;

	wmax[Z] = 0.0;
	wmin[Z] = 0.0;

	wcs.restype         = RTSHORT;         // WORLD coord system flag
	wcs.resval.rint = 0;
	ccs.restype         = RTSHORT;         // CURRENT coord system flag
	ccs.resval.rint = 1;
	dcs.restype         = RTSHORT;         // DEVICE coord system flag
	dcs.resval.rint = 2;

	// Get the 'VPOINT' direction vector
	ads_getvar( _T("VIEWDIR"), &rb);
	ads_trans(rb.resval.rpoint, &ccs, &wcs, 0, vpDir);
	viewDir.set(vpDir[X], vpDir[Y], vpDir[Z]);

	// calculate and set view center point
	ads_getvar( _T("VIEWCTR"), &rb);
	AcGePoint2d Ptcen1(rb.resval.rpoint[0], rb.resval.rpoint[1] );
	view.setCenterPoint(Ptcen1);

	ads_getvar( _T("VIEWSIZE"), &rb);
	// set view height and width and direction
	view.setHeight((rb.resval.rreal));
	view.setWidth((rb.resval.rreal) * 3 );
	view.setViewDirection(viewDir);

	// get and set other properties
	ads_getvar( _T("LENSLENGTH"), &rb);
	lenslength = rb.resval.rreal;
	view.setLensLength(lenslength);

	ads_getvar( _T("VIEWTWIST"), &rb);
	viewtwist = rb.resval.rreal;
	view.setViewTwist(viewtwist);

	ads_getvar( _T("FRONTZ"), &rb);
	frontz = rb.resval.rreal;

	ads_getvar( _T("BACKZ"), &rb);
	backz = rb.resval.rreal;

	ads_getvar( _T("VIEWMODE"), &rb);
	viewmode = rb.resval.rint;

	view.setPerspectiveEnabled(viewmode & 1);
	view.setFrontClipEnabled(viewmode & 2);
	view.setBackClipEnabled(viewmode & 4);
	view.setFrontClipAtEye(!(viewmode & 16));

	ads_getvar( _T("TILEMODE"), &rb);
	tilemode = rb.resval.rint;
	ads_getvar( _T("CVPORT"), &rb);
	cvport = rb.resval.rint;

	// Paperspace flag
	Adesk::Boolean paperspace =
		((tilemode == 0) && (cvport == 1)) ? Adesk::kTrue:Adesk::kFalse;
	view.setIsPaperspaceView(paperspace);

	if (Adesk::kFalse == paperspace)
	{
		view.setFrontClipDistance(frontz);
		view.setBackClipDistance(backz);
	}
	else
	{
		view.setFrontClipDistance(0.0);
		view.setBackClipDistance(0.0);
	}

	ads_getvar( _T("TARGET"), &rb);
	ads_trans(rb.resval.rpoint, &ccs, &wcs, 0, target);
	view.setTarget(AcGePoint3d(target[X], target[Y], target[Z]));

	// update view
	acedSetCurrentView( &view, NULL );

	return Acad::eOk;
}

#pragma endregion TWArxViewPortFun



#pragma region TWArxRegappFun

BOOL TWArxRegappFun::RegisteAppname( IN const CString& strName )
{
	if( RTNORM == ads_regapp(strName) ) return TRUE;
	return FALSE;
}

#pragma endregion TWArxRegappFun




#pragma region TWArxSSelFun

int TWArxSSelFun::SelectEntities( IN const resbuf* pFilter, OUT ads_name ss )
{
	int nRet = acedSSGet( _T("X"), NULL, NULL, pFilter, ss );
	long Len = 0;
	acedSSLength( ss, &Len );
	return Len;
}

int TWArxSSelFun::SelectEntities( IN const resbuf* pFilter, OUT AcDbObjectIdArray& IdAry )
{
	ads_name ss;
	int nLen = SelectEntities( pFilter, ss );
	for ( int i = 0; i < nLen; i++ )
	{
		ads_name ent;
		AcDbObjectId Id;
		acedSSName( ss, i, ent );
		if( acdbGetObjectId(Id, ent) == Acad::eOk )
			IdAry.append( Id );
	}
	acedSSFree( ss );

	return IdAry.length();
}

int TWArxSSelFun::SelectEntities( IN ads_point PtLB, IN ads_point PtRT, OUT ads_name ss, IN const _TCHAR* chKey )
{
	int nRet = acedSSGet( chKey, PtLB, PtRT, NULL, ss );
	long Len = 0;
	acedSSLength( ss, &Len );
	return Len;
}

int TWArxSSelFun::SelectEntities( IN ads_point PtLB, IN ads_point PtRT, OUT AcDbObjectIdArray& IdAry, IN const _TCHAR* chKey )
{
	ads_name ss;
	int nLen = SelectEntities( PtLB, PtRT, ss, chKey );
	for ( int i = 0; i < nLen; i++ )
	{
		ads_name ent;
		AcDbObjectId Id;
		acedSSName( ss, i, ent );
		if( acdbGetObjectId(Id, ent) == Acad::eOk )
			IdAry.append( Id );
	}
	acedSSFree( ss );

	return IdAry.length();
}

int TWArxSSelFun::ObjectIdAry2Selectset( IN const vector<AcDbObjectId>& vIds, OUT ads_name ss )
{
	ads_name_clear(ss);
	ads_ssadd( NULL, NULL, ss );
	int nSize = vIds.size();
	int nRet = 0;
	for ( int i = 0; i < nSize; i++ )
	{
		ads_name ent;
		if( acdbGetAdsName(ent, vIds[i]) == Acad::eOk )
		{
			acedSSAdd( ent, ss, ss );
			nRet++;
		}
	}
	
	return nRet;
}

int TWArxSSelFun::Selectset2ObjectIdAry( IN ads_name ss, OUT vector<AcDbObjectId>& vIds )
{
	long Len = 0;

	ads_sslength( ss, &Len );
	for ( int i = 0; i < Len; i++ )
	{
		AcDbObjectId Id;
		ads_name     ent;

		ads_ssname( ss, i, ent );
		if( Acad::eOk == acdbGetObjectId(Id, ent) )
			vIds.push_back( Id );
	}
	return int(vIds.size());
}

#pragma endregion TWArxSSelFun




#pragma region TWArxResbufFun


resbuf* TWArxResbufFun::GetTail( IN resbuf* pList )
{
	resbuf* pTem = pList;
	if( pTem == NULL ) return NULL;

	while( pTem->rbnext != NULL )
		pTem = pTem->rbnext;

	return pTem;
}


resbuf* TWArxResbufFun::GetResbuf( IN resbuf* pList, IN int nCode )
{
	resbuf* pTemp = pList;

	if( pList == NULL ) return NULL;
	while( pTemp != NULL )
	{
		if( pTemp->restype == nCode )
			return pTemp;
		pTemp = pTemp->rbnext;
	}

	return NULL;
}

resbuf* TWArxResbufFun::GetResbuf( IN resbuf* pList, IN int nCode, IN int nIndex )
{
	resbuf* pTemp = pList;
	int     n     = 1;

	if( pList == NULL ) return NULL;
	while( pTemp != NULL )
	{
		if( pTemp->restype == nCode && n++ == nIndex )
			return pTemp;
		pTemp = pTemp->rbnext;
	}

	return NULL;
}

BOOL TWArxResbufFun::GetString( IN resbuf* pList, IN int nCode, OUT CString& strRes )
{
	strRes.Empty();
	resbuf* pRb = GetResbuf( pList, nCode );
	if( pRb == NULL ) return FALSE;
	strRes = pRb->resval.rstring;
	return TRUE;
}

BOOL TWArxResbufFun::GetString( IN resbuf* pList, IN int nCode, IN int nIndex, OUT CString& strRes )
{
	resbuf* pRb = GetResbuf( pList, nCode, nIndex );
	if( pRb == NULL ) return FALSE;

	strRes = pRb->resval.rstring;
	return TRUE;
}

BOOL TWArxResbufFun::GetReal( IN resbuf* pList, IN int nCode, OUT double& dRes )
{
	resbuf* pRb = GetResbuf( pList, nCode );
	if( pRb == NULL ) return FALSE;
	dRes = pRb->resval.rreal;
	return TRUE;
}

BOOL TWArxResbufFun::GetReal( IN resbuf* pList, IN int nCode, IN int nIndex, OUT double& dRes )
{
	resbuf* pRb = GetResbuf( pList, nCode, nIndex );
	if( pRb == NULL ) return FALSE;

	dRes = pRb->resval.rreal;
	return TRUE;
}

BOOL TWArxResbufFun::GetInt( IN resbuf* pList, IN int nCode, OUT int& nRes )
{
	resbuf* pRb = GetResbuf( pList, nCode );
	if( pRb == NULL ) return FALSE;
	nRes = pRb->resval.rint;
	return TRUE;
}

BOOL TWArxResbufFun::GetInt( IN resbuf* pList, IN int nCode, IN int nIndex, OUT int& nRes )
{
	resbuf* pRb = GetResbuf( pList, nCode, nIndex );
	if( pRb == NULL ) return FALSE;

	nRes = pRb->resval.rint;
	return TRUE;
}

#pragma endregion TWArxResbufFun




#pragma region CTwArxLineTypeFun

BOOL CTwArxLineTypeFun::Has( IN const CString& strLTName , AcDbObjectId& IdRes  )
{
	AcDbLinetypeTable *pLinetypeTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pLinetypeTbl, AcDb::kForRead);
	if( pLinetypeTbl == NULL ) return FALSE;
	pLinetypeTbl->close();

	if(!pLinetypeTbl->has(strLTName)) return FALSE;

	if( Acad::eOk != pLinetypeTbl->getAt( strLTName, IdRes ) )  return FALSE;
	return TRUE;

}


BOOL CTwArxLineTypeFun::LoadLineType( IN const CString& strLTName, AcDbObjectId& IdRes, IN const CString& strLTFile )
{
	CString str = strLTFile;

	if( strLTFile.IsEmpty() )
		str = _T("acadiso.lin");
	Acad::ErrorStatus es = acdbLoadLineTypeFile( strLTName, str, acdbCurDwg() );
	return Has( strLTName,IdRes );
}

#pragma endregion CTwArxLineTypeFun




#pragma region AcadDocumentManage

void AcadDocumentManage::GetCurDocument( OUT vector<AcApDocument*>& DocAry )
{
	DocAry.clear();
	AcApDocumentIterator* pIte = acDocManager->newAcApDocumentIterator();
	if( pIte == NULL ) return;
	for ( ; !pIte->done(); pIte->step() )
	{
		DocAry.push_back( pIte->document() );
	}
	delete pIte;
	pIte = NULL;
}

void AcadDocumentManage::ContextCreateDocument( void* pVoid )
{
	static _TCHAR chTemplate[] = _T("acad.dwt"); 
	int nCount = *((int*)pVoid);
	if (acDocManager->isApplicationContext()) 
	{ 
		for ( int i = 0; i < nCount; i++ )
		{
			acDocManager->appContextNewDocument( chTemplate ); 
		}

// 		AcApDocument* pLast =  AcadDocumentManage::GetLastDocument();
// 		if( pLast != NULL )
// 		{
// 			acDocManager->setCurDocument( pLast);
// 			//acDocManager->activateDocument( pLast );
// 			acDocManager->unlockDocument( pLast );
// 		}
	} 
} 

void AcadDocumentManage::ContextCloseDocument( void* pVoid )
{
	vector<AcApDocument*>* pCloseDocAry = (vector<AcApDocument*>*)pVoid;
	int                    nCount       = (int)pCloseDocAry->size();

	if (acDocManager->isApplicationContext()) 
	{ 
		for ( int i = 0; i < nCount; i++ )
		{
			acDocManager->closeDocument( pCloseDocAry->at(i) ); 
		}
	} 
}

void AcadDocumentManage::ContextNewProject( void* pVoid )
{
	vector<AcApDocument*>* pCloseDocAry = (vector<AcApDocument*>*)pVoid;
	static _TCHAR          chTemplate[] = _T("acad.dwt"); 
	if (acDocManager->isApplicationContext()) 
	{ 
		for ( int i = 0; i < 3; i++ )
		{
			acDocManager->appContextNewDocument( chTemplate ); 
		}

		AcApDocument* pLast =  AcadDocumentManage::GetLastDocument();
		if( pLast != NULL )
		{
			acDocManager->setCurDocument( pLast);
			acDocManager->unlockDocument( pLast );
		}

		int nCount = (int)pCloseDocAry->size();
		for ( int i = 0; i < nCount; i++ )
		{
			acDocManager->closeDocument( pCloseDocAry->at(i) ); 
		}
	} 
}


AcApDocument* AcadDocumentManage::GetLastDocument()
{
	AcApDocument*			pDoc		= NULL;
	AcApDocumentIterator*	pDocIter	= acDocManager->newAcApDocumentIterator();

	for ( ; !pDocIter->done(); pDocIter->step() )
		pDoc = pDocIter->document();

	delete pDocIter;
	pDocIter = NULL;
	return pDoc;
};


#pragma endregion AcadDocumentManage