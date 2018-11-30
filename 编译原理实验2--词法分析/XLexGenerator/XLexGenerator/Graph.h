#pragma once
#pragma warning(disable:4996)

#include "VertexEdge.h"

// ���ڽӱ����ͼ��
class Graph
{
private:
	Vertex *startVertex;
	int numOfVertices;
	int numOfEdges;
public:
	Graph();
	~Graph();
	int GetValueByPos(int pos) const;
	int GetPosByValue(int value) const;
	char GetWeightByPos(int v1, int v2) const;
	char GetWeightByValue(int value1, int value2) const;
	void SetValue(int value, int pos);
	void InsertVertex(int value);
	void InsertEdgeByPos(int v1, int v2, char weight);
	void InsertEdgeByValue(int value1, int value2, char weight);
	void RemoveAllEdges(void);
	void Clear(void);
	int* Closure(int *T);
	int* Move(int *T, char ch);
	void OutputNFA(CListCtrl *ShowDate);
};
// ���캯��
Graph::Graph()
{
	numOfVertices = 1;
	numOfEdges = 0;
	startVertex = new Vertex();
}
// ��������
Graph::~Graph()
{
	Vertex *pVertex;
	Edge *pEdge;
	pVertex = startVertex;
	for (int i = 0; i < numOfVertices; i++)
	{
		pEdge = pVertex->link;
		while (pEdge)
		{
			pVertex->link = pEdge->next;
			delete pEdge;
			pEdge = pVertex->link;
		}
		pVertex = pVertex->next;
	}
}
// ������λ�û�ȡ�����ֵ
int Graph::GetValueByPos(int posi) const
{
	if ((posi >= 0) && (posi < numOfVertices))
	{
		Vertex *p = startVertex;
		for (int i = 0; i < posi; i++)
		{
			p = p->next;
		}
		return p->number;
	}
	return -1;
}
// ������ֵ��ȡ�����λ��
int Graph::GetPosByValue(int value) const
{
	Vertex *p = startVertex;
	for (int i = 0; i < numOfVertices; i++)
	{
		if (p->number == value)
		{
			return i;
		}
		p = p->next;
	}
	return -1;
}
// ������λ�û�ȡ�ߵ�Ȩ
char Graph::GetWeightByPos(int position1, int position2) const
{
	if ((position1 >= 0) && (position2 >= 0) && (position1 < numOfVertices) && (position2 < numOfVertices))
	{
		Vertex *pVertex = startVertex;
		for (int i = 0; i < position1; i++)
		{
			pVertex = pVertex->next;
		}
		Edge *pEdge = pVertex->link;
		while (pEdge)
		{
			if (pEdge->position == position2)
			{
				return (pEdge->element);
			}
			else
			{
				pEdge = pEdge->next;
			}
		}
	}
	return '#';
}
// ������ֵ��ȡ�ߵ�Ȩ
char Graph::GetWeightByValue(int value1, int value2) const
{
	return GetWeightByPos(GetPosByValue(value1), GetPosByValue(value2));
}
// ��λ�����ö����ֵ
void Graph::SetValue(int value, int pos)
{
	if ((pos < 0) || (pos >= numOfVertices))
	{
		exit(1);
	}
	Vertex *p = startVertex;
	for (int i = 0; i < pos; i++)
	{
		p = p->next;
	}
	p->number = value;
}
// ���붥��
void Graph::InsertVertex(int value)
{
	int pos = GetPosByValue(value);
	if ((pos >= 0) && (pos < numOfVertices))
	{
		exit(1);
	}
	Vertex *p = startVertex;
	while (p->next)
	{
		p = p->next;
	}
	Vertex *newVertex = new Vertex(value);
	p->next = newVertex;
	numOfVertices++;
}
// ������λ�ò���߱�
void Graph::InsertEdgeByPos(int position1, int position2, char weight)
{
	if ((position1 < 0) || (position1 >= numOfVertices) || (position2 < 0) || (position2 >= numOfVertices))
	{
		exit(1);
	}
	Vertex *pVertex = startVertex;
	for (int i = 0; i < position1; i++)
	{
		pVertex = pVertex->next;
	}
	Edge *pEdge = pVertex->link;
	Edge *newEdge = new Edge(GetValueByPos(position2), position2, weight);
	if (!pEdge)
	{
		pVertex->link = newEdge;
		numOfEdges++;
		return;
	}
	while ((pEdge->position != position2) && (pEdge->next))
	{
		pEdge = pEdge->next;
	}
	if (pEdge->position == position2)
	{
		exit(1);
	}
	if (!pEdge->next)
	{
		pEdge->next = newEdge;
		numOfEdges++;
	}
}
// ������ֵ����߱�
void Graph::InsertEdgeByValue(int value1, int value2, char weight)
{
	int v1 = GetPosByValue(value1), v2 = GetPosByValue(value2);
	InsertEdgeByPos(v1, v2, weight);
}
// ɾ�����еı�
void Graph::RemoveAllEdges(void)
{
	Vertex *pVertex = startVertex;
	for (int i = 0; i < numOfVertices; i++)
	{
		Edge *pEdge = pVertex->link;
		while (pEdge)
		{
			pVertex->link = pEdge->next;
			delete pEdge;
			pEdge = pVertex->link;
		}
		pVertex = pVertex->next;
	}
	numOfEdges = 0;
}
// ����ڽӱ�
void Graph::Clear(void)
{
	RemoveAllEdges();
	Vertex *p = startVertex->next;
	while (p)
	{
		startVertex->next = p->next;
		delete p;
		p = startVertex->next;
	}
	numOfVertices = 1;
}
// �հ�����
int* Graph::Closure(int *T)
{
	int i = 0, j, k = 0, l, len = 0;
	int *temp = new int[128];
	Vertex *pVertex;
	Edge *pEdge;
	while (T[len] != -1)
	{
		len++;
	}
	while (T[i] != -1)
	{
		for (l = 0; l < k; l++)
		{
			if (T[i] == temp[l])
			{
				break;
			}
		}
		if (l == k)
		{
			temp[k] = T[i];
			k++;
		}
		int pos = GetPosByValue(T[i]);
		pVertex = startVertex;
		for (j = 0; j < pos; j++)
		{
			pVertex = pVertex->next;
		}
		pEdge = pVertex->link;
		while (pEdge)
		{
			if (pEdge->element == '~')
			{
				for (l = 0; l < k; l++)
				{
					if (pEdge->number == temp[l])
					{
						break;
					}
				}
				if (l == k)
				{
					temp[k] = pEdge->number;
					k++;
					T[len++] = pEdge->number;
					T[len] = -1;
				}
			}
			pEdge = pEdge->next;
		}
		i++;
	}
	temp[k] = -1;
	return temp;
}
// �ƶ�����
int* Graph::Move(int *T, char ch)
{
	int i = 0, j, k = 0, l;
	int *temp = new int[128];
	Vertex *pVertex;
	Edge *pEdge;
	while (T[i] != -1)
	{
		int pos = GetPosByValue(T[i]);
		pVertex = startVertex;
		for (j = 0; j < pos; j++)
		{
			pVertex = pVertex->next;
		}
		pEdge = pVertex->link;
		while (pEdge)
		{
			if (pEdge->element == ch)
			{
				for (l = 0; l < k; l++)
				{
					if (pEdge->number == temp[l])
					{
						break;
					}
				}
				if (l == k)
				{
					temp[k] = pEdge->number;
					k++;
				}
			}
			pEdge = pEdge->next;
		}
		i++;
	}
	temp[k] = -1;
	return temp;
}
// ����ڽӱ�
void Graph::OutputNFA(CListCtrl *ShowDate)
{
	
	Vertex *p = startVertex;
	Edge *q = new Edge();

	CString s;
	int temp,j;
	while (ShowDate->DeleteColumn(0));
	ShowDate->DeleteAllItems();
	ShowDate->InsertColumn(0, _T("����0"), LVCFMT_CENTER, 60);
	ShowDate->InsertColumn(1, _T("����1"), LVCFMT_CENTER, 60);
	ShowDate->InsertColumn(2, _T("0-1�ı�Ԫ��"), LVCFMT_CENTER, 100);
	ShowDate->InsertColumn(3, _T("����2"), LVCFMT_CENTER, 60);
	ShowDate->InsertColumn(4, _T("0-2�ı�Ԫ��"), LVCFMT_CENTER, 100);
	ShowDate->InsertColumn(5, _T("����3"), LVCFMT_CENTER, 60);
	ShowDate->InsertColumn(6, _T("0-3�ı�Ԫ��"), LVCFMT_CENTER, 100);
	ShowDate->InsertColumn(7, _T("����4"), LVCFMT_CENTER, 60);
	ShowDate->InsertColumn(8, _T("0-4�ı�Ԫ��"), LVCFMT_CENTER, 100);

	for (int i = 0; i < numOfVertices; i++)
	{
		temp = p->number;
		s.Format(_T("%d"), temp);
		ShowDate->InsertItem(i, s);
		q = p->link;
		if (q)
		{
			j = 0;
			while (q)
			{

				s.Format(_T("%d"), q->number);
				ShowDate->SetItemText(i, 1+j, s);
				s.Format(_T("%c"), q->element);
				ShowDate->SetItemText(i, 2+j, s);
				q = q->next;
				j += 2;
			}
		}
		else
		{
			ShowDate->SetItemText(i, 1, L"END");
		}
		p = p->next;
	}
}
