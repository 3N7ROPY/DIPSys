#pragma once

#include "ColorGradWnd.h"


// CColorGradDlg �Ի���

class CColorGradDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorGradDlg)

public:
	CColorGradDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CColorGradDlg();

// �Ի�������
	enum { IDD = IDD_COLORGRAD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public://Ψһ�ĳ�Ա����
	CColorGradWnd* m_pColorGradWnd;  /*ID:2000*/
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
