#include "StdAfx.h"
#include "TWLayerCombox.h"
#include "../PubFun/TWArxCommonFun.h"
#include "../PubFun/TWMFCPubFun.h"

#pragma region TWLayerCombox
IMPLEMENT_DYNAMIC( TWLayerCombox, CAcUiStringComboBox );
BEGIN_MESSAGE_MAP( TWLayerCombox, CAcUiStringComboBox )
END_MESSAGE_MAP()
TWLayerCombox::TWLayerCombox()
:CAcUiStringComboBox()
{

}

TWLayerCombox::~TWLayerCombox()
{

}

BOOL TWLayerCombox::AutoLoad( AcDbDatabase* pCurDB /*= NULL */ )
{
	vector<CString> vLayerNames;
	TWArxLayerFun::GetLayerNames( vLayerNames, pCurDB );
	
	int nSize = vLayerNames.size();
	for ( int i = 0; i < nSize; i++ )
	{
		AddString( vLayerNames[i] );
	}

	return TRUE;
}

void TWLayerCombox::SetItemValue( IN const CString& strValue )
{
	CTwDlgItemOpFun::SetComboxValue( (CDialog*)GetParent(), GetDlgCtrlID(), strValue );
}


#pragma endregion TWLayerCombox