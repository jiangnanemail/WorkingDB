#pragma once

/*
	ƽ�����ͼֽ�еȸ��ߺ�
	�����̵߳�ת��Ϊtinʵ�֡�
*/


//�߳���Ϣ�����ȡ��,�����еȸ��ߣ��Ͷ����̵߳㡣
#pragma region ElevationObjectPick
class ElevationObjectPick
{
public:
	ElevationObjectPick();
	~ElevationObjectPick();
	
public:
	//����:ѡ��߳���Ϣ����
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL PickElevationObjects( OUT vector<AcDbObjectId>& vIsoHeight, OUT vector<AcDbObjectId>& vElePoint ) const;

protected:
	//����:
	//����:
	//���:
	//����:
	//˵��:
	BOOL IsIsoHeight( IN const AcDbObjectId& Id ) const;

	//����:
	//����:
	//���:
	//����:
	//˵��:
	BOOL IsElePoint( IN const AcDbObjectId& Id ) const;

private:
	vector<CString>    m_vLayerIsoHeight;                                                          //�ȸ���ͼ��
	vector<CString>    m_vLayerElePoint;                                                           //�̵߳�ͼ��
};
#pragma endregion ElevationObjectPick




//�̵߳���ɢ��
//Ĭ�ϲ��Ŵӵ�ǰdwg�л�ȡ�߳���Ϣ����
#pragma region ElevationDisperse
class ElevationDisperse
{
public:
	ElevationDisperse();
	~ElevationDisperse();

public:

	//����:
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL IsoHeightDisperse( IN const vector<AcDbObjectId>& vRes, OUT vector<AcGePoint3d>& vPts ) const;
	virtual BOOL ElevPointDisperse( IN const vector<AcDbObjectId>& vRes, OUT vector<AcGePoint3d>& vPts ) const;



};
#pragma endregion ElevationDisperse