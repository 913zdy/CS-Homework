#pragma once

// ��ʽջ���ǰ�Ӷ���
template <class T>
class LinkedStack;

// ������ʽջ�����
template <class T>
class StackNode
{
	friend class LinkedStack<T>;
private:
	T data;
	StackNode<T> *next;
	StackNode(T item = 0, StackNode<T> *p = NULL)
	{
		data = item;
		next = p;
	}
};

// ������ʽջ��
template <class T>
class LinkedStack
{
private:
	StackNode<T> *top;
public:
	LinkedStack();
	~LinkedStack();
	bool IsEmpty(void) const;
	int Length(void) const;
	void Push(const T &item);
	T Pop(void);
	T GetTop(void);
	void Clear(void);
};
// ���캯��
template <class T>
LinkedStack<T>::LinkedStack()
{
	top = NULL;
}
// ��������
template <class T>
LinkedStack<T>::~LinkedStack()
{
	Clear();
}
// �ж�ջ�Ƿ�Ϊ��
template <class T>
bool LinkedStack<T>::IsEmpty(void) const
{
	return (!top);
}
// ��ȡ���еĳ���
template <class T>
int LinkedStack<T>::Length(void) const
{
	StackNode<T> *temp = new StackNode<T>();
	temp = top;
	int length = 0;
	while (temp)
	{
		temp = temp->next;
		length++;
	}
	return length;
}
// ѹ������(��ջ)
template <class T>
void LinkedStack<T>::Push(const T &item)
{
	top = new StackNode<T>(item, top);
}
// �������(��ջ)
template <class T>
T LinkedStack<T>::Pop(void)
{
	if (!IsEmpty())
	{
		StackNode<T> *temp = top;
		top = top->next;
		T value = temp->data;
		delete temp;
		return value;
	}
}
// ��ȡջͷ����
template <class T>
T LinkedStack<T>::GetTop(void)
{
	if (!IsEmpty())
	{
		return top->data;
	}
}
// ����ջΪ��ջ
template <class T>
void LinkedStack<T>::Clear(void)
{
	StackNode<T> *temp = new StackNode<T>();
	while (top)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}