#pragma once

#pragma region CArxEntityFun
class ArxCommonLib_CLASS CArxEntityFun
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
	static Acad::ErrorStatus PostModelSpace( IN vector<AcDbEntity*>& EntAry, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE  );

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

#pragma endregion CArxEntityFun