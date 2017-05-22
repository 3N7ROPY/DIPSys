#pragma once
#include "afxwin.h"

class CDIPSysDlg;

// CZoomDlg 对话框

class CZoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZoomDlg)

public:
	CZoomDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZoomDlg();

// 对话框数据
	enum { IDD = IDD_ZOOM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox					m_ZoomDlgCombo;
	CEdit						m_EditImageWidth;
	CEdit						m_EditImageHeight;
	CEdit						m_EditImageRatio;
	int							m_nComboSelected;
	double						m_dWidthEdit;
	double						m_dHeightEdit;
	double						m_dImageRatio;

	int							m_nWidthNew;
	int							m_nHeightNew;
	double						m_dWidthRatio;
	double						m_dHeightRatio;
	
	BYTE*						m_dataSrc;            //原始数据
	CDIPSysDlg*					m_pMainDlg;           //主对话框
	CImage*						m_pImage;             //当前图像
	int							m_nChannel;           //通道数
	long						m_nImageWidth;        //图像宽度
	long						m_nImageHeight;       //图像高度
	long						m_nRowLen;            //每行字节数
	long						m_nDatalen;           //总长度


	BOOL Zoom(int widthnew, int heightnew);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedZoomDlgApply();
	afx_msg void OnCbnSelchangeZoomDlgCombo();
};
