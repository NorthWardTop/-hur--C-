/*
	MsgCore.h:����ļ�����Ϣ������,
	��Ϣ��ֻ������һ��int t��������,
	��Ҫ��������������޸�operato=()�����͹��캯��,��������
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