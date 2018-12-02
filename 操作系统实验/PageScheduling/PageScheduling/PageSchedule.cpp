#include<iostream>
using namespace std;

class Page          //������Page
{
public:
	Page();
	int creatAddress();
	int getMaxMin();
	int getMaxMemory();
	int getChange();
	int FIFO(int a[], int m, int p[], int count);
	int LRU(int b[], int m, int p[], int count);
	int OPT(int c[], int m, int p[], int count);
	int doPage();
private:
	int d[256];     //���ڴ��ָ���ַ������
	int MaxAddress;  //��ʼ������ַ
	int MinAddress;  //��ʼ����С��ַ
	int PageSize;      //��ʼ��ҳ��Ĵ�С
	int change[256];//���ڴ����ҵ���ʵ�ҳ��˳�������
	int MaxMemory;       //��ʼ���������ҵ���ڴ����
};

Page::Page()          //���캯��
{
	MaxAddress = 0;    //��ʼ������ַ
	MinAddress = 32768;//��ʼ����С��ַ
	PageSize = 1024;     //��ʼ��ҳ��Ĵ�С
	MaxMemory = 1;           //��ʼ���������ҵ���ڴ����
}

int Page::creatAddress()
{
	d[0] = 10000;       //��һ��ָ��ĵ�ַ
	int a, i;
	for (i = 1; i<256; i++)
	{
		a = rand() % 1024 + 1;
		if (a>0 && a<513)
			d[i] = d[i - 1] + 1;
		else
		if (a>512 && a<769)
			d[i] = rand() % (d[i - 1]) + 1;
		else
		if (a>768 && a<1025)
			d[i] = d[i - 1] + 1 + rand() % (32767 - d[i - 1]);
	}

	return 0;
}

int Page::getMaxMin()        //��ø���ҵ��������С��ַ
{
	for (int i = 0; i<256; i++)
	{
		if (MaxAddress<d[i])
			MaxAddress = d[i];
		if (MinAddress>d[i])
			MinAddress = d[i];
	}

	return 1;
}

int Page::getMaxMemory()          //ȷ������ҵ����Ҫ������ڴ����
{
	int H = MaxAddress / PageSize;
	if (MaxAddress%PageSize != 0)
		H++;

	int L = MinAddress / PageSize;
	if (MinAddress%PageSize != 0)
		L++;
	MaxMemory = H - L + 1;
	return MaxMemory;
}

int Page::getChange()       //ȷ������ҵ���ʵ�ҳ�ŵ�˳�򣬶���������ͬ��ҳ�ţ��ϲ�Ϊһ��
{
	int count = 1;
	change[0] = d[0] / PageSize;
	if (d[0] % PageSize != 0)
		change[0]++;
	int j = 1;
	int i;
	for (i = 1; i<256; i++)
	{
		int temp = d[i] / PageSize;
		if (d[i] % PageSize != 0)
			temp++;
		if (temp != change[j - 1])
		{
			change[j] = temp;
			count++;
			j++;
		}
	}

	return count;
}

int Page::FIFO(int a[], int m, int p[], int count)   //����FIFO�㷨
{
	int k = 0;
	int countF = 0;
	int i, j;

	for (j = m; j<count; j++)
	{
		for (i = 0; i<m; i++)
		if (a[i] == p[j])
			break;
		if (i == m)
		{
			a[k] = p[j];
			k = (k + 1) % m;
			countF++;
		}
	}

	return countF;
}

int Page::LRU(int b[], int m, int p[], int count)   //����LRU�㷨
{
	int countL = 0;
	int i, j, ii;
	for (j = m; j<count; j++)
	{
		for (i = 0; i<m; i++)
		if (b[i] == p[j])
			break;
		if (i == m)
		{
			for (ii = 0; ii<m - 1; ii++)
				b[ii] = b[ii + 1];
			b[ii] = p[j];
			countL++;
		}
		else
		{
			int temp = b[i];
			for (ii = i; ii<m - 1; ii++)
				b[ii] = b[ii + 1];
			b[ii] = temp;
		}
	}

	return countL;
}

int Page::OPT(int c[], int m, int p[], int count)  //����OPT�㷨
{
	int countO = 0;
	int i, j, ii, jj;
	for (j = m; j<count; j++)
	{
		for (i = 0; i<m; i++)
		if (c[i] == p[j])
			break;
		if (i == m)
		{
			int mincount = count;
			int outpage;
			int tempcount = 0;

			for (ii = 0; ii<m; ii++)
			{
				for (jj = j; jj<count; jj++)
				if (c[ii] == p[jj])
					tempcount++;
				if (mincount>tempcount)
				{
					mincount = tempcount;
					outpage = c[ii];
					tempcount = 0;
				}
				tempcount = 0;
			}

			for (ii = 0; ii<m; ii++)
			if (c[ii] == outpage)
				break;
			c[ii] = p[j];
			countO++;
		}
	}

	return countO;
}

int Page::doPage()
{
	creatAddress();

	cout << "1. ���е���ҵ����256��ָ���ַ��ΧΪ[0��32767]" << endl;
	cout << "2. �ɹ�ѡ���ҳ���СΪ��1k��2k��4k��8k��16k" << endl;
	cout << "3. ���������������磺2" << endl << endl;

	cout << "��������ѡ���ҳ���С��";
	cin >> PageSize;
	PageSize *= 1024;

	int count = getChange();
	cout << endl << "����ҵ����Ҫ���ʵ�ҳ�ŵ������ǣ�" << count << endl << endl;

	int *pFIFO = new int[count];
	int *pLRU = new int[count];
	int *pOPT = new int[count];
	int i;
	for (i = 0; i<count; i++)
		pFIFO[i] = pLRU[i] = pOPT[i] = change[i];
	getMaxMin();
	int M = getMaxMemory();
	int m;

	cout << "����ҵ��������ڴ����Ϊ��" << M << endl << endl;
	cout << "�����������[1," << M << "]�ĸ�������Ϊ���������ҵ���ڴ���������:" << endl;

	for (m = 1; m <= M; m++)
	{
		int *a = new int[m];
		int *b = new int[m];
		int *c = new int[m];
		a[0] = b[0] = c[0] = change[0];
		int j, ii;
		for (i = 1; i<m; i++)
		{
			for (j = i; j<count; j++)
			{
				for (ii = 0; ii<i; ii++)
				if (a[ii] == change[j])
					break;
				if (ii == i)
				{
					a[i] = b[i] = c[i] = change[j];
					break;
				}
			}
			if (j == count)
				break;
		}

		int CountF = FIFO(a, m, pFIFO, count);
		int CountL = LRU(b, m, pLRU, count);
		int CountO = OPT(c, m, pOPT, count);
		delete a;
		delete b;
		delete c;

		cout << "1.ҳ���С��" << PageSize / 1024 << "k" << endl;
		cout << "2.�����������ڴ������" << m << endl;
		cout << "3.ȱҳ�ʣ�" << endl;
		cout << "  ��1��OPT�㷨��ȱҳ�ʣ� " << CountO / (float)count << endl;
		cout << "  ��2��FIFO�㷨��ȱҳ�ʣ�" << CountF / (float)count << endl;
		cout << "  ��3��LRU�㷨��ȱҳ��Ϊ��" << CountL / (float)count << endl;
		cout << endl;
	}

	return 0;
}
int main()
{
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "            ģ�����ϵͳ��ҳ���û���OPT��FIFO��LRU�㷨��                  " << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	Page p;
	p.doPage();
	system("pause");
	return 0;
}
