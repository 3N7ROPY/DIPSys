#pragma once


// CCLAHEDLg 对话框

class CHistogramWnd;

class CHistogramDLg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDLg)

public:
	CHistogramDLg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHistogramDLg();

// 对话框数据
	enum { IDD = IDD_HISTOGRAM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public://新增成员与函数
	CHistogramWnd*              m_pCLAHEWnd;  //唯一的成员变量(ID:2100)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};