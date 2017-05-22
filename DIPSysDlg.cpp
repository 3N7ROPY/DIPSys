
// DIPSysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DIPSys.h"
#include "DIPSysDlg.h"
#include "ColorGradDlg.h"
#include "CurveDlg.h"
#include "HistogramDLg.h"
#include "SpaceFilterDlg.h"
#include "FreqFilterDlg.h"
#include "ZoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CDIPSysDlg �Ի���



CDIPSysDlg::CDIPSysDlg(CWnd* pParent /*=NULL*/)	: CDialogEx(CDIPSysDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pColorGradDlg = NULL;
	m_pCurveDlg = NULL;
	m_pHistogramDlg = NULL;
	m_pSpaceFilterDlg = NULL;
	m_pFreqFilterDlg = NULL;

	m_bScroll = FALSE;
	m_MyHotkey = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_HOTKEYS));
}

CDIPSysDlg::~CDIPSysDlg()
{
	if (m_pImage != NULL)             delete m_pImage;
	if (m_pPaintRect != NULL)         delete m_pPaintRect;
	if (m_pptOrigin != NULL)          delete m_pptOrigin;

	if (m_pColorGradDlg != NULL)      delete m_pColorGradDlg;
	if (m_pCurveDlg != NULL)          delete m_pCurveDlg;
	if (m_pHistogramDlg != NULL)      delete m_pHistogramDlg;
	if (m_pSpaceFilterDlg != NULL)    delete m_pSpaceFilterDlg;
	if (m_pFreqFilterDlg != NULL)     delete m_pFreqFilterDlg;
}

void CDIPSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDIPSysDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(1001, &CDIPSysDlg::OnCmdOpen)
	ON_COMMAND(1002, &CDIPSysDlg::OnCmdSave)
	ON_COMMAND(1003, &CDIPSysDlg::OnCmdColorGrad)
	ON_COMMAND(1004, &CDIPSysDlg::OnCmdCurve)
	ON_COMMAND(1005, &CDIPSysDlg::OnCmdHistogramDlg)
	ON_COMMAND(1006, &CDIPSysDlg::OnCmdSpaceFilter)
	ON_COMMAND(1007, &CDIPSysDlg::OnCmdFreqFilter)
	ON_COMMAND(ID_APP_ABOUT, &CDIPSysDlg::OnAppAbout)
	ON_COMMAND(ID_AUTHOR_BLOG, &CDIPSysDlg::OnAuthorBlog)
	ON_COMMAND(ID_AUTHOR_MICRO_BLOG, &CDIPSysDlg::OnAuthorMicroBlog)
	ON_COMMAND(ID_CALL_ZOOM_DLG, &CDIPSysDlg::OnCallZoomDlg)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_HOTKEY_APP_EXIT, &CDIPSysDlg::OnHotkeyAppExit)
	ON_COMMAND(ID_HOTKEY_OPEN_IMAGE, &CDIPSysDlg::OnHotkeyOpenImage)
	ON_COMMAND(ID_HOTKEY_SAVE_IMAGE, &CDIPSysDlg::OnHotkeySaveImage)
	ON_COMMAND(ID_HOTKEY_COLORGRAD, &CDIPSysDlg::OnHotkeyColorgrad)
	ON_COMMAND(ID_HOTKEY_CURVE, &CDIPSysDlg::OnHotkeyCurve)
	ON_COMMAND(ID_HOTKEY_HISTOGRAM, &CDIPSysDlg::OnHotkeyHistogram)
	ON_COMMAND(ID_HOTKEY_SPACEFILTER, &CDIPSysDlg::OnHotkeySpacefilter)
	ON_COMMAND(ID_HOTKEY_FREQFILTER, &CDIPSysDlg::OnHotkeyFreqfilter)
	ON_COMMAND(ID_HOTKEY_ZOOM, &CDIPSysDlg::OnHotkeyZoom)
	ON_COMMAND(ID_HOTKEY_ABOUT, &CDIPSysDlg::OnHotkeyAbout)
	ON_COMMAND(ID_HOTKEY_BLOG, &CDIPSysDlg::OnHotkeyBlog)
	ON_COMMAND(ID_HOTKEY_MICRO_BLOG, &CDIPSysDlg::OnHotkeyMicroBlog)
	ON_COMMAND(ID_RGB_TO_GRAY, &CDIPSysDlg::OnRgbToGray)
	ON_COMMAND(ID_HOTKEY_RGB_TO_GRAY, &CDIPSysDlg::OnHotkeyRgbToGray)
	ON_COMMAND(ID_EDIT_UNDO, &CDIPSysDlg::OnEditUndo)
	ON_COMMAND(ID_HOTKEY_UNDO, &CDIPSysDlg::OnHotkeyUndo)
	ON_COMMAND(ID_FIT_WINDOW, &CDIPSysDlg::OnFitWindow)
END_MESSAGE_MAP()


// CDIPSysDlg ��Ϣ�������

BOOL CDIPSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 1024, 768, SWP_SHOWWINDOW);
	CenterWindow();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDIPSysDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (m_pImage == NULL) return;
	if (m_pPaintRect->Width()<=0 || m_pPaintRect->Height()<=0) return;
	if (m_pImage->GetWidth()-m_pPaintRect->Width() <= 0 || m_pImage->GetHeight()-m_pPaintRect->Height() <= 0)
		m_pImage->Draw(dc, CRect(m_pPaintRect->left, m_pPaintRect->top, m_pPaintRect->left + m_pImage->GetWidth(), m_pPaintRect->top + m_pImage->GetHeight()));
	else 
		m_pImage->Draw(dc, CRect(m_pPaintRect->left, m_pPaintRect->top, m_pPaintRect->left + m_pImage->GetWidth(), m_pPaintRect->top + m_pImage->GetHeight()),
		CRect(m_pptOrigin->x, m_pptOrigin->y, m_pptOrigin->x + m_pImage->GetWidth(), m_pptOrigin->y + m_pImage->GetHeight()));
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDIPSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDIPSysDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);

	m_pPaintRect->right = rect.right;
	m_pPaintRect->bottom = rect.bottom;

	double Space = rect.Height()/8.0;
	InvalidateRect(m_pPaintRect);
}

int CDIPSysDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//��ͼ��
	CRect rect;
	GetClientRect(&rect);

	m_pptOrigin = new CPoint(0, 0);
	m_pPaintRect = new CRect(0, 0, rect.right, rect.bottom);

	return 0;
}

CImage* CDIPSysDlg::GetImage()
{
	return m_pImage;
}

void CDIPSysDlg::Refresh()
{
	InvalidateRect(m_pPaintRect);
}

/*** ��Ϣ��Ӧ ***/

void CDIPSysDlg::OnCmdOpen()
{
	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	CFileDialog hFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, TEXT("�����ļ�(*.*)|*.* | ͼ���ļ�(*.jpg;*.gif;*.png;*.tif;*.bmp)|*.jpg;*.gif;*.png;*.tif;*.bmp||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 2;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("��ͼ���ļ�...\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;

	if(hFileDlg.DoModal() != IDOK) return;
	CString path = hFileDlg.GetPathName();
	m_pImage = new CImage;
	m_pImage->Load(path);
	if(m_pImage->IsNull()) return;
	PushImage();

	InvalidateRect(m_pPaintRect);
	UpdateWindow();
}

void CDIPSysDlg::OnCmdSave()
{
	if (m_pImage == NULL) return;

	SYSTEMTIME sys;
	GetLocalTime(&sys);
	CString CurTime;
	CurTime.Format(_T("%04d%02d%02d%02d%02d%02d"), sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);

	CString strFileName = _T("");
	CString strExtension = _T("");

	CFileDialog dlg(FALSE, NULL, CurTime, NULL, TEXT("BMP λͼ�ļ�(*.bmp)|*.bmp|JPEG ͼ���ļ�(*.jpg)|*.jpg|PNG ͼ���ļ�(*.png)|*.png|TIF �ļ���ʽ(*.tif)|*.tif|GIF ͼ���ļ�(*.gif)|*.gif||"), NULL);
	dlg.m_ofn.hwndOwner = m_hWnd;
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	dlg.m_ofn.lpstrTitle = TEXT("����ͼ���ļ�...\0");
	dlg.m_ofn.nMaxFile = MAX_PATH;

	if ( dlg.DoModal() != IDOK) return;

	strFileName += dlg.GetPathName();

	switch (dlg.m_ofn.nFilterIndex)
	{
	case 1 : strExtension = _T("bmp"); break;
	case 2 : strExtension = _T("jpg"); break;
	case 3 : strExtension = _T("png"); break;
	case 4 : strExtension = _T("tif"); break;
	case 5 : strExtension = _T("gif"); break;
	default:                           break;
	}
	if (strFileName.Right(4) != _T(".bmp") && strFileName.Right(4) != _T(".jpg") && strFileName.Right(4) != _T(".png") && strFileName.Right(4) != _T(".tif") && strFileName.Right(4) != _T(".gif"))
	{
		strFileName = strFileName + '.' + strExtension;
	}
	if (m_pImage->Save(strFileName) != S_OK) MessageBox(_T("����ͼƬʧ�ܣ�"));
}

void CDIPSysDlg::OnCmdColorGrad()
{
	if (m_pColorGradDlg != NULL) delete m_pColorGradDlg;
	m_pColorGradDlg = new CColorGradDlg;
	m_pColorGradDlg->Create(IDD_COLORGRAD_DLG);
	m_pColorGradDlg->ShowWindow(SW_RESTORE);
}

void CDIPSysDlg::OnCmdCurve()
{
	if (m_pCurveDlg != NULL) delete m_pCurveDlg;
	m_pCurveDlg = new CCurveDlg;
	m_pCurveDlg->Create(IDD_CURVE_DLG);
	m_pCurveDlg->ShowWindow(SW_RESTORE);
}

void CDIPSysDlg::OnCmdHistogramDlg()
{
	if (m_pHistogramDlg != NULL) delete m_pHistogramDlg;
	m_pHistogramDlg = new CHistogramDLg;
	m_pHistogramDlg->Create(IDD_HISTOGRAM_DLG);
	m_pHistogramDlg->ShowWindow(SW_RESTORE);
}

void CDIPSysDlg::OnCmdSpaceFilter()
{
	if (m_pSpaceFilterDlg != NULL) delete m_pSpaceFilterDlg;
	m_pSpaceFilterDlg = new CSpaceFilterDlg;
	m_pSpaceFilterDlg->Create(IDD_SPACEFILTER_DLG);
	m_pSpaceFilterDlg->ShowWindow(SW_RESTORE);
}

void CDIPSysDlg::OnCmdFreqFilter()
{
	if (m_pFreqFilterDlg != NULL) delete m_pFreqFilterDlg;
	m_pFreqFilterDlg = new CFreqFilterDlg;
	m_pFreqFilterDlg->Create(IDD_FREQFILTER_DLG);
	m_pFreqFilterDlg->ShowWindow(SW_RESTORE);
}

// ����
void CDIPSysDlg::OnAppAbout()
{
	CDialogEx AboutDlg(IDD_ABOUT_DLG);
	AboutDlg.DoModal();
}

// ����
void CDIPSysDlg::OnAuthorBlog()
{
	ShellExecute(NULL, L"open", L"http://www.user.qzone.qq.com/962914132", NULL, NULL, SW_SHOWNORMAL);
}

// ΢��
void CDIPSysDlg::OnAuthorMicroBlog()
{
	ShellExecute(NULL, L"open", L"http://www.weibo.com/yuanyuanxiang", NULL, NULL, SW_SHOWNORMAL);
}

// �����任�Ի���
void CDIPSysDlg::OnCallZoomDlg()
{
	if (m_pImage == NULL) return;
	CZoomDlg  ZoomDlg;
	ZoomDlg.m_nWidthNew = ZoomDlg.m_dWidthEdit = m_pImage->GetWidth();
	ZoomDlg.m_nHeightNew = ZoomDlg.m_dHeightEdit = m_pImage->GetHeight();
	ZoomDlg.DoModal();
}

// ˮƽ������
void CDIPSysDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int errX = m_pImage->GetWidth()-m_pPaintRect->Width();
	if (errX <= 0) return;

	m_bScroll = TRUE;
	int pos,min,max,thumbwidth;

	SCROLLINFO vinfo;
	GetScrollInfo(SB_HORZ,&vinfo);

	pos = vinfo.nPos;
	min = vinfo.nMin;
	max = vinfo.nMax;
	thumbwidth = vinfo.nPage;

	switch (nSBCode)
	{
	case SB_THUMBTRACK: //�϶�������
		ScrollWindow(-((int)nPos-pos),0);
		SetScrollPos(SB_HORZ,nPos);
		break;
	case SB_LINELEFT : //�������ͷ
		if (pos != 0)
		{
			ScrollWindow(1,0);
			SetScrollPos(SB_HORZ,pos-1);
		}
		break;
	case SB_LINERIGHT: //�����Ҽ�ͷ
		if (pos+thumbwidth <= max)
		{
			SetScrollPos(SB_HORZ,pos+1);
			ScrollWindow(-1,0); 
		}
		break;
	case SB_PAGELEFT: //�ڹ�������󷽿հ׹������򵥻�
		if (pos >= thumbwidth)
		{
			ScrollWindow(thumbwidth,0);
			SetScrollPos(SB_HORZ,pos-thumbwidth);
		}
		else
		{
			ScrollWindow(pos,0);
			SetScrollPos(SB_HORZ,0);
		}
		break;
	case SB_PAGERIGHT: //�ڹ�������ҷ��հ׹������򵥻�
		if (pos+thumbwidth <= max-thumbwidth)
		{
			ScrollWindow(-thumbwidth,0);
			SetScrollPos(SB_HORZ,pos+thumbwidth);
		}
		else
		{
			ScrollWindow(-(max-(pos+thumbwidth)),0);
			SetScrollPos(SB_HORZ,max-thumbwidth);
		}
		break;
	}
	m_pptOrigin->x = m_pPaintRect->left + errX*pos/100.0;
	InvalidateRect(m_pPaintRect);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// ��ֱ������
void CDIPSysDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int errY = m_pImage->GetHeight()-m_pPaintRect->Height();
	if (errY <= 0) return;

	m_bScroll = TRUE;
	int pos,min,max,thumbwidth;

	SCROLLINFO vinfo;
	GetScrollInfo(SB_VERT,&vinfo);

	pos = vinfo.nPos;
	min = vinfo.nMin;
	max = vinfo.nMax;
	thumbwidth = vinfo.nPage;

	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		ScrollWindow(0,-((int)nPos-pos));
		SetScrollPos(SB_VERT,nPos); 
		break;
	case SB_LINELEFT:
		SetScrollPos(SB_VERT,pos-1);
		if (pos != 0)
			ScrollWindow(0,1);
		break;
	case SB_LINERIGHT:
		SetScrollPos(SB_VERT,pos+1);
		if (pos+thumbwidth < max)
			ScrollWindow(0,-1); 
		break;
	case SB_PAGELEFT: //�ڹ�������Ϸ��հ׹������򵥻�
		if (pos >= thumbwidth)
		{
			ScrollWindow(0,thumbwidth);
			SetScrollPos(SB_VERT,pos-thumbwidth);
		}
		else
		{
			ScrollWindow(0,pos);
			SetScrollPos(SB_VERT,0);
		}
		break;
	case SB_PAGERIGHT: //�ڹ�������·��հ׹������򵥻�
		if (pos+thumbwidth <= max-thumbwidth)
		{
			ScrollWindow(0,-thumbwidth);
			SetScrollPos(SB_VERT,pos+thumbwidth);
		}
		else
		{
			ScrollWindow(0,-(max-(pos+thumbwidth)));
			SetScrollPos(SB_VERT,max-thumbwidth);
		}
		break;
	}
	m_pptOrigin->y = m_pPaintRect->top + errY*pos/100.0;
	InvalidateRect(m_pPaintRect);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

// �����϶�������ʱ������
BOOL CDIPSysDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bScroll == TRUE)
	{
		m_bScroll = FALSE;
		return TRUE;
	}
	else
		return CDialogEx::OnEraseBkgnd(pDC);
}

// ��ϢԤ����
BOOL CDIPSysDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_MyHotkey && ::TranslateAccelerator(m_hWnd, m_MyHotkey, pMsg)) 
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

// ��ɫͼ��ת��Ϊ�Ҷ�ͼ��
BOOL CDIPSysDlg::RGB2Gray()
{
	if(m_pImage == NULL) return FALSE;
	int ImageWidth = m_pImage->GetWidth();    //��
	int ImageHeight = m_pImage->GetHeight();  //��
	int Channel = m_pImage->GetBPP()/8;       //ͨ��
	long Rowlen = abs(m_pImage->GetPitch());  //�п�
	long lenData = Rowlen*ImageHeight;        //����
	if (Channel == 1) return FALSE;
	BYTE* dataSrc = new BYTE[lenData];
	BYTE* pBits = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(ImageHeight-1));
	memcpy(dataSrc, pBits, lenData);
	// ��ʼת��
	delete m_pImage;
	m_pImage = new CImage;
	m_pImage->Create(ImageWidth, ImageHeight, 8, 0);

	RGBQUAD ColorTab[256];
	for(int i = 0; i<256; i++)
	{
		ColorTab[i].rgbBlue = ColorTab[i].rgbGreen = ColorTab[i].rgbRed = i;
	}
	m_pImage->SetColorTable(0, 256, ColorTab);

	int NewRowlen = abs(m_pImage->GetPitch());
	BYTE* pCur = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(ImageHeight-1));

	for(int y = 0; y<ImageHeight; y++)
	{
		for(int x = 0; x<ImageWidth; x++)
		{
			BYTE* pixel = dataSrc + x*Channel + y*Rowlen;
			*(pCur + x + y*NewRowlen) = *(pixel) * 0.114 + *(pixel+1) * 0.587 + *(pixel+2) * 0.299;
		}
	}
	delete [] dataSrc;
	return TRUE;
}

// ����ǰͼ�񱣴�
void CDIPSysDlg::PushImage()
{
	int Channel = m_pImage->GetBPP()/8;
	int ImageWidth = m_pImage->GetWidth();
	int ImageHeight = m_pImage->GetHeight();
	int RowLen = abs(m_pImage->GetPitch());
	int Datalen = ImageHeight*RowLen;

	CImage* pImage = new CImage;
	if (Channel == 1)//�Ҷ�ͼ�����⴦��
	{
		pImage->Create(ImageWidth, ImageHeight, 8);
		RGBQUAD ColorTab[256];
		for(int i = 0; i<256; i++)
		{
			ColorTab[i].rgbBlue = ColorTab[i].rgbGreen = ColorTab[i].rgbRed = i;
		}
		pImage->SetColorTable(0, 256, ColorTab);
	}
	else pImage->Create(ImageWidth, ImageHeight, 24);
	BYTE* pSrc = (BYTE *)pImage->GetBits()+(pImage->GetPitch()*(ImageHeight-1));
	BYTE* pBits = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(ImageHeight-1));
	memcpy(pSrc, pBits, Datalen);
	//������ѹ��ջ��
	m_UndoStack.Push(pImage);
}

// ��ջ��ͼ��ȡ��
void CDIPSysDlg::PopImage()
{
	if (m_UndoStack.m_nSizeOfStack == 0) return;
	if (m_pImage != NULL) delete m_pImage;
	m_pImage = m_UndoStack.Top();
	InvalidateRect(m_pPaintRect);
}

// ����
BOOL CDIPSysDlg::Zoom(int widthnew, int heightnew)
{

	if (m_pImage == NULL) return FALSE;

	int Channel = m_pImage->GetBPP()/8;
	int ImageWidth = m_pImage->GetWidth();
	int ImageHeight = m_pImage->GetHeight();
	long RowLen = abs(m_pImage->GetPitch());
	long Datalen = ImageHeight*RowLen;

	//��ȡԭͼ����
	BYTE* pBits = new BYTE[Datalen];
	BYTE* dataSrc =(BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(ImageHeight-1));
	memcpy(pBits, dataSrc, Datalen);

	//�������ź��ͼ��ߴ�����
	long WidthCur = widthnew;
	long HeightCur = heightnew;
	long RowlenCur = (widthnew*Channel*8+31)/32*4;
	long DataLenCur = HeightCur * RowlenCur;
	//�������ű���
	float ratewidth = 1.0f * WidthCur / ImageWidth;
	float rateheight = 1.0f * HeightCur/ ImageHeight;
	//����ռ����ڱ���Ŀ��ͼ�����ݼ��м���
	BYTE* dataStep1 = new BYTE[ImageHeight * RowlenCur];
	BYTE* dataDes = new BYTE[DataLenCur];

	//˫���β�ֵ��
	int r = 0, c = 0, k = 0;
	//�������ֵ
	for(r = 0; r < ImageHeight; r++)
	{
		BYTE* pDes = dataStep1 + r * RowlenCur;
		for(c = 0; c < WidthCur; c++)
		{
			int col = (int)(c / ratewidth);
			float fRateX = c / ratewidth - col;
			BYTE* pSrc = pBits + r * RowLen + col * Channel;
			if (col < ImageWidth-1)
			{
				for (k = 0; k<Channel; k++)
				{
					*(pDes+k) = (BYTE)(*(pSrc+k) * (1-fRateX) + *(pSrc+Channel+k) * fRateX);
				}
			}
			else
			{
				for (k = 0; k<Channel; k++)
				{
					*(pDes+k) = (BYTE)*(pSrc+k);
				}
			}
			pDes += Channel;
		}
	}
	delete [] pBits;
	pBits = NULL;
	//�������ֵ
	for (c = 0; c < WidthCur; c++)
	{
		BYTE* pDes = dataDes + c * Channel;
		for (r = 0; r < HeightCur; r++)
		{
			int row = (int)(r / rateheight);
			float fRateY = r / rateheight - row;
			BYTE* pSrc = dataStep1 + row * RowlenCur + c * Channel;
			if(row < ImageHeight-1)
			{
				for (k = 0; k<Channel; k++)
				{
					*(pDes+k) = (BYTE)(*(pSrc+k) * (1-fRateY) + *(pSrc+RowlenCur+k) * fRateY);
				}
			}
			else
			{
				for (k = 0; k<Channel; k++)
				{
					*(pDes+k) = (BYTE)*(pSrc+k);
				}
			}
			pDes += RowlenCur;
		}
	}
	delete m_pImage;
	m_pImage = NULL;
	m_pImage = new CImage;
	if (Channel == 1)//�Ҷ�ͼ�����⴦��
	{
		m_pImage->Create(widthnew, heightnew, 8);
		RGBQUAD ColorTab[256];
		for(int i = 0; i<256; i++)
		{
			ColorTab[i].rgbBlue = ColorTab[i].rgbGreen = ColorTab[i].rgbRed = i;
		}
		m_pImage->SetColorTable(0, 256, ColorTab);
	}
	else m_pImage->Create(widthnew, heightnew, 24);
	pBits = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(m_pImage->GetHeight()-1));
	memcpy(pBits, dataDes, DataLenCur);
	InvalidateRect(m_pPaintRect);
	delete [] dataStep1;
	delete [] dataDes;
	return TRUE;
}

// ��ݼ�Ctrl+Q���˳�����
void CDIPSysDlg::OnHotkeyAppExit()			{  SendMessage(WM_CLOSE);}

// ��ݼ�Ctrl+O����ͼ��
void CDIPSysDlg::OnHotkeyOpenImage()		{  OnCmdOpen();}

// ��ݼ�Ctrl+S������ͼ��
void CDIPSysDlg::OnHotkeySaveImage()		{  OnCmdSave();}

// ��ݼ�Ctrl+G��ɫ��
void CDIPSysDlg::OnHotkeyColorgrad()		{  OnCmdColorGrad();}

// ��ݼ�Ctrl+M������
void CDIPSysDlg::OnHotkeyCurve()			{  OnCmdCurve();}

// ��ݼ�Ctrl+H��ֱ��ͼ
void CDIPSysDlg::OnHotkeyHistogram()		{  OnCmdHistogramDlg();}

// ��ݼ�Ctrl+F���ռ��˲�
void CDIPSysDlg::OnHotkeySpacefilter()		{  OnCmdSpaceFilter();}

// ��ݼ�Ctrl+F2��Ƶ���˲�
void CDIPSysDlg::OnHotkeyFreqfilter()		{  OnCmdFreqFilter();}

// ��ݼ�Alt+Z�������任
void CDIPSysDlg::OnHotkeyZoom()				{  OnCallZoomDlg();}

// ��ݼ�F10������
void CDIPSysDlg::OnHotkeyAbout()			{  OnAppAbout();}

// ��ݼ�F11�����߲���
void CDIPSysDlg::OnHotkeyBlog()				{  OnAuthorBlog();}

// ��ݼ�F12������΢��
void CDIPSysDlg::OnHotkeyMicroBlog()		{  OnAuthorMicroBlog();}

// ��ݼ�Alt+G���Ҷ�ͼ��
void CDIPSysDlg::OnHotkeyRgbToGray()		{  OnRgbToGray();}

// ��ݼ���Ctrl+Z������
void CDIPSysDlg::OnHotkeyUndo()				{  PopImage();}

// �˵�������
void CDIPSysDlg::OnEditUndo()
{
	PopImage();
}

void CDIPSysDlg::OnRgbToGray()
{
	if(RGB2Gray())
		InvalidateRect(m_pPaintRect);
}

// ��Ӧ��Ļ
void CDIPSysDlg::OnFitWindow()
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	Zoom(width, height);
}