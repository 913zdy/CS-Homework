// QuickSerachDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinResourcesManager.h"
#include "QuickSerachDlg.h"
#include "afxdialogex.h"


// CQuickSerachDlg �Ի���

IMPLEMENT_DYNAMIC(CQuickSerachDlg, CDialogEx)

CQuickSerachDlg::CQuickSerachDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuickSerachDlg::IDD, pParent)
{

}

CQuickSerachDlg::~CQuickSerachDlg()
{
}

void CQuickSerachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_searchResult);
}


BEGIN_MESSAGE_MAP(CQuickSerachDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CQuickSerachDlg::OnNMDblclkList1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CQuickSerachDlg ��Ϣ�������

BOOL CQuickSerachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_searchResult.SetExtendedStyle(m_searchResult.GetExtendedStyle() | LVS_EX_FLATSB | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_searchResult.InsertColumn(0, _T("����"), LVCFMT_LEFT, 150);
	m_searchResult.InsertColumn(1, _T("�ļ�·��"), LVCFMT_LEFT, 400);
	m_searchResult.InsertColumn(2, _T("����"), LVCFMT_LEFT, 80);
	m_searchResult.InsertColumn(3, _T("��С"), LVCFMT_LEFT, 50);

	GetClientRect(&m_rect);     //ȡ�ͻ�����С 
	Old.x = m_rect.right - m_rect.left;
	Old.y = m_rect.bottom - m_rect.top;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CQuickSerachDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strPath;
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����2��������ı�   
		strPath = m_searchResult.GetItemText(pNMListView->iItem, 1);
	}
	ShellExecute(NULL, NULL, _T("explorer"), strPath, NULL, SW_SHOW);
	*pResult = 0;
}


void CQuickSerachDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		float fsp[2];
		POINT Newp; //��ȡ���ڶԻ���Ĵ�С
		CRect recta;
		GetClientRect(&recta);     //ȡ�ͻ�����С  
		Newp.x = recta.right - recta.left;
		Newp.y = recta.bottom - recta.top;
		fsp[0] = (float)Newp.x / Old.x;
		fsp[1] = (float)Newp.y / Old.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint, TLPoint; //���Ͻ�
		CPoint OldBRPoint, BRPoint; //���½�
		HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]);
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		Old = Newp;
	}
}
