#pragma once

#include "FreqFilterWnd.h"

// CFreqFilterDlg �Ի���

class CFreqFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFreqFilterDlg)

public:
	CFreqFilterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFreqFilterDlg();

// �Ի�������
	enum { IDD = IDD_FREQFILTER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public://������Ա�ͺ���
	CFreqFilterWnd* m_pFreqFilterWnd;  //Ψһ�ĳ�Ա����(ID:2300)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
