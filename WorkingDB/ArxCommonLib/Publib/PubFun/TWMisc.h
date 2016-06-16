#pragma once

/*
	��������
*/

class CTwMiscFun
{
public:

	//����:���src�����в��ظ��ĵ�һֵ��
	//����:
	//���:
	//����:
	//˵��:�˷���ģ��������һ�����󣬲�Ӧ��һ��ָ��������á�ģ�������Ҫʵ�� == ��������
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

	//����:
	//����:
	//���:
	//����:
	//˵��:
	void Start();

	//����:
	//����:
	//���:
	//����:
	//˵��:
	void End();

	//����:
	//����:
	//���:
	//����:
	//˵��:
	void ShowMsg() const;

protected:
	__int64      m_timeStart;
	__int64      m_timeFr;
	__int64      m_timeEnd;
};

//�������Ż��Ʒ���
class CTwSmbolDrawToolKid
{
public:
	
	//����:����ͼ��
	//����:vEnt ���ص���������ָ�롣pSrcEnt����Դ����ָ�룬��ͬ�����಻ͬ��Ҫ��
	//���:
	//����:
	//˵��:
	virtual BOOL Draw( OUT vector<AcDbEntity*>& vEnt ) const;
	virtual BOOL Draw( IN AcDbEntity* pSrcEnt, OUT vector<AcDbEntity*>& vEnt ) const;

public:
	//����:���Ƶȱ�������   ___
	//                     \_/					    
	//����:
	//���:PtBase �²��Ķ��㡣 dLen��
	//����:
	//˵��:
	static BOOL DrawTriangle( IN const AcGePoint3d& PtBase, IN double dLen, OUT AcDbPolyline*& pPolyline );

	//����:
	//����:
	//���:
	//����:
	//˵��:
	static BOOL DrawElevtionSymbol( IN const AcGePoint3d& PtBase, IN double dLen, IN OUT AcDbText* pTxt, OUT AcDbPolyline*& pPolyline );

};



//�ȱ������λ���
#pragma region CTwSmblolDrawTriangle
class CTwSmblolDrawTriangle : public CTwSmbolDrawToolKid
{
public:
	CTwSmblolDrawTriangle();
	virtual ~CTwSmblolDrawTriangle();

	//����:�ȱ������λ���
	//����:
	//���:
	//����:
	//˵��:
	virtual BOOL Draw( vector<AcDbEntity*>& vEnt ) const;


public:

	AcGePoint3d     m_Ptbase;                       //����
	AcGeVector3d    m_vNormal;                      //�����㷽������
	double          m_dLen;                         //�����α߳�
};
#pragma endregion CTwSmblolDrawTriangle



//�̷߳���
#pragma region CTwSmblolDrawElevation
class CTwSmblolDrawElevation : public CTwSmblolDrawTriangle
{
public:
	CTwSmblolDrawElevation();
	virtual~CTwSmblolDrawElevation();

	//����:�����������
	//����:
	//���:
	//����:
	//˵��:
	static AcDbText* CreateElevtionNote( IN const CString& strCon, IN double dTxtH, IN const AcDbObjectId& IdTxtStyle );

	//����:��߷��Ż���
	//����:pSrcEnt���߷�����ص����ݶ��󣬴˴�ΪAcdbTextʵ�壬ʵ���д������
	//���:
	//����:
	//˵��:pSrcEnt �����н��������λ�õ����ã�ʹ�������ƥ�䡣
	virtual BOOL Draw( IN AcDbEntity* pSrcEnt, OUT vector<AcDbEntity*>& vEnt ) const;

public:

	AcGeVector3d      m_vLeader;                    //���ߵķ�����������NormalҪ������
	double            m_dTxtOff;                    //���־������߾���
	double            m_dExt;                       //�������˳������־���
	BOOL              m_bUnderLine;                 //�����������ϻ�����
};

#pragma endregion CTwSmblolDrawTriangle




//���λ���
#pragma region CTwSymbolDrawRectangle
class CTwSymbolDrawRectangle : public CTwSmbolDrawToolKid
{
public:
	CTwSymbolDrawRectangle();
	~CTwSymbolDrawRectangle();

	//����:���λ���
	//����:
	//���:
	//����:
	//˵��:������һ���պϵ�lwpolylineʵ�塣
	virtual BOOL Draw( OUT vector<AcDbEntity*>& vEnt ) const;
	static AcDbPolyline* Draw_Cen( IN double dH, IN double dW, IN const AcGePoint3d& PtCen ,IN const AcGeVector3d& vNormal = AcGeVector3d::kYAxis );
	static AcDbPolyline* Draw_Lb( IN double dH, IN double dW, IN const AcGePoint3d& PtLB ,IN const AcGeVector3d& vNormal = AcGeVector3d::kYAxis );

public:
	AcGePoint3d      m_PtCen;
	double           m_dWidht;
	double           m_dHeigh;
	AcGeVector3d     m_vNormal;                      //���������ĵķ�����

};
#pragma endregion CTwSymbolDrawRectangle



//API
#pragma region API

//����:excle����������ת��ΪA1�ķ�����
//����:nRowOff nColOff��ʾ����ʼ���˵���Ŀ��
//���:
//����:
//˵��:���������ޣ������� С�ڵ��� 26 * 26 = 676 ��.excle������������1��ʼ��
BOOL Index2String( IN int nRow, IN int nCol, OUT CString& strRes, IN int nRowOff = 0, IN int nColOff = 0 );

//����:����ͼֽ�ĳߴ�
//����:strTZ ͼֽ��Iso����
//���:
//����:
//˵��:
BOOL GetIsoPapaerSize( IN const CString& strTZ, OUT double& dH, OUT double& dW );

#pragma endregion API
