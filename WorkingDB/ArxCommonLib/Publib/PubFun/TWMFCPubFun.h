#pragma once

/*
	�й�MFC������������
*/

/*
	�Ի���ؼ��Ĳ���
*/
class CTwDlgItemOpFun
{
public:

	//����:���ÿؼ�����
	//����:
	//���:
	//����:
	//˵��:һ������edit droplist��combox��һ��Ŀؼ���
	static BOOL SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN const CString& strValue );
	static BOOL SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN int nValue );
	static BOOL SetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN double dValue, int nDec = 3, BOOL bTrim = TRUE );

	//����:��ȡ�ؼ�����
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN CString& strValue );
	static BOOL GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN int& nValue );
	static BOOL GetDlgItemValue( IN const CDialog* pParent, IN UINT Id, IN double& dValue );

	//����:����combox�ؼ�����
	//����:
	//���:
	//����:
	//˵��:
	static BOOL SetComboxValue( IN const CDialog* pParent, IN UINT Id, IN const CString& strValue );

	//����:�������������
	//����:bDelete �Ƿ�ɾ��ԭ����Ŀ
	//���:
	//����:
	//˵��:
	static BOOL AddComboxStrings( IN const CDialog* pParent, IN UINT Id, IN const CStringArray& ItemAry, BOOL bDelete = TRUE );

	//����:check btn or radio btn״̬��ȡ�����á�
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetButtonCheckStatus( IN const CDialog* pParent, IN UINT Id, OUT BOOL& bCheck );
	static BOOL SetButtonCheckStatus( IN const CDialog* pParent, IN UINT Id, IN BOOL bCheck );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetDlgItemEnableStatus( IN const CDialog* pParent, IN UINT Id, OUT BOOL& bStatus );
	static BOOL SetDlgItemEnableStatus( IN const CDialog* pParent, IN UINT Id, IN BOOL bStatus );

};


class CTwFilePath
{
public:
	//����:���ģ�������ļ�·����
	//����:
	//���:
	//����:
	//˵��:���ص�·�����û�� '\'.
	static BOOL GetModulePath( IN HMODULE hModule, CString& strPath );
};


//һ���ļ��Ĳ���
class CTwFile
{
public:

	//����:��ȡһ���ļ�����ȫ·���ļ��µ��ļ���չ����
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetFileExtName( IN const CString& strFullPath, OUT CString& strExtName );

	//����:�ж� strFileFullPath �Ƿ���ڡ�
	//����:
	//���:
	//����:
	//˵��:
	static BOOL FileExist( IN const CString& strFileFullPath );

	//����:��ȡ�ļ������ƣ���������չ����
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetFileName( IN const CString& strFullPath, OUT CString& strFileName );

	//����:��ȡ·������ȥ�ļ���+��չ��
	//����:
	//���:
	//����:
	//˵��:���û�� "\"
	static BOOL GetPath( IN const CString& strFullPath, OUT CString& strPath );

};