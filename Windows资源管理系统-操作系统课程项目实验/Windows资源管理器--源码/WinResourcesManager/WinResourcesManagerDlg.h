
// WinResourcesManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MyMFCShellListCtrl.h"
#include "afxwin.h"

// CWinResourcesManagerDlg �Ի���
class CWinResourcesManagerDlg : public CDialogEx
{
// ����
public:
	CWinResourcesManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WINRESOURCESMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	CRect m_rect;//��ȡ�ʼ�Ĵ��ڴ�С
	POINT Old;
	CRect rc;
	int m_Row;
	int m_Col;
	CString  oldName;
	CString newName;
	CString copyName;
	CString copyPath;
	CString path;
	CMFCShellTreeCtrl m_wbdShellTree;
	//CMFCShellListCtrl m_wndShellList;
	CMyMFCShellListCtrl m_wndShellList;
	CEdit m_edit;
	//����·������
	CEdit m_absolutePath;
	afx_msg void OnEnKillfocusEdit();
	afx_msg void OnBnClickedRename();
	afx_msg void OnNMClickFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedProcess();	
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedPaste();
	afx_msg void OnBnClickedMove();
	afx_msg void OnBnClickedNew();
	afx_msg void OnLvnInsertitemFile(NMHDR *pNMHDR, LRESULT *pResult);
	// �������������
	CEdit m_QuickSearch;
	afx_msg void OnBnClickedQuick();
	CString m_strPath;
	CString m_strFileName;
	void FindFile();
	void FindFiles(CString m_strPath, CString m_strFileName);
	bool stop;
	afx_msg void OnBnClickedJump();
	afx_msg void OnBnClickedButton3();
};