#pragma once
class CTwRectangle;
/*
	����arx��صĹ�������
*/

//ͼ�����
#pragma region TWArxLayerFun
class ArxCommonLib_CLASS TWArxLayerFun
{
public:
	//����:��õ�ǰ���е�ͼ������
	//����:vLayerNames ����ͼ������; pCur Ŀ�����ݿ⡣
	//���:
	//����:
	//˵��:pCur ΪNULL ʹ�õ�ǰ���ݿ⡣
	static Acad::ErrorStatus GetLayerNames( OUT vector<CString>& vLayerNames, IN AcDbDatabase* pCur = NULL );

};

#pragma endregion TWArxLayerFun


//������ʽ���
#pragma region TWArxTextStyleFun
class  ArxCommonLib_CLASS TWArxTextStyleFun
{
public:
	//����:��õ�ǰ����������ʽ������
	//����:vTextStyleNames ����������ʽ����;  pCur Ŀ�����ݿ⡣
	//���:
	//����:
	//˵��:pCur ΪNULL ʹ�õ�ǰ���ݿ⡣
	static Acad::ErrorStatus GetTextStyleNames( OUT vector<CString>& vTextStyleNames, IN AcDbDatabase* pCur = NULL );

	//����:�������ƻ��������ʽID
	//����:
	//���:
	//����:
	//˵��:
	static AcDbObjectId GetTextStyleId( IN const CString strStyleName, IN AcDbDatabase* pCur = NULL  );

	static Acad::ErrorStatus CreateTextStyle( IN const CString& strName, IN const CString& strSHXName, IN const CString& strBigFront, IN double dWidthFactor );
};

#pragma endregion TWArxTextStyleFun




#pragma region TWArxBlokTableFun
class ArxCommonLib_CLASS TWArxBlokTableFun
{
public:
	//����:�����Ƿ���ڸ����Ŀ鶨�����ơ�
	//����:IdRes �������ʹ��IdRes���ش˶���ID��
	//���:
	//����:
	//˵��:
	static BOOL HasBlockTableRecord( IN const CString& strName, OUT AcDbObjectId& IdRes, IN AcDbDatabase* pCur = NULL );

	//����:���ָ��BlockTableRecord��ʵ���������
	//����:����ɹ� pIte ���ص�����ָ�롣
	//���:
	//����:
	//˵��:��������Ҫ�ͷ� pIte.
	static BOOL GetBlockTableRecordIterator( IN const CString& strName, OUT AcDbBlockTableRecordIterator*& pIte, IN AcDbDatabase* pCur = NULL );

	//����:�����鶨��
	//����:PtOrigin �鶨��ԭ��; strName ����; IdRes ���ش����Ŀ鶨��ID�� vEnt �鶨���ڵ���ʵ������; pCur Ŀ�����ݿ⡣
	//���:
	//����:
	//˵��:vEntʵ�����Ȩ����˺��������ⲿ�Ͳ�Ҫ�ٽ�����������
	static Acad::ErrorStatus CreateBlockDef( IN const AcGePoint3d& PtOrigin, IN const CString& strName, OUT AcDbObjectId& IdRes, IN vector<AcDbEntity*>& vEnt, IN AcDbDatabase* pCur = NULL );

	//����:���ⲿ�ļ����п鶨�塣
	//����:strExtDB �ⲿ�ļ�����;vBlockName ��Ҫ���صĿ������ϣ�vErrorBlockName ����ʧ�ܵĿ�����
	//���:
	//����:
	//˵��:
	static void LoadBlockDef( IN const CString& strExtDB, IN const vector<CString>& vBlockName, OUT vector<CString>& vErrorBlockName );

	//����:����lpszFileNameָ����Dwg�ļ���Ϊ����ղ��뵽��ǰͼ�У��鶨����������ΪpszBlockName��Id�������Ŀ鶨��ֵ
	//����: pszBlockName:��ָ���Ŀ���,lpszFileName���ⲿdwg��������,�²���� block id
	//���:
	//����:1����ǰͼ�д���ͬ������գ�2������ɹ�������  ʧ��
	//˵��:
	static int InsertDwgToCurrDwgBlockTableRecord(TCHAR *pszBlockName,TCHAR *lpszFileName, AcDbObjectId &id);
	static int InsertDwgToCurrDwgBlockTableRecord(TCHAR *pszBlockName,AcDbDatabase* pExtDB, AcDbObjectId &id);


};
#pragma endregion TWArxBlokTableFun



//ʵ��������
#pragma region TWArxEntityFun
class ArxCommonLib_CLASS TWArxEntityFun
{
public:
	
	//����:ʵ����������չ�ֵ�
	//����:IdObj��pObj���Ŀ�����
	//���:
	//����:
	//˵��:pObj ��Ҫ��д����������Ѵ�����ֱ�ӷ��ء�
	static Acad::ErrorStatus CreateExtendDictionary( IN const AcDbObjectId& IdObj, OUT AcDbObjectId& IdExtDic );
	static Acad::ErrorStatus CreateExtendDictionary( IN AcDbObject* pObj, OUT AcDbObjectId& IdExtDic );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	static void TransformBy( vector<AcDbEntity*> vEnt, IN const AcGeMatrix3d& Mat );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	static void GetGeometryExtend( IN const vector<AcDbEntity*> vEnt, OUT AcDbExtents& Ext );

	//����:��ʵ������������չ��
	//����:
	//���:
	//����:
	//˵��:txtΪˮƽ������ֱ���ͬ��ԭʼ����������������������⴦��
	static BOOL GetTxtGeometryExtend( IN const AcDbText* pTxt, OUT CTwRectangle* Rectangle );

	//����:��ø���ʵ�����ľ���ַ���
	//����:ID ʵ��ID�� chHanle ���ֵ��
	//���:
	//����:
	//˵��:
	static Acad::ErrorStatus GetHandString( IN const AcDbObjectId& Id, OUT _TCHAR* chHandle );

	//����:ʵ�������ж���
	//����:
	//���:
	//����:
	//˵��:
	static BOOL IsA( IN ads_name ent, IN AcRxClass* pClass  );
	static BOOL IsA( IN const AcDbObjectId& Id, IN AcRxClass* pClass  );


	//����:�Ƿ�voidָ��
	//����:
	//���:
	//����:
	//˵��:
	static void Free( AcDbVoidPtrArray& vPtr );

	//����:ɾ��ʵ��ѡ��������ʵ�塣
	//����:
	//���:
	//����:
	//˵��:
	static void DeleteSS( ads_name ss );

	//����:ʵ�����ģ�Ϳռ�
	//����:pEnt �����ʵ��; IdRes����ʵ��ID; bAutoCLoseʵ����ӳɹ��Ƿ��Զ��رղ���; bAutoDel ʵ�����ʵ���Ƿ��Ƿ�ָ�롣
	//���:
	//����:
	//˵��:
	static Acad::ErrorStatus PostModelSpace( IN AcDbEntity* pEnt, OUT AcDbObjectId& IdRes, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE, IN BOOL bUseTran = FALSE );

	//����:����ʵ����ӵ�ģ�Ϳռ�
	//����:
	//���:
	//����:
	//˵��:bAutoDel��bAutoCLose ǿ��Ҫ��ʹ��Ĭ��ֵ��
	static Acad::ErrorStatus PostModelSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE  );

	//����:ʵ�������ӵ���ǰ�ռ�
	//����:
	//���:
	//����:
	//˵��:
	static Acad::ErrorStatus PostCurSpace( IN vector<AcDbEntity*>& EntAry, OUT vector<AcDbObjectId>& IdAry, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE );


	class For_each_AppendEnt2TableRecor
	{
	public:
		void operator()( AcDbEntity* pEnt );

	public:
		AcDbBlockTableRecord*   m_pBtr;                             //����¼
		vector<AcDbObjectId>    m_vSuccObjIds;                      //�ɹ���ӵ�����¼��id
		vector<AcDbEntity*>     m_vSuccEnt;                         //�ɹ�ʵ��ָ��
		vector<AcDbEntity*>     m_vFalsEnt;                         //ʧ��ʵ��ָ�� 
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

	//����:���ŵ�ǰcad�ӿ�
	//����:
	//���:
	//����:
	//˵��:	
	static Acad::ErrorStatus Zoom( IN const AcGePoint3d& Ptcen,IN double dWidth,IN double dHeight,IN BOOL zflag );

	//����:��õ�ǰ�ӿڵĲ���
	//����:
	//���:
	//����:
	//˵��:
	static Acad::ErrorStatus GetCurrentViwe( AcDbViewTableRecord& pVtr );
};

#pragma endregion TWArxViewPortFun



#pragma region TWArxRegappFun
class ArxCommonLib_CLASS TWArxRegappFun
{
public:
    
	//����:ע��Ӧ�ó�������
	//����:
	//���:
	//����:
	//˵��:
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



//ʵ��ѡ�񼯺�
#pragma region TWArxSSelFun
class ArxCommonLib_CLASS TWArxSSelFun
{
public:
	//����:ͨ����������ѡ��ʵ�����
	//����:
	//���:
	//����:ʵ��ѡ��������
	//˵��:ss ��Ҫ�������ͷš�
	static int SelectEntities( IN const resbuf* pFilter, OUT ads_name ss );
	static int SelectEntities( IN const resbuf* pFilter, OUT AcDbObjectIdArray& IdAry );


	//����:ʹ�÷�Χѡ�����
	//����:
	//���:
	//����:ʵ��ѡ��������
	//˵��:ss ��Ҫ�������ͷš�
	static int SelectEntities( IN ads_point PtLB, IN ads_point PtRT, OUT ads_name ss, IN const _TCHAR* chKey = _T("W") );
	static int SelectEntities( IN ads_point PtLB, IN ads_point PtRT, OUT AcDbObjectIdArray& IdAry, IN const _TCHAR* chKey = _T("W") );

	//����:����id�����ʵ��ѡ��ת����
	//����:
	//���:
	//����:�ɹ����ص�Ԫ�ظ���
	//˵��:�������ɵ�ssѡ�񼯺ϣ���Ҫ�������ͷš�
	static int ObjectIdAry2Selectset( IN const vector<AcDbObjectId>& vIds, OUT ads_name ss );
	static int Selectset2ObjectIdAry( IN ads_name ss, OUT vector<AcDbObjectId>& vIds );
};
#pragma endregion TWArxSSelFun



#pragma region TWArxResbufFun
class ArxCommonLib_CLASS TWArxResbufFun
{
public:

	//����:�������һ���ڵ��ָ�롣
	//����:
	//���:
	//����:
	//˵��:
	static resbuf* GetTail( IN resbuf* pList );

	//����:���ҽڵ�
	//����:
	//���:
	//����:
	//˵��:
	static resbuf* GetResbuf( IN resbuf* pList, IN int nCode );
	static resbuf* GetResbuf( IN resbuf* pList, IN int nCode, IN int nIndex );

	//����:���ָ���ڵ���ַ���ֵ
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetString( IN resbuf* pList, IN int nCode, OUT CString& strRes );
	static BOOL GetString( IN resbuf* pList, IN int nCode, IN int nIndex, OUT CString& strRes );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	static BOOL GetReal( IN resbuf* pList, IN int nCode, OUT double& dRes);
	static BOOL GetReal( IN resbuf* pList, IN int nCode, IN int nIndex, OUT double& dRes);

	//����:
	//����:
	//���:
	//����:
	//˵��:
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

	//��õ�ǰ�Ѿ��򿪵�doc����
	static void GetCurDocument( OUT vector<AcApDocument*>& DocAry );

	//pVoidָ��һ�������ĵ�������intָ�롣����dwgʹ��Ĭ�ϵ�ģ��acad.dwt
	static void ContextCreateDocument( void* pVoid );

	//pVoidָ��һ��vectord<AcApDocument*>���顣
	static void ContextCloseDocument( void* pVoid );

	//��õ�ǰ���һ��doc
	static AcApDocument* GetLastDocument();

	//���½�����ʱ��Ҫִ�е�cad�����Ĳ���
	static void ContextNewProject( void* pVoid );

};

#pragma endregion AcadDocumentManage