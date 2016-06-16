#pragma once
class CTwRectangle;
/*
	定义arx相关的公共函数
*/

//图层相关
#pragma region TWArxLayerFun
class ArxCommonLib_CLASS TWArxLayerFun
{
public:
	//功能:获得当前所有的图层名称
	//输入:vLayerNames 返回图层名称; pCur 目标数据库。
	//输出:
	//返回:
	//说明:pCur 为NULL 使用当前数据库。
	static Acad::ErrorStatus GetLayerNames( OUT vector<CString>& vLayerNames, IN AcDbDatabase* pCur = NULL );

};

#pragma endregion TWArxLayerFun


//文字样式相关
#pragma region TWArxTextStyleFun
class  ArxCommonLib_CLASS TWArxTextStyleFun
{
public:
	//功能:获得当前所有文字样式的名称
	//输入:vTextStyleNames 返回文字样式名称;  pCur 目标数据库。
	//输出:
	//返回:
	//说明:pCur 为NULL 使用当前数据库。
	static Acad::ErrorStatus GetTextStyleNames( OUT vector<CString>& vTextStyleNames, IN AcDbDatabase* pCur = NULL );

	//功能:根据名称获得文字样式ID
	//输入:
	//输出:
	//返回:
	//说明:
	static AcDbObjectId GetTextStyleId( IN const CString strStyleName, IN AcDbDatabase* pCur = NULL  );

	static Acad::ErrorStatus CreateTextStyle( IN const CString& strName, IN const CString& strSHXName, IN const CString& strBigFront, IN double dWidthFactor );
};

#pragma endregion TWArxTextStyleFun




#pragma region TWArxBlokTableFun
class ArxCommonLib_CLASS TWArxBlokTableFun
{
public:
	//功能:测试是否存在给定的块定义名称。
	//输入:IdRes 如果存在使用IdRes返回此对象ID。
	//输出:
	//返回:
	//说明:
	static BOOL HasBlockTableRecord( IN const CString& strName, OUT AcDbObjectId& IdRes, IN AcDbDatabase* pCur = NULL );

	//功能:获得指定BlockTableRecord的实体迭代器。
	//输入:如果成功 pIte 返回迭代器指针。
	//输出:
	//返回:
	//说明:调用者需要释放 pIte.
	static BOOL GetBlockTableRecordIterator( IN const CString& strName, OUT AcDbBlockTableRecordIterator*& pIte, IN AcDbDatabase* pCur = NULL );

	//功能:创建块定义
	//输入:PtOrigin 块定义原点; strName 名称; IdRes 返回创建的块定义ID； vEnt 块定义内的子实体名称; pCur 目标数据库。
	//输出:
	//返回:
	//说明:vEnt实体控制权交予此函数处理，外部就不要再进行其他处理。
	static Acad::ErrorStatus CreateBlockDef( IN const AcGePoint3d& PtOrigin, IN const CString& strName, OUT AcDbObjectId& IdRes, IN vector<AcDbEntity*>& vEnt, IN AcDbDatabase* pCur = NULL );

	//功能:从外部文件夹中块定义。
	//输入:strExtDB 外部文件名称;vBlockName 需要加载的块名集合；vErrorBlockName 加载失败的块名。
	//输出:
	//返回:
	//说明:
	static void LoadBlockDef( IN const CString& strExtDB, IN const vector<CString>& vBlockName, OUT vector<CString>& vErrorBlockName );

	//功能:将由lpszFileName指定的Dwg文件作为块参照插入到当前图中，块定义名称命名为pszBlockName以Id返回他的块定义值
	//输入: pszBlockName:被指定的块名,lpszFileName：外部dwg完整名称,新插入的 block id
	//输出:
	//返回:1：当前图中存在同名块参照，2：插入成功，否则  失败
	//说明:
	static int InsertDwgToCurrDwgBlockTableRecord(TCHAR *pszBlockName,TCHAR *lpszFileName, AcDbObjectId &id);
	static int InsertDwgToCurrDwgBlockTableRecord(TCHAR *pszBlockName,AcDbDatabase* pExtDB, AcDbObjectId &id);


};
#pragma endregion TWArxBlokTableFun



//实体对象相关
#pragma region TWArxEntityFun
class ArxCommonLib_CLASS TWArxEntityFun
{
public:
	
	//功能:实体对象添加扩展字典
	//输入:IdObj、pObj添加目标对象。
	//输出:
	//返回:
	//说明:pObj 需要可写操作。如果已存在则直接返回。
	static Acad::ErrorStatus CreateExtendDictionary( IN const AcDbObjectId& IdObj, OUT AcDbObjectId& IdExtDic );
	static Acad::ErrorStatus CreateExtendDictionary( IN AcDbObject* pObj, OUT AcDbObjectId& IdExtDic );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static void TransformBy( vector<AcDbEntity*> vEnt, IN const AcGeMatrix3d& Mat );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static void GetGeometryExtend( IN const vector<AcDbEntity*> vEnt, OUT AcDbExtents& Ext );

	//功能:对实体外包计算的扩展。
	//输入:
	//输出:
	//返回:
	//说明:txt为水平或者竖直则等同于原始方法，如果其他情形则特殊处理
	static BOOL GetTxtGeometryExtend( IN const AcDbText* pTxt, OUT CTwRectangle* Rectangle );

	//功能:获得给定实体对象的句柄字符串
	//输入:ID 实体ID； chHanle 句柄值。
	//输出:
	//返回:
	//说明:
	static Acad::ErrorStatus GetHandString( IN const AcDbObjectId& Id, OUT _TCHAR* chHandle );

	//功能:实体类型判定。
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL IsA( IN ads_name ent, IN AcRxClass* pClass  );
	static BOOL IsA( IN const AcDbObjectId& Id, IN AcRxClass* pClass  );


	//功能:是否void指针
	//输入:
	//输出:
	//返回:
	//说明:
	static void Free( AcDbVoidPtrArray& vPtr );

	//功能:删除实体选择集中所有实体。
	//输入:
	//输出:
	//返回:
	//说明:
	static void DeleteSS( ads_name ss );

	//功能:实体添加模型空间
	//输入:pEnt 被添加实体; IdRes返回实体ID; bAutoCLose实体添加成功是否自动关闭操作; bAutoDel 实体添加实体是否是否指针。
	//输出:
	//返回:
	//说明:
	static Acad::ErrorStatus PostModelSpace( IN AcDbEntity* pEnt, OUT AcDbObjectId& IdRes, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE, IN BOOL bUseTran = FALSE );

	//功能:批量实体添加到模型空间
	//输入:
	//输出:
	//返回:
	//说明:bAutoDel、bAutoCLose 强烈要求使用默认值。
	static Acad::ErrorStatus PostModelSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE  );

	//功能:实体对象添加到当前空间
	//输入:
	//输出:
	//返回:
	//说明:
	static Acad::ErrorStatus PostCurSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE );


	class For_each_AppendEnt2TableRecor
	{
	public:
		void operator()( AcDbEntity* pEnt );

	public:
		AcDbBlockTableRecord*   m_pBtr;                             //块表记录
		vector<AcDbObjectId>    m_vSuccObjIds;                      //成功添加到块表记录的id
		vector<AcDbEntity*>     m_vSuccEnt;                         //成功实体指针
		vector<AcDbEntity*>     m_vFalsEnt;                         //失败实体指针 
	};

	class For_each_Close
	{
	public:
		void operator()( AcDbEntity* pEnt ); 
	};

	class For_each_Delete
	{
	public:
		void operator()( AcDbEntity* pEnt ); 
	};
};

#pragma endregion TWArxEntityFun



#pragma region TWArxViewPortFun
class ArxCommonLib_CLASS TWArxViewPortFun
{
public:

	//功能:缩放当前cad视口
	//输入:
	//输出:
	//返回:
	//说明:	
	static Acad::ErrorStatus Zoom( IN const AcGePoint3d& Ptcen,IN double dWidth,IN double dHeight,IN BOOL zflag );

	//功能:获得当前视口的参数
	//输入:
	//输出:
	//返回:
	//说明:
	static Acad::ErrorStatus GetCurrentViwe( AcDbViewTableRecord& pVtr );
};

#pragma endregion TWArxViewPortFun



#pragma region TWArxRegappFun
class ArxCommonLib_CLASS TWArxRegappFun
{
public:
    
	//功能:注册应用程序名称
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL RegisteAppname( IN const CString& strName );

};
#pragma endregion TWArxRegappFun



#pragma region CTwArxLineTypeFun
class ArxCommonLib_CLASS CTwArxLineTypeFun
{
public:

	static BOOL Has( IN const CString& strLTName, AcDbObjectId& IdRes );
	static BOOL LoadLineType( IN const CString& strLTName, AcDbObjectId& IdRes, IN const CString& strLTFile );
};
#pragma endregion CTwArxLineTypeFun



//实体选择集合
#pragma region TWArxSSelFun
class ArxCommonLib_CLASS TWArxSSelFun
{
public:
	//功能:通过过滤条件选择实体对象。
	//输入:
	//输出:
	//返回:实体选择数量。
	//说明:ss 需要调用者释放。
	static int SelectEntities( IN const resbuf* pFilter, OUT ads_name ss );
	static int SelectEntities( IN const resbuf* pFilter, OUT AcDbObjectIdArray& IdAry );


	//功能:使用范围选择对象
	//输入:
	//输出:
	//返回:实体选择数量。
	//说明:ss 需要调用者释放。
	static int SelectEntities( IN ads_point PtLB, IN ads_point PtRT, OUT ads_name ss, IN const _TCHAR* chKey = _T("W") );
	static int SelectEntities( IN ads_point PtLB, IN ads_point PtRT, OUT AcDbObjectIdArray& IdAry, IN const _TCHAR* chKey = _T("W") );

	//功能:对象id数组和实体选择集转换。
	//输入:
	//输出:
	//返回:成功返回的元素个数
	//说明:函数生成的ss选择集合，需要调用者释放。
	static int ObjectIdAry2Selectset( IN const vector<AcDbObjectId>& vIds, OUT ads_name ss );
	static int Selectset2ObjectIdAry( IN ads_name ss, OUT vector<AcDbObjectId>& vIds );
};
#pragma endregion TWArxSSelFun



#pragma region TWArxResbufFun
class ArxCommonLib_CLASS TWArxResbufFun
{
public:

	//功能:返回最后一个节点的指针。
	//输入:
	//输出:
	//返回:
	//说明:
	static resbuf* GetTail( IN resbuf* pList );

	//功能:查找节点
	//输入:
	//输出:
	//返回:
	//说明:
	static resbuf* GetResbuf( IN resbuf* pList, IN int nCode );
	static resbuf* GetResbuf( IN resbuf* pList, IN int nCode, IN int nIndex );

	//功能:获得指定节点的字符串值
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetString( IN resbuf* pList, IN int nCode, OUT CString& strRes );
	static BOOL GetString( IN resbuf* pList, IN int nCode, IN int nIndex, OUT CString& strRes );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetReal( IN resbuf* pList, IN int nCode, OUT double& dRes);
	static BOOL GetReal( IN resbuf* pList, IN int nCode, IN int nIndex, OUT double& dRes);

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL GetInt( IN resbuf* pList, IN int nCode, OUT int& nRes);
	static BOOL GetInt( IN resbuf* pList, IN int nCode, IN int nIndex, OUT int& nRes);



};
#pragma endregion TWArxResbufFun




#pragma region AcadDocumentManage
class ArxCommonLib_CLASS AcadDocumentManage
{
public:
	AcadDocumentManage();
	~AcadDocumentManage();

public:

	//获得当前已经打开的doc对象。
	static void GetCurDocument( OUT vector<AcApDocument*>& DocAry );

	//pVoid指向一个创建文档数量的int指针。创建dwg使用默认的模板acad.dwt
	static void ContextCreateDocument( void* pVoid );

	//pVoid指向一个vectord<AcApDocument*>数组。
	static void ContextCloseDocument( void* pVoid );

	//获得当前最后一个doc
	static AcApDocument* GetLastDocument();

	//在新建工程时需要执行的cad上下文操作
	static void ContextNewProject( void* pVoid );

};

#pragma endregion AcadDocumentManage