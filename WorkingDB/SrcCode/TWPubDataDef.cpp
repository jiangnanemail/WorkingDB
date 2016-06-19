#include "StdAfx.h"
#include "TWPubDataDef.h"


#pragma region CTwAtom_StringPair

CTwAtom_StringPair::CTwAtom_StringPair( IN const CString& strKey, IN const CString& strValue )
:TWPairObjAtom( strKey, strValue )
{

}

CTwAtom_StringPair::CTwAtom_StringPair()
:TWPairObjAtom()
{

}

CTwAtom_StringPair::~CTwAtom_StringPair()
{

}

CString& CTwAtom_StringPair::GetKey()
{
	return GetAtom1();
}

CString CTwAtom_StringPair::GetKey() const
{
	return GetAtom1();
}

void CTwAtom_StringPair::SetKey( IN const CString& strKey )
{
	SetAtom1( strKey );
}

CString& CTwAtom_StringPair::GetValue()
{
	return GetAtom2();
}

CString CTwAtom_StringPair::GetValue() const
{
	return GetAtom2();
}

void CTwAtom_StringPair::SetValue( IN const CString& strValue )
{
	SetAtom2( strValue );
}

#pragma endregion CTwAtom_StringPair



#pragma region CTwAtom_StringInt
CTwAtom_StringInt::CTwAtom_StringInt( IN const CString& str, IN int n )
:TWPairObjAtom( str, n )
{

}

CTwAtom_StringInt::CTwAtom_StringInt()
:TWPairObjAtom()
{

}

CTwAtom_StringInt::~CTwAtom_StringInt()
{

}

CString& CTwAtom_StringInt::GetString()
{
	return GetAtom1();
}

CString CTwAtom_StringInt::GetString() const
{
	return GetAtom1();
}

void CTwAtom_StringInt::SetString( IN const CString& strKey )
{
	SetAtom1( strKey );
}

int& CTwAtom_StringInt::GetInt()
{
	return GetAtom2();
}

int CTwAtom_StringInt::GetInt() const
{
	return GetAtom2();
}

void CTwAtom_StringInt::SetInt( int n )
{
	SetAtom2( n );
}

#pragma endregion CTwAtom_StringInt



#pragma region TWStingPairObjAry


TWStingPairObjAry::TWStingPairObjAry()
:vector<CTwAtom_StringPair>()
{

}

TWStingPairObjAry::~TWStingPairObjAry()
{

}

#pragma endregion TWStingPairObjAry



#pragma region CTwStingIntObjAry
CTwStingIntObjAry::CTwStingIntObjAry()
:vector<CTwAtom_StringInt>()
{

}

CTwStingIntObjAry::~CTwStingIntObjAry()
{

}

#pragma endregion CTwStingIntObjAry


#pragma region CTwAtom_SRI

CTwAtom_SRI::CTwAtom_SRI()
:TWTripleObjAtom()
{

}

CTwAtom_SRI::CTwAtom_SRI( IN const CString& str, IN double d, IN int n )
:TWTripleObjAtom( str, d, n )
{

}

CTwAtom_SRI::~CTwAtom_SRI()
{

}

CString& CTwAtom_SRI::GetString()
{
	return GetAtom1();
}

CString  CTwAtom_SRI::GetString() const
{
	return GetAtom1();
}

void CTwAtom_SRI::SetString( IN const CString& strKey )
{
	SetAtom1( strKey );
}

double& CTwAtom_SRI::GetDouble()
{
	return GetAtom2();
}

double  CTwAtom_SRI::GetDouble() const
{
	return GetAtom2();
}

void CTwAtom_SRI::SetDouble( double d )
{
	SetAtom2( d );
}

int& CTwAtom_SRI::GetInt()
{
	return GetAtom3();
}

int  CTwAtom_SRI::GetInt() const
{
	return GetAtom3();
}

void CTwAtom_SRI::SetInt( int n )
{
	SetAtom3( n );
}

#pragma endregion CTwAtom_SRI



#pragma region CTwSRIObjAry

CTwSRIObjAry::CTwSRIObjAry()
{

}

CTwSRIObjAry::~CTwSRIObjAry()
{

}

#pragma endregion CTwSRIObjAry



#pragma region TWAtom_StringDouble

TWAtom_StringDouble::TWAtom_StringDouble( IN const CString& str, IN double d )
:TWPairObjAtom<CString, double>( str, d )
{

}

TWAtom_StringDouble::TWAtom_StringDouble()
:TWPairObjAtom<CString, double>()
{
}

TWAtom_StringDouble::~TWAtom_StringDouble()
{

}

CString& TWAtom_StringDouble::GetString()
{
	return GetAtom1();
}

CString  TWAtom_StringDouble::GetString() const
{
	return GetAtom1();
}

void TWAtom_StringDouble::SetString( IN const CString& strKey )
{
	SetAtom1( strKey );
}

double& TWAtom_StringDouble::GetDouble()
{
	return GetAtom2();
}

double  TWAtom_StringDouble::GetDouble() const
{
	return GetAtom2();
}

void TWAtom_StringDouble::SetDouble( IN double n )
{
	SetAtom2( n );
}

#pragma endregion TWAtom_StringDouble


#pragma region TWAtom_StringPt3d

TWAtom_StringPt3d::TWAtom_StringPt3d( IN const CString& str, IN const AcGePoint3d& Pt )
:TWPairObjAtom<CString, AcGePoint3d>( str, Pt )
{

}

TWAtom_StringPt3d::TWAtom_StringPt3d()
:TWPairObjAtom<CString, AcGePoint3d>()
{

}

TWAtom_StringPt3d::~TWAtom_StringPt3d()
{

}

CString& TWAtom_StringPt3d::GetString()
{
	return GetAtom1();
}

CString TWAtom_StringPt3d::GetString() const
{
	return GetAtom1();
}

void TWAtom_StringPt3d::SetString( IN const CString& strKey )
{
	SetAtom1( strKey );
}

AcGePoint3d& TWAtom_StringPt3d::GetPoint()
{
	return GetAtom2();
}

AcGePoint3d TWAtom_StringPt3d::GetPoint() const
{
	return GetAtom2();
}

void TWAtom_StringPt3d::SetPoint( const AcGePoint3d& Pt )
{
	SetAtom2( Pt );
}

#pragma endregion TWAtom_StringPt3d