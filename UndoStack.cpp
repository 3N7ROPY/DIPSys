#include "stdafx.h"
#include "UndoStack.h"

// ջ��ʼ��
CUndoStack::CUndoStack()
{
	m_nCapacity = MAX_UNDO_NUMBER;
	for (int i = 0; i<m_nCapacity; i++)
	{
		m_Array[i] = NULL;
	}
	m_nSizeOfStack = 0;
	m_nTopOfStack = -1;
	m_nBottomOfStack = 0;
}

// ��ջ�ݻ�
CUndoStack::~CUndoStack()
{
	while (m_nSizeOfStack>0) Pop();
	m_nTopOfStack = -1;
}

// �ж�Ϊ��
int CUndoStack::IsEmpty()
{
	return m_nSizeOfStack == 0;
}

// �ж�Ϊ��
int CUndoStack::IsFull()
{
	return m_nSizeOfStack == m_nCapacity;
}

// ��ջ���������ǿ��Խ���
void CUndoStack::Push(ElementType X)
{
	m_nTopOfStack++;
	m_nSizeOfStack++;
	if (m_nSizeOfStack<=m_nCapacity)
	{//δ��
		m_Array[m_nTopOfStack] = X;
	}
	else
	{//����
		if (m_nTopOfStack == m_nCapacity)
		{
			m_nTopOfStack = 0;
		}
		m_nSizeOfStack = m_nCapacity;
		ElementType TempCell = m_Array[m_nBottomOfStack];
		m_nBottomOfStack++;
		if (m_nBottomOfStack == m_nCapacity)
		{
			m_nBottomOfStack = 0;
		}
		m_Array[m_nTopOfStack] = X;
		if (TempCell != NULL)
			delete TempCell;
	}
}

// ��ջ������ջ�����ڼ�С
void CUndoStack::Pop()
{
	if (IsEmpty())
	{
		AfxMessageBox(_T("Empty stack!"));
		return;
	}
	if (m_Array[m_nTopOfStack] != NULL)
		delete m_Array[m_nTopOfStack];
	m_nTopOfStack--;
	if (m_nTopOfStack == -1)
	{
		m_nTopOfStack = m_nCapacity-1;
	}
	m_nSizeOfStack--;
}

// ȡ��ջ��Ԫ��
ElementType CUndoStack::Top()
{
	if(!IsEmpty())
	{
		ElementType top =  m_Array[m_nTopOfStack];
		m_nTopOfStack--;
		if (m_nTopOfStack == -1)
		{
			m_nTopOfStack = m_nCapacity-1;
		}
		m_nSizeOfStack--;
		return top;
	}
	AfxMessageBox(_T("Empty stack!"));
	return NULL;
}