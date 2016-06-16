#pragma once
/*
	����arxʵ�������
*/

#pragma region TWArxEntityParam

//ʵ�����
class ArxCommonLib_CLASS TWArxEntityParam
{
public:

	TWArxEntityParam();
	virtual ~TWArxEntityParam();

	//����:���û�ȡʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//����:ʹ�ò�������ʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual AcDbEntity* CreateEntity() const;

protected:
	//����:����ʵ�弶����
	//����:
	//���:
	//����:
	//˵��:
	BOOL SetCommonEntityProperty( IN AcDbEntity* pEnt ) const;

public:
	CString       m_strLayer;                                        //ͼ��
	int           m_nColor;                                          //��ɫ
};
#pragma endregion TWArxEntityParam



#pragma region TWArxTextParam

class ArxCommonLib_CLASS TWArxTextParam :public TWArxEntityParam
{
public:
	TWArxTextParam();
	virtual ~TWArxTextParam();

	//����:���û�ȡʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//����:ʹ�ò�������ʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual AcDbEntity* CreateEntity() const;

public:
	CString       m_strCon;                                          //��������
	AcDbObjectId  m_IdStyle;                                         //������ʽ
	double        m_dTextHei;                                        //�ָ�
	double        m_dWidthFactor;                                    //���ϵ��
    TextHorzMode  m_HorMode;                                         //ˮƽ���뷽ʽ
    TextVertMode  m_VerMode;                                         //��ֱ���뷽ʽ
	AcGePoint3d   m_PtAln;                                           //�����
	AcGePoint3d   m_PtPos;                                           //λ��

	double        m_dRot;                                            //��б�Ƕ�
	double        m_dObl;                                            //��ת�Ƕ�
};
#pragma endregion TWArxTextParam



#pragma region TWArxAttributedefParam
class ArxCommonLib_CLASS TWArxAttributedefParam :public TWArxTextParam
{
public:
	TWArxAttributedefParam();
	~TWArxAttributedefParam();

public:
	//����:���û�ȡʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//����:ʹ�ò�������ʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual AcDbEntity* CreateEntity() const;

public:

	CString       m_strTag;                                          //��ǩ
	CString       m_strPormpt;                                       //��ʾ�ַ�



};

#pragma endregion TWArxAttributedefParam


#pragma region TWArxLineParam
class ArxCommonLib_CLASS TWArxLineParam :public TWArxEntityParam
{
public:
	TWArxLineParam();
	~TWArxLineParam();

	//����:���û�ȡʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//����:ʹ�ò�������ʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual AcDbEntity* CreateEntity() const;

public:
	AcGePoint3d            m_PtStart;                                //���
	AcGePoint3d            m_PtEnd;                                  //�յ�

};
#pragma endregion TWArxLineParam


//ֱ�߶���ߣ�����������
#pragma region TWArxPolylineParam
class ArxCommonLib_CLASS TWArxPolylineParam:public TWArxEntityParam
{
public:
	TWArxPolylineParam();
	~TWArxPolylineParam();

	//����:���û�ȡʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//����:ʹ�ò�������ʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual AcDbEntity* CreateEntity() const;

	//����:
	//����:
	//���:
	//����:
	//˵��:
	void SetPointAry( IN const AcGePoint3dArray& PtAry );

public:
	AcGePoint2dArray  m_PtVertexAry;
	bool              m_bIsClosed;
	double            m_dLineWidth;
};
#pragma endregion TWArxPolylineParam


//3dpline�� ֱ�߲��֣����������߲���
#pragma region TWArxAcDb3dPolylineParam
class ArxCommonLib_CLASS TWArxAcDb3dPolylineParam : public TWArxEntityParam
{
public:
	TWArxAcDb3dPolylineParam();
	virtual~TWArxAcDb3dPolylineParam();

	//����:���û�ȡʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//����:ʹ�ò�������ʵ�����
	//����:
	//���:
	//����:
	//˵��:
	virtual AcDbEntity* CreateEntity() const;

	//����:
	//����:
	//���:
	//����:
	//˵��:
	void SetVertex( IN const vector<AcGePoint3d>& vVertex );


public:
	AcDb::Poly3dType         m_TypeP3D;
	bool                     m_bIsClosed;
	AcGePoint3dArray         m_Vertex;
};
#pragma endregion TWArxAcDb3dPolylineParam


//not database-resident��AcDb3dPolyline��
#pragma region TWArxAcDb3dPolylineNDRParam
class ArxCommonLib_CLASS TWArxAcDb3dPolylineNDRParam : public TWArxAcDb3dPolylineParam
{
public:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );

};
#pragma endregion TWArxAcDb3dPolylineParam


