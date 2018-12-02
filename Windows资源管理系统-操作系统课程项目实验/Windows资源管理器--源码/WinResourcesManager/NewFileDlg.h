#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include "MyMFCShellListCtrl.h"

// CNewFileDlg �Ի���

class CNewFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewFileDlg)

public:
	CNewFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewFileDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �½��ļ�ʱ��·��
	CMFCEditBrowseCtrl m_newfilePath;
	virtual BOOL OnInitDialog();
	CString path;
	CMyMFCShellListCtrl* m_wndShellList;
	void setPath(CString path, CMyMFCShellListCtrl* m_wndShellList1);
	CString getPath();
	// �����ļ�������
	CEdit m_newfileName;
	afx_msg void OnBnClickedOk();
};
