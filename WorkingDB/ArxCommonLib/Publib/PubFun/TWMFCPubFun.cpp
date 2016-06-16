#include "StdAfx.h"
#include "TWMFCPubFun.h"
#include "shlwapi.h"
#include "TWStringPubFun.h"

#pragma region CTwDlgItemOpFun

BOOL CTwDlgItemOpFun::SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN const CString& strValue )
{
	if( pParent == NULL ) return FALSE;

	CWnd* pWnd = pParent->GetDlgItem( Id );
	if( pWnd == NULL ) return FALSE;

	pWnd->SetWindowText( strValue );

	return TRUE;
}

BOOL CTwDlgItemOpFun::SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN int nValue )
{

	return SetDlgItemValue( pParent, Id, StringCommonFun::Int2String(nValue) );
}

BOOL CTwDlgItemOpFun::SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN double dValue, int nDec /*= 3*/, BOOL bTrim /*= TRUE */ )
{
	return SetDlgItemValue( pParent, Id, StringCommonFun::Real2String(dValue, nDec, bTrim) );
}

BOOL CTwDlgItemOpFun::GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN CString& strValue )
{
	if( pParent == NULL ) return FALSE;

	CWnd* pWnd = pParent->GetDlgItem( Id );
	if( pWnd == NULL ) return FALSE;

	pWnd->GetWindowText( strValue );

	return TRUE;
}

BOOL CTwDlgItemOpFun::GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN int& nValue )
{
	CString str;
	BOOL    b = GetDlgItemValue( pParent, Id, str );
	if( b == FALSE ) return b;

	nValue = _tstoi( str );

	return TRUE;

}

BOOL CTwDlgItemOpFun::GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN double& dValue )
{
	CString str;
	BOOL    b = GetDlgItemValue( pParent, Id, str );
	if( b == FALSE ) return b;

	dValue = _tstof( str );

	return TRUE;
}

BOOL CTwDlgItemOpFun::SetComboxValue( IN const CDialog* pParent, IN UINT Id, IN const CString& strValue )
{
	if( pParent == NULL ) return FALSE;

	CComboBox* pComb = ( CComboBox* ) pParent->GetDlgItem( Id );
	if( pComb == NULL ) return FALSE;

	DWORD dwStyle = pComb->GetStyle();

	BOOL bUsingCurTxt = TRUE;
	dwStyle &= 3;
	if( dwStyle == CBS_DROPDOWNLIST )
		bUsingCurTxt = FALSE;

	int nIndex = -1;
	int nSize = pComb->GetCount();
	for ( int i = 0; i < nSize; i++ )
	{
		CString strItem ;
		pComb->GetLBText( i, strItem );
		if( strValue.CompareNoCase( strItem ) ==0 )
		{
			nIndex = i;
			break;;
		}
	}

	if( nIndex < 0 )
	{
		if( bUsingCurTxt )
			pComb->SetWindowText( strValue );
		else
			pComb->SetCurSel( 0 );
	}
	else
		pComb->SetCurSel( nIndex );

	return TRUE;
}

BOOL CTwDlgItemOpFun::AddComboxStrings( IN const CDialog* pParent, IN UINT Id, IN const CStringArray& ItemAry, BOOL bDelete /*= TRUE */ )
{
	if( pParent == NULL ) return FALSE;

	CComboBox* pComb = ( CComboBox* ) pParent->GetDlgItem( Id );
	if( pComb == NULL ) return FALSE;
	
	if( bDelete )
	{
		while(pComb->GetCount() != 0 )
		{
			pComb->DeleteString( 0 );
		}
	}

	for ( int i = 0; i < ItemAry.GetCount(); i++ )
	{
		pComb->AddString( ItemAry[i] );
	}

	return TRUE;
}

BOOL CTwDlgItemOpFun::GetButtonCheckStatus( IN const CDialog* pParent, IN UINT Id, OUT BOOL& bCheck )
{
	if( pParent == NULL ) return FALSE;

	CButton* pBtn = ( CButton* ) pParent->GetDlgItem( Id );
	if( pBtn == NULL ) return FALSE;

	bCheck = pBtn->GetCheck();
	return TRUE;
}

BOOL CTwDlgItemOpFun::SetButtonCheckStatus( IN const CDialog* pParent, IN UINT Id, IN BOOL bCheck )
{
	if( pParent == NULL ) return FALSE;

	CButton* pBtn = ( CButton* ) pParent->GetDlgItem( Id );
	if( pBtn == NULL ) return FALSE;

	 pBtn->SetCheck( bCheck );

	 return TRUE;
}

BOOL CTwDlgItemOpFun::GetDlgItemEnableStatus( IN const CDialog* pParent, IN UINT Id, OUT BOOL& bStatus )
{
	if( pParent == NULL ) return FALSE;

	CWnd* pWnd = pParent->GetDlgItem( Id );
	if( pWnd == NULL ) return FALSE;

	bStatus = pWnd->IsWindowEnabled();

	return bStatus;
}

BOOL CTwDlgItemOpFun::SetDlgItemEnableStatus( IN const CDialog* pParent, IN UINT Id, IN BOOL bStatus )
{
	if( pParent == NULL ) return FALSE;

	CWnd* pWnd = pParent->GetDlgItem( Id );
	if( pWnd == NULL ) return FALSE;

	return pWnd->EnableWindow( bStatus );
}

#pragma endregion CTwDlgItemOpFun



#pragma region CTwFilePath
BOOL CTwFilePath::GetModulePath( IN HMODULE hModule, CString& strPath )
{
	_TCHAR szModuleName[_MAX_PATH];
	BOOL b = ::GetModuleFileName( hModule, szModuleName , _MAX_PATH );
	if(!b)
		return FALSE;
	strPath = szModuleName;
	int nPos = strPath.ReverseFind( _T('\\') );
	if( nPos <0 )
		return FALSE;
	strPath = strPath.Left( nPos );
	return TRUE;
}
#pragma endregion CTwFilePath



#pragma region CTwFile

BOOL CTwFile::GetFileExtName( IN const CString& strFullPath, OUT CString& strExtName )
 {
	int nPos = strFullPath.ReverseFind( _T('.') );
	if( nPos < 0 ) return FALSE;
	strExtName = strFullPath.Right( strFullPath.GetLength()- nPos - 1 );
	return TRUE;
}

BOOL CTwFile::FileExist( IN const CString& strFileFullPath )
{
	return PathFileExists( strFileFullPath )? TRUE : FALSE;
}

BOOL CTwFile::GetFileName( IN const CString& strFullPath, OUT CString& strFileName )
{
	int nPosDot = strFullPath.ReverseFind(  _T('.') );
	int nPosSy  = strFullPath.ReverseFind( _T('\\') );

	if( nPosSy < 0 || nPosDot < 0 ) return FALSE;

	strFileName = strFullPath.Mid( nPosSy+1, nPosDot - nPosSy - 1 );

	return TRUE;
}

BOOL CTwFile::GetPath( IN const CString& strFullPath, OUT CString& strPath )
{
	
	int nPosSy  = strFullPath.ReverseFind( _T('\\') );
	if( nPosSy < 0 ) return FALSE;

	strPath = strFullPath.Left( nPosSy );

	return TRUE;
}

#pragma endregion CTwFile
