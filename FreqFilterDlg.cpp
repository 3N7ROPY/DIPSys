// FreqFilterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPSys.h"
#include "FreqFilterDlg.h"
#include "afxdialogex.h"


// CFreqFilterDlg 对话框

IMPLEMENT_DYNAMIC(CFreqFilterDlg, CDialogEx)

CFreqFilterDlg::CFreqFilterDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CFreqFilterDlg::IDD, pParent)
{
	m_pFreqFilterWnd = NULL;
}

CFreqFilterDlg::~CFreqFilterDlg()
{
	if (m_pFreqFilterWnd != NULL)
	{
		delete m_pFreqFilterWnd;
	}
}

void CFreqFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFreqFilterDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFreqFilterDlg 消息处理程序


void CFreqFilterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pFreqFilterWnd->GetSafeHwnd())
	{
		m_pFreqFilterWnd->MoveWindow(0, 0, cx, cy);
	}
}


int CFreqFilterDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	//成员变量初始化
	m_pFreqFilterWnd = new CFreqFilterWnd;
	m_pFreqFilterWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 2300);

	return 0;
}


BOOL CFreqFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置对话框大小
	int nDlgWidth = 800;
	int nDlgHeight = 600;
	::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, nDlgWidth, nDlgHeight, SWP_SHOWWINDOW);
	return TRUE;
}