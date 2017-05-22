#pragma once
#include "afxwin.h"

class CDIPSysDlg;

// CZoomDlg �Ի���

class CZoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZoomDlg)

public:
	CZoomDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZoomDlg();

// �Ի�������
	enum { IDD = IDD_ZOOM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	
	BYTE*						m_dataSrc;            //ԭʼ����
	CDIPSysDlg*					m_pMainDlg;           //���Ի���
	CImage*						m_pImage;             //��ǰͼ��
	int							m_nChannel;           //ͨ����
	long						m_nImageWidth;        //ͼ����
	long						m_nImageHeight;       //ͼ��߶�
	long						m_nRowLen;            //ÿ���ֽ���
	long						m_nDatalen;           //�ܳ���


	BOOL Zoom(int widthnew, int heightnew);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedZoomDlgApply();
	afx_msg void OnCbnSelchangeZoomDlgCombo();
};
