#pragma once

/*
	平面地形图纸中等高线和
	独立高程点转换为tin实现。
*/


//高程信息对象获取类,类型有等高线，和独立高程点。
#pragma region ElevationObjectPick
class ElevationObjectPick
{
public:
	ElevationObjectPick();
	~ElevationObjectPick();
	
public:
	//功能:选择高程信息对象。
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL PickElevationObjects( OUT vector<AcDbObjectId>& vIsoHeight, OUT vector<AcDbObjectId>& vElePoint ) const;

protected:
	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL IsIsoHeight( IN const AcDbObjectId& Id ) const;

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL IsElePoint( IN const AcDbObjectId& Id ) const;

private:
	vector<CString>    m_vLayerIsoHeight;                                                          //等高线图层
	vector<CString>    m_vLayerElePoint;                                                           //高程点图层
};
#pragma endregion ElevationObjectPick




//高程点离散类
//默认操着从当前dwg中获取高程信息对象
#pragma region ElevationDisperse
class ElevationDisperse
{
public:
	ElevationDisperse();
	~ElevationDisperse();

public:

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	virtual BOOL IsoHeightDisperse( IN const vector<AcDbObjectId>& vRes, OUT vector<AcGePoint3d>& vPts ) const;
	virtual BOOL ElevPointDisperse( IN const vector<AcDbObjectId>& vRes, OUT vector<AcGePoint3d>& vPts ) const;



};
#pragma endregion ElevationDisperse