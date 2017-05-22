// FreqFilterWnd.cpp : ʵ���ļ�
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

	m_pBnOK = NULL;            //ȷ��
	m_pBnCancel = NULL;        //ȡ��
	m_pBnReset = NULL;         //����
	m_pBnFreq = NULL;          //Ƶ��
	m_pBnMinPower = NULL;      //��Сƽ���˲�
	m_pBnPSEFilter = NULL;     //Ƶ�����˲�
	m_pBnWienerFilter = NULL;  //ά���˲�
	m_pBnButterworthH = NULL;  //������˹��ͨ
	m_pBnButterworthL = NULL;  //������˹��ͨ
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
	//��ť
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



// CFreqFilterWnd ��Ϣ�������




void CFreqFilterWnd::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (m_pFreq == NULL) return;
	if (m_pPaintRect->Width()<=0 || m_pPaintRect->Height()<=0) return;
	m_pFreq->Draw(dc, *m_pPaintRect);
}


int CFreqFilterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pImage = GetDocument()->GetImage();

	//��ͼ��
	CRect rect;
	GetClientRect(&rect);
	m_pPaintRect = new CRect(100, 10, rect.right-10, rect.bottom-10);
	double Space = rect.Height()/10.0;

	//ȷ��
	m_pBnOK = new CMFCButton;
	m_pBnOK->Create(L"ȷ  ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, Space-10, 80, Space+10), this, 2301);

	//ȡ��
	m_pBnCancel = new CMFCButton;
	m_pBnCancel->Create(L"ȡ  ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 2*Space-10, 80, 2*Space+10), this, 2302);

	//����
	m_pBnReset = new CMFCButton;
	m_pBnReset->Create(L"��  ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 3*Space-10, 80, 3*Space+10), this, 2303);

	//Ƶ��
	m_pBnFreq = new CMFCButton;
	m_pBnFreq->Create(L"Ƶ  ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 4*Space-10, 80, 4*Space+10), this, 2304);

	//��Сƽ���˲�
	m_pBnMinPower = new CMFCButton;
	m_pBnMinPower->Create(L"MP", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 5*Space-10, 80, 5*Space+10), this, 2305);

	//Ƶ�����˲�
	m_pBnPSEFilter = new CMFCButton;
	m_pBnPSEFilter->Create(L"PSE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 6*Space-10, 80, 6*Space+10), this, 2306);

	//ά���˲�
	m_pBnWienerFilter = new CMFCButton;
	m_pBnWienerFilter->Create(L"ά���˲�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 7*Space-10, 80, 7*Space+10), this, 2307);

	//������˹��ͨ
	m_pBnButterworthH = new CMFCButton;
	m_pBnButterworthH->Create(L"��ͨ�˲�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 8*Space-10, 80, 8*Space+10), this, 2308);

	//������˹��ͨ
	m_pBnButterworthL = new CMFCButton;
	m_pBnButterworthL->Create(L"��ͨ�˲�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 9*Space-10, 80, 9*Space+10), this, 2309);

	//��ȡλͼ��Ϣ
	GetImageInfo();
	//��ȡλͼ����
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
	//��ȡλͼ��Ϣ
	m_nBPP = m_pImage->GetBPP();             //λ��
	m_nChannel = m_nBPP/8;                   //ͨ��

	//Դͼ����Ϣ
	m_nImageWidth = m_pImage->GetWidth();    //��
	m_nImageHeight = m_pImage->GetHeight();  //��
	m_nRowlen = m_nImageWidth*m_nChannel;    //λ��
	m_nlenData = m_nImageHeight*m_nRowlen;   //����
}

void CFreqFilterWnd::GetImageData()
{
	if (m_pImage == NULL) return;
	m_dataSrc = new BYTE[m_nlenData];
	m_pFreq = new CImage;
	m_pFreq->Create(m_nImageWidth, m_nImageHeight, 24);
	//���ͼ�������׵�ַ
	m_pOrigin = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(m_nImageHeight-1));
	m_pThis = (BYTE *)m_pFreq->GetBits()+(m_pFreq->GetPitch()*(m_nImageHeight-1));

	memcpy(m_dataSrc, m_pOrigin, m_nlenData);
	memcpy(m_pThis, m_dataSrc, m_nlenData);
}

afx_msg void CFreqFilterWnd::OnCmdOK()
{
	//ֱ�ӹر�
	::SendMessage(GetParent()->GetSafeHwnd(), WM_CLOSE, 0, 0);
}

afx_msg void CFreqFilterWnd::OnCmdCancel()
{
	//�ָ����ݺ�ر�
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
	// ����DIBFourier()�������и���Ҷ�任
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
// *** ���� ***
//

// ************************************************************************
//  �ļ�����FFTDlg.cpp
//
//  ͼ�������任�����⣺
//
//	FFT()				- һά���ٸ���Ҷ�任
//  IFFT()				- һά���ٸ���Ҷ��任
//  Fourier()			- ��ά���ٸ���Ҷ�任
//  IFourier()			- ��ά���ٸ���Ҷ��任
//  DCT()				- һά������ɢ���ұ任
//  IDCT()				- һά������ɢ������任
//	FreqDCT()			- ��ά������ɢ���ұ任
//  IFreqDCT()			- ��ά������ɢ������任
//  WALSH()				- һά�ֶ�ʲ��������任
//  IWALSH()			- һά�ֶ�ʲ����������任
//	FreqWALSH()			- ��ά�ֶ�ʲ��������任
//	IFreqWALSH()		- ��ά�ֶ�ʲ����������任
//	DWT()				- ��ά�����С���ֽ�
//	IDWT()				- ��ά�����С���ع�
//	
//  DIBFourier()		- ͼ��ĸ���Ҷ�任
//  DIBDCT()			- ͼ�����ɢ���ұ任
//  DIBWalsh()			- ͼ����ֶ�ʲ��������任
//  DIBDWT()			- ͼ��Ķ�ά��ɢС���任
//
//*************************************************************************


/*************************************************************************
 *
 * �������ƣ�
 *   FFT()
 *
 * ����:
 *   complex<double> * TD	- ָ��ʱ�������ָ��
 *   complex<double> * FD	- ָ��Ƶ�������ָ��
 *   r						��2������������������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ��ٸ���Ҷ�任��
 *
 ************************************************************************/

void CFreqFilterWnd::FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	
	// �м����
	int		p;
	
	// �Ƕ�
	double	angle;
	
	complex<double> *W,*X1,*X2,*X;
	
	// ���㸵��Ҷ�任����
	LONG N = 1 << r;
	
	// ������������洢��
	W  = new complex<double>[N / 2];
	X1 = new complex<double>[N];
	X2 = new complex<double>[N];
	
	// �����Ȩϵ��
	for(i = 0; i < N / 2; i++)
	{
		angle = -i * PI * 2 / N;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// ��ʱ���д��X1
	memcpy(X1, TD, sizeof(complex<double>) * N);
	
	// ���õ����㷨���п��ٸ���Ҷ�任
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
	
	// ��������
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
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}


/*************************************************************************
 *
 * �������ƣ�
 *   IFFT()
 *
 * ����:
 *   complex<double> * FD	- ָ��Ƶ��ֵ��ָ��
 *   complex<double> * TD	- ָ��ʱ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ��ٸ���Ҷ��任��
 *
 ************************************************************************/

void CFreqFilterWnd::IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ѭ������
	int		i;
	
	complex<double> *X;
	
	// ���㸵��Ҷ�任����
	LONG N = 1<<r;
	
	// ������������洢��
	X = new complex<double>[N];
	
	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(complex<double>) * N);
	
	// ����
	for (i = 0; i < N; i++)
	{
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	}
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ���Ĺ���
	for (i = 0; i < N; i++)
	{
		TD[i] = complex<double> (TD[i].real() / N, -TD[i].imag() / N);
	}
	
	// �ͷ��ڴ�
	delete X;
}


/*************************************************************************
 *
 * �������ƣ�
 *   Fourier()
 *
 * ����:
 *   complex* TD		- �����ʱ������
 *	 LONG lWidth		- ͼ����
 *	 LONG lHeight		- ͼ��߶�
 *	 complex* FD		- �����Ƶ������
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú������ж�ά���ٸ���Ҷ�任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::Fourier(complex<double> * TD, LONG lWidth, LONG lHeight, complex<double> * FD)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;

	// ���Ĺ����״
	BeginWaitCursor();
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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
		
	// �����ڴ�
	complex<double> *TempT, *TempF;
	TempT = new complex<double>[h];
	TempF = new complex<double>[h];
	
	// ��y������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempT[j] = TD[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		FFT(TempT, TempF, hp);

		// ����任���
		for (j = 0; j < h; j++)
			TD[j * w * 3 + i] = TempF[j];
	}
	
	// �ͷ��ڴ�
	delete TempT;
	delete TempF;

	// �����ڴ�
	TempT = new complex<double>[w];
	TempF = new complex<double>[w];
	
	// ��x������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempT[j] = TD[i * w * 3 + j * 3 + k];

			// һά���ٸ���Ҷ�任
			FFT(TempT, TempF, wp);

			// ����任���
			for (j = 0; j < w; j++)
				FD[i * w * 3 + j * 3 + k] = TempF[j];
		}
	}

	// �ͷ��ڴ�
	delete TempT;
	delete TempF;

	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   IFourier()
 *
 * ����:
 *   LPBYTE TD			- ���صĿ�������
 *   LONG lWidth		- ����ͼ��Ŀ��
 *	 LONG lHeight		- ����ͼ��ĸ߶�
 *	 complex* FD		- �����Ƶ������
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú������ж�ά���ٸ���Ҷ��任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::IFourier(LPBYTE TD, LONG lWidth, LONG lHeight, complex<double> * FD)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;

	// ���Ĺ����״
	BeginWaitCursor();
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = m_nRowlen;

	// �����ڴ�
	complex<double> *TempT, *TempF;
	TempT = new complex<double>[w];
	TempF = new complex<double>[w];
	
	// ��x������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempF[j] = FD[i * w * 3 + j * 3 + k];

			// һά���ٸ���Ҷ�任
			IFFT(TempF, TempT, wp);

			// ����任���
			for (j = 0; j < w; j++)
				FD[i * w * 3 + j * 3 + k] = TempT[j];
		}
	}

	// �ͷ��ڴ�
	delete TempT;
	delete TempF;
	
	TempT = new complex<double>[h];
	TempF = new complex<double>[h];

	// ��y������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempF[j] = FD[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		IFFT(TempF, TempT, hp);

		// ����任���
		for (j = 0; j < h; j++)
			FD[j * w * 3 + i] = TempT[j];
	}
	
	// �ͷ��ڴ�
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
 * �������ƣ�
 *   DIBFourier()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����и���Ҷ�任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::DIBFourier(HDIB hDIB)
{
	// ָ��Դͼ���ָ��
	BYTE*	lpSrc;

	// �м����
	double	dTemp;
	LONG TI,TJ;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ָ��DIB��ָ��
	LPBYTE	lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE    lpDIBBits = m_dataSrc;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = m_nRowlen;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// �����ڴ�
	complex<double> *FD, *TD, *TempD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];
	TempD =  new complex<double>[w * h * 3];
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷���
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return FALSE;

	// �ͷ��ڴ�
	delete []TD;

	// ��ԭ�������ͼ������λ��
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

			// ����ת�����Ƶ��ͼ��
			TempD[i * w * 3 + j] = FD[TI * w * 3 + TJ];
		}
	}

	// ��
	for(i = (int)(h - lHeight) / 2; i < (int)(h + lHeight) / 2; i++)
	{
		// ��
		for(j = (int)(w * 3 - lLineBytes) / 2; j < (int)(w * 3 + lLineBytes) / 2; j += 3)
		{
			// ����Ƶ��
			dTemp = sqrt(TempD[w * 3 * i + j].real() * TempD[w * 3 * i + j].real() + 
				         TempD[w * 3 * i + j].imag() * TempD[w * 3 * i + j].imag()) / 100;

			// �ж��Ƿ񳬹�255
			if (dTemp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				dTemp = 255;
			}

			// ����Ϊԭͼ��С��Χ
			TI = i - (h - lHeight) / 2;
			TJ = j / 3 - (w - lWidth) / 2;
			
			// ��Ӧ����ָ��
			lpSrc = (BYTE*)lpDIBBits + lLineBytes * TI + TJ * 3;

			// ����Դͼ��
			* (lpSrc) = (BYTE) (dTemp);
			* (lpSrc + 1) = (BYTE) (dTemp);
			* (lpSrc + 2) = (BYTE) (dTemp);
		}
	}

	// �������
	::GlobalUnlock(hDIB);

	// ɾ����ʱ����
	delete []FD;
	delete []TempD;
	
	// �ָ����
	EndWaitCursor();
	
	// ����
	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   DCT()
 *
 * ����:
 *   double * f				- ָ��ʱ��ֵ��ָ��
 *   double * F				- ָ��Ƶ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ��һά������ɢ���ұ任
 *
 ************************************************************************/

void CFreqFilterWnd::DCT(double *f, double *F, int r)
{
	// ѭ������
	int		i;
	
	// �м����
	double	dTemp;
	
	// ������ɢ���ұ任����
	LONG N = 1<<r;
	
	// ���벢�����ڴ�
	complex<double> *XIn;
	complex<double> *XOut;
	XIn = new complex<double>[N * 2];
	XOut = new complex<double>[N * 2];
	
	// ����ֵΪ0
	memset(XIn, 0, sizeof(complex<double>) * N * 2);
	memset(XOut, 0, sizeof(complex<double>) * N * 2);
	
	// ��ʱ���д������X
	for (i = 0; i < N; i++)
		XIn[i] = complex<double>(*(f + i), 0);
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(XIn, XOut, r + 1);
	
	// ����ϵ��
	dTemp = 1 / sqrt(N);
	
	// ��F[0]
	F[0] = XOut[0].real() * dTemp;
	
	dTemp *= sqrt(2);
	
	// ��F[u]
	for (i = 1; i < N; i++)
		*(F + i) = (XOut[i].real() * cos(i * PI / (N * 2)) + XOut[i].imag() * sin(i * PI / (N * 2))) * dTemp;
	
	// �ͷ��ڴ�
	delete[] XIn;
	delete[] XOut;
}


/*************************************************************************
 *
 * �������ƣ�
 *   IDCT()
 *
 * ����:
 *   double * F				- ָ��Ƶ��ֵ��ָ��
 *   double * f				- ָ��ʱ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú���ʵ��һά������ɢ������任
 *
 ************************************************************************/

void CFreqFilterWnd::IDCT(double *F, double *f, int r)
{
	// ѭ������
	int		i;
	
	// �м����
	double	dTemp, d0;
		
	// ������ɢ���ұ任����
	LONG N = 1<<r;
	
	// �����ڴ�
	complex<double> *XIn;
	complex<double> *XOut;
	XIn = new complex<double>[N * 2];
	XOut = new complex<double>[N * 2];

	// ����ֵΪ0
	memset(XIn, 0, sizeof(complex<double>) * N * 2);
	memset(XOut, 0, sizeof(complex<double>) * N * 2);
	
	// ��Ƶ��任���д������X
	for (i = 0; i < N; i++)
		XIn[i] = complex<double>(F[i] * cos(i * PI / (N * 2)), F[i] * sin(i * PI / (N * 2)));
	
	// ���ÿ��ٸ���Ҷ���任
	IFFT(XIn, XOut, r + 1);
	
	// ����ϵ��
	dTemp = sqrt(2.0 / N);
	d0 = (sqrt(1.0 / N) - dTemp) * F[0];
	
	// ����f(x)
	for (i = 0; i < N; i++)
		f[i] = d0 + XOut[i].real()* dTemp * 2 * N;
	
	// �ͷ��ڴ�
	delete[] XIn;
	delete[] XOut;
}


/*************************************************************************
 *
 * �������ƣ�
 *   FreqDCT()
 *
 * ����:
 *   double* f			- �����ʱ������
 *   double* F			- �����Ƶ������
 *	 LONG lWidth		- ͼ����
 *	 LONG lHeight		- ͼ��߶�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú������ж�ά������ɢ���ұ任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::FreqDCT(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;

	// ���Ĺ����״
	BeginWaitCursor();
	
	// ������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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
		
	// �����ڴ�
	double* TempIn = new double[h];
	double* TempOut = new double[h];
	
	// ��y���������ɢ���ұ任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = f[j * w * 3 + i];
		
		// һά������ɢ���ұ任
		DCT(TempIn, TempOut, hp);

		// ����任���
		for (j = 0; j < h; j++)
			f[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;

	// �����ڴ�
	TempIn = new double[w];
	TempOut = new double[w];
	
	// ��x������п�����ɢ���ұ任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = f[i * w * 3 + j * 3 + k];

			// һά������ɢ���ұ任
			DCT(TempIn, TempOut, wp);

			// ����任���
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;

	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   IFreqDCT()
 *
 * ����:
 *   double* f			- �����ʱ������
 *   double* F			- �����Ƶ������
 *	 LONG lWidth		- ͼ����
 *	 LONG lHeight		- ͼ��߶�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú������ж�ά������ɢ������任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::IFreqDCT(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;

	// ���Ĺ����״
	BeginWaitCursor();
	
	// ������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = m_nRowlen;

	// �����ڴ�
	double* TempIn = new double[w];
	double* TempOut = new double[w];
	
	// ��x������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = F[i * w * 3 + j * 3 + k];

			// һά���ٸ���Ҷ�任
			IDCT(TempIn, TempOut, wp);

			// ����任���
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	TempIn = new double[h];
	TempOut = new double[h];

	// ��y������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = F[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		IDCT(TempIn, TempOut, hp);

		// ����任���
		for (j = 0; j < h; j++)
			F[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
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
 * �������ƣ�
 *   DIBDCT()
 *
 * ����:
 *   HDIB  hDIB		    - �������DIB
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ�������ɢ���ұ任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::DIBDCT(HDIB hDIB)
{
	// ������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	i;
	LONG	j;
	
	// ָ��DIB��ָ��
	LPBYTE	lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE  lpDIBBits = m_dataSrc;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;
	
	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = m_nRowlen;
	
	// ������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// �����ڴ�
	double *f = new double[w * h * 3];
	double *F = new double[w * h * 3];

	// ��ʱ��ֵ������
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

	// ����Ƶ�׷���
	if (FreqDCT(f, F,lWidth, lHeight) == FALSE)
		return FALSE;

	// ������������
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lLineBytes; j++)
		{
			// �ж��Ƿ񳬹�255
			if (fabs(F[i * w * 3 + j]) > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = 255;
			}
			else
			{
				// ���û�г�������ʵ�ʼ�������ֵ
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = fabs(F[i * w * 3 + j]);
			}
		}
	}

	// �������
	::GlobalUnlock(hDIB);
	
	// �ͷ��ڴ�
	delete []f;
	delete[] F;

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   WALSH()
 *
 * ����:
 *   double* f			- �����ʱ������
 *   double* F			- �����Ƶ������
 *   int r				- 2������		
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������һά�����ֶ�ʲ����������任��
 *
 ************************************************************************/

void CFreqFilterWnd::WALSH(double *f, double *F, int r)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	
	// �м����
	int		p;	
	double* X;
	
	// ��������ֶ�ʲ�任����
	LONG N = 1 << r;
	
	// �����������������
	double* X1 = new double[N];
	double* X2 = new double[N];
	
	// ��ʱ���д������X1
	memcpy(X1, f, sizeof(double) * N);
	
	// ��������
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
		
		// ����X1��X2  
		X = X1;
		X1 = X2;
		X2 = X;
	}
	
	// ����ϵ��
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
	
	// �ͷ��ڴ�
	delete X1;
	delete X2;
}


/*************************************************************************
 *
 * �������ƣ�
 *   IWALSH()
 *
 * ����:
 *   double* f			- �����ʱ������
 *   double* F			- �����Ƶ������
 *   int r				- 2������		
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������һά�����ֶ�ʲ������������任��
 *
 ************************************************************************/

void CFreqFilterWnd::IWALSH(double *F, double *f, int r)
{
	// ѭ������
	int		i;
	
	// ����任����
	LONG N = 1 << r;
	
	// ���ÿ����ֶ�ʲ��������任���з��任
	WALSH(F, f, r);
	
	// ����ϵ��
	for (i = 0; i < N; i++)
		f[i] *= N;
}


/*************************************************************************
 *
 * �������ƣ�
 *   FreqWALSH()
 *
 * ����:
 *   double* f			- �����ʱ������
 *   double* F			- �����Ƶ������
 *	 LONG lWidth		- ͼ����
 *	 LONG lHeight		- ͼ��߶�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú������ж�ά�����ֶ�ʲ����������任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::FreqWALSH(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;

	// ���Ĺ����״
	BeginWaitCursor();
	
	// ������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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
		
	// �����ڴ�
	double* TempIn = new double[h];
	double* TempOut = new double[h];
	
	// ��y���������ɢ���ұ任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = f[j * w * 3 + i];
		
		// һά������ɢ���ұ任
		WALSH(TempIn, TempOut, hp);

		// ����任���
		for (j = 0; j < h; j++)
			f[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;

	// �����ڴ�
	TempIn = new double[w];
	TempOut = new double[w];
	
	// ��x������п�����ɢ���ұ任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = f[i * w * 3 + j * 3 + k];

			// һά������ɢ���ұ任
			WALSH(TempIn, TempOut, wp);

			// ����任���
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;

	return TRUE;
}



/*************************************************************************
 *
 * �������ƣ�
 *   IFreqWALSH()
 *
 * ����:
 *   double* f			- �����ʱ������
 *   double* F			- �����Ƶ������
 *	 LONG lWidth		- ͼ����
 *	 LONG lHeight		- ͼ��߶�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú������ж�ά�����ֶ�ʲ������������任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::IFreqWALSH(double *f, double *F, LONG lWidth, LONG lHeight)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;

	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����ֵ
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = m_nRowlen;

	// �����ڴ�
	double* TempIn = new double[w];
	double* TempOut = new double[w];
	
	// ��x������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = F[i * w * 3 + j * 3 + k];

			// һά���ٸ���Ҷ�任
			IWALSH(TempIn, TempOut, wp);

			// ����任���
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}

	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	TempIn = new double[h];
	TempOut = new double[h];

	// ��y������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = F[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		IWALSH(TempIn, TempOut, hp);

		// ����任���
		for (j = 0; j < h; j++)
			F[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
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
 * �������ƣ�
 *   DIBWalsh()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����ͼ����ж�ά�����ֶ�ʲ����������任��
 *
 ************************************************************************/

BOOL CFreqFilterWnd::DIBWalsh(HDIB hDIB)
{
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ָ��DIB��ָ��
	LPBYTE	lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE  lpDIBBits = m_dataSrc;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = m_nRowlen;
	
	// �����ֶ�ʲ����������任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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
	
	// �����ڴ�
	double *f = new double[w * h * 3];
	double *F = new double[w * h * 3];
	
	// ��ʱ��ֵ������
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

	// ����Ƶ�׷���
	if (FreqWALSH(f, F,lWidth, lHeight) == FALSE)
		return FALSE;
	
	// ������������
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lLineBytes; j++)
		{
			// �ж��Ƿ񳬹�255
			if (fabs(F[i * w * 3 + j] * 1000) > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = 255;
			}
			else
			{
				// ���û�г�������ʵ�ʼ�������ֵ
				*(BYTE*)(lpDIBBits + lLineBytes * (lHeight - 1 - i) + j) = fabs(F[i * w * 3 + j] * 1000);
			}
		}
	}

	// �������
	::GlobalUnlock(hDIB);

	//�ͷ��ڴ�
	delete[] f;
	delete[] F;

	// ����
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
//																	     //
//							С���任									 //
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
 * �������ƣ�
 *   DWT()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *
 * ����ֵ:
 *   void	            - �޷���ֵ
 *
 * ˵��:
 *   �ú����Զ�ά���������ɢС���任��
 *
 ************************************************************************/

void CFreqFilterWnd::DWT(LPBYTE lpData, int nX, int nY, int nXSize, int nYSize)
{
	// ѭ������
	int i, j, k, n;

	// �м����
	float temp1, temp2;
	float* BufferX;
	float* BufferY;

	BufferX = new float[nXSize];
	BufferY = new float[nYSize];

	// ˮƽ����
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

		// �ش�����
		for (k = 0; k < nX; k++)
			*(lpData + n * nX + k) = BufferX[k];
	}

	// ��ֱ����
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

		// �ش�����
		for (k = 0; k < nY; k++)
			*(lpData + k * nX + n) = BufferY[k];
	}
	
	delete[] BufferX;
	delete[] BufferY;
}


/*************************************************************************
 *
 * �������ƣ�
 *   IDWT()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *
 * ����ֵ:
 *   void	            - �޷���ֵ
 *
 * ˵��:
 *   �ú����Զ�ά�������С���ع���
 *
 ************************************************************************/

void CFreqFilterWnd::IDWT(LPBYTE lpData, int nX, int nY, int nXSize, int nYSize)
{
	// ѭ������
	int i, j, k, n;

	// �м����
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

	// ��ֱ����
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

		// �ش�����
		for (k = 0; k < nY; k++)
			*(lpData + k * nX + n) = Buffer2[k];
	}

	// ˮƽ����
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

		// �ش�����
		for (k = 0; k < nX; k++)
			*(lpData + n * nX + k) = Buffer2[k] * 4;
	}

	delete[] Buffer1;
	delete[] Buffer2;
}


/*************************************************************************
 *
 * �������ƣ�
 *   DIBDWT()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *
 * ����ֵ:
 *   void	            - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����ж�ά��ɢС���任��
 *
 ************************************************************************/

void CFreqFilterWnd::DIBDWT(HDIB hDIB)
{
	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits = m_dataSrc;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);
	
	// �ж��Ƿ���24-bppλͼ
	if (m_nBPP != 8)
	{
		// ��ʾ�û�
		MessageBox(L"���Ƚ���ת��Ϊ8λɫλͼ���ٽ��д���", L"ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����С���ֽ�
	DWT(lpDIBBits, lWidth, lHeight, lWidth, lHeight);

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   DIBIDWT()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *
 * ����ֵ:
 *   void	            - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����ж�άС���ع���
 *
 ************************************************************************/

void CFreqFilterWnd::DIBIDWT(HDIB hDIB)
{
	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits = m_dataSrc;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);
	
	// �ж��Ƿ���24-bppλͼ
	if (m_nBPP != 8)
	{
		// ��ʾ�û�
		MessageBox(L"���Ƚ���ת��Ϊ8λɫλͼ���ٽ��д���", L"ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����С���ع�	
	IDWT(lpDIBBits, lWidth, lHeight, lWidth, lHeight);

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ָ����
	EndWaitCursor();
}

//
//*** Ƶ���˲� ***
//
// ************************************************************************
//
//  ͼ��Ƶ���˲������⣺
//
//	ButterworthL()		- ������˹��ͨ�˲���
//	ButterworthH()		- ������˹��ͨ�˲���
//	MutualFilter()		- ����ʽ�����˲���
//	RetrorseFilter()	- ������˹��ͨ�˲��������˲�
//	WienerFilter()		- ��Լ���ָ���ά���˲�
//	PSE_Filter()		- ��Լ���ָ��Ĺ����׾����˲�
//	MinPower()			- ��Լ���ָ�����Сƽ���˲�
//
//*************************************************************************

/*************************************************************************
 *
 * �������ƣ�
 *   ButterworthL()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 float  fD			- ��ͨ�˲���ֵ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����а�����˹��ͨ�˲�
 *
 ************************************************************************/

void CFreqFilterWnd::ButterworthL(HDIB hDIB, float fD)
{
	// ��ʱ����
	LONG	i;
	LONG	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// �ͷ��ڴ�
	delete[] TD;

	// ��ǰƵ��
	float fDN;

	// ��ͼ����е�ͨ�˲�
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// �������
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			// ���������˹��ͨ�˲������˲�
			FD[i * 3 * w + j] *= complex<double>(1 / (1 + 0.414 * (fDN / fD) * (fDN / fD)), 0.0f);
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   ButterworthH()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 float  fD			- ��ͨ�˲���ֵ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����а�����˹��ͨ�˲�
 *
 ************************************************************************/

void CFreqFilterWnd::ButterworthH(HDIB hDIB, float fD)
{
	// ��ʱ����
	LONG	i;
	LONG	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// �ͷ��ڴ�
	delete[] TD;

	// ��ǰƵ��
	float fDN;

	// ��ͼ����и�ͨ�˲�
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// �������
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			// ���������˹��ͨ�˲������˲�
			FD[i * 3 * w + j] *= complex<double>(1.0 / (1.0 + 0.414 * (fD / fDN) * (fD / fDN) + 0.5), 0.0f);
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   MutualFilter()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 CRect* pRect		- Ƶ�������������
 *	 int	nSum		- ����������Ŀ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����н���ʽ�����˲�
 *
 ************************************************************************/

void CFreqFilterWnd::MutualFilter(HDIB hDIB, CRect* pRect, int nSum)
{
	// ��ʱ����
	LONG	i;
	LONG	j;
	LONG	k;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// �ͷ��ڴ�
	delete[] TD;

	// ����ѡ����ʵʩ�����˲�
	for(k = 0; k < nSum; k++)
	{
		// ������Ƶ������ƽ���ڵ�����
		pRect[k].top += (h - lHeight) / 2;
		pRect[k].bottom += (h - lHeight) / 2;
		pRect[k].left *= 3;
		pRect[k].right *= 3;
		pRect[k].left += (w - lWidth) * 3 / 2;
		pRect[k].right += (w - lWidth) * 3 / 2;

		// �ָ����任ǰ������λ��
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
	
		// �����ѡ������ͬһ����
		if (pRect[k].top < pRect[k].bottom && pRect[k].left < pRect[k].right)
		{
			// ��������д����˲�
			for (i = h - pRect[k].bottom; i < h - pRect[k].top; i++)
			{
				for (j = pRect[k].left * 3; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}

		// �����ѡ����Ϊһ����������������
		if (pRect[k].top < pRect[k].bottom && pRect[k].left > pRect[k].right)
		{
			// ��������д����˲�
			for (i = h - pRect[k].bottom; i < h - pRect[k].top; i++)
			{
				// �Զ��������޽����˲�
				for (j = 0; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);

				// ��һ�������޽����˲�
				for (j = pRect[k].left * 3; j < h; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}

		// �����ѡ����Ϊһ���Ļ����������
		if (pRect[k].top > pRect[k].bottom && pRect[k].left < pRect[k].right)
		{
			// ��������д����˲�
			// �����������޽����˲�
			for (i = 0; i < h - pRect[k].top; i++)
			{
				for (j = pRect[k].left * 3; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
			// ��һ������޽����˲�
			for (i = h - pRect[k].bottom; i < h; i++)
			{
				for (j = pRect[k].left * 3; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}

		// �����ѡ����Ϊһ����������������
		if (pRect[k].top > pRect[k].bottom && pRect[k].left > pRect[k].right)
		{
			// ��������д����˲�
			for (i = 0; i < h - pRect[k].top; i++)
			{
				// �������޽����˲�
				for (j = 0; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
				
				// �������޽����˲�
				for (j = pRect[k].left * 3; j < h; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
			for (i = h - pRect[k].bottom; i < h; i++)
			{
				// �Զ����޽����˲�
				for (j = 0; j < pRect[k].right * 3; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);

				// ��һ���޽����˲�
				for (j = pRect[k].left * 3; j < h; j++)
					FD[i * w * 3 + j] = complex<double>(0, 0);
			}
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   RetrorseFilter()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 float  fD			- ��ͨ�˲���ֵ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����а�����˹��ͨ�˲������˲�����
 *
 ************************************************************************/

void CFreqFilterWnd::RetrorseFilter(HDIB hDIB, float fD)
{
	// ��ʱ����
	LONG	i;
	LONG	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// �ͷ��ڴ�
	delete[] TD;

	// ��ǰƵ��
	float fDN;

	// ��ͼ����е�ͨ�˲�
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// �������
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		
			
			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// ���˲��ָ�
			if(fH > 0.25f)
				FD[i * 3 * w + j] /= complex<double>(fH, 0.0f);
			else
				FD[i * 3 * w + j] *= complex<double>(0.2f, 0.0f);
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   WienerFilter()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 float  fD			- ��ͨ�˲���ֵ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ�������Լ���ָ���ά���˲�����
 *
 ************************************************************************/

void CFreqFilterWnd::WienerFilter(HDIB hDIB, float fD)
{
	// ��ʱ����
	LONG	i;
	LONG	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// �ͷ��ڴ�
	delete[] TD;

	// ��ǰƵ��
	float fDN;

	// Ԥ���趨�ľ��鳣��
	float K = 0.05f;

	// ��ͼ����е�ͨ�˲�
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// �������
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// ά���˲��ָ�
			FD[i * 3 * w + j] *= complex<double>(fH / (fH * fH + K), 0.0f);
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   PSE_Filter()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 float  fD			- ��ͨ�˲���ֵ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ����й����׾����˲�
 *
 ************************************************************************/

void CFreqFilterWnd::PSE_Filter(HDIB hDIB, float fD)
{
	// ��ʱ����
	LONG	i;
	LONG	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
		return;

	// �ͷ��ڴ�
	delete[] TD;

	// ��ǰƵ��
	float fDN;

	// Ԥ���趨�ľ��鳣��
	float K=0.05f;

	// ��ͼ����е�ͨ�˲�
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// �������
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		
			
			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// �����׾����˲�
			FD[i * 3 * w + j] *= complex<double>(1 / sqrt(fH * fH + K), 0.0f);
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
		return;

	// �������
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}


/*************************************************************************
 *
 * �������ƣ�
 *   MinPower()
 *
 * ����:
 *   HDIB	hDIB		- �������DIB
 *	 float  fD			- ��ͨ�˲���ֵ
 *
 * ����ֵ:
 *   void			    - �޷���ֵ
 *
 * ˵��:
 *   �ú�����ͼ�������Լ����Сƽ���˲��˲�
 *
 ************************************************************************/

void CFreqFilterWnd::MinPower(HDIB hDIB, float fD)
{
	// ��ʱ����
	LONG	i;
	LONG	j;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;

	// ָ��DIB��ָ��
	LPBYTE lpDIB;
	
	// ָ��DIB����ָ��
	LPBYTE lpDIBBits;
	
	// ����DIB
	lpDIB = (LPBYTE) ::GlobalLock((HGLOBAL) hDIB);

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = m_dataSrc;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// DIB�Ŀ��
	LONG lWidth = m_nImageWidth;
	
	// DIB�ĸ߶�
	LONG lHeight = m_nImageHeight;

	// ����ͼ��ÿ�е��ֽ���
	LONG lLineBytes = WIDTHBYTES(lWidth * 24);

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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

	// ����Ƶ������
	complex<double> *FD, *TD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];

	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < lHeight && j < lLineBytes)
			{
				// ��ȡʱ����ֵ
				BYTE Value = *((BYTE *)lpDIBBits + lLineBytes * i + j);
			
				// ʱ��ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}

	// ����Ƶ�׷��� ʱ��->Ƶ��
	if (Fourier(TD, lWidth, lHeight, FD) == FALSE)
	{
		delete [] TD;
		delete [] FD;
		return;
	}

	// �ͷ��ڴ�
	delete[] TD;

	// ��ǰƵ��
	float fDN;

	// Ԥ���趨�ľ��鳣��
	float S = 0.00003f;

	// ��ͼ����е�ͨ�˲�
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w * 3; j++)
		{
			// �������
			int k = (int)(j / 3);
			fDN = (float)sqrt( i * i + k * k);		

			// ������Qʵ�ֵĸ�ͨ�˲�����ת�ƺ���P(u,v)
			float P = 2 * PI * fDN;
			
			// ����H(u,v)
			float fH = 1 / (1 + 0.414 * (fDN / fD) * (fDN / fD));

			// ��Сƽ���˲��ָ�
			FD[i * 3 * w + j] *= complex<double>(fH / (fH * fH + S * P), 0.0f);
		}
	}

	// ����Ƶ�׷��� Ƶ��->ʱ��
	if (IFourier(lpDIBBits, lWidth, lHeight, FD) == FALSE)
	{
		delete [] FD;
		return;
	}

	// ������� 
	::GlobalUnlock((HGLOBAL) hDIB);

	// �ͷ��ڴ�
	delete[] FD;

	// �ָ����
	EndWaitCursor();
}