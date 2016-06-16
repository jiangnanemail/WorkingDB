#include "StdAfx.h"
#include "TWColorCombox.h"

#include "StdAfx.h"
#include "TWColorCombox.h"

#pragma region TWColorCombox
IMPLEMENT_DYNAMIC( TWColorCombox, CAcUiColorComboBox );

BEGIN_MESSAGE_MAP( TWColorCombox, CAcUiColorComboBox )
END_MESSAGE_MAP()
TWColorCombox::TWColorCombox()
:CAcUiColorComboBox()
{
}

TWColorCombox::~TWColorCombox()
{

}

void TWColorCombox::SetItemValue( IN int nValue )
{
	int nItem = FindItemByColorIndex( nValue );   
	if ( nItem < 0 )
		nItem = AddColorToMRU( nValue );  

	SetCurSel( nItem );  
}

void TWColorCombox::GetItemValue( OUT int& nValue )
{
	nValue = GetCurrentItemColorIndex();
}

#pragma endregion TWColorCombox