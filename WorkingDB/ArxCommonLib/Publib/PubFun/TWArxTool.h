
#pragma once
#include "TWWorkingDatabase.h"

/*
	����arxͨ�ù�����
*/

//����չ�����
#pragma region TWBlockRefenceTool
class ArxCommonLib_CLASS TWBlockRefenceTool
{
public:
	TWBlockRefenceTool();
	virtual ~TWBlockRefenceTool();

public:

	//����:�ж���ǰ�����blockref�����Ƿ���Ч��
	//����:
	//���:
	//����:
	//˵��:
	BOOL IsValid() const;


	//����:�����
	//����:
	//���:
	//����:
	//˵��:
	BOOL Insert( IN const CString& strBlockName, IN const AcGePoint3d& PtIns, IN double dScale, IN double dRat, AcDbDatabase* pDb = NULL );

	//����:���ɿ���ն���ָ�롣
	//����:
	//���:
	//����:
	//˵��:
	static AcDbBlockReference* CreateBlockRefence( IN const CString& strBlockName, IN const AcGePoint3d& PtIns, IN double dScale, IN double dRat, AcDbDatabase* pDb = NULL );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	AcDbObjectId GetBlockRefId() const;


protected:

	AcDbObjectId    m_IdblockRef;						//����ն���ID
	
	//attreq
};

#pragma endregion TWBlockRefenceTool



#pragma region TWLockCurDoc
class ArxCommonLib_CLASS TWLockCurDoc
{
public:
	TWLockCurDoc()
	{
		acDocManager->lockDocument( curDoc() );
	}
	~TWLockCurDoc()
	{
		acDocManager->unlockDocument( curDoc() );
	}
};
#pragma endregion TWLockCurDoc


#pragma region CTwAutoTransaction

class ArxCommonLib_CLASS CTwAutoTransaction
{
public:
	//m_bCommit�Ƿ��ύ����;
	CTwAutoTransaction( IN BOOL m_bUsed = FALSE )
	{
		m_bUsed = m_bUsed;
		acTransactionManagerPtr()->startTransaction();
	}

	~CTwAutoTransaction()
	{
		if( m_bUsed == TRUE )
			acTransactionManagerPtr()->endTransaction();
		else
			acTransactionManagerPtr()->abortTransaction();
	}

	void SetCommit( BOOL bUsed )
	{
		m_bUsed = bUsed;
	}

private:
	//CTwAutoTransaction() {}
	BOOL m_bUsed;
};
#pragma endregion CTwAutoTransaction




#pragma region TWZoomExt

class ArxCommonLib_CLASS TWZoomExt
{
public:
	TWZoomExt() { ads_command(RTSTR, _T("zoom"), RTSTR, _T("E"), 0); } 
	~TWZoomExt(){ ads_command(RTSTR, _T("zoom"), RTSTR, _T("P"), 0); }
};


#pragma endregion TWZoomExt

#pragma region TWZoomObj

class ArxCommonLib_CLASS TWZoomObj
{
public:
	TWZoomObj( ads_name ent ) { ads_command(RTSTR, _T("zoom"), RTSTR, _T("o"), RTENAME, ent, RTSTR,_T(""), 0 ); } 
	~TWZoomObj(){ ads_command(RTSTR, _T("zoom"), RTSTR, _T("P"), 0); }
};


#pragma endregion TWZoomObj



/*
	���¶���ͼ����ز������߲�����
*/

//ͼ�������
#pragma region TWArxLayer
class ArxCommonLib_CLASS TWArxLayer : public TWWorkingDatabase
{
public:
	TWArxLayer();
	~TWArxLayer();

public:

	//get or set function
	void SetName( IN const CString& strLayer );


public:

	//����:��ʼ��ͼ�����
	//����:
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus Init( IN const AcDbObjectId IdLayer );
	
	//����:����ͼ��
	//����:pWorking Ŀ�����ݿ⣻IdLayer �´���ͼ��ID��
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus Create( OUT AcDbObjectId& IdLayer) const;

	//����:ͼ���Ƿ��Ѿ�����
	//����:
	//���:
	//����:
	//˵��:pWorking = NULL ��ǰ���ݿ⣬ ����ָ�����ݿ��С�
	BOOL IsExist() const;


	//����:�ж��Ƿ���targetͼ����ȡ�
	//����:
	//���:
	//����:
	//˵��:
	BOOL IsEqual( IN const TWArxLayer& Target ) const;

	//����:����ͼ������
	//����:
	//���:
	//����:
	//˵��:pWorking = NULL ��ǰ���ݿ⣬ ����ָ�����ݿ��С�
	Acad::ErrorStatus Update() const;
	
protected:

	CString            m_strName;                         //����
	int                m_nColor;                          //��ɫ
	bool               m_bIsFrozen;                       //�Ƿ񶳽�
	bool               m_bIsLocked;                       //�Ƿ�����
	bool               m_bIsOff ;                         //�Ƿ�ر�

	//CString            m_strLineType;//����
	//CString            m_strLineW;//�߿�
};

#pragma endregion TWArxLayer



//ͼ�����
#pragma region TWArxLayerMan
class ArxCommonLib_CLASS TWArxLayerMan : public TWWorkingDatabase
{
public:
	TWArxLayerMan();
	virtual ~TWArxLayerMan();

public:

	//����:��ʼ��ͼ��ṹ
	//����:
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus Init();

	//����:�������ͼ������
	//����:
	//���:
	//����:ͼ����������
	//˵��:
	int GetLayerNames( OUT vector<CString>& vLayerNames ) const;

	//����:�������ƻ��ͼ��ID
	//����:
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus GetLayerId( IN const CString& strLayerName, OUT AcDbObjectId& IdLayer ) const;

	//����:��ȡͼ�����
	//����:
	//���:
	//����:ͼ���������
	//˵��:
	int GetLayer( OUT TWAutoFreeVector<TWArxLayer>& vLayer ) const;


protected:

	//����:���ͼ������
	//����:
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus GetLayerName( IN const AcDbObjectId& Id , OUT CString& strName ) const;

protected:



protected:
	vector< AcDbObjectId >       m_vLayers;
};
#pragma endregion TWArxLayerMan



//��չ�ֵ�
#pragma region CTwArxDictionary
class ArxCommonLib_CLASS CTwArxDictionary
{
public:
	CTwArxDictionary();
	~CTwArxDictionary();

public:
	//����:��ȡָ��·���µ�xrecord��
	//����:
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus GetXrecordObject(IN const AcDbObjectId& IdRoot, IN const vector<CString>& vDicPath, IN const CString& strXrecordName, OUT AcDbXrecord*& pXrecord, IN AcDb::OpenMode os, AcDbDatabase* pCurDB = NULL ) const;

	//����:��ָ���ֵ�Ŀ¼�´����ֵ����չ��¼��
	//����:IdRoot ���ֵ䣻vDicPath �ֵ�·��; strXrecordName ��չ��¼���ơ�
	//���:
	//����:
	//˵��:����Ѵ����򷵻��Ѵ��ڼ�¼��
	Acad::ErrorStatus CreateXrecord( IN const AcDbObjectId& IdRoot, IN const vector<CString>& vDicPath, IN const CString& strXrecordName, OUT AcDbObjectId& IdRes ) const;

	//����:�򿪡����ָ����Ŀ¼�µ����ֵ����
	//����:IdRoot ���ֵ䣬���Ϊ����Ϊ���ݿ�������ֵ䡣
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus GetSubDictionaryID( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObjectId& IdSub, AcDbDatabase* pCurDB = NULL )const;
	Acad::ErrorStatus OpenSubDictionary( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbDictionary*& pDic, AcDb::OpenMode os )const;
	Acad::ErrorStatus OpenXrecord( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbXrecord*& pXrecord, AcDb::OpenMode os )const;
	Acad::ErrorStatus OpenSubObject( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObject*& pObj, AcDb::OpenMode os )const;

	//����:
	//����:
	//���:
	//����:
	//˵��:
	Acad::ErrorStatus CreateSubDictionaryID( IN const AcDbObjectId& IdRoot, IN const CString& strKey, OUT AcDbObjectId& IdSubDic, IN AcRxClass* pRxObjType = AcDbDictionary::desc() )const;
	Acad::ErrorStatus CreateSubDictionary  ( IN const AcDbObjectId& IdRoot, IN const CString& strKey, OUT AcDbObjectId& IdSubDic )const;
	Acad::ErrorStatus CreateXRecord( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObjectId& IdSubDic ) const;


protected:

};
#pragma endregion CTwArxDictionary



#pragma region CTwAutoRedraw
class ArxCommonLib_CLASS CTwAutoRedraw
{
public:
	CTwAutoRedraw();
	~CTwAutoRedraw();

	//����:��������
	//����:
	//���:
	//����:
	//˵��:
	void Highlight( IN ads_name ent );

protected:
	//����:
	//����:
	//���:
	//����:
	//˵��:
	void Remove();
protected:
	ads_name m_ss;
};
#pragma endregion CTwAutoRedraw



//ϵͳ����
#pragma region CTwSymstemVar
class ArxCommonLib_CLASS CTwSymstemVar
{
public:
	CTwSymstemVar()                  { m_Buf.rbnext = NULL;};
	virtual ~CTwSymstemVar()         {};

protected:
	resbuf   m_Buf;
	CString  m_strSys;
};
#pragma endregion CTwSymstemVar




#pragma region CTwSymstemVar_INT
class ArxCommonLib_CLASS CTwSymstemVar_INT : CTwSymstemVar
{
public:
	CTwSymstemVar_INT( const CString& strSys, int nNew )
	{
		resbuf rb ;
		rb.rbnext =NULL;
		m_strSys = strSys;
		ads_getvar( strSys, &m_Buf );
		rb.restype = m_Buf.restype;
		rb.resval.rint = nNew;
		ads_setvar( strSys, &rb );
	}
	~CTwSymstemVar_INT()
	{
		ads_setvar( m_strSys, &m_Buf );
	}
};

//��׽
#define  CTwSymstemVar_Snap(value)        CTwSymstemVar_INT CTWSYMSTEMVAR_SNAP( _T("OSMODE"), value)
//����
#define  CTwSymstemVar_Ortho(value)       CTwSymstemVar_INT CTWSYMSTEMVAR_ORTHO( _T("ORTHOMODE"), value)   
//����
#define  CTwSymstemVar_Cmdecho(value)     CTwSymstemVar_INT CTWSYMSTEMVAR_Cmdecho( _T("cmdecho"), value)



#pragma endregion CTwSymstemVar_INT

