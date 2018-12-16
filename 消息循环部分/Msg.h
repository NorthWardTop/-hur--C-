/*
	Msg.h:消息体和消息队列类的声明和实现
*/

#pragma once
#ifndef __MSG_H__
#define __MSG_H__

#include "stdafx.h"
#include "Actor.h"
//-------------------------------------------消息体
class Msg
{
public:
	Msg(){}
	Msg(MsgCore *msgc);//传入一个消息对象指针
	~Msg();
	Msg& operator=(Msg const& msg)
	{//将消息体内的消息核心赋值给this的消息核心
		this->pMsgc = msg.pMsgc;
		return *this;
	}
public:
	Act act;//消息的执行者
	MsgCore* pMsgc;//消息指针
	Msg* nextMsg;//下一个消息指针
};
//*******************************************消息函数实现

Msg::Msg(MsgCore *msgc) 
{
	act = NULL;
	pMsgc = msgc;
	nextMsg = NULL;
}


Msg::~Msg()
{
}


//-------------------------------------------消息队列类
class MsgList
{
public://构造析构
	MsgList();
	~MsgList();
public:
	/*
	函数功能:创建节点,malloc申请节点以及数据的赋值
	函数参数: 需要赋值的数据
	返回值:创建的节点指针
	*///类内使用
	static Msg* create_node(Msg const& msg);

	/*
	函数作用:删除节点,把头结点删除.
	函数参数: 队列指针
	返回值:如果失败返回NULL,如果成功返回新的头结点.
	也就是当前节点的下一个节点
	*///类内使用
	Msg* MsgList::delete_node();

	//得到队列头数据
	//Msg getFront() const;

	// 初始化 ,成功返回1,失败返回0
	int init();

	// 判断队列是否空 成功返回1 失败返回0
	int empty() const;

	/*函数功能:入队,把数据存入队列中,
	函数参数:1:需要插入的数据
	*/
	void push_queue(Msg const& msg) ;

	/*
	函数功能:出队列,把数据从队列中删除,从队列头删除
	函数参数:
	*/
	Msg const pop_queue();

	/*
	函数功能:显示所有队列数据
	函数参数:
	*/
	void show() const;

	/*
	函数功能:查看队首元素
	函数参数:
	*/
	Msg const& front_queue() const;

	//获取消息数目
	int const& getCount() const;
private:
	Msg* frontMsg;//消息列表头指针
	Msg* rearMsg;//消息列表尾指针
	int msgCount;//消息数目
};
//***************************************MsgList函数实现
//----------构造析构
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
函数功能:创建节点,malloc申请节点以及数据的赋值
函数参数: 需要赋值的数据
返回值:创建的节点指针
*/
Msg* MsgList::create_node(Msg const& msg)
{
	Msg* temp = (Msg*)malloc(sizeof(Msg));
	if (temp == NULL)
	{
		printf("节点创建失败\n");
		return NULL;
	}
	temp->pMsgc = msg.pMsgc;//将消息核赋值
	temp->nextMsg = NULL;//消息体后指针置空
	temp->act = NULL;
	return temp;//返回消息体指针
}
/*
函数作用:删除节点,把头结点删除.
函数参数: 队列指针
返回值:如果失败返回NULL,如果成功返回新的头结点.
也就是当前节点的下一个节点
*///此函数内部使用
Msg* MsgList::delete_node()
{
	if (msgCount == 0)
	{
		return NULL;
	}
	Msg* temp = frontMsg->nextMsg;//临时指针后移
	free(frontMsg);
	return temp;//返回临时指针(将是新的列首指针)
}

// 初始化 成功返回1,失败返回0
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

// 判断队列是否空 空返回1 非空返回0
int MsgList::empty() const
{
	return msgCount == 0;
	//return !que->front&& !que->rear;
}

/*函数功能:入队,把数据存入队列中,
函数参数: 1:需要插入的数据
*/
void MsgList::push_queue(Msg const& msg)
{
	//创建节点
	Msg* pnode = create_node(msg);
	if (NULL == pnode)
	{
		return;
	}
	//如果尾部指针不为空,则直接把数据插入到尾部指针的next位置
	if (rearMsg != NULL)
	{
		rearMsg->nextMsg = pnode;
	}
	else
	{
		//如果尾部rear为null说明队列中没有数据.让头结点和尾部节点都指向新创建的节点
		frontMsg = pnode;
	}
	rearMsg = pnode;
	msgCount++;
}

/*
函数功能:出队列,把数据从队列中删除,从队列头删除
函数参数:
*/
Msg const MsgList::pop_queue()
{
	Msg data = *frontMsg;//将目前列首指向的内容赋值给节点
	//删除节点返回删除的下一个节点
	Msg* pDel = delete_node();
	//把头指针移动到下一个节点
	frontMsg = pDel;//新的列首
	msgCount--;
	return data;//返回原列首数据
}

/*
函数功能:显示所有队列数据
函数参数:
*///此函数为测试函数
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
函数功能:查看队首元素
函数参数:1:队列地址
*/
Msg const& MsgList::front_queue() const
{
	return *frontMsg;//返回列首指针指向的内容
}

//获取消息数目
int const& MsgList::getCount() const
{
	//由于数据不连续 所以不可以直接用尾指针减去头指针
	//int temp = que->rear - que->front;
	return msgCount;
}


#endif