
// ProcessScheduling.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProcessSchedulingApp: 
// �йش����ʵ�֣������ ProcessScheduling.cpp
//

class CProcessSchedulingApp : public CWinApp
{
public:
	CProcessSchedulingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProcessSchedulingApp theApp;