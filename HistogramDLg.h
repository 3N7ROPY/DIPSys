#pragma once


// CCLAHEDLg �Ի���

class CHistogramWnd;

class CHistogramDLg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDLg)

public:
	CHistogramDLg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHistogramDLg();

// �Ի�������
	enum { IDD = IDD_HISTOGRAM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public://������Ա�뺯��
	CHistogramWnd*              m_pCLAHEWnd;  //Ψһ�ĳ�Ա����(ID:2100)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};