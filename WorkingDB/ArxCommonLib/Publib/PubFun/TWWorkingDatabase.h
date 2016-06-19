#pragma once


#pragma region TWWorkingDatabase
class ArxCommonLib_CLASS TWWorkingDatabase
{
public:
	TWWorkingDatabase();
	TWWorkingDatabase( IN AcDbDatabase* pWD );
	virtual ~TWWorkingDatabase();

public:

	void SetWrokingDB( IN AcDbDatabase* pWD  );

	//����:��õ�ǰ���ݿ�
	//����:
	//���:
	//����:
	//˵��:
	AcDbDatabase* GetWorkingDB() const;

private:
	TWWorkingDatabase( IN const TWWorkingDatabase* Item )                   {}
	const TWWorkingDatabase& operator = ( IN const TWWorkingDatabase& Item ){ return *this;};

private:
	AcDbDatabase*            m_pWorkingDatabase;       //�������ݿ�
};
#pragma endregion TWWorkingDatabase




//��ǰ���ⲿ���ݿ��л�
#pragma region CTwWorkingDatebaseSwitch
class ArxCommonLib_CLASS CTwWorkingDatebaseSwitch
{
public:
	CTwWorkingDatebaseSwitch();
	CTwWorkingDatebaseSwitch( IN AcDbDatabase* pWorkingDB );
	virtual ~CTwWorkingDatebaseSwitch();

public:

	//����:���õ�ǰ�������ݿ�
	//����:
	//���:
	//����:
	//˵��:
	void Push( IN AcDbDatabase* pWorkingDB );
	
	//����:�ָ���ǰ�����ݿ�
	//����:
	//���:
	//����:
	//˵��:
	AcDbDatabase* Pop();


private:
	AcDbDatabase*           m_pOldDB;
};

#pragma endregion CTwWorkingDatebaseSwitch