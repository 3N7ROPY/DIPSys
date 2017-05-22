
// DIPSysDlg.h : 头文件
//

#pragma once

#include "resource.h"
#include "UndoStack.h"

//类声明
class CColorGradDlg;
class CCurveDlg;
class CHistogramDLg;
class CSpaceFilterDlg;
class CFreqFilterDlg;

#define  MAX_UNDO_NUMBER 10   //最大撤销级别

// CDIPSysDlg 对话框
class CDIPSysDlg : public CDialogEx
{
// 构造
public:
	CDIPSysDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CDIPSysDlg();

// 对话框数据
	enum { IDD = IDD_DIPSYS_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	/*** 新增成员与函数 ***/
private:
	CImage*                  m_pImage;  //CImage对象
	CRect*               m_pPaintRect;  //绘图区
	CPoint*               m_pptOrigin;  //绘图起点

	//堆栈
	CUndoStack            m_UndoStack;  //用于撤销的堆栈

	/*** 非模式对话框 ***/
	CColorGradDlg*    m_pColorGradDlg;  //"色阶"对话框
	CCurveDlg*            m_pCurveDlg;  //"曲线"对话框
	CHistogramDLg*    m_pHistogramDlg;  //"直方图"对话框
	CSpaceFilterDlg*m_pSpaceFilterDlg;  //"空间滤波"对话框
	CFreqFilterDlg*  m_pFreqFilterDlg;  //"频域滤波"对话框

	//控制变量
	BOOL                    m_bScroll;  //正在滚动视图

	//快捷键
	HACCEL                 m_MyHotkey;  //快捷键

public:
	CImage* GetImage();              // 方法
	void Refresh();                  // 刷新
	BOOL RGB2Gray();                 // 转换为灰度图像
	void PushImage();                // 将当前图像保存
	void PopImage();                 // 将栈顶图像取出
	BOOL Zoom(int widthnew, int heightnew);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCmdOpen();
	afx_msg void OnCmdSave();
	afx_msg void OnCmdColorGrad();
	afx_msg void OnCmdCurve();
	afx_msg void OnCmdHistogramDlg();
	afx_msg void OnCmdSpaceFilter();
	afx_msg void OnCmdFreqFilter();
	afx_msg void OnAppAbout();
	afx_msg void OnAuthorBlog();
	afx_msg void OnAuthorMicroBlog();
	afx_msg void OnCallZoomDlg();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHotkeyAppExit();
	afx_msg void OnHotkeyOpenImage();
	afx_msg void OnHotkeySaveImage();
	afx_msg void OnHotkeyColorgrad();
	afx_msg void OnHotkeyCurve();
	afx_msg void OnHotkeyHistogram();
	afx_msg void OnHotkeySpacefilter();
	afx_msg void OnHotkeyFreqfilter();
	afx_msg void OnHotkeyZoom();
	afx_msg void OnHotkeyAbout();
	afx_msg void OnHotkeyBlog();
	afx_msg void OnHotkeyMicroBlog();
	afx_msg void OnRgbToGray();
	afx_msg void OnHotkeyRgbToGray();
	afx_msg void OnEditUndo();
	afx_msg void OnHotkeyUndo();
	afx_msg void OnFitWindow();
};