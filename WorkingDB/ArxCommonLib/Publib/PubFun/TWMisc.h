#pragma once

/*
	其他方法
*/

class CTwMiscFun
{
public:

	//功能:获得src中所有不重复的单一值。
	//输入:
	//输出:
	//返回:
	//说明:此方法模板类型是一个对象，不应是一个指针或者引用。模板对象需要实现 == 操作符。
	template<typename U>
	static void RemoveDuplicate( IN const vector<U>& vSrc, OUT vector<U>& vRes )
	{
		vRes.assign( vSrc.begin(), vSrc.end() );
		sort( vRes.begin(), vRes.end() );
		vector<U>::iterator Ite = unique( vRes.begin(), vRes.end() );
		vRes.erase( Ite, vRes.end() );
	}

	template<typename U>
	static void RemoveDuplicate( IN vector<U>& v )
	{
		sort( v.begin(), v.end() );
		vector<U>::iterator Ite = unique( v.begin(), v.end() );
		v.erase( Ite, v.end() );
	}

// 	template<typename U, class  _Pre >
// 	static void RemoveDuplicate( IN vector<U>& v, _Pre pre )
// 	{
// 		sort( v.begin(), v.end(), pre );
// 		//vector<U>::iterator Ite = unique( v.begin(), v.end(), pre );
// 		//v.erase( Ite, v.end() );
// 	}

};

class CTwTimeRun
{
public:

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	void Start();

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	void End();

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	void ShowMsg() const;

protected:
	__int64      m_timeStart;
	__int64      m_timeFr;
	__int64      m_timeEnd;
};

//基本符号绘制方法
class CTwSmbolDrawToolKid
{
public:
	
	//功能:绘制图形
	//输入:vEnt 返回的是他对象指针。pSrcEnt输入源对象指针，不同的子类不同的要求。
	//输出:
	//返回:
	//说明:
	virtual BOOL Draw( OUT vector<AcDbEntity*>& vEnt ) const;
	virtual BOOL Draw( IN AcDbEntity* pSrcEnt, OUT vector<AcDbEntity*>& vEnt ) const;

public:
	//功能:绘制等边三角形   ___
	//                     \_/					    
	//输入:
	//输出:PtBase 下部的顶点。 dLen：
	//返回:
	//说明:
	static BOOL DrawTriangle( IN const AcGePoint3d& PtBase, IN double dLen, OUT AcDbPolyline*& pPolyline );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	static BOOL DrawElevtionSymbol( IN const AcGePoint3d& PtBase, IN double dLen, IN OUT AcDbText* pTxt, OUT AcDbPolyline*& pPolyline );

};



//等边三角形绘制
#pragma region CTwSmblolDrawTriangle
class CTwSmblolDrawTriangle : public CTwSmbolDrawToolKid
{
public:
	CTwSmblolDrawTriangle();
	virtual ~CTwSmblolDrawTriangle();

	//功能:等边三角形绘制
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL Draw( vector<AcDbEntity*>& vEnt ) const;


public:

	AcGePoint3d     m_Ptbase;                       //基点
	AcGeVector3d    m_vNormal;                      //过基点方向向量
	double          m_dLen;                         //三角形边长
};
#pragma endregion CTwSmblolDrawTriangle



//高程符号
#pragma region CTwSmblolDrawElevation
class CTwSmblolDrawElevation : public CTwSmblolDrawTriangle
{
public:
	CTwSmblolDrawElevation();
	virtual~CTwSmblolDrawElevation();

	//功能:创建标高文字
	//输入:
	//输出:
	//返回:
	//说明:
	static AcDbText* CreateElevtionNote( IN const CString& strCon, IN double dTxtH, IN const AcDbObjectId& IdTxtStyle );

	//功能:标高符号绘制
	//输入:pSrcEnt与标高符号相关的内容对象，此处为AcdbText实体，实体可写操作。
	//输出:
	//返回:
	//说明:pSrcEnt 程序中将对其进行位置的设置，使其与符号匹配。
	virtual BOOL Draw( IN AcDbEntity* pSrcEnt, OUT vector<AcDbEntity*>& vEnt ) const;

public:

	AcGeVector3d      m_vLeader;                    //引线的方向向量，与Normal要正交。
	double            m_dTxtOff;                    //文字距离引线距离
	double            m_dExt;                       //引线两端超出文字距离
	BOOL              m_bUnderLine;                 //文字在引线上或者下
};

#pragma endregion CTwSmblolDrawTriangle




//矩形绘制
#pragma region CTwSymbolDrawRectangle
class CTwSymbolDrawRectangle : public CTwSmbolDrawToolKid
{
public:
	CTwSymbolDrawRectangle();
	~CTwSymbolDrawRectangle();

	//功能:矩形绘制
	//输入:
	//输出:
	//返回:
	//说明:返回是一个闭合的lwpolyline实体。
	virtual BOOL Draw( OUT vector<AcDbEntity*>& vEnt ) const;
	static AcDbPolyline* Draw_Cen( IN double dH, IN double dW, IN const AcGePoint3d& PtCen ,IN const AcGeVector3d& vNormal = AcGeVector3d::kYAxis );
	static AcDbPolyline* Draw_Lb( IN double dH, IN double dW, IN const AcGePoint3d& PtLB ,IN const AcGeVector3d& vNormal = AcGeVector3d::kYAxis );

public:
	AcGePoint3d      m_PtCen;
	double           m_dWidht;
	double           m_dHeigh;
	AcGeVector3d     m_vNormal;                      //与宽边正交的的法向量

};
#pragma endregion CTwSymbolDrawRectangle



//API
#pragma region API

//功能:excle中行列索引转换为A1的方法。
//输入:nRowOff nColOff表示从起始便宜的数目。
//输出:
//返回:
//说明:行数量不限，列数量 小于等于 26 * 26 = 676 个.excle中行列索引从1开始。
BOOL Index2String( IN int nRow, IN int nCol, OUT CString& strRes, IN int nRowOff = 0, IN int nColOff = 0 );

//功能:计算图纸的尺寸
//输入:strTZ 图纸的Iso名称
//输出:
//返回:
//说明:
BOOL GetIsoPapaerSize( IN const CString& strTZ, OUT double& dH, OUT double& dW );

#pragma endregion API
