#pragma once

/*
	定义颜色列表下拉框
*/

class TWColorCombox : public CAcUiColorComboBox 
{
	 DECLARE_DYNAMIC(TWColorCombox);

public:
	TWColorCombox();
	virtual ~TWColorCombox();

public:
	//功能:设置当前颜色
	//输入:nValue 岩石索引值。
	//输出:
	//返回:
	//说明:
	void SetItemValue( IN int nValue );

	void GetItemValue( OUT int& nValue );
protected:

protected:
	DECLARE_MESSAGE_MAP()
};