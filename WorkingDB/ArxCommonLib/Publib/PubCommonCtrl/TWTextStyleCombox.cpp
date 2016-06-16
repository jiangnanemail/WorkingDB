#include "StdAfx.h"
#include "TWTextStyleCombox.h"
#include "../PubFun/TWArxCommonFun.h"
#include "../PubFun//TWMFCPubFun.h"

#pragma region TWTextStyleCombox
IMPLEMENT_DYNAMIC( TWTextStyleCombox, CAcUiStringComboBox );
BEGIN_MESSAGE_MAP( TWTextStyleCombox, CAcUiStringComboBox )
END_MESSAGE_MAP()
TWTextStyleCombox::TWTextStyleCombox()
:CAcUiStringComboBox()
{

}

TWTextStyleCombox::~TWTextStyleCombox()
{

}

BOOL TWTextStyleCombox::AutoLoad( AcDbDatabase* pCurDB /*= NULL */ )
{
	vector<CString> vTextStyleNames;
	TWArxTextStyleFun::GetTextStyleNames( vTextStyleNames, pCurDB );

	int nSize = vTextStyleNames.size();
	for ( int i = 0; i < nSize; i++ )
	{
		AddString( vTextStyleNames[i] );
	}

	return TRUE;
}

void TWTextStyleCombox::SetItemValue( IN const CString& strValue )
{
	CTwDlgItemOpFun::SetComboxValue( (CDialog*)GetParent(), GetDlgCtrlID(), strValue );
}

#pragma endregion TWTextStyleCombox