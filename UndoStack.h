#pragma once

//
// ���CImageָ���ջ
//

#include "afxwin.h"

#define MAX_UNDO_NUMBER 10

typedef CImage* ElementType;

class CUndoStack
{

public:
	CUndoStack();
	~CUndoStack();

	int IsEmpty();											//�ж�Ϊ��
	int IsFull();											//�ж�Ϊ��
	void Push(ElementType X);								//��ջ����
	void Pop();												//��ջ����
	ElementType Top();										//ջ��Ԫ��

	int                                   m_nCapacity;       //����
	int                                m_nSizeOfStack;       //��С
	int                                 m_nTopOfStack;       //ջ��
	int                              m_nBottomOfStack;       //ջ��
	ElementType              m_Array[MAX_UNDO_NUMBER];       //Ԫ��
};