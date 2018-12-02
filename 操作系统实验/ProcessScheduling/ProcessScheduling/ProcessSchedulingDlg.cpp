
// ProcessSchedulingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessScheduling.h"
#include "ProcessSchedulingDlg.h"
#include "afxdialogex.h"
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
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProcessSchedulingDlg �Ի���



CProcessSchedulingDlg::CProcessSchedulingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessSchedulingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessSchedulingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RUN, m_run);
	DDX_Control(pDX, IDC_READY, m_ready);
	DDX_Control(pDX, IDC_FINISH, m_finish);
}

BEGIN_MESSAGE_MAP(CProcessSchedulingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProcessSchedulingDlg ��Ϣ�������

BOOL CProcessSchedulingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_run.SetExtendedStyle(m_run.GetExtendedStyle() | LVS_EX_FLATSB | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_run.InsertColumn(0, _T("��������"), LVCFMT_LEFT, 130);
	m_run.InsertColumn(1, _T("�������ȼ�"), LVCFMT_LEFT, 130);
	m_run.InsertColumn(2, _T("������������"), LVCFMT_LEFT, 130);
	m_run.InsertColumn(3, _T("����״̬"), LVCFMT_LEFT, 129);
	
	m_ready.SetExtendedStyle(m_ready.GetExtendedStyle() | LVS_EX_FLATSB | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ready.InsertColumn(0, _T("��������"), LVCFMT_LEFT, 130);
	m_ready.InsertColumn(1, _T("�������ȼ�"), LVCFMT_LEFT, 130);
	m_ready.InsertColumn(2, _T("������������"), LVCFMT_LEFT, 130);
	m_ready.InsertColumn(3, _T("����״̬"), LVCFMT_LEFT, 129);

	m_finish.SetExtendedStyle(m_ready.GetExtendedStyle() | LVS_EX_FLATSB | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_finish.InsertColumn(0, _T("��������"), LVCFMT_LEFT, 130);
	m_finish.InsertColumn(1, _T("�������ȼ�"), LVCFMT_LEFT, 130);
	m_finish.InsertColumn(2, _T("������������"), LVCFMT_LEFT, 130);
	m_finish.InsertColumn(3, _T("����״̬"), LVCFMT_LEFT, 129);

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
	::RegisterHotKey(m_hWnd,ID_Create,MOD_CONTROL,'F');
	::RegisterHotKey(m_hWnd, ID_Quit, MOD_CONTROL, 'Q');
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CProcessSchedulingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProcessSchedulingDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProcessSchedulingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CProcessSchedulingDlg::OnHotKey(WPARAM wParam , LPARAM lParam)
{
	if(wParam == ID_Create)
	{
		CreateProssess();
		Prinft();
		SetTimer(1, 2000, NULL);
	}
	if (wParam == ID_Quit)
	{

		if (AfxMessageBox(_T("�Ƿ�ȷ���˳�"), MB_YESNO) == IDYES)	
		{
			KillTimer(1);
			exit(0);
		}
	}
	return TRUE;
}

void CProcessSchedulingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	flag++;
	Priority();
	CDialogEx::OnTimer(nIDEvent);
}

void CProcessSchedulingDlg::CreateProssess()          //��������
{
	PCB *node;                 //����ָ��
	srand((int)time(0));
	node = new PCB;
	if (node == NULL)
	{
		return;
	}
	else
	{
		node->pid = (1 + rand() % (100 + 1));
		node->life = rand() % 5 + 1; //Ϊ�����������ռ��CPUʱ��
		node->runtime = 0;
		node->status = "����";
		node->priority = rand() % 49; //Ϊ�����������������
	}
	insert(node);          //�������������뵽����������
}

void CProcessSchedulingDlg::insert(PCB *p)    //��priority��С�����������
{
	PCB *S1, *S2;
	if (ready == NULL)
	{
		p->next = NULL;
		ready = p;
	}
	else
	{
		S1 = ready;
		S2 = S1;
		while (S1 != NULL)
		{
			if (S1->priority >= p->priority)
			{
				S2 = S1;
				S1 = S1->next;
			}
			else
				break;
		}

		if (S2->priority >= p->priority)
		{
			S2->next = p;
			p->next = S1;
		}
		else
		{
			p->next = ready;
			ready = p;
		}
	}
}

void CProcessSchedulingDlg::Prinft()
{
	CString str1,str2,str3;
	int pid1,priority1,life1,i = 0;
	PCB *p;            //���̿��ƿ�ָ��
	p = run;           //���ж���
	if (p != NULL)
		p->next = NULL;

	m_run.DeleteAllItems(); // ȫ�����
	while (p != NULL)
	{
		pid1 = p->pid;
		priority1 = p->priority;
		life1 = p->life;
		str1.Format(_T("%d"), pid1);
		str2.Format(_T("%d"), priority1);
		str3.Format(_T("%d"), life1);

		m_run.InsertItem(i, str1);
		m_run.SetItemText(i, 1, str2);
		m_run.SetItemText(i, 2, str3);
		m_run.SetItemText(i, 3, _T("����"));
		p = p->next;
	}

	m_ready.DeleteAllItems(); // ȫ�����
	p = ready;
	while (p != NULL)
	{
		pid1 = p->pid;
		priority1 = p->priority;
		life1 = p->life;
		str1.Format(_T("%d"), pid1);
		str2.Format(_T("%d"), priority1);
		str3.Format(_T("%d"), life1);

		m_ready.InsertItem(i, str1);
		m_ready.SetItemText(i, 1, str2);
		m_ready.SetItemText(i, 2, str3);
		m_ready.SetItemText(i, 3,_T("����"));
		p = p->next;
	}

	m_finish.DeleteAllItems(); // ȫ�����
	p = finish;
	while (p != NULL)
	{
		pid1 = p->pid;
		priority1 = p->priority;
		life1 = p->life;
		str1.Format(_T("%d"), pid1);
		str2.Format(_T("%d"), priority1);
		str3.Format(_T("%d"), life1);

		m_finish.InsertItem(i, str1);
		m_finish.SetItemText(i, 1, str2);
		m_finish.SetItemText(i, 2, str3);
		m_finish.SetItemText(i, 3, _T("���"));
		p = p->next;
	}
}

void CProcessSchedulingDlg::Priority()                 //�������ȼ��ĺ���
{
	if (flag == 1)
	{
		run = ready;
		if (run == NULL) return;
		ready = ready->next;
		run->status = "����";
	}
	if (run == NULL){
		flag = 0;
		return;
	}

	//���ж��в���ʱ���н�����������
	run->runtime = run->runtime + 1;
	run->life = run->life - 1;
	run->priority = run->priority / 2; //ÿ����һ����������Ϊԭ���Ķ���֮һ

	if (run->life == 0)        //������ʱ��Ϊ0���������ɶ���
	{
		run->status = "���";
		run->next = finish;
		finish = run;
		run = NULL;           //���ж���ͷָ���ƿ�

		if (ready != NULL)     //�������в���
		{
			run = ready;
			run->status = "����";
			ready = ready->next;
		}
	}
	else if ((ready != NULL) && (run->priority < ready->priority))
	{
		run->status = "����";
		insert(run);
		run = ready;
		run->status = "����";
		ready = ready->next;
	}
	Prinft();              //������̿��ƿ�PCB��Ϣ
}