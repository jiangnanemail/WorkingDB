#pragma once
/*
	字符串相关的操作方法
*/

class StringCommonFun
{
public:
	//功能:字符串分解
	//输入:strSrc 被分解字符串; strSymbol 分割符合;vArr 分解返回点原子字符串。 
	//输出:
	//返回:
	//说明:源字符串最后是否有分割分割符均可。
	static int StringResolving( IN const CString& strSrc, IN const CString& strSymbol, OUT CStringArray& vArr );
	static int StringResolving( IN const CString& strSrc, IN const CString& strSymbol, OUT vector<CString>& vArr );

	//功能:分解字符串
	//输入:strSrc 被分解字符串;vArr 分解返回点原子字符串; vSymbol可能存在的所有分割符号。
	//输出:
	//返回:
	//说明:分割字符串是使用第一出现在strSrc中的且在vSymbol中的符号。
	static int StringResolving( IN const CString& strSrc, IN const vector<CString>& vSymbol, OUT vector<CString>& vArr );

	//功能:字符串合并
	//输入:vStr 被合并字符串数组; strSymbol 分隔符。
	//输出:
	//返回:合并字符串
	//说明:合并字符串最后没有分隔符。
	static CString StringConnecting( IN const CStringArray &vStr, IN const CString& strSymbol );

	//功能:实数转换为字符串。
	//输入: nDec 精度; bTrimZero 是否后削零。
	//输出:
	//返回:
	//说明:
	static CString Real2String( IN double dValue, IN int nDec = 3, IN BOOL bTrimZero = TRUE );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static CString Int2String( IN int nValue );

	//功能:将如 1：2000比例字符转换为 2000的实数。
	//输入:
	//输出:
	//返回:如何返回 < 0则计算错误
	//说明:
	static double GetScale( IN const CString& strScale );

	//功能:将源字符串从chFrom 到 _TCHAR To内容截取。
	//输入:
	//输出:
	//返回:
	//说明:在strsrc中chFrom索引位置小于To。
	static BOOL RemoveSubString( IN const CString& strSrc, IN _TCHAR chFrom, IN _TCHAR To, OUT CString& strRes );
};