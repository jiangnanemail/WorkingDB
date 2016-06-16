#pragma once

/*
	有关MFC公共方法定义
*/

/*
	对话框控件的操作
*/
class CTwDlgItemOpFun
{
public:

	//功能:设置控件内容
	//输入:
	//输出:
	//返回:
	//说明:一般用于edit droplist的combox等一般的控件。
	static BOOL SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN const CString& strValue );
	static BOOL SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN int nValue );
	static BOOL SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN double dValue, int nDec = 3, BOOL bTrim = TRUE );

	//功能:获取控件内容
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN CString& strValue );
	static BOOL GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN int& nValue );
	static BOOL GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN double& dValue );

	//功能:设置combox控件内容
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL SetComboxValue( IN const CDialog* pParent, IN UINT Id, IN const CString& strValue );

	//功能:下拉框添加内容
	//输入:bDelete 是否删除原有条目
	//输出:
	//返回:
	//说明:
	static BOOL AddComboxStrings( IN const CDialog* pParent, IN UINT Id, IN const CStringArray& ItemAry, BOOL bDelete = TRUE );

	//功能:check btn or radio btn状态获取和设置。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetButtonCheckStatus( IN const CDialog* pParent, IN UINT Id, OUT BOOL& bCheck );
	static BOOL SetButtonCheckStatus( IN const CDialog* pParent, IN UINT Id, IN BOOL bCheck );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetDlgItemEnableStatus( IN const CDialog* pParent, IN UINT Id, OUT BOOL& bStatus );
	static BOOL SetDlgItemEnableStatus( IN const CDialog* pParent, IN UINT Id, IN BOOL bStatus );

};


class CTwFilePath
{
public:
	//功能:获得模块所在文件路径。
	//输入:
	//输出:
	//返回:
	//说明:返回的路径最后没有 '\'.
	static BOOL GetModulePath( IN HMODULE hModule, CString& strPath );
};


//一般文件的操作
class CTwFile
{
public:

	//功能:获取一个文件或者全路径文件下的文件扩展名。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetFileExtName( IN const CString& strFullPath, OUT CString& strExtName );

	//功能:判定 strFileFullPath 是否存在。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL FileExist( IN const CString& strFileFullPath );

	//功能:获取文件的名称，不包括扩展名。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetFileName( IN const CString& strFullPath, OUT CString& strFileName );

	//功能:获取路径，减去文件名+扩展名
	//输入:
	//输出:
	//返回:
	//说明:最后没有 "\"
	static BOOL GetPath( IN const CString& strFullPath, OUT CString& strPath );

};