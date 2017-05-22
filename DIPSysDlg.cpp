
// DIPSysDlg.cpp : 实现文件
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



// CDIPSysDlg 对话框



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


// CDIPSysDlg 消息处理程序

BOOL CDIPSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 1024, 768, SWP_SHOWWINDOW);
	CenterWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDIPSysDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (m_pImage == NULL) return;
	if (m_pPaintRect->Width()<=0 || m_pPaintRect->Height()<=0) return;
	if (m_pImage->GetWidth()-m_pPaintRect->Width() <= 0 || m_pImage->GetHeight()-m_pPaintRect->Height() <= 0)
		m_pImage->Draw(dc, CRect(m_pPaintRect->left, m_pPaintRect->top, m_pPaintRect->left + m_pImage->GetWidth(), m_pPaintRect->top + m_pImage->GetHeight()));
	else 
		m_pImage->Draw(dc, CRect(m_pPaintRect->left, m_pPaintRect->top, m_pPaintRect->left + m_pImage->GetWidth(), m_pPaintRect->top + m_pImage->GetHeight()),
		CRect(m_pptOrigin->x, m_pptOrigin->y, m_pptOrigin->x + m_pImage->GetWidth(), m_pptOrigin->y + m_pImage->GetHeight()));
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	//绘图区
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

/*** 消息响应 ***/

void CDIPSysDlg::OnCmdOpen()
{
	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	CFileDialog hFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, TEXT("所有文件(*.*)|*.* | 图像文件(*.jpg;*.gif;*.png;*.tif;*.bmp)|*.jpg;*.gif;*.png;*.tif;*.bmp||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 2;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("打开图像文件...\0");
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

	CFileDialog dlg(FALSE, NULL, CurTime, NULL, TEXT("BMP 位图文件(*.bmp)|*.bmp|JPEG 图像文件(*.jpg)|*.jpg|PNG 图像文件(*.png)|*.png|TIF 文件格式(*.tif)|*.tif|GIF 图像文件(*.gif)|*.gif||"), NULL);
	dlg.m_ofn.hwndOwner = m_hWnd;
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	dlg.m_ofn.lpstrTitle = TEXT("保存图像文件...\0");
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
	if (m_pImage->Save(strFileName) != S_OK) MessageBox(_T("保存图片失败！"));
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

// 关于
void CDIPSysDlg::OnAppAbout()
{
	CDialogEx AboutDlg(IDD_ABOUT_DLG);
	AboutDlg.DoModal();
}

// 博客
void CDIPSysDlg::OnAuthorBlog()
{
	ShellExecute(NULL, L"open", L"http://www.user.qzone.qq.com/962914132", NULL, NULL, SW_SHOWNORMAL);
}

// 微博
void CDIPSysDlg::OnAuthorMicroBlog()
{
	ShellExecute(NULL, L"open", L"http://www.weibo.com/yuanyuanxiang", NULL, NULL, SW_SHOWNORMAL);
}

// 伸缩变换对话框
void CDIPSysDlg::OnCallZoomDlg()
{
	if (m_pImage == NULL) return;
	CZoomDlg  ZoomDlg;
	ZoomDlg.m_nWidthNew = ZoomDlg.m_dWidthEdit = m_pImage->GetWidth();
	ZoomDlg.m_nHeightNew = ZoomDlg.m_dHeightEdit = m_pImage->GetHeight();
	ZoomDlg.DoModal();
}

// 水平滚动条
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
	case SB_THUMBTRACK: //拖动滚动块
		ScrollWindow(-((int)nPos-pos),0);
		SetScrollPos(SB_HORZ,nPos);
		break;
	case SB_LINELEFT : //单击左箭头
		if (pos != 0)
		{
			ScrollWindow(1,0);
			SetScrollPos(SB_HORZ,pos-1);
		}
		break;
	case SB_LINERIGHT: //单击右箭头
		if (pos+thumbwidth <= max)
		{
			SetScrollPos(SB_HORZ,pos+1);
			ScrollWindow(-1,0); 
		}
		break;
	case SB_PAGELEFT: //在滚动块的左方空白滚动区域单击
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
	case SB_PAGERIGHT: //在滚动块的右方空白滚动区域单击
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

// 垂直滚动条
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
	case SB_PAGELEFT: //在滚动块的上方空白滚动区域单击
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
	case SB_PAGERIGHT: //在滚动块的下方空白滚动区域单击
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

// 避免拖动滑动条时候闪屏
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

// 消息预处理
BOOL CDIPSysDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_MyHotkey && ::TranslateAccelerator(m_hWnd, m_MyHotkey, pMsg)) 
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

// 彩色图像转换为灰度图像
BOOL CDIPSysDlg::RGB2Gray()
{
	if(m_pImage == NULL) return FALSE;
	int ImageWidth = m_pImage->GetWidth();    //宽
	int ImageHeight = m_pImage->GetHeight();  //高
	int Channel = m_pImage->GetBPP()/8;       //通道
	long Rowlen = abs(m_pImage->GetPitch());  //行宽
	long lenData = Rowlen*ImageHeight;        //长度
	if (Channel == 1) return FALSE;
	BYTE* dataSrc = new BYTE[lenData];
	BYTE* pBits = (BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(ImageHeight-1));
	memcpy(dataSrc, pBits, lenData);
	// 开始转换
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

// 将当前图像保存
void CDIPSysDlg::PushImage()
{
	int Channel = m_pImage->GetBPP()/8;
	int ImageWidth = m_pImage->GetWidth();
	int ImageHeight = m_pImage->GetHeight();
	int RowLen = abs(m_pImage->GetPitch());
	int Datalen = ImageHeight*RowLen;

	CImage* pImage = new CImage;
	if (Channel == 1)//灰度图像特殊处理
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
	//将副本压入栈里
	m_UndoStack.Push(pImage);
}

// 将栈顶图像取出
void CDIPSysDlg::PopImage()
{
	if (m_UndoStack.m_nSizeOfStack == 0) return;
	if (m_pImage != NULL) delete m_pImage;
	m_pImage = m_UndoStack.Top();
	InvalidateRect(m_pPaintRect);
}

// 伸缩
BOOL CDIPSysDlg::Zoom(int widthnew, int heightnew)
{

	if (m_pImage == NULL) return FALSE;

	int Channel = m_pImage->GetBPP()/8;
	int ImageWidth = m_pImage->GetWidth();
	int ImageHeight = m_pImage->GetHeight();
	long RowLen = abs(m_pImage->GetPitch());
	long Datalen = ImageHeight*RowLen;

	//获取原图数据
	BYTE* pBits = new BYTE[Datalen];
	BYTE* dataSrc =(BYTE *)m_pImage->GetBits()+(m_pImage->GetPitch()*(ImageHeight-1));
	memcpy(pBits, dataSrc, Datalen);

	//设置缩放后的图像尺寸数据
	long WidthCur = widthnew;
	long HeightCur = heightnew;
	long RowlenCur = (widthnew*Channel*8+31)/32*4;
	long DataLenCur = HeightCur * RowlenCur;
	//计算缩放比例
	float ratewidth = 1.0f * WidthCur / ImageWidth;
	float rateheight = 1.0f * HeightCur/ ImageHeight;
	//申请空间用于保存目标图像数据及中间结果
	BYTE* dataStep1 = new BYTE[ImageHeight * RowlenCur];
	BYTE* dataDes = new BYTE[DataLenCur];

	//双二次插值法
	int r = 0, c = 0, k = 0;
	//先行向插值
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
	//再纵向插值
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
	if (Channel == 1)//灰度图像特殊处理
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

// 快捷键Ctrl+Q：退出程序
void CDIPSysDlg::OnHotkeyAppExit()			{  SendMessage(WM_CLOSE);}

// 快捷键Ctrl+O：打开图像
void CDIPSysDlg::OnHotkeyOpenImage()		{  OnCmdOpen();}

// 快捷键Ctrl+S：保存图像
void CDIPSysDlg::OnHotkeySaveImage()		{  OnCmdSave();}

// 快捷键Ctrl+G：色阶
void CDIPSysDlg::OnHotkeyColorgrad()		{  OnCmdColorGrad();}

// 快捷键Ctrl+M：曲线
void CDIPSysDlg::OnHotkeyCurve()			{  OnCmdCurve();}

// 快捷键Ctrl+H：直方图
void CDIPSysDlg::OnHotkeyHistogram()		{  OnCmdHistogramDlg();}

// 快捷键Ctrl+F：空间滤波
void CDIPSysDlg::OnHotkeySpacefilter()		{  OnCmdSpaceFilter();}

// 快捷键Ctrl+F2：频域滤波
void CDIPSysDlg::OnHotkeyFreqfilter()		{  OnCmdFreqFilter();}

// 快捷键Alt+Z：伸缩变换
void CDIPSysDlg::OnHotkeyZoom()				{  OnCallZoomDlg();}

// 快捷键F10：关于
void CDIPSysDlg::OnHotkeyAbout()			{  OnAppAbout();}

// 快捷键F11：作者博客
void CDIPSysDlg::OnHotkeyBlog()				{  OnAuthorBlog();}

// 快捷键F12：作者微博
void CDIPSysDlg::OnHotkeyMicroBlog()		{  OnAuthorMicroBlog();}

// 快捷键Alt+G：灰度图像
void CDIPSysDlg::OnHotkeyRgbToGray()		{  OnRgbToGray();}

// 快捷键：Ctrl+Z：撤销
void CDIPSysDlg::OnHotkeyUndo()				{  PopImage();}

// 菜单：撤销
void CDIPSysDlg::OnEditUndo()
{
	PopImage();
}

void CDIPSysDlg::OnRgbToGray()
{
	if(RGB2Gray())
		InvalidateRect(m_pPaintRect);
}

// 适应屏幕
void CDIPSysDlg::OnFitWindow()
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	Zoom(width, height);
}