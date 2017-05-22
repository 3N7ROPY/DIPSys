// FreqFilterWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPSys.h"
#include "FreqFilterWnd.h"


// CFreqFilterWnd

IMPLEMENT_DYNAMIC(CFreqFilterWnd, CWnd)

CFreqFilterWnd::CFreqFilterWnd()
{
	m_pFreq = NULL;
	m_pPaintRect = NULL;
	m_dataSrc = NULL;

	m_pBnOK = NULL;            //确定
	m_pBnCancel = NULL;        //取消
	m_pBnReset = NULL;         //重置
	m_pBnFreq = NULL;          //频谱
	m_pBnMinPower = NULL;      //最小平方滤波
	m_pBnPSEFilter = NULL;     //频均衡滤波
	m_pBnWienerFilter = NULL;  //维纳滤波
	m_pBnButterworthH = NULL;  //巴特沃斯高通
	m_pBnButterworthL = NULL;  //巴特沃斯低通
}

CFreqFilterWnd::~CFreqFilterWnd()
{
	if (m_pFreq != NULL)                delete m_pFreq;
	if (m_pPaintRect != NULL)           delete m_pPaintRect;
	if (m_dataSrc != NULL)              delete [] m_dataSrc;

	if (m_pBnOK != NULL)                delete m_pBnOK;
	if (m_pBnCancel != NULL)            delete m_pBnCancel;
	if (m_pBnReset != NULL)             delete m_pBnReset;
	if (m_pBnFreq != NULL)              delete m_pBnFreq;
	if (m_pBnMinPower != NULL)          delete m_pBnMinPower;
	if (m_pBnPSEFilter != NULL)         delete m_pBnPSEFilter;
	if (m_pBnWienerFilter != NULL)      delete m_pBnWienerFilter;
	if (m_pBnButterworthH != NULL)      delete m_pBnButterworthH;
	if (m_pBnButterworthL != NULL)      delete m_pBnButterworthL;
}


BEGIN_MESSAGE_MAP(CFreqFilterWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//按钮
	ON_BN_CLICKED(2301, &CFreqFilterWnd::OnCmdOK)
	ON_BN_CLICKED(2302, &CFreqFilterWnd::OnCmdCancel)
	ON_BN_CLICKED(2303, &CFreqFilterWnd::OnCmdReset)
	ON_BN_CLICKED(2304, &CFreqFilterWnd::OnCmdFreq)
	ON_BN_CLICKED(2305, &CFreqFilterWnd::OnCmdMinPower)
	ON_BN_CLICKED(2306, &CFreqFilterWnd::OnCmdPSEFilter)
	ON_BN_CLICKED(2307, &CFreqFilterWnd::OnCmdWienerFilter)
	ON_BN_CLICKED(2308, &CFreqFilterWnd::OnCmdButterworthH)
	ON_BN_CLICKED(2309, &CFreqFilterWnd::OnCmdButterworthL)
END_MESSAGE_MAP()



// CFreqFilterWnd 消息处理程序




void CFreqFilterWnd::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (m_pFreq == NULL) return;
	if (m_pPaintRect->Width()<=0 || m_pPaintRect->Height()<=0) return;
	m_pFreq->Draw(dc, *m_pPaintRect);
}


int CFreqFilterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pImage = GetDocument()->GetImage();

	//绘图区
	CRect rect;
	GetClientRect(&rect);
	m_pPaintRect = new CRect(100, 10, rect.right-10, rect.bottom-10);
	double Space = rect.Height()/10.0;

	//确定
	m_pBnOK = new CMFCButton;
	m_pBnOK->Create(L"确  定", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, Space-10, 80, Space+10), this, 2301);

	//取消
	m_pBnCancel = new CMFCButton;
	m_pBnCancel->Create(L"取  消", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 2*Space-10, 80, 2*Space+10), this, 2302);

	//重置
	m_pBnReset = new CMFCButton;
	m_pBnReset->Create(L"重  置", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 3*Space-10, 80, 3*Space+10), this, 2303);

	//频谱
	m_pBnFreq = new CMFCButton;
	m_pBnFreq->Create(L"频  谱", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 4*Space-10, 80, 4*Space+10), this, 2304);

	//最小平方滤波
	m_pBnMinPower = new CMFCButton;
	m_pBnMinPower->Create(L"MP", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 5*Space-10, 80, 5*Space+10), this, 2305);

	//频均衡滤波
	m_pBnPSEFilter = new CMFCButton;
	m_pBnPSEFilter->Create(L"PSE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 6*Space-10, 80, 6*Space+10), this, 2306);

	//维纳滤波
	m_pBnWienerFilter = new CMFCButton;
	m_pBnWienerFilter->Create(L"维纳滤波", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 7*Space-10, 80, 7*Space+10), this, 2307);

	//巴特沃斯高通
	m_pBnButterworthH = new CMFCButton;
	m_pBnButterworthH->Create(L"高通滤波", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 8*Space-10, 80, 8*Space+10), this, 2308);

	//巴特沃斯低通
	m_pBnButterworthL = new CMFCButton;
	m_pBnButterworthL->Create(L"低通滤波", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 9*Space-10, 80, 9*Space+10), this, 2309);

	//获取位图信息
	GetImageInfo();
	//获取位图数据
	GetImageData();

	return 0;
}


void CFreqFilterWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	m_pPaintRect->right = rect.right-10;
	m_pPaintRect->bottom = rect.bottom-10;
	double Space = rect.Height()/10.0;
	Reshape(m_pBnOK, Space, 1);
	Reshape(m_pBnCancel, Space, 2);
	Reshape(m_pBnReset, Space, 3);
	Reshape(m_pBnFreq, Space, 4);
	Reshape(m_pBnMinPower, Space, 5);
	Reshape(m_pBnPSEFilter, Space, 6);
	Reshape(m_pBnWienerFilter, Space, 7);
	Reshape(m_pBnButterworthH, Space, 8);
	Reshape(m_pBnButterworthL, Space, 9);
}

void CFreqFilterWnd::Reshape(CWnd* pWnd, double Space, int nNumber)
{
	if (pWnd->GetSafeHwnd())
	{
		pWnd->MoveWindow(20, nNumber*Space-10, 60, 20);
	}
}

CDIPSysDlg* CFreqFilterWnd::GetDocument()
{
	return (CDIPSysDlg*)GetParent()->GetParent();
}

void CFreqFilterWnd::GetImageInfo()
{
	if (m_pImage == NULL) return;
	//获取位图信息
	m_nBPP = m_pImage->GetBPP();             //位数
	m_nChannel = m_nBPP/8;                   //通道

	//源图像信息
	m_nImageWidth = m_pImage->GetWidth();    //宽
	m_nImageHeight = m_pImage->GetHeight();  //高
	m_nRowlen = m_nImageWidth*m_nChannel;    //位宽
	m_nlenData = m_nImageHeight*m_nRowlen;   //长度
}

void CFreqFilterWnd::GetImageData()
{
	if (m_pImage == NULL) return;
	m_dataSrc = new BYTE[m_nlenData];
	m_pFreq = new CImage;
	m_pFreq->Create(m_nImageWidth, m_nImageHeight, 24);
	//获得图像数据首地址
	m_pOrigin = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(m_nImageHeight-1));
	m_pThis = (BYTE *)m_pFreq->GetBits()+(m_pFreq->GetPitch()*(m_nImageHeight-1));

	memcpy(m_dataSrc, m_pOrigin, m_nlenData);
	memcpy(m_pThis, m_dataSrc, m_nlenData);
}

afx_msg void CFreqFilterWnd::OnCmdOK()
{
	//直接关闭
	::SendMessage(GetParent()->GetSafeHwnd(), WM_CLOSE, 0, 0);
}

afx_msg void CFreqFilterWnd::OnCmdCancel()
{
	//恢复数据后关闭
	OnCmdReset();
	::SendMessage(GetParent()->GetSafeHwnd(), WM_CLOSE, 0, 0);
}

afx_msg void CFreqFilterWnd::OnCmdReset()
{
	if (m_pFreq != NULL)
	{
		memcpy(m_dataSrc, m_pOrigin, m_nlenData);
		memcpy(m_pThis, m_dataSrc, m_nlenData);
	}
}

afx_msg void CFreqFilterWnd::OnCmdFreq()
{
	// 调用DIBFourier()函数进行傅里叶变换
	if (m_pImage == NULL) return;
	if (DIBFourier(m_pImage) == FALSE)	return;
	memcpy(m_pThis, m_dataSrc, m_nlenData);
	memcpy(m_dataSrc, m_pOrigin, m_nlenData);
	InvalidateRect(m_pPaintRect);
}

afx_msg void CFreqFilterWnd::OnCmdMinPower()
{

}

afx_msg void CFreqFilterWnd::OnCmdPSEFilter()
{

}

afx_msg void CFreqFilterWnd::OnCmdWienerFilter()
{

}

afx_msg void CFreqFilterWnd::OnCmdButterworthH()
{

}

afx_msg void CFreqFilterWnd::OnCmdButterworthL()
{

}

//
// *** 其他 ***
//

// ************************************************************************
//  文件名：FFTDlg.cpp
//
//  图像正交变换函数库：
//
//	FFT()				- 一维快速傅里叶变换
//  IFFT()				- 一维快速傅里叶逆变换
//  Fourier()			- 二维快速傅立叶变换
//  IFourier()			- 二维快速傅立叶逆变换
//  DCT()				- 一维快速离散余弦变换
//  IDCT()				- 一维快速离散余弦逆变换
//	FreqDCT()			- 二维快速离散余弦变换
//  IFreqDCT()			- 二维快速离散余弦逆变换
//  WALSH()				- 一维沃尔什－哈达玛变换
//  IWALSH()			- 一维沃尔什－哈达玛逆变换
//	FreqWALSH()			- 二维沃尔什－哈达玛变换
//	IFreqWALSH()		- 二维沃尔什－哈达玛逆变换
//	DWT()				- 二维点阵的小波分解
//	IDWT()				- 二维点阵的小波重构
//	
//  DIBFourier()		- 图像的傅里叶变换
//  DIBDCT()			- 图像的离散余弦变换
//  DIBWalsh()			- 图像的沃尔什－哈达玛变换
//  DIBDWT()			- 图象的二维离散小波变换
//
//*************************************************************************


/*************************************************************************
 *
 * 函数名称：
 *   FFT()
 *
 * 参数:
 *   complex<double> * TD	- 指向时域数组的指针
 *   complex<double> * FD	- 指向频域数组的指针
 *   r						－2的幂数，即迭代次数
 *
 * 返回值:
 *   无。
 *
 * 说明:
 *   该函数用来实现快速傅里叶变换。
 *
 ************************************************************************/

void CFreqFilterWnd::FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	
	// 中间变量
	int		p;
	
	// 角度
	double	angle;
	
	complex<double> *W,*X1,*X2,*X;
	
	// 计算傅里叶变换点数
	LONG N = 1 << r;
	
	// 分配运算所需存储器
	W  = new complex<double>[N / 2];
	X1 = new complex<double>[N];
	X2 = new complex<double>[N];
	
	// 计算加权系数
	for(i = 0; i < N / 2; i++)
	{
		angle = -i * PI * 2 / N;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// 将时域点写入X1
	memcpy(X1, TD, sizeof(complex<double>) * N);
	
	// 采用蝶形算法进行快速傅里叶变换
	for(k = 0; k < r; k++)
	{
		for(j = 0; j < 1 << k; j++)
		{
			for(i = 0; i < 1<<(r - k -1); i++)
			{
				p = j * (1<<(r - k));
				X2[i + p] = X1[i + p] + X1[i + p + (int)(1<<(r - k -1))];
				X2[i + p + (int)(1<<(r - k -1))] = (X1[i + p] - X1[i + p + (int)(1<<(r - k -1))]) * W[i * (1<<k)];
			}
		}
		X  = X1;
		X1 = X2;
		X2 = X;
	}
	
	// 重新排序
	for(j = 0; j < N; j++)
	{
		p = 0;
		for(i = 0; i < r; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(r - i - 1);
			}
		}
		FD[j] = X1[p];
	}
	
	// 释放内存
	delete W;
	delete X1;
	delete X2;
}


/*************************************************************************
 *
 * 函数名称：
 *   IFFT()
 *
 * 参数:
 *   complex<double> * FD	- 指向频域值的指针
 *   complex<double> * TD	- 指向时域值的指针
 *   r						－2的幂数
 *
 * 返回值:
 *   无。
 *
 * 说明:
 *   该函数用来实现快速傅里叶逆变换。
 *
 ************************************************************************/

void CFreqFilterWnd::IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// 循环变量
	int		i;
	
	complex<double> *X;
	
	// 计算傅里叶变换点数
	LONG N = 1<<r;
	
	// 分配运算所需存储器
	X = new complex<double>[N];
	
	// 将频域点写入X
	memcpy(X, FD, sizeof(complex<double>) * N);
	
	// 求共轭
	for (i = 0; i < N; i++)
	{
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	}
	
	// 调用快速傅里叶变换
	FFT(X, TD, r);
	
	// 求时域点的共轭
	for (i = 0; i < N; i++)
	{
		TD[i] = complex<double> (TD[i].real() / N, -TD[i].imag() / N);
	}
	
	// 释放内存
	delete X;
}


/*************************************************************************
 *
 * 函数名称：
 *   Fourier()
 *
 * 参数:
 *   complex* TD		- 输入的时域序列
 *	 LONG lWidth		- 图象宽度
 *	 LONG lHeight		- 图象高度
 *	 complex* FD		- 输出的频域序列
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行二维快速傅里叶变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::Fourier(complex<double> * TD, LONG lWidth, LONG lHeight, complex<double> * FD)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG    k;

	// 更改光标形状
	BeginWaitCursor();
	
	// 进行傅里叶变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行傅里叶变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	         
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}
		
	// 分配内存
	complex<double> *TempT, *TempF;
	TempT = new complex<double>[h];
	TempF = new complex<double>[h];
	
	// 对y方向进行快速傅里叶变换
	for (i = 0; i < w * 3; i++)
	{
		// 抽取数据
		for (j = 0; j < h; j++)
			TempT[j] = TD[j * w * 3 + i];
		
		// 一维快速傅立叶变换
		FFT(TempT, TempF, hp);

		// 保存变换结果
		for (j = 0; j < h; j++)
			TD[j * w * 3 + i] = TempF[j];
	}
	
	// 释放内存
	delete TempT;
	delete TempF;

	// 分配内存
	TempT = new complex<double>[w];
	TempF = new complex<double>[w];
	
	// 对x方向进行快速傅里叶变换
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// 抽取数据
			for (j = 0; j < w; j++)
				TempT[j] = TD[i * w * 3 + j * 3 + k];

			// 一维快速傅立叶变换
			FFT(TempT, TempF, wp);

			// 保存变换结果
			for (j = 0; j < w; j++)
				FD[i * w * 3 + j * 3 + k] = TempF[j];
		}
	}

	// 释放内存
	delete TempT;
	delete TempF;

	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   IFourier()
 *
 * 参数:
 *   LPBYTE TD			- 返回的空域数据
 *   LONG lWidth		- 空域图象的宽度
 *	 LONG lHeight		- 空域图象的高度
 *	 complex* FD		- 输入的频域数据
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行二维快速傅里叶逆变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::IFourier(LPBYTE TD, LONG lWidth, LONG lHeight, complex<double> * FD)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG    k;

	// 更改光标形状
	BeginWaitCursor();
	
	// 进行傅里叶变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行傅里叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 计算图像每行的字节数
	LONG lLineBytes = m_nRowlen;

	// 分配内存
	complex<double> *TempT, *TempF;
	TempT = new complex<double>[w];
	TempF = new complex<double>[w];
	
	// 对x方向进行快速傅里叶变换
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// 抽取数据
			for (j = 0; j < w; j++)
				TempF[j] = FD[i * w * 3 + j * 3 + k];

			// 一维快速傅立叶变换
			IFFT(TempF, TempT, wp);

			// 保存变换结果
			for (j = 0; j < w; j++)
				FD[i * w * 3 + j * 3 + k] = TempT[j];
		}
	}

	// 释放内存
	delete TempT;
	delete TempF;
	
	TempT = new complex<double>[h];
	TempF = new complex<double>[h];

	// 对y方向进行快速傅里叶变换
	for (i = 0; i < w * 3; i++)
	{
		// 抽取数据
		for (j = 0; j < h; j++)
			TempF[j] = FD[j * w * 3 + i];
		
		// 一维快速傅立叶变换
		IFFT(TempF, TempT, hp);

		// 保存变换结果
		for (j = 0; j < h; j++)
			FD[j * w * 3 + i] = TempT[j];
	}
	
	// 释放内存
	delete TempT;
	delete TempF;

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < lHeight && j < lLineBytes)
				*(TD + i * lLineBytes + j) = FD[i * w * 3 + j].real();
		}
	}

	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBFourier()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行傅里叶变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::DIBFourier(HDIB hDIB)
{
	// 指向源图像的指针
	BYTE*	lpSrc;

	// 中间变量
	double	dTemp;
	LONG TI,TJ;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 指向DIB的指针
	LPBYTE	lpDIB;
	
	// 指向DIB象素指针
	LPBYTE    lpDIBBits = m_dataSrc;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = m_nRowlen;

	// 进行傅里叶变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行傅里叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 分配内存
	complex<double> *FD, *TD, *TempD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];
	TempD =  new complex<double>[w * h * 3];
	
	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return FALSE;

	// 释放内存
	delete []TD;

	// 将原点放置于图像中心位置
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < 3 * w; j++)
		{
			if (i < h / 2)
				TI = i + h / 2;
			else
				TI = i - h / 2;

			if (j < w * 3 /2)
				TJ = j + 3 * w / 2;
			else 
				TJ = j - 3 * w / 2;

			// 保存转换后的频谱图像
			TempD[i * w * 3 + j] = FD[TI * w * 3 + TJ];
		}
	}

	// 行
	for(i = (int)(h - lHeight) / 2; i < (int)(h + lHeight) / 2; i++)
	{
		// 列
		for(j = (int)(w * 3 - lLineBytes) / 2; j < (int)(w * 3 + lLineBytes) / 2; j += 3)
		{
			// 计算频谱
			dTemp = sqrt(TempD[w * 3 * i + j].real() * TempD[w * 3 * i + j].real() + 
				         TempD[w * 3 * i + j].imag() * TempD[w * 3 * i + j].imag()) / 100;

			// 判断是否超过255
			if (dTemp > 255)
			{
				// 对于超过的，直接设置为255
				dTemp = 255;
			}

			// 限制为原图大小范围
			TI = i - (h - lHeight) / 2;
			TJ = j / 3 - (w - lWidth) / 2;
			
			// 对应象素指针
			lpSrc = (BYTE*)lpDIBBits + lLineBytes * TI + TJ * 3;

			// 更新源图像
			* (lpSrc) = (BYTE) (dTemp);
			* (lpSrc + 1) = (BYTE) (dTemp);
			* (lpSrc + 2) = (BYTE) (dTemp);
		}
	}

	// 解除锁定
	::GlobalUnlock(hDIB);

	// 删除临时变量
	delete []FD;
	delete []TempD;
	
	// 恢复光标
	EndWaitCursor();
	
	// 返回
	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   DCT()
 *
 * 参数:
 *   double * f				- 指向时域值的指针
 *   double * F				- 指向频域值的指针
 *   r						－2的幂数
 *
 * 返回值:
 *   无。
 *
 * 说明:
 *   该函数用来实现一维快速离散余弦变换
 *
 ************************************************************************/

void CFreqFilterWnd::DCT(double *f, double *F, int r)
{
	// 循环变量
	int		i;
	
	// 中间变量
	double	dTemp;
	
	// 计算离散余弦变换点数
	LONG N = 1<<r;
	
	// 申请并分配内存
	complex<double> *XIn;
	complex<double> *XOut;
	XIn = new complex<double>[N * 2];
	XOut = new complex<double>[N * 2];
	
	// 赋初值为0
	memset(XIn, 0, sizeof(complex<double>) * N * 2);
	memset(XOut, 0, sizeof(complex<double>) * N * 2);
	
	// 将时域点写入数组X
	for (i = 0; i < N; i++)
		XIn[i] = complex<double>(*(f + i), 0);
	
	// 调用快速傅里叶变换
	FFT(XIn, XOut, r + 1);
	
	// 调整系数
	dTemp = 1 / sqrt(N);
	
	// 求F[0]
	F[0] = XOut[0].real() * dTemp;
	
	dTemp *= sqrt(2);
	
	// 求F[u]
	for (i = 1; i < N; i++)
		*(F + i) = (XOut[i].real() * cos(i * PI / (N * 2)) + XOut[i].imag() * sin(i * PI / (N * 2))) * dTemp;
	
	// 释放内存
	delete[] XIn;
	delete[] XOut;
}


/*************************************************************************
 *
 * 函数名称：
 *   IDCT()
 *
 * 参数:
 *   double * F				- 指向频域值的指针
 *   double * f				- 指向时域值的指针
 *   r						－2的幂数
 *
 * 返回值:
 *   无。
 *
 * 说明:
 *   该函数实现一维快速离散余弦逆变换
 *
 ************************************************************************/

void CFreqFilterWnd::IDCT(double *F, double *f, int r)
{
	// 循环变量
	int		i;
	
	// 中间变量
	double	dTemp, d0;
		
	// 计算离散余弦变换点数
	LONG N = 1<<r;
	
	// 分配内存
	complex<double> *XIn;
	complex<double> *XOut;
	XIn = new complex<double>[N * 2];
	XOut = new complex<double>[N * 2];

	// 赋初值为0
	memset(XIn, 0, sizeof(complex<double>) * N * 2);
	memset(XOut, 0, sizeof(complex<double>) * N * 2);
	
	// 将频域变换后点写入数组X
	for (i = 0; i < N; i++)
		XIn[i] = complex<double>(F[i] * cos(i * PI / (N * 2)), F[i] * sin(i * PI / (N * 2)));
	
	// 调用快速傅里叶反变换
	IFFT(XIn, XOut, r + 1);
	
	// 调整系数
	dTemp = sqrt(2.0 / N);
	d0 = (sqrt(1.0 / N) - dTemp) * F[0];
	
	// 计算f(x)
	for (i = 0; i < N; i++)
		f[i] = d0 + XOut[i].real()* dTemp * 2 * N;
	
	// 释放内存
	delete[] XIn;
	delete[] XOut;
}


/*************************************************************************
 *
 * 函数名称：
 *   FreqDCT()
 *
 * 参数:
 *   double* f			- 输入的时域序列
 *   double* F			- 输出的频域序列
 *	 LONG lWidth		- 图象宽度
 *	 LONG lHeight		- 图象高度
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行二维快速离散余弦变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::FreqDCT(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG    k;

	// 更改光标形状
	BeginWaitCursor();
	
	// 进行离散余弦变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}
		
	// 分配内存
	double* TempIn = new double[h];
	double* TempOut = new double[h];
	
	// 对y方向进行离散余弦变换
	for (i = 0; i < w * 3; i++)
	{
		// 抽取数据
		for (j = 0; j < h; j++)
			TempIn[j] = f[j * w * 3 + i];
		
		// 一维快速离散余弦变换
		DCT(TempIn, TempOut, hp);

		// 保存变换结果
		for (j = 0; j < h; j++)
			f[j * w * 3 + i] = TempOut[j];
	}
	
	// 释放内存
	delete TempIn;
	delete TempOut;

	// 分配内存
	TempIn = new double[w];
	TempOut = new double[w];
	
	// 对x方向进行快速离散余弦变换
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// 抽取数据
			for (j = 0; j < w; j++)
				TempIn[j] = f[i * w * 3 + j * 3 + k];

			// 一维快速离散余弦变换
			DCT(TempIn, TempOut, wp);

			// 保存变换结果
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// 释放内存
	delete TempIn;
	delete TempOut;

	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   IFreqDCT()
 *
 * 参数:
 *   double* f			- 输入的时域序列
 *   double* F			- 输出的频域序列
 *	 LONG lWidth		- 图象宽度
 *	 LONG lHeight		- 图象高度
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行二维快速离散余弦逆变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::IFreqDCT(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG    k;

	// 更改光标形状
	BeginWaitCursor();
	
	// 进行离散余弦变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行傅里叶变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 计算图像每行的字节数
	LONG lLineBytes = m_nRowlen;

	// 分配内存
	double* TempIn = new double[w];
	double* TempOut = new double[w];
	
	// 对x方向进行快速傅里叶变换
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// 抽取数据
			for (j = 0; j < w; j++)
				TempIn[j] = F[i * w * 3 + j * 3 + k];

			// 一维快速傅立叶变换
			IDCT(TempIn, TempOut, wp);

			// 保存变换结果
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// 释放内存
	delete TempIn;
	delete TempOut;
	
	TempIn = new double[h];
	TempOut = new double[h];

	// 对y方向进行快速傅里叶变换
	for (i = 0; i < w * 3; i++)
	{
		// 抽取数据
		for (j = 0; j < h; j++)
			TempIn[j] = F[j * w * 3 + i];
		
		// 一维快速傅立叶变换
		IDCT(TempIn, TempOut, hp);

		// 保存变换结果
		for (j = 0; j < h; j++)
			F[j * w * 3 + i] = TempOut[j];
	}
	
	// 释放内存
	delete TempIn;
	delete TempOut;
	
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < lHeight && j < lLineBytes)
				*(f + i * lLineBytes + j) = F[i * w * 3 + j];
		}
	}

	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   DIBDCT()
 *
 * 参数:
 *   HDIB  hDIB		    - 待处理的DIB
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行离散余弦变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::DIBDCT(HDIB hDIB)
{
	// 进行离散余弦变换的宽度和高度（2的整数次方）
	LONG	i;
	LONG	j;
	
	// 指向DIB的指针
	LPBYTE	lpDIB;
	
	// 指向DIB象素指针
	LPBYTE  lpDIBBits = m_dataSrc;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;
	
	// 计算图像每行的字节数
	LONG lLineBytes = m_nRowlen;
	
	// 进行离散余弦变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 分配内存
	double *f = new double[w * h * 3];
	double *F = new double[w * h * 3];

	// 向时域赋值并补零
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < lHeight && j < lLineBytes)
				f[i * w * 3 + j] = *(BYTE*)(lpDIBBits + lLineBytes * i + j);
			else
				f[w * i * 3 + j] = 0.0f;
		}
	}

	// 进行频谱分析
	if (FreqDCT(f, F,lWidth, lHeight) == FALSE)
		return FALSE;

	// 更新所有象素
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lLineBytes; j++)
		{
			// 判断是否超过255
			if (fabs(F[i * w * 3 + j]) > 255)
			{
				// 对于超过的，直接设置为255
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = 255;
			}
			else
			{
				// 如果没有超过，则按实际计算结果赋值
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = fabs(F[i * w * 3 + j]);
			}
		}
	}

	// 解除锁定
	::GlobalUnlock(hDIB);
	
	// 释放内存
	delete []f;
	delete[] F;

	// 返回
	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   WALSH()
 *
 * 参数:
 *   double* f			- 输入的时域序列
 *   double* F			- 输出的频域序列
 *   int r				- 2的幂数		
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行一维快速沃尔什——哈达马变换。
 *
 ************************************************************************/

void CFreqFilterWnd::WALSH(double *f, double *F, int r)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	
	// 中间变量
	int		p;	
	double* X;
	
	// 计算快速沃尔什变换点数
	LONG N = 1 << r;
	
	// 分配运算所需的数组
	double* X1 = new double[N];
	double* X2 = new double[N];
	
	// 将时域点写入数组X1
	memcpy(X1, f, sizeof(double) * N);
	
	// 蝶形运算
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1<<k; j++)
		{
			for (i = 0; i < 1<<(r - k - 1); i++)
			{
				p = j * (1<<(r - k));
				X2[i + p] = X1[i + p] + X1[i + p + (int)(1<<(r - k - 1))];
				X2[i + p + (int)(1<<(r - k - 1))] = X1[i + p] - X1[i + p + (int)(1<<(r - k - 1))];
			}
		}
		
		// 互换X1和X2  
		X = X1;
		X1 = X2;
		X2 = X;
	}
	
	// 调整系数
	for (j = 0; j < N; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r - i - 1);
			}
		}

		F[j] = X1[p] / N;
	}
	
	// 释放内存
	delete X1;
	delete X2;
}


/*************************************************************************
 *
 * 函数名称：
 *   IWALSH()
 *
 * 参数:
 *   double* f			- 输入的时域序列
 *   double* F			- 输出的频域序列
 *   int r				- 2的幂数		
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行一维快速沃尔什——哈达马逆变换。
 *
 ************************************************************************/

void CFreqFilterWnd::IWALSH(double *F, double *f, int r)
{
	// 循环变量
	int		i;
	
	// 计算变换点数
	LONG N = 1 << r;
	
	// 调用快速沃尔什－哈达玛变换进行反变换
	WALSH(F, f, r);
	
	// 调整系数
	for (i = 0; i < N; i++)
		f[i] *= N;
}


/*************************************************************************
 *
 * 函数名称：
 *   FreqWALSH()
 *
 * 参数:
 *   double* f			- 输入的时域序列
 *   double* F			- 输出的频域序列
 *	 LONG lWidth		- 图象宽度
 *	 LONG lHeight		- 图象高度
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行二维快速沃尔什——哈达玛变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::FreqWALSH(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG    k;

	// 更改光标形状
	BeginWaitCursor();
	
	// 进行离散余弦变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}
		
	// 分配内存
	double* TempIn = new double[h];
	double* TempOut = new double[h];
	
	// 对y方向进行离散余弦变换
	for (i = 0; i < w * 3; i++)
	{
		// 抽取数据
		for (j = 0; j < h; j++)
			TempIn[j] = f[j * w * 3 + i];
		
		// 一维快速离散余弦变换
		WALSH(TempIn, TempOut, hp);

		// 保存变换结果
		for (j = 0; j < h; j++)
			f[j * w * 3 + i] = TempOut[j];
	}
	
	// 释放内存
	delete TempIn;
	delete TempOut;

	// 分配内存
	TempIn = new double[w];
	TempOut = new double[w];
	
	// 对x方向进行快速离散余弦变换
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// 抽取数据
			for (j = 0; j < w; j++)
				TempIn[j] = f[i * w * 3 + j * 3 + k];

			// 一维快速离散余弦变换
			WALSH(TempIn, TempOut, wp);

			// 保存变换结果
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// 释放内存
	delete TempIn;
	delete TempOut;

	return TRUE;
}



/*************************************************************************
 *
 * 函数名称：
 *   IFreqWALSH()
 *
 * 参数:
 *   double* f			- 输入的时域序列
 *   double* F			- 输出的频域序列
 *	 LONG lWidth		- 图象宽度
 *	 LONG lHeight		- 图象高度
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数进行二维快速沃尔什——哈达玛逆变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::IFreqWALSH(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// 循环变量
	LONG	i;
	LONG	j;
	LONG    k;

	// 更改光标形状
	BeginWaitCursor();
	
	// 赋初值
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行傅里叶变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 计算图像每行的字节数
	LONG lLineBytes = m_nRowlen;

	// 分配内存
	double* TempIn = new double[w];
	double* TempOut = new double[w];
	
	// 对x方向进行快速傅里叶变换
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// 抽取数据
			for (j = 0; j < w; j++)
				TempIn[j] = F[i * w * 3 + j * 3 + k];

			// 一维快速傅立叶变换
			IWALSH(TempIn, TempOut, wp);

			// 保存变换结果
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// 释放内存
	delete TempIn;
	delete TempOut;
	
	TempIn = new double[h];
	TempOut = new double[h];

	// 对y方向进行快速傅里叶变换
	for (i = 0; i < w * 3; i++)
	{
		// 抽取数据
		for (j = 0; j < h; j++)
			TempIn[j] = F[j * w * 3 + i];
		
		// 一维快速傅立叶变换
		IWALSH(TempIn, TempOut, hp);

		// 保存变换结果
		for (j = 0; j < h; j++)
			F[j * w * 3 + i] = TempOut[j];
	}
	
	// 释放内存
	delete TempIn;
	delete TempOut;

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < lHeight && j < lLineBytes)
				*(f + i * lLineBytes + j) = F[i * w * 3 + j];
		}
	}

	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   DIBWalsh()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数对图象进行二维快速沃尔什——哈达马变换。
 *
 ************************************************************************/

BOOL CFreqFilterWnd::DIBWalsh(HDIB hDIB)
{
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 指向DIB的指针
	LPBYTE	lpDIB;
	
	// 指向DIB象素指针
	LPBYTE  lpDIBBits = m_dataSrc;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = m_nRowlen;
	
	// 进行沃尔什——哈达玛变换的宽度和高度（2的整数次方）
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	while (w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while (h < lHeight)
	{
		h *= 2;
		hp++;
	}
	
	// 分配内存
	double *f = new double[w * h * 3];
	double *F = new double[w * h * 3];
	
	// 向时域赋值并补零
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < lHeight && j < lLineBytes)
				f[i * w * 3 + j] = *(BYTE*)(lpDIBBits + lLineBytes * i + j);
			else
				f[w * i * 3 + j] = 0.0f;
		}
	}

	// 进行频谱分析
	if (FreqWALSH(f, F,lWidth, lHeight) == FALSE)
		return FALSE;
	
	// 更新所有象素
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lLineBytes; j++)
		{
			// 判断是否超过255
			if (fabs(F[i * w * 3 + j] * 1000) > 255)
			{
				// 对于超过的，直接设置为255
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = 255;
			}
			else
			{
				// 如果没有超过，则按实际计算结果赋值
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = fabs(F[i * w * 3 + j] * 1000);
			}
		}
	}

	// 解除锁定
	::GlobalUnlock(hDIB);

	//释放内存
	delete[] f;
	delete[] F;

	// 返回
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
//																	     //
//							小波变换									 //
//																		 //
///////////////////////////////////////////////////////////////////////////

#define DD 13
float h[DD] = { -0.00332761f,0.00569794f,	0.0196637f,	-0.0482603f,	-0.0485391f,
				0.292562f,	0.564406f,	0.292562f,	-0.0485391f,	-0.0482602f,
				-0.0196637f,	0.00569794f,	-0.0033276f};
float g[DD] = {0.00332761f,  0.00569794f,	-0.0196637f,	-0.0482603f,	0.0485391f,
			   0.292562f,	-0.564406f,	0.292562f,	0.0485391f,	-0.0482602f,
			   0.0196637f,	0.00569794f,	0.0033276f};
float hi[DD];
float gi[DD];

int CFreqFilterWnd::a(int nX, int nXSize)
{
	if (nX < 0)
		nX = -nX;
	if (nX >= nXSize)
		nX = nXSize * 2 - nX - 2;
	return nX;
}


/*************************************************************************
 *
 * 函数名称：
 *   DWT()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *
 * 返回值:
 *   void	            - 无返回值
 *
 * 说明:
 *   该函数对二维点阵进行离散小波变换。
 *
 ************************************************************************/

void CFreqFilterWnd::DWT(LPBYTE lpData, int nX, int nY, int nXSize, int nYSize)
{
	// 循环变量
	int i, j, k, n;

	// 中间变量
	float temp1, temp2;
	float* BufferX;
	float* BufferY;

	BufferX = new float[nXSize];
	BufferY = new float[nYSize];

	// 水平方向
	for (n = 0; n < nY; n++)
	{
		for (i = 0; i < nX; i += 2)
		{
			temp1 = temp2 = 0;
			for (j = -(DD - 1) / 2; j <= (DD - 1) / 2; j++)
				temp1 = temp1 + *(lpData + n * nX + a(i + j, nX)) * h[j + (DD - 1) / 2];
			for (j = -(DD - 1) / 2 + 1; j <= (DD - 1) / 2 + 1; j++)
				temp2 = temp2 + *(lpData + n * nX + a(i + j, nX)) * g[j + (DD - 1) / 2 - 1];
			BufferX[i / 2] = temp1;
			BufferX[i / 2 + nX / 2] = temp2;
		}

		// 回存数据
		for (k = 0; k < nX; k++)
			*(lpData + n * nX + k) = BufferX[k];
	}

	// 垂直方向
	for (n = 0; n < nX; n++)
	{
		for (i = 0; i < nY; i += 2)
		{
			temp1 = temp2 = 0;
			for (j = -(DD - 1) / 2; j <= (DD - 1) / 2; j++)
				temp1 = temp1 + *(lpData + a(i + j, nY) * nX + n) * h[j + (DD - 1) / 2];
			for (j = -(DD - 1) / 2 + 1; j <= (DD - 1) / 2 + 1; j++)
				temp2 = temp2 + *(lpData + a(i + j, nY) * nX + n) * g[j + (DD - 1) / 2 - 1];
			BufferY[i / 2] = temp2;
			BufferY[i / 2 + nY / 2] = temp1;
		}

		// 回存数据
		for (k = 0; k < nY; k++)
			*(lpData + k * nX + n) = BufferY[k];
	}
	
	delete[] BufferX;
	delete[] BufferY;
}


/*************************************************************************
 *
 * 函数名称：
 *   IDWT()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *
 * 返回值:
 *   void	            - 无返回值
 *
 * 说明:
 *   该函数对二维点阵进行小波重构。
 *
 ************************************************************************/

void CFreqFilterWnd::IDWT(LPBYTE lpData, int nX, int nY, int nXSize, int nYSize)
{
	// 循环变量
	int i, j, k, n;

	// 中间变量
	float temp1, temp2;
	float* Buffer1;
	float* Buffer2;

	Buffer1 = new float[nXSize];
	Buffer2 = new float[nYSize];

	for (i = 0; i < DD; i++)
	{
		hi[i] = h[DD - 1 - i];
		gi[i] = g[DD - 1 - i];
	}

	// 垂直方向
	for (n = 0; n < nX; n++)
	{
		for (k = 0; k < nY / 2; k++)
		{
			Buffer1[k * 2] = *(lpData + k * nX + n);
			Buffer1[k * 2 + 1] = 0;
		}
		for (i = 0; i <  nY; i++)
		{
			temp1 = 0;
			for (j = -(DD - 1) / 2; j <= (DD - 1) / 2; j++)
			{
				temp1 = temp1 + Buffer1[a(i + j, nY)] * hi[j + (DD - 1) / 2];
				Buffer2[i] = temp1;
			}
		}
		for (k = 0; k < nY / 2; k++)
		{
			Buffer1[k * 2] = *(lpData + (k + nY / 2) * nX + n);
			Buffer1[k * 2 + 1] = 0;
		}
		for (i = 0; i < nY; i++)
		{
			temp1 = 0;
			for (j = -(DD - 1) / 2 - 1; j <= (DD - 1) / 2 - 1; j++)
				temp1 = temp1 + Buffer1[a(i + j, nY)] * gi[j + (DD - 1) / 2 + 1];
			temp2 = temp1 + Buffer2[i];
			Buffer2[i] = temp2;
		}

		// 回存数据
		for (k = 0; k < nY; k++)
			*(lpData + k * nX + n) = Buffer2[k];
	}

	// 水平方向
	for (n = 0; n < nY; n++)
	{
		for (k = 0; k < nX / 2; k++)
		{
			Buffer1[k * 2] = *(lpData + n * nX + k);
			Buffer1[k * 2 + 1] = 0;
		}
		
		for (i = 0; i < nX; i++)
		{
			temp1 = 0;
			for (j = -(DD - 1) / 2; j <= (DD - 1) / 2; j++)
				temp1 = temp1 + Buffer1[a(i + j, nX)] * hi[j + (DD - 1) / 2];
			Buffer2[i] = temp1;
		}
		
		for (k = 0; k < nX / 2; k++)
		{
			Buffer1[k * 2] = *(lpData + n * nX + k + nX / 2);
			Buffer1[k * 2 + 1] = 0;
		}

		for (i = 0; i < nX; i++)
		{
			temp1 = 0;
			for (j = -(DD - 1) / 2 - 1; j <= (DD - 1) / 2 - 1; j++)
				temp1 = temp1 + gi[j + (DD - 1) / 2 + 1] * Buffer1[a(i + j, nX)];
			temp2 = temp1 + Buffer2[i];
			Buffer2[i] = temp2;
		}

		// 回存数据
		for (k = 0; k < nX; k++)
			*(lpData + n * nX + k) = Buffer2[k] * 4;
	}

	delete[] Buffer1;
	delete[] Buffer2;
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBDWT()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *
 * 返回值:
 *   void	            - 无返回值
 *
 * 说明:
 *   该函数对图象进行二维离散小波变换。
 *
 ************************************************************************/

void CFreqFilterWnd::DIBDWT(HDIB hDIB)
{
	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits = m_dataSrc;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);
	
	// 判断是否是24-bpp位图
	if (m_nBPP != 8)
	{
		// 提示用户
		MessageBox(L"请先将其转换为8位色位图，再进行处理！", L"系统提示" , MB_ICONINFORMATION | MB_OK);
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// 返回
		return;
	}
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 进行小波分解
	DWT(lpDIBBits, lWidth, lHeight, lWidth, lHeight);

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBIDWT()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *
 * 返回值:
 *   void	            - 无返回值
 *
 * 说明:
 *   该函数对图象进行二维小波重构。
 *
 ************************************************************************/

void CFreqFilterWnd::DIBIDWT(HDIB hDIB)
{
	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits = m_dataSrc;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);
	
	// 判断是否是24-bpp位图
	if (m_nBPP != 8)
	{
		// 提示用户
		MessageBox(L"请先将其转换为8位色位图，再进行处理！", L"系统提示" , MB_ICONINFORMATION | MB_OK);
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// 返回
		return;
	}
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 进行小波重构	
	IDWT(lpDIBBits, lWidth, lHeight, lWidth, lHeight);

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 恢复光标
	EndWaitCursor();
}

//
//*** 频域滤波 ***
//
// ************************************************************************
//
//  图像频域滤波函数库：
//
//	ButterworthL()		- 巴特沃斯低通滤波器
//	ButterworthH()		- 巴特沃斯高通滤波器
//	MutualFilter()		- 交互式带阻滤波器
//	RetrorseFilter()	- 巴特沃斯低通滤波器的逆滤波
//	WienerFilter()		- 有约束恢复的维纳滤波
//	PSE_Filter()		- 有约束恢复的功率谱均衡滤波
//	MinPower()			- 有约束恢复的最小平方滤波
//
//*************************************************************************

/*************************************************************************
 *
 * 函数名称：
 *   ButterworthL()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 float  fD			- 低通滤波阀值
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行巴特沃斯低通滤波
 *
 ************************************************************************/

void CFreqFilterWnd::ButterworthL(HDIB hDIB, float fD)
{
	// 临时变量
	LONG	i;
	LONG	j;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// 释放内存
	delete[] TD;

	// 当前频率
	float fDN;

	// 对图象进行低通滤波
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// 计算距离
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			// 构造巴特沃斯低通滤波器并滤波
			FD[i * 3 * w + j] *= complex<double>(1 / (1 + 0.414 * (fDN / fD) * (fDN / fD)), 0.0f);
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   ButterworthH()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 float  fD			- 高通滤波阀值
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行巴特沃斯高通滤波
 *
 ************************************************************************/

void CFreqFilterWnd::ButterworthH(HDIB hDIB, float fD)
{
	// 临时变量
	LONG	i;
	LONG	j;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// 释放内存
	delete[] TD;

	// 当前频率
	float fDN;

	// 对图象进行高通滤波
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// 计算距离
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			// 构造巴特沃斯高通滤波器并滤波
			FD[i * 3 * w + j] *= complex<double>(1.0 / (1.0 + 0.414 * (fD / fDN) * (fD / fDN) + 0.5), 0.0f);
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   MutualFilter()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 CRect* pRect		- 频域带阻区域序列
 *	 int	nSum		- 带阻序列数目
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行交互式带阻滤波
 *
 ************************************************************************/

void CFreqFilterWnd::MutualFilter(HDIB hDIB, CRect* pRect, int nSum)
{
	// 临时变量
	LONG	i;
	LONG	j;
	LONG	k;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// 释放内存
	delete[] TD;

	// 对所选区域实施带阻滤波
	for(k = 0; k < nSum; k++)
	{
		// 计算在频域补零后的平面内的坐标
		pRect[k].top += (h - lHeight) / 2;
		pRect[k].bottom += (h - lHeight) / 2;
		pRect[k].left *= 3;
		pRect[k].right *= 3;
		pRect[k].left += (w - lWidth) * 3 / 2;
		pRect[k].right += (w - lWidth) * 3 / 2;

		// 恢复到变换前的象限位置
		if (pRect[k].top < h / 2)
			pRect[k].top += h / 2;
		else
			pRect[k].top -= h / 2;

		if (pRect[k].bottom < h / 2)
			pRect[k].bottom += h / 2;
		else
			pRect[k].bottom -= h / 2;

		if (pRect[k].left < w * 3 /2)
			pRect[k].left += 3 * w / 2;
		else 
			pRect[k].left -= 3 * w / 2;

		if (pRect[k].right < w * 3 /2)
			pRect[k].right += 3 * w / 2;
		else 
			pRect[k].right -= 3 * w / 2;
	
		// 如果所选区域在同一象限
		if (pRect[k].top < pRect[k].bottom && pRect[k].left < pRect[k].right)
		{
			// 对区域进行带阻滤波
			for (i = h - pRect[k].bottom; i < h - pRect[k].top; i++)
			{
				for (j = pRect[k].left * 3; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}

		// 如果所选区域为一、二或三、四象限
		if (pRect[k].top < pRect[k].bottom && pRect[k].left > pRect[k].right)
		{
			// 对区域进行带阻滤波
			for (i = h - pRect[k].bottom; i < h - pRect[k].top; i++)
			{
				// 对二或三象限进行滤波
				for (j = 0; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);

				// 对一或四象限进行滤波
				for (j = pRect[k].left * 3; j < h; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}

		// 如果所选区域为一、四或二、三象限
		if (pRect[k].top > pRect[k].bottom && pRect[k].left < pRect[k].right)
		{
			// 对区域进行带阻滤波
			// 对三或四象限进行滤波
			for (i = 0; i < h - pRect[k].top; i++)
			{
				for (j = pRect[k].left * 3; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
			// 对一或二象限进行滤波
			for (i = h - pRect[k].bottom; i < h; i++)
			{
				for (j = pRect[k].left * 3; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}

		// 如果所选区域为一、二、三、四象限
		if (pRect[k].top > pRect[k].bottom && pRect[k].left > pRect[k].right)
		{
			// 对区域进行带阻滤波
			for (i = 0; i < h - pRect[k].top; i++)
			{
				// 对三象限进行滤波
				for (j = 0; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
				
				// 对四象限进行滤波
				for (j = pRect[k].left * 3; j < h; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
			for (i = h - pRect[k].bottom; i < h; i++)
			{
				// 对二象限进行滤波
				for (j = 0; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);

				// 对一象限进行滤波
				for (j = pRect[k].left * 3; j < h; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   RetrorseFilter()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 float  fD			- 低通滤波阀值
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行巴特沃斯低通滤波的逆滤波处理
 *
 ************************************************************************/

void CFreqFilterWnd::RetrorseFilter(HDIB hDIB, float fD)
{
	// 临时变量
	LONG	i;
	LONG	j;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// 释放内存
	delete[] TD;

	// 当前频率
	float fDN;

	// 对图象进行低通滤波
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// 计算距离
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		
			
			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// 逆滤波恢复
			if(fH > 0.25f)
				FD[i * 3 * w + j] /= complex<double>(fH, 0.0f);
			else
				FD[i * 3 * w + j] *= complex<double>(0.2f, 0.0f);
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   WienerFilter()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 float  fD			- 低通滤波阀值
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行有约束恢复的维纳滤波处理
 *
 ************************************************************************/

void CFreqFilterWnd::WienerFilter(HDIB hDIB, float fD)
{
	// 临时变量
	LONG	i;
	LONG	j;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// 释放内存
	delete[] TD;

	// 当前频率
	float fDN;

	// 预先设定的经验常数
	float K = 0.05f;

	// 对图象进行低通滤波
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// 计算距离
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// 维纳滤波恢复
			FD[i * 3 * w + j] *= complex<double>(fH / (fH * fH + K), 0.0f);
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   PSE_Filter()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 float  fD			- 低通滤波阀值
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行功率谱均衡滤波
 *
 ************************************************************************/

void CFreqFilterWnd::PSE_Filter(HDIB hDIB, float fD)
{
	// 临时变量
	LONG	i;
	LONG	j;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// 释放内存
	delete[] TD;

	// 当前频率
	float fDN;

	// 预先设定的经验常数
	float K=0.05f;

	// 对图象进行低通滤波
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// 计算距离
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		
			
			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// 功率谱均衡滤波
			FD[i * 3 * w + j] *= complex<double>(1 / sqrt(fH * fH + K), 0.0f);
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}


/*************************************************************************
 *
 * 函数名称：
 *   MinPower()
 *
 * 参数:
 *   HDIB	hDIB		- 待处理的DIB
 *	 float  fD			- 低通滤波阀值
 *
 * 返回值:
 *   void			    - 无返回值
 *
 * 说明:
 *   该函数对图象进行有约束最小平方滤波滤波
 *
 ************************************************************************/

void CFreqFilterWnd::MinPower(HDIB hDIB, float fD)
{
	// 临时变量
	LONG	i;
	LONG	j;

	// 进行付立叶变换的宽度和高度（2的整数次方）
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// 指向DIB的指针
	LPBYTE lpDIB;
	
	// 指向DIB象素指针
	LPBYTE lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = m_dataSrc;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// DIB的宽度
	LONG lWidth = m_nImageWidth;
	
	// DIB的高度
	LONG lHeight = m_nImageHeight;

	// 计算图像每行的字节数
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// 计算进行付立叶变换的宽度和高度（2的整数次方）
	while(w < lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h < lHeight)
	{
		h *= 2;
		hp++;
	}

	// 保存频域数据
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// 行
	for(i = 0; i < h; i++)
	{
		// 列
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// 获取时域数值
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// 时域赋值
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// 否则补零
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// 进行频谱分析 时域->频域
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
	{
		delete [] TD;
		delete [] FD;
		return;
	}

	// 释放内存
	delete[] TD;

	// 当前频率
	float fDN;

	// 预先设定的经验常数
	float S = 0.00003f;

	// 对图象进行低通滤波
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// 计算距离
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			// 计算用Q实现的高通滤波器的转移函数P(u,v)
			float P = 2 * PI * fDN;
			
			// 计算H(u,v)
			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// 最小平方滤波恢复
			FD[i * 3 * w + j] *= complex<double>(fH / (fH * fH + S * P), 0.0f);
		}
	}

	// 进行频谱分析 频域->时域
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
	{
		delete [] FD;
		return;
	}

	// 解除锁定 
	::GlobalUnlock((HGLOBAL) hDIB);

	// 释放内存
	delete[] FD;

	// 恢复光标
	EndWaitCursor();
}