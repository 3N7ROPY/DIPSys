
// DIPSys.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDIPSysApp:
// �йش����ʵ�֣������ DIPSys.cpp
//

class CDIPSysApp : public CWinApp
{
public:
	CDIPSysApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDIPSysApp theApp;