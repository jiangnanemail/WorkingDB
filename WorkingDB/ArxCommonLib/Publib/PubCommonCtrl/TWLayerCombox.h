#pragma once

/*
	����ͼ���б�������
*/

class TWLayerCombox : public CAcUiStringComboBox
{
	 DECLARE_DYNAMIC(TWLayerCombox);

public:
	TWLayerCombox();
	virtual ~TWLayerCombox();

	//����:����ͼ������
	//����:pCurDB �������ݿ�
	//���:
	//����:
	//˵��:
	BOOL AutoLoad( AcDbDatabase* pCurDB = NULL );

public:

	void SetItemValue( IN const CString& strValue );

protected:
	DECLARE_MESSAGE_MAP()
};
