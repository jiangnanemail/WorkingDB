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

	//功能:获得当前数据库
	//输入:
	//输出:
	//返回:
	//说明:
	AcDbDatabase* GetWorkingDB() const;

private:
	TWWorkingDatabase( IN const TWWorkingDatabase* Item )                   {}
	const TWWorkingDatabase& operator = ( IN const TWWorkingDatabase& Item ){ return *this;};

private:
	AcDbDatabase*            m_pWorkingDatabase;       //工作数据库
};
#pragma endregion TWWorkingDatabase




//当前和外部数据库切换
#pragma region CTwWorkingDatebaseSwitch
class ArxCommonLib_CLASS CTwWorkingDatebaseSwitch
{
public:
	CTwWorkingDatebaseSwitch();
	CTwWorkingDatebaseSwitch( IN AcDbDatabase* pWorkingDB );
	virtual ~CTwWorkingDatebaseSwitch();

public:

	//功能:设置当前工作数据库
	//输入:
	//输出:
	//返回:
	//说明:
	void Push( IN AcDbDatabase* pWorkingDB );
	
	//功能:恢复以前的数据库
	//输入:
	//输出:
	//返回:
	//说明:
	AcDbDatabase* Pop();


private:
	AcDbDatabase*           m_pOldDB;
};

#pragma endregion CTwWorkingDatebaseSwitch