#pragma once
#include "afxcmn.h"
#include "ThreadTabDlg.h"
#include "ProcessTabDlg.h"
#include "DiskMonitorTabDlg.h"
// CProcessManagerDlg �Ի���

class CProcessManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessManagerDlg)

public:
	CProcessManagerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessManagerDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;  //CListCtrl m_procList;
	CThreadTabDlg m_ThreadTab;
	CProcessTabDlg m_ProcessTab;
	CDiskMonitorTabDlg m_DiskMonitorTab;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEnd();
	CString path;
	void setPath(CString p) {  path = p; }
	CString getPath() { return path; }
	bool isShow;
};
