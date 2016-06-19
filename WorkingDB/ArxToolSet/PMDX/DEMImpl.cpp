#include "StdAfx.h"
#include "DEMImpl.h"

#pragma region ElevationObjectPick

ElevationObjectPick::ElevationObjectPick()
{

}

ElevationObjectPick::~ElevationObjectPick()
{

}

BOOL ElevationObjectPick::PickElevationObjects( OUT vector<AcDbObjectId>& vIsoHeight, OUT vector<AcDbObjectId>& vElePoint ) const
{
	AcDbObjectId IdSpace = acdbCurDwg()->currentSpaceId();

	AcDbBlockTableRecord* pBtr = NULL;
	acdbOpenObject( pBtr, IdSpace, AcDb::kForRead );
	if( pBtr == NULL ) return FALSE;
	pBtr->close();

	AcDbBlockTableRecordIterator* pIte = NULL;
	pBtr->newIterator( pIte );
	if( pIte == NULL ) return FALSE;

	//遍历当前所有对象
	for ( pIte->start(); !pIte->done(); pIte->step() )
	{
		AcDbObjectId Id;
		pIte->getEntityId( Id );
	}


	return FALSE;
}

BOOL ElevationObjectPick::IsIsoHeight( IN const AcDbObjectId& Id ) const
{
	return FALSE;
}

BOOL ElevationObjectPick::IsElePoint( IN const AcDbObjectId& Id ) const
{
	return FALSE;
}

#pragma endregion ElevationObjectPick



#pragma region ElevationDisperse

ElevationDisperse::ElevationDisperse()
{

}

ElevationDisperse::~ElevationDisperse()
{

}

BOOL ElevationDisperse::IsoHeightDisperse( IN const vector<AcDbObjectId>& vIsoHeight, OUT vector<AcGePoint3d>& vPts ) const
{
	return FALSE;
}

BOOL ElevationDisperse::ElevPointDisperse( IN const vector<AcDbObjectId>& vElePoint, OUT vector<AcGePoint3d>& vPts ) const
{
	return FALSE;
}

#pragma endregion ElevationDisperse