// ThreadTabDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinResourcesManager.h"
#include "ThreadTabDlg.h"
#include "afxdialogex.h"
#include <tlhelp32.h>
#include <Windows.h>
#include <Psapi.h>

// CThreadTabDlg �Ի���

IMPLEMENT_DYNAMIC(CThreadTabDlg, CDialogEx)

CThreadTabDlg::CThreadTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadTabDlg::IDD, pParent)
{

}

CThreadTabDlg::~CThreadTabDlg()
{
}

void CThreadTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ThreadList, m_threadList);
}


BEGIN_MESSAGE_MAP(CThreadTabDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CThreadTabDlg ��Ϣ�������


BOOL CThreadTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_threadList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_threadList.InsertColumn(0, _T("�߳�ID"), LVCFMT_LEFT, 60, 0);
	m_threadList.InsertColumn(1, _T("�߳����"), LVCFMT_LEFT, 80, 0);
	m_threadList.InsertColumn(2, _T("��������"), LVCFMT_LEFT, 180, 0);
	m_threadList.InsertColumn(3, _T("����·��"), LVCFMT_LEFT, 180, 0);

	//getThreadList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

BOOL CThreadTabDlg::getThreadList()
{
	//��ȡϵͳ���̿���
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  // ��ȡϵͳ�����б�
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    // ��ȡΪ�˻�ȡ�߳��б�
	PROCESSENTRY32 pe;      //������Ϣ
	pe.dwSize = sizeof(PROCESSENTRY32);
	THREADENTRY32 te;       // �߳���Ϣ
	te.dwSize = sizeof(THREADENTRY32);
	if (hProcessSnap == INVALID_HANDLE_VALUE || hSnapshot == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"CreateToolhelp32Snapshot����ʧ��!\n");
		return FALSE;
	}
	DWORD idThread = 0;
	DWORD idProcess = 0;
	TCHAR  szFilePath[MAX_PATH];
	CString strID;
	BOOL bMore = ::Process32First(hProcessSnap, &pe);
	//�������̿���
	while (bMore)
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
		::K32GetModuleFileNameExW(hProcess, NULL, szFilePath, MAX_PATH);
		// ��ȡ���̵����߳�ID
		idProcess = pe.th32ProcessID;
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);  // ϵͳ�����߳̿���
		if (Thread32First(hSnapshot, &te))       // ��һ���߳�
		{
			do
			{
				if (idProcess == te.th32OwnerProcessID)  // ��Ϊ�ҵ��ĵ�һ���ý��̵��߳�Ϊ���߳�
				{
					idThread = te.th32ThreadID;
					m_threadList.InsertItem(0, _T(""));
					strID.Format(L"%d", idThread);
					m_threadList.SetItemText(0, 0, strID);
					m_threadList.SetItemText(0, 1, L"������");
					m_threadList.SetItemText(0, 2, pe.szExeFile);
					m_threadList.SetItemText(0, 3, szFilePath);
					break;
				}
			} while (Thread32Next(hSnapshot, &te));  // ��һ���߳�
		}
		bMore = ::Process32Next(hProcessSnap, &pe);  // ��һ������
		::CloseHandle(hProcess);
	}
	// ɾ������  
	::CloseHandle(hProcessSnap);
	::CloseHandle(hSnapshot);
	return TRUE;
}