#pragma once
/*
	����������ʽ�б�������
*/

class TWNumericEdit : public CAcUiNumericEdit
{
	 DECLARE_DYNAMIC(TWNumericEdit);

public:
	TWNumericEdit();
	virtual ~TWNumericEdit();

public:
	void SetItemValue( IN double dValue,IN int nDec = 3, BOOL bTrim = TRUE );  
	void GetItemValue( double& dValue ) const;

protected:
	DECLARE_MESSAGE_MAP()
};