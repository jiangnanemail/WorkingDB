#pragma once

#pragma region CArxEntityFun
class ArxCommonLib_CLASS CArxEntityFun
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
	static Acad::ErrorStatus PostModelSpace( IN vector<AcDbEntity*>& EntAry, IN BOOL bAutoCLose = TRUE, IN BOOL bAutoDel = TRUE  );

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

#pragma endregion CArxEntityFun