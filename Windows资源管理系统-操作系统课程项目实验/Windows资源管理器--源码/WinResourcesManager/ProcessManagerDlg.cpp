// ProcessManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinResourcesManager.h"
#include "ProcessManagerDlg.h"
#include "afxdialogex.h"
#include "ProcessTabDlg.h"
// CProcessManagerDlg �Ի���

IMPLEMENT_DYNAMIC(CProcessManagerDlg, CDialogEx)

CProcessManagerDlg::CProcessManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessManagerDlg::IDD, pParent)
{

}

CProcessManagerDlg::~CProcessManagerDlg()
{
}

void CProcessManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, m_tab);
}


BEGIN_MESSAGE_MAP(CProcessManagerDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CProcessManagerDlg::OnTcnSelchangeTab2)
	ON_BN_CLICKED(IDC_End, &CProcessManagerDlg::OnBnClickedEnd)
//	ON_WM_SIZE()
END_MESSAGE_MAP()


// CProcessManagerDlg ��Ϣ�������


BOOL CProcessManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_tab.InsertItem(0, _T("�����б�"));
	m_tab.InsertItem(1, _T("�߳��б�"));
	m_tab.InsertItem(3, _T("�ļ����"));
	m_ThreadTab.Create(IDD_Thread, &m_tab);
	m_ProcessTab.Create(IDD_Process, &m_tab);//IDC_MonitorList,
	m_DiskMonitorTab.Create(IDD_DiskMonitor, &m_tab);
	//��ȡm_tab�ؼ��Ĵ�С��
	CRect rec;
	m_tab.GetClientRect(&rec);
	//��m_tab�ؼ��Ĵ�С�ʵ���С���߼�����Ĭ������Ϊ��������Ϊ��
	rec.top += 22;  //ȥ��ѡ���ǩҳ��һ��ռ�
	rec.bottom -= 4;
	rec.left += 4;
	rec.right -= 4;
	//�ı�ѡ����ڵ�λ�úʹ�С
	m_ProcessTab.MoveWindow(&rec);
	m_ThreadTab.MoveWindow(&rec);
	m_DiskMonitorTab.MoveWindow(&rec);
	m_ProcessTab.ShowWindow(TRUE);
	m_ThreadTab.ShowWindow(FALSE);
	m_DiskMonitorTab.ShowWindow(FALSE);
	m_tab.SetCurSel(0); //Ĭ����ʾ��һ��ѡ�

	isShow = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CProcessManagerDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int CurSel;
	CurSel = m_tab.GetCurSel(); //��ȡ��������ĵڼ��ű�
	CString temp = getPath();
	switch (CurSel)
	{
	case 0: //�����һ�ű�
		m_ProcessTab.ShowWindow(TRUE);
		m_ThreadTab.ShowWindow(FALSE);
		m_DiskMonitorTab.ShowWindow(FALSE);
		//m_ProcessTab.getProcessList();
		break;
	case 1://����ڶ��ű�
		m_ProcessTab.ShowWindow(FALSE);
		m_ThreadTab.ShowWindow(TRUE);
		m_DiskMonitorTab.ShowWindow(FALSE);
		if (isShow)
		{
			m_ThreadTab.getThreadList();
			isShow = false;
		}
		break;
	case 2://��������ű�
		m_ProcessTab.ShowWindow(FALSE);
		m_ThreadTab.ShowWindow(FALSE);
		m_DiskMonitorTab.ShowWindow(TRUE);
		m_DiskMonitorTab.m_monitorPath.SetWindowTextW(temp);
		break;
	default:;
	}
}


void CProcessManagerDlg::OnBnClickedEnd()
{
	// TODO: Add your control notification handler code here
	CString strPID;
	for (int i = 0; i<m_ProcessTab.m_procList.GetItemCount(); i++)//���������б���ͼ
	{
		if (m_ProcessTab.m_procList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)          //��ȡѡ����
		{
			strPID = m_ProcessTab.m_procList.GetItemText(i, 1);//��ñ�ѡ�е��Ǹ�һ�еĵڶ�������PID
			UpdateData(false);
		}
	}
	DWORD a = _ttoi(strPID);
	HANDLE hProcess;
	// �򿪽���
	hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, a);
	if (hProcess)
	{
		if (!TerminateProcess(hProcess, 0))
		{
			CString strError;
			strError.Format(L"�����:%d", GetLastError());
			AfxMessageBox(strError, MB_OK | MB_ICONINFORMATION, NULL);
		}
	}
	else
	{
		CString strError;
		strError.Format(L"�����:%d", GetLastError());
		if (GetLastError() == ERROR_ACCESS_DENIED)
			strError = _T("�ܾ�����!") + strError;
		AfxMessageBox(strError, MB_OK | MB_ICONINFORMATION, NULL);
	}
	Sleep(300);
}
