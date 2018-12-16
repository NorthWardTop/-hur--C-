/*
	main.cpp:主函数
*/

#include "stdafx.h"
int main()
{
	MsgCore msgc1(2);//消息核对象
	MsgCore msgc2(3);
	Msg msg1(&msgc1);//消息体对象
	Msg msg2(&msgc2);
	MsgList ls;//消息列队

	ls.push_queue(msg1);//入队
	ls.push_queue(msg2);
	ls.show();//显示

	//得到消息队列列首消息体的消息核中的数据t
	int a = ls.pop_queue().pMsgc->t;
	cout << "首值:" << a << endl;

	ls.show();

	system("pause");
	return 0;
}