#pragma once
#include "afxcmn.h"


// CThreadTabDlg �Ի���

class CThreadTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreadTabDlg)

public:
	CThreadTabDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThreadTabDlg();

// �Ի�������
	enum { IDD = IDD_Thread };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_threadList;
	BOOL getThreadList();
};
