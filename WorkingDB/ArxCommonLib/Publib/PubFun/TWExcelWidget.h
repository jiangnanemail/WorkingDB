#pragma once

/*
	excel操作类
*/

#pragma region CTwRangeWidget
class CTwRangeWidget
{
public:
	CTwRangeWidget();
	~CTwRangeWidget();

public:
	//功能:初始化对象
	//输入:
	//输出:
	//返回:
	//说明:
	void AttachDispatch( LPDISPATCH lpDispatch );
	void ReleaseDispatch();

	//功能:获得当前范围的行列数量
	//输入:
	//输出:
	//返回:
	//说明:
	int GetRowCount();
	int GetColCount();

	//功能:获取指定的单元格
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL GetItem( IN int nRow, IN int nCol, OUT CTwRangeWidget& Item );

	//功能:返回指定单元格的文字内容。
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL GetItemText( IN int nRow, IN int nCol, OUT CString& strRes );

	//功能:指定位置写入内容。
	//输入:
	//输出:
	//返回:
	//说明:nRow， nCol 基于1的索引。相对于左上位置。
	BOOL WriteItemText( IN int nRow, IN int nCol, IN double dValue );
	BOOL WriteItemText( IN int nRow, IN int nCol, IN const CString& strValue );
	


protected:

	office::Range    m_Rg;

};

#pragma endregion CTwRangeWidget





#pragma region CTwWorkSheetWidget
class CTwWorkSheetWidget
{
public:

	CTwWorkSheetWidget();
	~CTwWorkSheetWidget();

	//功能:初始化对象
	//输入:
	//输出:
	//返回:
	//说明:
	void AttachDispatch( LPDISPATCH lpDispatch );
	void ReleaseDispatch();
	
	//功能:获得
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL GetUsedRange( OUT CTwRangeWidget& RgUsed );

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL GetAll( OUT CTwRangeWidget& RgAll );

protected:
	office::_Worksheet        m_Sheet;
};
#pragma endregion CTwWorkSheetWidget





#pragma region CTwWorkSheetsWidget
class CTwWorkSheetsWidget
{
public:
	CTwWorkSheetsWidget();
	~CTwWorkSheetsWidget();

public:
	//功能:初始化对象
	//输入:
	//输出:
	//返回:
	//说明:
	void AttachDispatch( LPDISPATCH lpDispatch );
	void ReleaseDispatch();

	//功能:获取数量
	//输入:
	//输出:
	//返回:
	//说明:
	int GetCount();

	//功能:获取指定的工作薄
	//输入:索引值基于1起始的。
	//输出:
	//返回:
	//说明:
	BOOL GetAt( IN int nIndex, OUT CTwWorkSheetWidget& WorkSheet );
	BOOL GetAt( IN const CString& strSheetName, OUT CTwWorkSheetWidget& WorkSheet );

protected:
	office::Worksheets        m_Sheets;
};
#pragma endregion CTwWorkSheetsWidget




#pragma region CTwExcleWidget
class CTwExcleWidget
{
public:
	CTwExcleWidget();
	~CTwExcleWidget();

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL RunApp();

	//功能:打开一个excel文件
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL Open( IN const CString& strFilePath, OUT CTwWorkSheetsWidget& Worksheets );

	//功能:创建一个新的excle文件
	//输入:
	//输出:
	//返回:
	//说明:
	BOOL Create( OUT CTwWorkSheetsWidget& Worksheets );

public:

	BOOL                      m_bVisual;
	BOOL                      m_bControl;
	BOOL                      m_bQuit;

protected:

	office::_Application      m_App;

	/*
		当前简单处理，日后应用增加后，
		可以分别将excel的对象分别提出
		为代理类。
	*/
	office::Workbooks         m_Books;
	office::_Workbook         m_Book;
};
#pragma endregion CTwExcleWidget



/*
	
*/

#define        TW_EXCLEWIDGET_EXCEPTION_CATCH   catch ( COleException* e )\
												{\
													e->ReportError();\
													e->Delete();\
													return FALSE;\
												}\
												catch( COleDispatchException* e )\
												{\
													e->ReportError();\
													e->Delete();\
													return FALSE;\
												}\




