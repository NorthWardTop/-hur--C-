/*
	MsgCore.h:这个文件是消息本身类,
	消息中只包含了一个int t测试数据,
	需要添加其他数据请修改operato=()函数和构造函数,析构函数
*/

#pragma once
#ifndef __MSGCORE_H__
#define __MSGCORE_H__

#include "stdafx.h"

class MsgCore
{
public:
	MsgCore(int t);
	~MsgCore();
	MsgCore &operator=(MsgCore const& msgc);
public:
	int t;
};

MsgCore::MsgCore(int t) :t(t)
{
}

MsgCore::~MsgCore()
{
	t = 0;
}

MsgCore& MsgCore::operator=(MsgCore const& msgc)
{
	this->t = msgc.t;
	return *this;
}


#endif