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

public://新增成员和函数
	CImage*                              m_pImage;  //图像指针
	CImage*                               m_pFreq;  //FFT频谱
	CRect*                           m_pPaintRect;  //绘图区
	BYTE*                               m_dataSrc;  //原始数据
	BYTE*                               m_pOrigin;  //指向原图
	BYTE*                                 m_pThis;  //指向当前图像
	int                                m_nChannel;  //通道
	int                                    m_nBPP;  //位数

	//源图像信息
	int                             m_nImageWidth;  //宽
	int                            m_nImageHeight;  //高
	LONG                                m_nRowlen;  //位宽
	LONG                               m_nlenData;  //长度

	//按钮
	CMFCButton*                           m_pBnOK;  //确定
	CMFCButton*                       m_pBnCancel;  //取消
	CMFCButton*                        m_pBnReset;  //重置
	CMFCButton*                         m_pBnFreq;  //频谱
	CMFCButton*                     m_pBnMinPower;  //最小平方滤波
	CMFCButton*                    m_pBnPSEFilter;  //频均衡滤波
	CMFCButton*                 m_pBnWienerFilter;  //维纳滤波
	CMFCButton*                 m_pBnButterworthH;  //巴特沃斯高通
	CMFCButton*                 m_pBnButterworthL;  //巴特沃斯低通

	/*** 函数 ***/
	CDIPSysDlg* GetDocument();
	void GetImageInfo();                            //获取源位图信息
	void GetImageData();                            //获取源位图数据
	void Reshape(CWnd* pWnd, double Space, int nNumber);

	/*** 变换函数 ***/
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

	/*** 频域滤波 ***/
	void MinPower(HDIB hDIB, float fD);
	void PSE_Filter(HDIB hDIB, float fD);
	void WienerFilter(HDIB hDIB, float fD);
	void RetrorseFilter(HDIB hDIB,float fD);
	void MutualFilter(HDIB hDIB, CRect* pRect, int nSum);
	void ButterworthH(HDIB hDIB, float fD);
	void ButterworthL(HDIB hDIB, float fD);

	//消息响应
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
