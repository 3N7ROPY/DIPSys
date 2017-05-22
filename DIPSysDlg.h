
// DIPSysDlg.h : ͷ�ļ�
//

#pragma once

#include "resource.h"
#include "UndoStack.h"

//������
class CColorGradDlg;
class CCurveDlg;
class CHistogramDLg;
class CSpaceFilterDlg;
class CFreqFilterDlg;

#define  MAX_UNDO_NUMBER 10   //���������

// CDIPSysDlg �Ի���
class CDIPSysDlg : public CDialogEx
{
// ����
public:
	CDIPSysDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CDIPSysDlg();

// �Ի�������
	enum { IDD = IDD_DIPSYS_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	/*** ������Ա�뺯�� ***/
private:
	CImage*                  m_pImage;  //CImage����
	CRect*               m_pPaintRect;  //��ͼ��
	CPoint*               m_pptOrigin;  //��ͼ���

	//��ջ
	CUndoStack            m_UndoStack;  //���ڳ����Ķ�ջ

	/*** ��ģʽ�Ի��� ***/
	CColorGradDlg*    m_pColorGradDlg;  //"ɫ��"�Ի���
	CCurveDlg*            m_pCurveDlg;  //"����"�Ի���
	CHistogramDLg*    m_pHistogramDlg;  //"ֱ��ͼ"�Ի���
	CSpaceFilterDlg*m_pSpaceFilterDlg;  //"�ռ��˲�"�Ի���
	CFreqFilterDlg*  m_pFreqFilterDlg;  //"Ƶ���˲�"�Ի���

	//���Ʊ���
	BOOL                    m_bScroll;  //���ڹ�����ͼ

	//��ݼ�
	HACCEL                 m_MyHotkey;  //��ݼ�

public:
	CImage* GetImage();              // ����
	void Refresh();                  // ˢ��
	BOOL RGB2Gray();                 // ת��Ϊ�Ҷ�ͼ��
	void PushImage();                // ����ǰͼ�񱣴�
	void PopImage();                 // ��ջ��ͼ��ȡ��
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