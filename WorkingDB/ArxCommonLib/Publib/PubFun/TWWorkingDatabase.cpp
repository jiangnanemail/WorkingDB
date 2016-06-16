#include "stdafx.h"
#include "TWWorkingDatabase.h"

#pragma region TWWorkingDatabase
TWWorkingDatabase::TWWorkingDatabase( IN AcDbDatabase* pWD /*= NULL */ )
{
	SetWrokingDB( pWD );
}

TWWorkingDatabase::TWWorkingDatabase()
{
	SetWrokingDB( NULL );
}

TWWorkingDatabase::~TWWorkingDatabase()
{

}

AcDbDatabase* TWWorkingDatabase::GetWorkingDB() const
{
	if( m_pWorkingDatabase == NULL ) return acdbCurDwg();
	return m_pWorkingDatabase;
}

void TWWorkingDatabase::SetWrokingDB( IN AcDbDatabase* pWD )
{
	m_pWorkingDatabase = pWD;
}

#pragma endregion TWWorkingDatabase



#pragma region CTwWorkingDatebaseSwitch

CTwWorkingDatebaseSwitch::CTwWorkingDatebaseSwitch()
{
	m_pOldDB = NULL;
}

CTwWorkingDatebaseSwitch::CTwWorkingDatebaseSwitch( IN AcDbDatabase* pWorkingDB )
{
	Push( pWorkingDB );
}

CTwWorkingDatebaseSwitch::~CTwWorkingDatebaseSwitch()
{
	Pop();
}

void CTwWorkingDatebaseSwitch::Push( IN AcDbDatabase* pWorkingDB )
{
	m_pOldDB = acdbHostApplicationServices()->workingDatabase();
	acdbHostApplicationServices()->setWorkingDatabase( pWorkingDB );
}

AcDbDatabase* CTwWorkingDatebaseSwitch::Pop()
{
	if( m_pOldDB == NULL ) return NULL;
	AcDbDatabase* p  = acdbHostApplicationServices()->workingDatabase();
	acdbHostApplicationServices()->setWorkingDatabase( m_pOldDB );
	m_pOldDB = NULL;
	return p;
}

#pragma endregion CTwWorkingDatebaseSwitch
