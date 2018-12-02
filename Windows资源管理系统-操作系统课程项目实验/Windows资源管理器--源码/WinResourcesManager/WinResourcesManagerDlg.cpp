
// WinResourcesManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinResourcesManager.h"
#include "WinResourcesManagerDlg.h"
#include "NewFileDlg.h"
#include "afxdialogex.h"
#include "ProcessManagerDlg.h"
#include<tlhelp32.h>
#include <afxwin.h>
#include <process.h>
#include "QuickSerachDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CWinResourcesManagerDlg �Ի���



CWinResourcesManagerDlg::CWinResourcesManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinResourcesManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinResourcesManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Folder, m_wbdShellTree);
	DDX_Control(pDX, IDC_File, m_wndShellList);
	DDX_Control(pDX, IDC_Edit, m_edit);
	DDX_Control(pDX, IDC_Path, m_absolutePath);
	DDX_Control(pDX, IDC_Search, m_QuickSearch);
}

BEGIN_MESSAGE_MAP(CWinResourcesManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_Process, &CWinResourcesManagerDlg::OnBnClickedProcess)
	ON_EN_KILLFOCUS(IDC_Edit, &CWinResourcesManagerDlg::OnEnKillfocusEdit)
	ON_BN_CLICKED(IDC_Rename, &CWinResourcesManagerDlg::OnBnClickedRename)
	ON_NOTIFY(NM_CLICK, IDC_File, &CWinResourcesManagerDlg::OnNMClickFile)
	ON_BN_CLICKED(IDC_Delete, &CWinResourcesManagerDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_Copy, &CWinResourcesManagerDlg::OnBnClickedCopy)
	ON_BN_CLICKED(IDC_Paste, &CWinResourcesManagerDlg::OnBnClickedPaste)
	ON_BN_CLICKED(IDC_Move, &CWinResourcesManagerDlg::OnBnClickedMove)
	ON_BN_CLICKED(IDC_New, &CWinResourcesManagerDlg::OnBnClickedNew)
	ON_NOTIFY(LVN_INSERTITEM, IDC_File, &CWinResourcesManagerDlg::OnLvnInsertitemFile)
	ON_BN_CLICKED(IDC_Quick, &CWinResourcesManagerDlg::OnBnClickedQuick)
	ON_BN_CLICKED(IDC_Jump, &CWinResourcesManagerDlg::OnBnClickedJump)
	ON_BN_CLICKED(IDC_BUTTON3, &CWinResourcesManagerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWinResourcesManagerDlg ��Ϣ�������

BOOL CWinResourcesManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	m_wbdShellTree.Expand(m_wbdShellTree.GetRootItem(), TVE_EXPAND);
	m_wbdShellTree.SetRelatedList(&m_wndShellList);

	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH;

	LPWSTR sName[4] = { _T("����"), _T("��С"), _T("����"), _T("�޸�����") };

	int nWidth[4] = { 200, 100, 100, 200 };

	for (int i = 0; i<4; i++)

	{

		lvColumn.pszText = sName[i];

		lvColumn.cx = nWidth[i];

		lvColumn.fmt = LVCFMT_LEFT;

		m_wndShellList.SetColumn(i, &lvColumn);
		//m_wndShellList.EnableShellContextMenu(false);

	}
	m_edit.ShowWindow(SW_HIDE);

	GetClientRect(&m_rect);     //ȡ�ͻ�����С 
	Old.x = m_rect.right - m_rect.left;
	Old.y = m_rect.bottom - m_rect.top;

	m_wndShellList.GetCurrentFolder(path);
	m_absolutePath.SetWindowTextW(path);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWinResourcesManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWinResourcesManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//���ñ���ɫΪ��ɫ,�Լ��ĵ�
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,RGB(250,250,250));

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWinResourcesManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���οͻ�����esc����enter���˳�����
BOOL CWinResourcesManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)// ����esc��
	{
		return TRUE;// �����κβ���
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)// ����enter��
	{
		return TRUE;// �����κδ���
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CWinResourcesManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED){
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

void CWinResourcesManagerDlg::OnBnClickedProcess()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString t;
	m_absolutePath.GetWindowTextW(t);

	CProcessManagerDlg *dlg = new CProcessManagerDlg;//��ģ̬
	dlg->Create(IDD_TaskManagerDlg, GetDesktopWindow());    //��һ�������ǶԻ���ID��
	dlg->ShowWindow(SW_SHOW);
	dlg->setPath(t);
	CDiskMonitorTabDlg *d = new CDiskMonitorTabDlg;
	d->setPath(t);
}

void CWinResourcesManagerDlg::OnNMClickFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_Row = pNMListView->iItem;//���ѡ�е���
	m_Col = pNMListView->iSubItem;//���ѡ����
	if (pNMListView->iItem != -1)
	{
		oldName = m_wndShellList.GetItemText(pNMListView->iItem, pNMListView->iSubItem);
		m_wndShellList.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//��������RECT�� 
	}
	m_wndShellList.GetCurrentFolder(path);
	//m_absolutePath.SetWindowTextW(path);
	//MessageBox(oldName);
	*pResult = 0;
}

void CWinResourcesManagerDlg::OnBnClickedRename()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_edit.SetParent(&m_wndShellList);//ת������Ϊ�б���е�����
	m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;
	m_edit.SetWindowText(m_wndShellList.GetItemText(m_Row, m_Col));//���������е�ֵ����Edit�ؼ��У�
	m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���
	m_edit.SetFocus();//����Edit����
	m_edit.ShowCaret();//��ʾ���
	m_edit.SetSel(-1);//������ƶ������
}

void CWinResourcesManagerDlg::OnEnKillfocusEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_edit.GetWindowText(newName);    //�õ��û�������µ�����
	if (PathFileExists(path + newName) && oldName != newName)
	{
		AfxMessageBox(_T("�ļ���Ŀ¼����"));
		m_wndShellList.SetItemText(m_Row, m_Col, oldName);   //���ñ༭���������
		m_edit.ShowWindow(SW_HIDE);
		//MessageBox(L"1");
	}
	else if (oldName == newName)
	{
		m_edit.ShowWindow(SW_HIDE);
		//MessageBox(L"2");
	}
	else
	{
		TCHAR szSrc[MAX_PATH] = { 0 };
		TCHAR szDesc[MAX_PATH] = { 0 };
		if (!PathIsRoot(path))
		{
			path=path + L"\\";
		}
		lstrcpy(szSrc, path+oldName);
		lstrcpy(szDesc, path + newName);
		//MessageBox(szSrc);
		//MessageBox(szDesc);
		SHFILEOPSTRUCT FileOp = { 0 };
		FileOp.fFlags = 0;
		FileOp.pFrom = szSrc;
		FileOp.pTo = szDesc;
		FileOp.wFunc = FO_RENAME;
		SHFileOperation(&FileOp);
		m_wndShellList.SetItemText(m_Row, m_Col, newName);   //���ñ༭���������
		//MessageBox(L"3");
		m_edit.ShowWindow(SW_HIDE);
	}
}


void CWinResourcesManagerDlg::OnBnClickedDelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TCHAR szSrc[MAX_PATH] = { 0 };
	lstrcpy(szSrc, path +"\\"+ oldName);
	SHFILEOPSTRUCT FileOp;
	ZeroMemory((void*)&FileOp, sizeof(SHFILEOPSTRUCT));
	FileOp.fFlags = FOF_NOCONFIRMATION;
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = szSrc;
	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;
	int i=SHFileOperation(&FileOp);
	if (i != 0)
	{
		CFile::Remove(szSrc);
		//MessageBox(L"�ɹ�");
	}
	m_wndShellList.Refresh();
}


void CWinResourcesManagerDlg::OnBnClickedCopy()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_absolutePath.GetWindowTextW(copyPath);
	copyName = oldName;
	if (PathIsRoot(copyPath))
	{
		copyPath = copyPath + copyName;
	}
	else
	{
		copyPath = copyPath + "\\" + copyName;
	}
	//MessageBox(copyPath);
}


void CWinResourcesManagerDlg::OnBnClickedPaste()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString realPath;
	m_absolutePath.GetWindowTextW(realPath);
	if (PathIsRoot(realPath))
	{
		realPath = realPath + copyName;
	}
	else
	{
		realPath = realPath + "\\" + copyName;
	}
	while (PathFileExists(realPath) && !PathIsDirectory(realPath))
	{
		int idx = realPath.ReverseFind('.'); //idx ��ֵΪ4;
		
		CString filename = realPath.Left(idx);
		CString suff = realPath.Mid(idx);
		realPath = filename + L"-����" + suff;
	}
	if (PathIsDirectory(copyPath) && !PathIsDirectory(path + oldName))
	{
		realPath = path + copyName + L"-����";
	}
	//MessageBox(copyPath);
	//MessageBox(realPath);
	
	TCHAR szSrc[MAX_PATH] = { 0 };
	TCHAR szDesc[MAX_PATH] = { 0 };
	lstrcpy(szSrc, copyPath);
	lstrcpy(szDesc, realPath);
	SHFILEOPSTRUCT FileOp = { 0 };
	ZeroMemory((void*)&FileOp, sizeof(SHFILEOPSTRUCT));
	FileOp.fFlags = FOF_NOCONFIRMATION;
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = szSrc;
	FileOp.pTo = szDesc;
	FileOp.wFunc = FO_COPY;
	SHFileOperation(&FileOp);
	m_wndShellList.Refresh();
}


void CWinResourcesManagerDlg::OnBnClickedMove()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BROWSEINFO   bInfo;
	ZeroMemory(&bInfo, sizeof(bInfo));
	bInfo.hwndOwner = m_hWnd;
	TCHAR tchPath[255];
	bInfo.lpszTitle = _T("��ѡ��·��:   ");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST lpDlist; 	//�������淵����Ϣ��IDList��ʹ��SHGetPathFromIDList����ת��Ϊ�ַ��� 
	lpDlist = SHBrowseForFolder(&bInfo);   //��ʾѡ��Ի��� 
	if (lpDlist != NULL)
	{
		SHGetPathFromIDList(lpDlist, tchPath);//����Ŀ��ʶ�б�ת����Ŀ¼ 
	}
	CString realPath1;
	CString realPath2;
	TCHAR szSrc[MAX_PATH] = { 0 };
	TCHAR szDesc[MAX_PATH] = { 0 };
	if (PathIsRoot(path))
	{
		realPath1 = path + oldName;
	}
	else
	{
		realPath1 = path + "\\" + oldName;
	}
	if (PathIsRoot(tchPath))
	{
		realPath2 = tchPath + oldName;
	}
	else
	{
		CString temp = L"\\" + oldName;
		realPath2 = tchPath + temp;
	}
	lstrcpy(szSrc, realPath1);
	lstrcpy(szDesc, realPath2);
	//MessageBox(szSrc);
	//MessageBox(szDesc);
	SHFILEOPSTRUCT FileOp;
	ZeroMemory((void*)&FileOp, sizeof(SHFILEOPSTRUCT));
	FileOp.fFlags = FOF_NOCONFIRMATION|FOF_NOCONFIRMMKDIR;;
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = szSrc;
	FileOp.pTo = szDesc;
	FileOp.wFunc = FO_MOVE;
	int i=SHFileOperation(&FileOp);
	if (i != 0)
	{
		MessageBox(L"�ƶ�ʧ�ܣ�");
	}
	m_wndShellList.Refresh();
}

void CWinResourcesManagerDlg::OnBnClickedNew()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CNewFileDlg dlg(this);
	dlg.setPath(path, &m_wndShellList);
	// ��ʾģʽ�Ի���
	dlg.DoModal();
}

void CWinResourcesManagerDlg::OnLvnInsertitemFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_wndShellList.GetCurrentFolder(path);
	m_absolutePath.SetWindowTextW(path);
	*pResult = 0;
}


UINT FindFileThreadFunc(LPVOID pParam)     //��������
{
	CWinResourcesManagerDlg* p = (CWinResourcesManagerDlg*)pParam;
	p->FindFile();
	return 0;
}

CQuickSerachDlg *dlg1;

void CWinResourcesManagerDlg::OnBnClickedQuick()   //�����߳��¼�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CQuickSerachDlg *dlg = new CQuickSerachDlg;
	dlg->Create(IDD_QuickSearchDlg, GetDesktopWindow());    //��һ�������ǶԻ���ID��
	dlg->ShowWindow(SW_SHOW);
	dlg1 = dlg;
	m_absolutePath.GetWindowTextW(m_strPath);
	m_QuickSearch.GetWindowTextW(m_strFileName);
	//m_wndShellList.DeleteAllItems();
	CWinThread *pThread = AfxBeginThread(FindFileThreadFunc, this, THREAD_PRIORITY_NORMAL,0,0);
	ASSERT_VALID(pThread);
	pThread->ResumeThread();
}

void CWinResourcesManagerDlg::FindFile()   //�����ļ�����
{
	stop = FALSE;
	if (m_strPath.IsEmpty() || m_strFileName.IsEmpty())
	{
		return;
	}
	FindFiles(m_strPath, m_strFileName);
	stop = FALSE;
}

void CWinResourcesManagerDlg::FindFiles(CString m_strPath, CString m_strFileName)  //�ݹ麯��
{
	if (m_strPath.Right(1) != _T("\\"))
	{
		m_strPath += "\\";
	}
	m_strPath += _T("*.*");
	CFileFind file;
	BOOL bContinue = file.FindFile(m_strPath);
	while (bContinue)
	{
		bContinue = file.FindNextFile();  //������һ���ļ�
		if (file.IsDirectory() && !file.IsDots())  //Ŀ¼
		{
			FindFiles(file.GetFilePath(), m_strFileName);
		}
		else if (!file.IsDots() && !file.IsDirectory())  //�ļ�
		{
			if (file.GetFileName().Find(m_strFileName)!=-1)
			{	//��������
				int index = dlg1->m_searchResult.GetItemCount();
				dlg1->m_searchResult.InsertItem(index, file.GetFileName());
				dlg1->m_searchResult.SetItemText(index, 1, file.GetFilePath());
			}
		}
	}
}

void CWinResourcesManagerDlg::OnBnClickedJump()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString path;
	m_absolutePath.GetWindowTextW(path);
	if (!PathFileExists(path))
	{
		AfxMessageBox(_T("��·��������"));
		return;
	}
	m_wndShellList.DisplayFolder(path);
}


void CWinResourcesManagerDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_wndShellList.Refresh();
}
