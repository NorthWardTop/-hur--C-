/*
	main.cpp:������
*/

#include "stdafx.h"
int main()
{
	MsgCore msgc1(2);//��Ϣ�˶���
	MsgCore msgc2(3);
	Msg msg1(&msgc1);//��Ϣ�����
	Msg msg2(&msgc2);
	MsgList ls;//��Ϣ�ж�

	ls.push_queue(msg1);//���
	ls.push_queue(msg2);
	ls.show();//��ʾ

	//�õ���Ϣ����������Ϣ�����Ϣ���е�����t
	int a = ls.pop_queue().pMsgc->t;
	cout << "��ֵ:" << a << endl;

	ls.show();

	system("pause");
	return 0;
}