#pragma once
#include "afxcmn.h"


// CQuickSerachDlg �Ի���

class CQuickSerachDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuickSerachDlg)

public:
	CQuickSerachDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQuickSerachDlg();

// �Ի�������
	enum { IDD = IDD_QuickSearchDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_searchResult;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CRect m_rect;//��ȡ�ʼ�Ĵ��ڴ�С
	POINT Old;
};
