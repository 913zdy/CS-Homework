// NewFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinResourcesManager.h"
#include "NewFileDlg.h"
#include "afxdialogex.h"
#include "WinResourcesManagerDlg.h"
// CNewFileDlg �Ի���

IMPLEMENT_DYNAMIC(CNewFileDlg, CDialogEx)

CNewFileDlg::CNewFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewFileDlg::IDD, pParent)
{

}

CNewFileDlg::~CNewFileDlg()
{
}

void CNewFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_newfilePath);
	DDX_Control(pDX, IDC_IDC_NewFileName, m_newfileName);
}


BEGIN_MESSAGE_MAP(CNewFileDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewFileDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewFileDlg ��Ϣ�������


BOOL CNewFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_newfilePath.SetWindowTextW(getPath());
	m_newfilePath.SetSel(-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void CNewFileDlg::setPath(CString path1, CMyMFCShellListCtrl* m_wndShellList1)
{
	path=path1;
	m_wndShellList = m_wndShellList1;
}

CString CNewFileDlg::getPath()
{
	return path;
}

void CNewFileDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString newFilePath;
	CString newFileName;
	m_newfilePath.GetWindowTextW(newFilePath);
	m_newfileName.GetWindowTextW(newFileName);
	//MessageBox(newFilePath);
	//MessageBox(newFileName);
	if (newFilePath == "" || newFileName == "")
	{
		MessageBox(L"�ļ������ļ�·������Ϊ��");
		return;
	}
	CString path = newFilePath + "\\" + newFileName;

	if (newFileName.FindOneOf(_T("/:*?<>|"))!=-1)
	{
		MessageBox(L"���ļ������ܺ��� / : * ? < > |��");
		MessageBox(newFileName);
	}
	else if (!PathFileExists(path))
	{
		if (newFileName.ReverseFind('.')!=-1)  // + 4 >= newFileName.GetLength()
		{
			int index = newFileName.ReverseFind('\\');
			if (index != -1)
			{
				CString t=newFileName.Left(index);
				::SHCreateDirectoryExW(NULL, newFilePath + t, NULL);
			}
			CFile m_sFile;
			m_sFile.Open(path, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyWrite);
			m_sFile.SeekToEnd();
			m_sFile.Close();
		}
		else
		{ 
			::SHCreateDirectoryExW(NULL, path, NULL);   		//CreateDirectory(path, 0);//�������򴴽�
		}
		m_wndShellList->Refresh();
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(L"���ļ����ļ����Ѵ���");
	}
	
}
