#include "StdAfx.h"
#include "TWNumericEdit.h"
#include "../PubFun/TWStringPubFun.h"

#pragma region TWNumericEdit
IMPLEMENT_DYNAMIC( TWNumericEdit, CAcUiNumericEdit );

BEGIN_MESSAGE_MAP( TWNumericEdit, CAcUiNumericEdit )
END_MESSAGE_MAP()
TWNumericEdit::TWNumericEdit()
:CAcUiNumericEdit()
{

}

TWNumericEdit::~TWNumericEdit()
{

}

void TWNumericEdit::SetItemValue( IN double dValue, IN int nDec /*= FALSE*/, BOOL bTrim /*= TRUE */ )
{
	SetWindowText( StringCommonFun::Real2String(dValue, nDec, bTrim) );
}


void TWNumericEdit::GetItemValue( double& dValue ) const
{
	CString str;
	GetWindowText( str );
	dValue = _tstof( str );
}

#pragma endregion TWNumericEdit