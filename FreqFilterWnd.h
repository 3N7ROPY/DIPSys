#pragma once


// CFreqFilterWnd

#include "DIPSysDlg.h"
#include <cmath>
#include <complex>
using namespace std;

#define HDIB                         HANDLE 
#define PI                           3.141592653
#define WIDTHBYTES(bits)             (((bits) + 31) / 32 * 4)


class CFreqFilterWnd : public CWnd
{
	DECLARE_DYNAMIC(CFreqFilterWnd)

public:
	CFreqFilterWnd();
	virtual ~CFreqFilterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public://������Ա�ͺ���
	CImage*                              m_pImage;  //ͼ��ָ��
	CImage*                               m_pFreq;  //FFTƵ��
	CRect*                           m_pPaintRect;  //��ͼ��
	BYTE*                               m_dataSrc;  //ԭʼ����
	BYTE*                               m_pOrigin;  //ָ��ԭͼ
	BYTE*                                 m_pThis;  //ָ��ǰͼ��
	int                                m_nChannel;  //ͨ��
	int                                    m_nBPP;  //λ��

	//Դͼ����Ϣ
	int                             m_nImageWidth;  //��
	int                            m_nImageHeight;  //��
	LONG                                m_nRowlen;  //λ��
	LONG                               m_nlenData;  //����

	//��ť
	CMFCButton*                           m_pBnOK;  //ȷ��
	CMFCButton*                       m_pBnCancel;  //ȡ��
	CMFCButton*                        m_pBnReset;  //����
	CMFCButton*                         m_pBnFreq;  //Ƶ��
	CMFCButton*                     m_pBnMinPower;  //��Сƽ���˲�
	CMFCButton*                    m_pBnPSEFilter;  //Ƶ�����˲�
	CMFCButton*                 m_pBnWienerFilter;  //ά���˲�
	CMFCButton*                 m_pBnButterworthH;  //������˹��ͨ
	CMFCButton*                 m_pBnButterworthL;  //������˹��ͨ

	/*** ���� ***/
	CDIPSysDlg* GetDocument();
	void GetImageInfo();                            //��ȡԴλͼ��Ϣ
	void GetImageData();                            //��ȡԴλͼ����
	void Reshape(CWnd* pWnd, double Space, int nNumber);

	/*** �任���� ***/
	void DIBIDWT(HDIB hDIB);
	void IDWT(LPBYTE lpData, int nX, int nY, int nXSize, int nYSize);
	void DIBDWT(HDIB hDIB);
	int a(int nX, int nXSize);
	void DWT(LPBYTE lpData, int nX, int nY, int nXSize, int nYSize);
	BOOL IFreqWALSH(double* f, double* F, LONG lWidth, LONG lHeight);
	BOOL FreqWALSH(double* f, double* F, LONG lWidth, LONG lHeight);
	BOOL DIBWalsh(HDIB hDIB);
	void IWALSH(double* F, double* f, int r);
	BOOL IFreqDCT(double* f, double* F, LONG lWidth, LONG lHeight);
	void WALSH(double* f, double* F, int r);
	BOOL FreqDCT(double* f, double* F, LONG lWidth, LONG lHeight);
	BOOL DIBDCT(HDIB hDIB);
	void IDCT(double* F,double* f, int r);
	void DCT(double* f, double* F, int r);
	BOOL IFourier(LPBYTE TD, LONG lWidth, LONG lHeight, complex<double> * FD);
	BOOL Fourier(complex<double> * TD, LONG lWidth, LONG lHeight, complex<double> * FD);
	BOOL DIBFourier(HDIB hDIB);
	void IFFT(complex<double> * FD, complex<double> * TD, int r);
	void FFT(complex<double> * TD, complex<double> * FD, int r);

	/*** Ƶ���˲� ***/
	void MinPower(HDIB hDIB, float fD);
	void PSE_Filter(HDIB hDIB, float fD);
	void WienerFilter(HDIB hDIB, float fD);
	void RetrorseFilter(HDIB hDIB,float fD);
	void MutualFilter(HDIB hDIB, CRect* pRect, int nSum);
	void ButterworthH(HDIB hDIB, float fD);
	void ButterworthL(HDIB hDIB, float fD);

	//��Ϣ��Ӧ
	afx_msg void OnCmdOK();
	afx_msg void OnCmdCancel();
	afx_msg void OnCmdReset();
	afx_msg void OnCmdFreq();
	afx_msg void OnCmdMinPower();
	afx_msg void OnCmdPSEFilter();
	afx_msg void OnCmdWienerFilter();
	afx_msg void OnCmdButterworthH();
	afx_msg void OnCmdButterworthL();
};
