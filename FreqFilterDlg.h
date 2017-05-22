#pragma once

#include "FreqFilterWnd.h"

// CFreqFilterDlg 对话框

class CFreqFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFreqFilterDlg)

public:
	CFreqFilterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFreqFilterDlg();

// 对话框数据
	enum { IDD = IDD_FREQFILTER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public://新增成员和函数
	CFreqFilterWnd* m_pFreqFilterWnd;  //唯一的成员变量(ID:2300)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
