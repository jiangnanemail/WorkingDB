#pragma once

/*
	定义文字样式列表下拉框
*/

class TWTextStyleCombox : public CAcUiStringComboBox
{
	 DECLARE_DYNAMIC(TWTextStyleCombox);

public:
	TWTextStyleCombox();
	virtual ~TWTextStyleCombox();

	//功能:加载文字样式名称
	//输入:pCurDB 工作数据库
	//输出:
	//返回:
	//说明:
	BOOL AutoLoad( AcDbDatabase* pCurDB = NULL );

	void SetItemValue( IN const CString& strValue );

protected:
	DECLARE_MESSAGE_MAP()
};
