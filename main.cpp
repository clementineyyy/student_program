#define _CRT_SECURE_NO_WARNINGS
#include "Management.h"
#include "Windows.h"
#include "Table.h"
#include <iostream>

//int main2()
//{
//	auto res = Table::split("3140602001\t�¼�н\t�ƿ�һ��\t93\t90\t91");
//	for (auto& val : res)
//	{
//		std::cout << val << " ";
//	}
//
//	return 0;
//}

int main()
 {
	Windows w(960,640,EX_SHOWCONSOLE);          //���봰�Ŀ��ߣ�����̨
	w.setwindowtitle("��ӭ����С�ͽ������ϵͳ��");

	Management m;
	m.run();

	return w.exec();                           //������
}