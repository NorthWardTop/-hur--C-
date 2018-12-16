/*
	Msg.h:��Ϣ�����Ϣ�������������ʵ��
*/

#pragma once
#ifndef __MSG_H__
#define __MSG_H__

#include "stdafx.h"
#include "Actor.h"
//-------------------------------------------��Ϣ��
class Msg
{
public:
	Msg(){}
	Msg(MsgCore *msgc);//����һ����Ϣ����ָ��
	~Msg();
	Msg& operator=(Msg const& msg)
	{//����Ϣ���ڵ���Ϣ���ĸ�ֵ��this����Ϣ����
		this->pMsgc = msg.pMsgc;
		return *this;
	}
public:
	Act act;//��Ϣ��ִ����
	MsgCore* pMsgc;//��Ϣָ��
	Msg* nextMsg;//��һ����Ϣָ��
};
//*******************************************��Ϣ����ʵ��

Msg::Msg(MsgCore *msgc) 
{
	act = NULL;
	pMsgc = msgc;
	nextMsg = NULL;
}


Msg::~Msg()
{
}


//-------------------------------------------��Ϣ������
class MsgList
{
public://��������
	MsgList();
	~MsgList();
public:
	/*
	��������:�����ڵ�,malloc����ڵ��Լ����ݵĸ�ֵ
	��������: ��Ҫ��ֵ������
	����ֵ:�����Ľڵ�ָ��
	*///����ʹ��
	static Msg* create_node(Msg const& msg);

	/*
	��������:ɾ���ڵ�,��ͷ���ɾ��.
	��������: ����ָ��
	����ֵ:���ʧ�ܷ���NULL,����ɹ������µ�ͷ���.
	Ҳ���ǵ�ǰ�ڵ����һ���ڵ�
	*///����ʹ��
	Msg* MsgList::delete_node();

	//�õ�����ͷ����
	//Msg getFront() const;

	// ��ʼ�� ,�ɹ�����1,ʧ�ܷ���0
	int init();

	// �ж϶����Ƿ�� �ɹ�����1 ʧ�ܷ���0
	int empty() const;

	/*��������:���,�����ݴ��������,
	��������:1:��Ҫ���������
	*/
	void push_queue(Msg const& msg) ;

	/*
	��������:������,�����ݴӶ�����ɾ��,�Ӷ���ͷɾ��
	��������:
	*/
	Msg const pop_queue();

	/*
	��������:��ʾ���ж�������
	��������:
	*/
	void show() const;

	/*
	��������:�鿴����Ԫ��
	��������:
	*/
	Msg const& front_queue() const;

	//��ȡ��Ϣ��Ŀ
	int const& getCount() const;
private:
	Msg* frontMsg;//��Ϣ�б�ͷָ��
	Msg* rearMsg;//��Ϣ�б�βָ��
	int msgCount;//��Ϣ��Ŀ
};
//***************************************MsgList����ʵ��
//----------��������
MsgList::MsgList()
{
	init();
}
MsgList::~MsgList()
{
	Msg msg = front_queue();
	while (msg.nextMsg!=NULL)
	{
		Msg msg = pop_queue();
	}
}

/*
��������:�����ڵ�,malloc����ڵ��Լ����ݵĸ�ֵ
��������: ��Ҫ��ֵ������
����ֵ:�����Ľڵ�ָ��
*/
Msg* MsgList::create_node(Msg const& msg)
{
	Msg* temp = (Msg*)malloc(sizeof(Msg));
	if (temp == NULL)
	{
		printf("�ڵ㴴��ʧ��\n");
		return NULL;
	}
	temp->pMsgc = msg.pMsgc;//����Ϣ�˸�ֵ
	temp->nextMsg = NULL;//��Ϣ���ָ���ÿ�
	temp->act = NULL;
	return temp;//������Ϣ��ָ��
}
/*
��������:ɾ���ڵ�,��ͷ���ɾ��.
��������: ����ָ��
����ֵ:���ʧ�ܷ���NULL,����ɹ������µ�ͷ���.
Ҳ���ǵ�ǰ�ڵ����һ���ڵ�
*///�˺����ڲ�ʹ��
Msg* MsgList::delete_node()
{
	if (msgCount == 0)
	{
		return NULL;
	}
	Msg* temp = frontMsg->nextMsg;//��ʱָ�����
	free(frontMsg);
	return temp;//������ʱָ��(�����µ�����ָ��)
}

// ��ʼ�� �ɹ�����1,ʧ�ܷ���0
int MsgList::init() 
{
	if (msgCount == 0)
	{
		return 0;
	}
	frontMsg = NULL;
	rearMsg = NULL;
	msgCount = 0;
	return 1;
}

// �ж϶����Ƿ�� �շ���1 �ǿշ���0
int MsgList::empty() const
{
	return msgCount == 0;
	//return !que->front&& !que->rear;
}

/*��������:���,�����ݴ��������,
��������: 1:��Ҫ���������
*/
void MsgList::push_queue(Msg const& msg)
{
	//�����ڵ�
	Msg* pnode = create_node(msg);
	if (NULL == pnode)
	{
		return;
	}
	//���β��ָ�벻Ϊ��,��ֱ�Ӱ����ݲ��뵽β��ָ���nextλ��
	if (rearMsg != NULL)
	{
		rearMsg->nextMsg = pnode;
	}
	else
	{
		//���β��rearΪnull˵��������û������.��ͷ����β���ڵ㶼ָ���´����Ľڵ�
		frontMsg = pnode;
	}
	rearMsg = pnode;
	msgCount++;
}

/*
��������:������,�����ݴӶ�����ɾ��,�Ӷ���ͷɾ��
��������:
*/
Msg const MsgList::pop_queue()
{
	Msg data = *frontMsg;//��Ŀǰ����ָ������ݸ�ֵ���ڵ�
	//ɾ���ڵ㷵��ɾ������һ���ڵ�
	Msg* pDel = delete_node();
	//��ͷָ���ƶ�����һ���ڵ�
	frontMsg = pDel;//�µ�����
	msgCount--;
	return data;//����ԭ��������
}

/*
��������:��ʾ���ж�������
��������:
*///�˺���Ϊ���Ժ���
void MsgList::show() const
{
	Msg* p = frontMsg;
	while (p)
	{
		printf("%d -> ", p->pMsgc->t);
		p = p->nextMsg;
	}
	printf("NULL\n");
}

//
//int getFront()
//{
//	if (!que->front)
//	{
//		return 0;
//	}
//	return que->front->data;
//}

/*
��������:�鿴����Ԫ��
��������:1:���е�ַ
*/
Msg const& MsgList::front_queue() const
{
	return *frontMsg;//��������ָ��ָ�������
}

//��ȡ��Ϣ��Ŀ
int const& MsgList::getCount() const
{
	//�������ݲ����� ���Բ�����ֱ����βָ���ȥͷָ��
	//int temp = que->rear - que->front;
	return msgCount;
}


#endif