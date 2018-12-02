
// ProcessSchedulingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

struct PCB             //PCB���̿��ƿ�
{
	int pid;        //���̱�ʶ��
	int priority;      //�������ȼ�
	string status;     //���̵�״̬��ʶ
	int runtime;       //����������CPUʱ��
	int life;          //���̵���������
	PCB *next;         //���̵Ķ���ָ��
};

// CProcessSchedulingDlg �Ի���
class CProcessSchedulingDlg : public CDialogEx
{
	// ����
public:
	CProcessSchedulingDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_PROCESSSCHEDULING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg long OnHotKey(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ��ǰ�������еĽ���
	CListCtrl m_run;
	// ��ǰ�ľ�������
	CListCtrl m_ready;
	// ��ǰ�Ѿ���ɵĽ���
	CListCtrl m_finish;
	PCB *run = NULL;       //���ж���ͷָ��
	PCB *ready = NULL;     //��������ͷָ��
	PCB *finish = NULL;    //��ɶ���ͷָ��
	void insert(PCB *p);    //��priority��С�����������
	void Prinft(); //��ӡ
	int flag = 0;
	void Priority();             //�������ȼ��ĺ���
	void CreateProssess();       //��������
};
