#pragma once
/*
	�ַ�����صĲ�������
*/

class StringCommonFun
{
public:
	//����:�ַ����ֽ�
	//����:strSrc ���ֽ��ַ���; strSymbol �ָ����;vArr �ֽⷵ�ص�ԭ���ַ����� 
	//���:
	//����:
	//˵��:Դ�ַ�������Ƿ��зָ�ָ�����ɡ�
	static int StringResolving( IN const CString& strSrc, IN const CString& strSymbol, OUT CStringArray& vArr );
	static int StringResolving( IN const CString& strSrc, IN const CString& strSymbol, OUT vector<CString>& vArr );

	//����:�ֽ��ַ���
	//����:strSrc ���ֽ��ַ���;vArr �ֽⷵ�ص�ԭ���ַ���; vSymbol���ܴ��ڵ����зָ���š�
	//���:
	//����:
	//˵��:�ָ��ַ�����ʹ�õ�һ������strSrc�е�����vSymbol�еķ��š�
	static int StringResolving( IN const CString& strSrc, IN const vector<CString>& vSymbol, OUT vector<CString>& vArr );

	//����:�ַ����ϲ�
	//����:vStr ���ϲ��ַ�������; strSymbol �ָ�����
	//���:
	//����:�ϲ��ַ���
	//˵��:�ϲ��ַ������û�зָ�����
	static CString StringConnecting( IN const CStringArray &vStr, IN const CString& strSymbol );

	//����:ʵ��ת��Ϊ�ַ�����
	//����: nDec ����; bTrimZero �Ƿ�����㡣
	//���:
	//����:
	//˵��:
	static CString Real2String( IN double dValue, IN int nDec = 3, IN BOOL bTrimZero = TRUE );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	static CString Int2String( IN int nValue );

	//����:���� 1��2000�����ַ�ת��Ϊ 2000��ʵ����
	//����:
	//���:
	//����:��η��� < 0��������
	//˵��:
	static double GetScale( IN const CString& strScale );

	//����:��Դ�ַ�����chFrom �� _TCHAR To���ݽ�ȡ��
	//����:
	//���:
	//����:
	//˵��:��strsrc��chFrom����λ��С��To��
	static BOOL RemoveSubString( IN const CString& strSrc, IN _TCHAR chFrom, IN _TCHAR To, OUT CString& strRes );
};