#pragma once
/*
	���幫�����ݽṹ
*/

/* 
	��ά Key Value ��ʽ��ԭ��Ԫ�ء�
	Atom1 Key�� Atom2 Valu��
*/
#pragma region CTwAtom_StringPair
class CTwAtom_StringPair : public  TWPairObjAtom<CString, CString>
{
public:
	CTwAtom_StringPair( IN const CString& strKey, IN const CString& strValue );
	CTwAtom_StringPair();
	virtual ~CTwAtom_StringPair();
    
	// get or set 
	CString& GetKey();
	CString  GetKey() const;
	void SetKey( IN const CString& strKey );
	CString& GetValue();
	CString  GetValue() const;
	void SetValue( IN const CString& strValue );

protected:

};
#pragma endregion CTwAtom_StringPair

/*
	��ά String Int ��ʽ��ԭ��Ԫ��
*/
#pragma region CTwAtom_StringInt
class CTwAtom_StringInt : public  TWPairObjAtom<CString, int>
{
public:
	CTwAtom_StringInt( IN const CString& str, IN int n );
	CTwAtom_StringInt();
	virtual ~CTwAtom_StringInt();

	// get or set 
	CString& GetString();
	CString  GetString() const;
	void SetString( IN const CString& strKey );
	int& GetInt();
	int  GetInt() const;
	void SetInt( int n );

protected:

};

#pragma endregion CTwAtom_StringInt

/*
	��ά String double ��ʽ��ԭ��Ԫ��
*/
#pragma region TWAtom_StringDouble
class TWAtom_StringDouble : public  TWPairObjAtom<CString, double>
{
public:
	TWAtom_StringDouble( IN const CString& str, IN double d );
	TWAtom_StringDouble();
	virtual ~TWAtom_StringDouble();

	// get or set 
	CString& GetString();
	CString  GetString() const;
	void SetString( IN const CString& strKey );
	double& GetDouble();
	double  GetDouble() const;
	void SetDouble( IN double n );

protected:

};

#pragma endregion CTwAtom_StringInt


/*
	��ά String GePt3d ��ʽ��ԭ��Ԫ��
*/
#pragma region TWAtom_StringPt3d
class TWAtom_StringPt3d : public  TWPairObjAtom<CString, AcGePoint3d>
{
public:
	TWAtom_StringPt3d( IN const CString& str, IN const AcGePoint3d& Pt );
	TWAtom_StringPt3d();
	virtual ~TWAtom_StringPt3d();

	// get or set 
	CString& GetString();
	CString  GetString() const;
	void SetString( IN const CString& strKey );
	AcGePoint3d& GetPoint();
	AcGePoint3d  GetPoint() const;
	void SetPoint( IN const AcGePoint3d& Pt );

protected:

};

#pragma endregion CTwAtom_StringInt


/*
	��ά string-double-intԭ��Ԫ��
*/
#pragma region CTwAtom_SRI
class CTwAtom_SRI:public TWTripleObjAtom<CString, double, int>
{
public:
	CTwAtom_SRI();
	CTwAtom_SRI( IN const CString& str, IN double d, IN int n );
	~CTwAtom_SRI();
public:

	// get or set 
	CString& GetString();
	CString  GetString() const;
	void SetString( IN const CString& strKey );
	double& GetDouble();
	double  GetDouble() const;
	void SetDouble( double d );
	int& GetInt();
	int  GetInt() const;
	void SetInt( int n );

};
#pragma endregion CTwAtom_SRI



/*
	һά stringPair��������ṹ
*/
#pragma region TWStingPairObjAry
class TWStingPairObjAry: public vector<CTwAtom_StringPair>
{
public:
	TWStingPairObjAry();
	virtual ~TWStingPairObjAry();

protected:

};

#pragma endregion TWStingPairObjAry

/*
	һά stringInt��������ṹ
*/

#pragma region CTwStingIntObjAry

class CTwStingIntObjAry:public vector<CTwAtom_StringInt>
{

public:
	CTwStingIntObjAry();
	virtual ~CTwStingIntObjAry();

};

#pragma endregion CTwStingIntObjAry

/*
	һά CTwAtom_SRI��������ṹ
*/

#pragma region CTwSRIObjAry

class CTwSRIObjAry:public vector<CTwAtom_SRI>
{

public:
	CTwSRIObjAry();
	virtual ~CTwSRIObjAry();

};

#pragma endregion CTwSRIObjAry


/*
	����ö�ٶ���
*/

//�ؼ����Ͷ���
enum TWEnuControlType{ eUnKnownCtl = 0, eEdit, eCheckBox, eCombox };