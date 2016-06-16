#include "StdAfx.h"
#include "TWStringPubFun.h"


#pragma region StringCommonFun
CString StringCommonFun::StringConnecting( IN const CStringArray &vStr, IN const CString& strSymbol )
{
	CString strRes;
	for( int i = 0; i < (int)vStr.GetSize(); i++ )
	{
		if( i < vStr.GetSize() -1 )
			strRes += vStr[i] + strSymbol;
		else
			strRes += vStr[i];
	}

	return strRes;
}

int StringCommonFun::StringResolving( IN const CString& strSrc, IN const CString& strSymbol, OUT CStringArray& vArr )
{
	vArr.RemoveAll();

	int nStart  = 0;
	int nFgfLen = strSymbol.GetLength();
	int nLen    = strSrc.GetLength();
	do
	{
		int nPos = strSrc.Find( strSymbol, nStart );
		if( nPos < 0 )
		{
			if( nStart >= nLen )
				break;
			else
			{
				CString strT = strSrc.Mid( nStart, nLen-nStart );
				vArr.Add( strT );
				break;
			}
		}
		CString str = strSrc.Mid( nStart, nPos-nStart );
		nStart = nPos+nFgfLen;
		vArr.Add( str );

	}while( TRUE );

	return (int)vArr.GetCount();
}


int StringCommonFun::StringResolving( IN const CString& strSrc, IN const CString& strSymbol, OUT vector<CString>& vArr )
{
	vArr.clear();
	CStringArray Temp;
	int n = StringResolving( strSrc, strSymbol, Temp );
	for ( int i = 0; i < n; i++ )
		vArr.push_back( Temp[i] );

	return n;
}


int StringCommonFun::StringResolving( IN const CString& strSrc, IN const vector<CString>& vSymbol, OUT vector<CString>& vArr )
{
	int nSize =vSymbol.size();
	for ( int i = 0; i < nSize; i++ )
	{
		vector<CString> Temp;
		if( StringResolving(strSrc, vSymbol[i], Temp) > 1 )
		{
			vArr.assign( Temp.begin(), Temp.end() );
			return (int) vArr.size();
		}
	}

	return 0;
}

CString StringCommonFun::Real2String( IN double dValue, IN int nDec /*= 3*/, IN BOOL bTrimZero /*= TRUE */ )
{
	CString str;
	str.Format( _T("%.*lf"), nDec, dValue );

	if( bTrimZero == TRUE )
	{
		str.TrimRight( _T('0') );
		str.TrimRight( _T('.') );
	}
	return str;
}

CString StringCommonFun::Int2String( IN int nValue )
{
	CString str;
	str.Format( _T("%d"), nValue );

	return str;
}

double StringCommonFun::GetScale( IN const CString& strScale )
{
	//中文符号和英文符号
	CStringArray StrAry;
	if( 2 != StringCommonFun::StringResolving(strScale, _T(":"), StrAry) )
	{
		if( 2 != StringCommonFun::StringResolving(strScale, _T("："), StrAry)  )
			return -1;
	}

	CString str = StrAry[1];
	str.Trim();
	return _tstof( str );
}

BOOL StringCommonFun::RemoveSubString( IN const CString& strSrc, IN _TCHAR chFrom, IN _TCHAR chTo, OUT CString& strRes )
{
	int nLen = strSrc.GetLength();

	int nPos1 = strSrc.Find( chFrom );
	int nPos2 = strSrc.ReverseFind( chTo );
	if( nPos1 > nPos2 || nPos2 < 0 || nPos1 < 0 ) return FALSE;

	CString strLeft = strSrc.Left( nPos1 );
	CString strRight = strSrc.Right( nLen - nPos2 - 1 );

	strRes = strLeft + strRight;

	return TRUE;
}

#pragma endregion StringCommonFun

