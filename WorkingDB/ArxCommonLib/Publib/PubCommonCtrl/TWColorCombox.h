#pragma once

/*
	������ɫ�б�������
*/

class TWColorCombox : public CAcUiColorComboBox 
{
	 DECLARE_DYNAMIC(TWColorCombox);

public:
	TWColorCombox();
	virtual ~TWColorCombox();

public:
	//����:���õ�ǰ��ɫ
	//����:nValue ��ʯ����ֵ��
	//���:
	//����:
	//˵��:
	void SetItemValue( IN int nValue );

	void GetItemValue( OUT int& nValue );
protected:

protected:
	DECLARE_MESSAGE_MAP()
};