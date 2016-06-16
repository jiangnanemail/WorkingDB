#pragma once

/*
	excel������
*/

#pragma region CTwRangeWidget
class CTwRangeWidget
{
public:
	CTwRangeWidget();
	~CTwRangeWidget();

public:
	//����:��ʼ������
	//����:
	//���:
	//����:
	//˵��:
	void AttachDispatch( LPDISPATCH lpDispatch );
	void ReleaseDispatch();

	//����:��õ�ǰ��Χ����������
	//����:
	//���:
	//����:
	//˵��:
	int GetRowCount();
	int GetColCount();

	//����:��ȡָ���ĵ�Ԫ��
	//����:
	//���:
	//����:
	//˵��:
	BOOL GetItem( IN int nRow, IN int nCol, OUT CTwRangeWidget& Item );

	//����:����ָ����Ԫ����������ݡ�
	//����:
	//���:
	//����:
	//˵��:
	BOOL GetItemText( IN int nRow, IN int nCol, OUT CString& strRes );

	//����:ָ��λ��д�����ݡ�
	//����:
	//���:
	//����:
	//˵��:nRow�� nCol ����1�����������������λ�á�
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

	//����:��ʼ������
	//����:
	//���:
	//����:
	//˵��:
	void AttachDispatch( LPDISPATCH lpDispatch );
	void ReleaseDispatch();
	
	//����:���
	//����:
	//���:
	//����:
	//˵��:
	BOOL GetUsedRange( OUT CTwRangeWidget& RgUsed );

	//����:
	//����:
	//���:
	//����:
	//˵��:
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
	//����:��ʼ������
	//����:
	//���:
	//����:
	//˵��:
	void AttachDispatch( LPDISPATCH lpDispatch );
	void ReleaseDispatch();

	//����:��ȡ����
	//����:
	//���:
	//����:
	//˵��:
	int GetCount();

	//����:��ȡָ���Ĺ�����
	//����:����ֵ����1��ʼ�ġ�
	//���:
	//����:
	//˵��:
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

	//����:
	//����:
	//���:
	//����:
	//˵��:
	BOOL RunApp();

	//����:��һ��excel�ļ�
	//����:
	//���:
	//����:
	//˵��:
	BOOL Open( IN const CString& strFilePath, OUT CTwWorkSheetsWidget& Worksheets );

	//����:����һ���µ�excle�ļ�
	//����:
	//���:
	//����:
	//˵��:
	BOOL Create( OUT CTwWorkSheetsWidget& Worksheets );

public:

	BOOL                      m_bVisual;
	BOOL                      m_bControl;
	BOOL                      m_bQuit;

protected:

	office::_Application      m_App;

	/*
		��ǰ�򵥴����պ�Ӧ�����Ӻ�
		���Էֱ�excel�Ķ���ֱ����
		Ϊ�����ࡣ
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




