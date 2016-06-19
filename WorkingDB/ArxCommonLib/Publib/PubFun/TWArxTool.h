
#pragma once
#include "TWWorkingDatabase.h"

/*
	定义arx通用工具类
*/

//块参照工具类
#pragma region TWBlockRefenceTool
class ArxCommonLib_CLASS TWBlockRefenceTool
{
public:
	TWBlockRefenceTool();
	virtual ~TWBlockRefenceTool();

public:

	//功能:判定当前代理的blockref对象是否有效。
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL IsValid() const;


	//功能:块插入
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL Insert( IN const CString& strBlockName, IN const AcGePoint3d& PtIns, IN double dScale, IN double dRat, AcDbDatabase* pDb = NULL );

	//功能:生成块参照对象指针。
	//输入:
	//输出:
	//返回:
	//说明:
	static AcDbBlockReference* CreateBlockRefence( IN const CString& strBlockName, IN const AcGePoint3d& PtIns, IN double dScale, IN double dRat, AcDbDatabase* pDb = NULL );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	AcDbObjectId GetBlockRefId() const;


protected:

	AcDbObjectId    m_IdblockRef;						//块参照对象ID
	
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
	//m_bCommit是否提交事务;
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
	以下定义图层相关参数或者操作类
*/

//图层代理类
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

	//功能:初始化图层参数
	//输入:
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus Init( IN const AcDbObjectId IdLayer );
	
	//功能:创建图层
	//输入:pWorking 目标数据库；IdLayer 新创建图层ID。
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus Create( OUT AcDbObjectId& IdLayer) const;

	//功能:图层是否已经存在
	//输入:
	//输出:
	//返回:
	//说明:pWorking = NULL 当前数据库， 否则指定数据库中。
	BOOL IsExist() const;


	//功能:判定是否与target图层相等。
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL IsEqual( IN const TWArxLayer& Target ) const;

	//功能:更新图层属性
	//输入:
	//输出:
	//返回:
	//说明:pWorking = NULL 当前数据库， 否则指定数据库中。
	Acad::ErrorStatus Update() const;
	
protected:

	CString            m_strName;                         //名称
	int                m_nColor;                          //颜色
	bool               m_bIsFrozen;                       //是否冻结
	bool               m_bIsLocked;                       //是否锁定
	bool               m_bIsOff ;                         //是否关闭

	//CString            m_strLineType;//线型
	//CString            m_strLineW;//线宽
};

#pragma endregion TWArxLayer



//图层管理
#pragma region TWArxLayerMan
class ArxCommonLib_CLASS TWArxLayerMan : public TWWorkingDatabase
{
public:
	TWArxLayerMan();
	virtual ~TWArxLayerMan();

public:

	//功能:初始化图层结构
	//输入:
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus Init();

	//功能:获得所有图层名称
	//输入:
	//输出:
	//返回:图层名称数量
	//说明:
	int GetLayerNames( OUT vector<CString>& vLayerNames ) const;

	//功能:根据名称获得图层ID
	//输入:
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus GetLayerId( IN const CString& strLayerName, OUT AcDbObjectId& IdLayer ) const;

	//功能:获取图层对象
	//输入:
	//输出:
	//返回:图层对象数量
	//说明:
	int GetLayer( OUT TWAutoFreeVector<TWArxLayer>& vLayer ) const;


protected:

	//功能:获得图层名称
	//输入:
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus GetLayerName( IN const AcDbObjectId& Id , OUT CString& strName ) const;

protected:



protected:
	vector< AcDbObjectId >       m_vLayers;
};
#pragma endregion TWArxLayerMan



//扩展字典
#pragma region CTwArxDictionary
class ArxCommonLib_CLASS CTwArxDictionary
{
public:
	CTwArxDictionary();
	~CTwArxDictionary();

public:
	//功能:获取指定路径下的xrecord。
	//输入:
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus GetXrecordObject(IN const AcDbObjectId& IdRoot, IN const vector<CString>& vDicPath, IN const CString& strXrecordName, OUT AcDbXrecord*& pXrecord, IN AcDb::OpenMode os, AcDbDatabase* pCurDB = NULL ) const;

	//功能:在指定字典目录下创建字典和扩展记录。
	//输入:IdRoot 根字典；vDicPath 字典路径; strXrecordName 扩展记录名称。
	//输出:
	//返回:
	//说明:如果已存在则返回已存在记录。
	Acad::ErrorStatus CreateXrecord( IN const AcDbObjectId& IdRoot, IN const vector<CString>& vDicPath, IN const CString& strXrecordName, OUT AcDbObjectId& IdRes ) const;

	//功能:打开、获得指定根目录下的子字典对象。
	//输入:IdRoot 根字典，如果为空则为数据库的命名字典。
	//输出:
	//返回:
	//说明:
	Acad::ErrorStatus GetSubDictionaryID( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObjectId& IdSub, AcDbDatabase* pCurDB = NULL )const;
	Acad::ErrorStatus OpenSubDictionary( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbDictionary*& pDic, AcDb::OpenMode os )const;
	Acad::ErrorStatus OpenXrecord( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbXrecord*& pXrecord, AcDb::OpenMode os )const;
	Acad::ErrorStatus OpenSubObject( IN const AcDbObjectId& IdRoot, IN const CString& strKey, AcDbObject*& pObj, AcDb::OpenMode os )const;

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
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

	//功能:高亮对象
	//输入:
	//输出:
	//返回:
	//说明:
	void Highlight( IN ads_name ent );

protected:
	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	void Remove();
protected:
	ads_name m_ss;
};
#pragma endregion CTwAutoRedraw



//系统变量
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

//捕捉
#define  CTwSymstemVar_Snap(value)        CTwSymstemVar_INT CTWSYMSTEMVAR_SNAP( _T("OSMODE"), value)
//正交
#define  CTwSymstemVar_Ortho(value)       CTwSymstemVar_INT CTWSYMSTEMVAR_ORTHO( _T("ORTHOMODE"), value)   
//回显
#define  CTwSymstemVar_Cmdecho(value)     CTwSymstemVar_INT CTWSYMSTEMVAR_Cmdecho( _T("cmdecho"), value)



#pragma endregion CTwSymstemVar_INT

