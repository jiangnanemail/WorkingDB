#pragma once

/*
	定义图层列表下拉框
*/

class TWLayerCombox : public CAcUiStringComboBox
{
	 DECLARE_DYNAMIC(TWLayerCombox);

public:
	TWLayerCombox();
	virtual ~TWLayerCombox();

	//功能:加载图层名称
	//输入:pCurDB 工作数据库
	//输出:
	//返回:
	//说明:
	BOOL AutoLoad( AcDbDatabase* pCurDB = NULL );

public:

	void SetItemValue( IN const CString& strValue );

protected:
	DECLARE_MESSAGE_MAP()
};
