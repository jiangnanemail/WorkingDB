#pragma once
/*
	定义arx实体参数类
*/

#pragma region TWArxEntityParam

//实体基类
class ArxCommonLib_CLASS TWArxEntityParam
{
public:

	TWArxEntityParam();
	virtual ~TWArxEntityParam();

	//功能:设置获取实体参数
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//功能:使用参数创建实体对象
	//输入:
	//输出:
	//返回:
	//说明:
	virtual AcDbEntity* CreateEntity() const;

protected:
	//功能:设置实体级属性
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL SetCommonEntityProperty( IN AcDbEntity* pEnt ) const;

public:
	CString       m_strLayer;                                        //图层
	int           m_nColor;                                          //颜色
};
#pragma endregion TWArxEntityParam



#pragma region TWArxTextParam

class ArxCommonLib_CLASS TWArxTextParam :public TWArxEntityParam
{
public:
	TWArxTextParam();
	virtual ~TWArxTextParam();

	//功能:设置获取实体参数
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//功能:使用参数创建实体对象
	//输入:
	//输出:
	//返回:
	//说明:
	virtual AcDbEntity* CreateEntity() const;

public:
	CString       m_strCon;                                          //文字内容
	AcDbObjectId  m_IdStyle;                                         //文字样式
	double        m_dTextHei;                                        //字高
	double        m_dWidthFactor;                                    //宽度系数
    TextHorzMode  m_HorMode;                                         //水平对齐方式
    TextVertMode  m_VerMode;                                         //垂直对齐方式
	AcGePoint3d   m_PtAln;                                           //对齐点
	AcGePoint3d   m_PtPos;                                           //位置

	double        m_dRot;                                            //倾斜角度
	double        m_dObl;                                            //旋转角度
};
#pragma endregion TWArxTextParam



#pragma region TWArxAttributedefParam
class ArxCommonLib_CLASS TWArxAttributedefParam :public TWArxTextParam
{
public:
	TWArxAttributedefParam();
	~TWArxAttributedefParam();

public:
	//功能:设置获取实体参数
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//功能:使用参数创建实体对象
	//输入:
	//输出:
	//返回:
	//说明:
	virtual AcDbEntity* CreateEntity() const;

public:

	CString       m_strTag;                                          //标签
	CString       m_strPormpt;                                       //提示字符



};

#pragma endregion TWArxAttributedefParam


#pragma region TWArxLineParam
class ArxCommonLib_CLASS TWArxLineParam :public TWArxEntityParam
{
public:
	TWArxLineParam();
	~TWArxLineParam();

	//功能:设置获取实体参数
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//功能:使用参数创建实体对象
	//输入:
	//输出:
	//返回:
	//说明:
	virtual AcDbEntity* CreateEntity() const;

public:
	AcGePoint3d            m_PtStart;                                //起点
	AcGePoint3d            m_PtEnd;                                  //终点

};
#pragma endregion TWArxLineParam


//直线多段线，不包括曲线
#pragma region TWArxPolylineParam
class ArxCommonLib_CLASS TWArxPolylineParam:public TWArxEntityParam
{
public:
	TWArxPolylineParam();
	~TWArxPolylineParam();

	//功能:设置获取实体参数
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//功能:使用参数创建实体对象
	//输入:
	//输出:
	//返回:
	//说明:
	virtual AcDbEntity* CreateEntity() const;

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	void SetPointAry( IN const AcGePoint3dArray& PtAry );

public:
	AcGePoint2dArray  m_PtVertexAry;
	bool              m_bIsClosed;
	double            m_dLineWidth;
};
#pragma endregion TWArxPolylineParam


//3dpline线 直线部分，不包括曲线部分
#pragma region TWArxAcDb3dPolylineParam
class ArxCommonLib_CLASS TWArxAcDb3dPolylineParam : public TWArxEntityParam
{
public:
	TWArxAcDb3dPolylineParam();
	virtual~TWArxAcDb3dPolylineParam();

	//功能:设置获取实体参数
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );
	virtual BOOL SetEntityParam( IN OUT AcDbEntity* pEnt ) const;

	//功能:使用参数创建实体对象
	//输入:
	//输出:
	//返回:
	//说明:
	virtual AcDbEntity* CreateEntity() const;

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	void SetVertex( IN const vector<AcGePoint3d>& vVertex );


public:
	AcDb::Poly3dType         m_TypeP3D;
	bool                     m_bIsClosed;
	AcGePoint3dArray         m_Vertex;
};
#pragma endregion TWArxAcDb3dPolylineParam


//not database-resident的AcDb3dPolyline。
#pragma region TWArxAcDb3dPolylineNDRParam
class ArxCommonLib_CLASS TWArxAcDb3dPolylineNDRParam : public TWArxAcDb3dPolylineParam
{
public:
	virtual BOOL GetEntityParam( IN const AcDbEntity* pEnt );

};
#pragma endregion TWArxAcDb3dPolylineParam


