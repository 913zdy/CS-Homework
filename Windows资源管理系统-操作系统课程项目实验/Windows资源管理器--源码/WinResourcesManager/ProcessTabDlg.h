#pragma once
#include "afxcmn.h"

// CProcessTabDlg �Ի���

class CProcessTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessTabDlg)

public:
	CProcessTabDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessTabDlg();

// �Ի�������
	enum { IDD = IDD_Process };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_procList;
	BOOL getProcessList();
};
