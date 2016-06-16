#include "StdAfx.h"
#include "TWExcelWidget.h"
#include <comutil.h>

#pragma region CTwExcleWidget
BOOL CTwExcleWidget::RunApp()
{
	COleException *e = new COleException();
	if( !m_App.CreateDispatch( _T("Excel.Application"), e ) )                                       //Excel.Application.12
	{
		AfxMessageBox( _T("您计算机上没有安装office excel！") );
		e->Delete();
		return FALSE;
	}
	e->Delete();
	m_App.SetVisible( m_bVisual );
	m_App.SetUserControl( m_bControl );

	return TRUE;
}


BOOL CTwExcleWidget::Open( IN const CString& strFilePath, OUT CTwWorkSheetsWidget& Worksheets )
{
	try
	{
		m_Books.AttachDispatch( m_App.GetWorkbooks() );
		COleVariant var( (long)DISP_E_PARAMNOTFOUND, VT_ERROR );
		COleVariant varTrue( (long)TRUE );
		LPDISPATCH  lpDisp = m_Books.Open(  strFilePath, var, varTrue, var, var, var, var, var, var, var, var, var, var, var, var );
		m_Book.AttachDispatch( lpDisp );
		Worksheets.AttachDispatch( m_Book.GetWorksheets() );
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH

	return TRUE;
}

BOOL CTwExcleWidget::Create( OUT CTwWorkSheetsWidget& Worksheets )
{
	try
	{
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
		m_Books.AttachDispatch( m_App.GetWorkbooks() ); 
		m_Book.AttachDispatch(m_Books.Add(covOptional),TRUE);
		Worksheets.AttachDispatch(  m_Book.GetWorksheets() );

		return TRUE;
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH
	
}

CTwExcleWidget::CTwExcleWidget()
{
	m_bVisual    = FALSE;
	m_bControl   = FALSE;
	m_bQuit      = TRUE;

}

CTwExcleWidget::~CTwExcleWidget()
{
	if( m_bQuit )
		m_App.Quit();
}

#pragma endregion CTwExcleWidget



#pragma region CTwWorkSheetsWidget
CTwWorkSheetsWidget::CTwWorkSheetsWidget()
{

}

CTwWorkSheetsWidget::~CTwWorkSheetsWidget()
{
	ReleaseDispatch();
}

void CTwWorkSheetsWidget::AttachDispatch( LPDISPATCH lpDispatch )
{
	m_Sheets.AttachDispatch( lpDispatch );
}

void CTwWorkSheetsWidget::ReleaseDispatch()
{
	m_Sheets.ReleaseDispatch();
}

int CTwWorkSheetsWidget::GetCount()
{
	try
	{
		return m_Sheets.GetCount();
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH
}

BOOL CTwWorkSheetsWidget::GetAt( IN int nIndex, OUT CTwWorkSheetWidget& WorkSheet )
{
	try
	{
		LPDISPATCH lpDisp = m_Sheets.GetItem( COleVariant( (short)(nIndex) ) );
		WorkSheet.AttachDispatch( lpDisp );

		return TRUE;
	}

	TW_EXCLEWIDGET_EXCEPTION_CATCH
		
	return FALSE;
}

BOOL CTwWorkSheetsWidget::GetAt( IN const CString& strSheetName, OUT CTwWorkSheetWidget& WorkSheet )
{
	return FALSE;
}

#pragma endregion CTwWorkSheetsWidget




#pragma region CTwWorkSheetWidget

CTwWorkSheetWidget::CTwWorkSheetWidget()
{

}

CTwWorkSheetWidget::~CTwWorkSheetWidget()
{
	ReleaseDispatch();
}

void CTwWorkSheetWidget::AttachDispatch( LPDISPATCH lpDispatch )
{
	m_Sheet.AttachDispatch( lpDispatch );
}

void CTwWorkSheetWidget::ReleaseDispatch()
{
	m_Sheet.ReleaseDispatch();
}

BOOL CTwWorkSheetWidget::GetUsedRange( OUT CTwRangeWidget& RgUsed )
{
	try
	{
		RgUsed.AttachDispatch( m_Sheet.GetUsedRange() );

		return TRUE;
	}

	TW_EXCLEWIDGET_EXCEPTION_CATCH
	return FALSE;
}

BOOL CTwWorkSheetWidget::GetAll( OUT CTwRangeWidget& RgAll )
{
	try
	{
		RgAll.AttachDispatch( m_Sheet.GetCells() ) ;
		return TRUE;
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH
	return FALSE;
}

#pragma endregion CTwWorkSheetWidget





#pragma region CTwRangeWidget
CTwRangeWidget::CTwRangeWidget()
{

}

CTwRangeWidget::~CTwRangeWidget()
{
	ReleaseDispatch();
}

void CTwRangeWidget::AttachDispatch( LPDISPATCH lpDispatch )
{
	m_Rg.AttachDispatch( lpDispatch );
}

void CTwRangeWidget::ReleaseDispatch()
{
	m_Rg.ReleaseDispatch();
}


BOOL CTwRangeWidget::GetItem( IN int nRow, IN int nCol, OUT CTwRangeWidget& Item )
{
	try
	{
		Item.AttachDispatch( m_Rg.GetItem(COleVariant((long)(nRow)), COleVariant((long)(nCol))).pdispVal );
		return TRUE;
	}

	TW_EXCLEWIDGET_EXCEPTION_CATCH
}

BOOL CTwRangeWidget::GetItemText( IN int nRow, IN int nCol, OUT CString& strRes )
{
	CTwRangeWidget  Item;
	if( GetItem(nRow, nCol, Item)  == FALSE ) return FALSE;

	strRes.Empty();

	//office::Range::GetValue();
	//office::Range::GetValue2();
	try
	{
		_bstr_t bstr( Item.m_Rg.GetText() );                //使用此种方法 当单元跟内容显示为 #########时会出现错误
		strRes = (TCHAR*)bstr;
		strRes.Trim();
		return TRUE;
	}

	TW_EXCLEWIDGET_EXCEPTION_CATCH
	
}

int CTwRangeWidget::GetRowCount()
{
	try
	{
		office::Range rg( m_Rg.GetRows() );
		return rg.GetCount();
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH;
}

int CTwRangeWidget::GetColCount()
{
	try
	{
		office::Range rg( m_Rg.GetColumns() );
		return rg.GetCount();
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH;
}

BOOL CTwRangeWidget::WriteItemText( IN int nRow, IN int nCol, IN double dValue )
{
	try
	{
		m_Rg.SetItem( (COleVariant)(short)(nRow), (COleVariant)(short)( nCol),_variant_t(dValue) );
		return TRUE;
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH;
 
}

BOOL CTwRangeWidget::WriteItemText( IN int nRow, IN int nCol, IN const CString& strValue )
{
	try
	{
		m_Rg.SetItem( (COleVariant)(short)(nRow), (COleVariant)(short)( nCol),_variant_t(strValue) );
		return TRUE;
	}
	TW_EXCLEWIDGET_EXCEPTION_CATCH;
}

#pragma endregion CTwRangeWidget
