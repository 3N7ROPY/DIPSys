// CLAHEDLg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPSys.h"
#include "HistogramDLg.h"
#include "afxdialogex.h"

#include "HistogramWnd.h"


// CCLAHEDLg 对话框

IMPLEMENT_DYNAMIC(CHistogramDLg, CDialogEx)

CHistogramDLg::CHistogramDLg(CWnd* pParent /*=NULL*/) : CDialogEx(CHistogramDLg::IDD, pParent)
{
	m_pCLAHEWnd = NULL;
}

CHistogramDLg::~CHistogramDLg()
{
	if (m_pCLAHEWnd != NULL)
	{
		delete m_pCLAHEWnd;
	}
}

void CHistogramDLg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDLg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCLAHEDLg 消息处理程序


int CHistogramDLg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pCLAHEWnd = new CHistogramWnd;
	m_pCLAHEWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 400), this, 2100);
	return 0;
}


void CHistogramDLg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}


void CHistogramDLg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pCLAHEWnd->GetSafeHwnd())
	{
		m_pCLAHEWnd->MoveWindow(0, 0, cx, cy);
	}
}

BOOL CHistogramDLg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置对话框大小
	int nDlgWidth = 500;
	int nDlgHeight = 400;
	::SetWindowPos(this->m_hWnd, HWND_TOP, 200, 600, nDlgWidth, nDlgHeight, SWP_SHOWWINDOW);
	return TRUE;
}
