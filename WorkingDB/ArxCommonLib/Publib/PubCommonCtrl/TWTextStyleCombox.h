#pragma once

/*
	����������ʽ�б�������
*/

class TWTextStyleCombox : public CAcUiStringComboBox
{
	 DECLARE_DYNAMIC(TWTextStyleCombox);

public:
	TWTextStyleCombox();
	virtual ~TWTextStyleCombox();

	//����:����������ʽ����
	//����:pCurDB �������ݿ�
	//���:
	//����:
	//˵��:
	BOOL AutoLoad( AcDbDatabase* pCurDB = NULL );

	void SetItemValue( IN const CString& strValue );

protected:
	DECLARE_MESSAGE_MAP()
};
