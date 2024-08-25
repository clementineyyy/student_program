#define _CRT_SECURE_NO_WARNINGS
#include "Management.h"
#include "Windows.h"
#include "Table.h"
#include <iostream>

//int main2()
//{
//	auto res = Table::split("3140602001\t郝加薪\t计科一班\t93\t90\t91");
//	for (auto& val : res)
//	{
//		std::cout << val << " ";
//	}
//
//	return 0;
//}

int main()
 {
	Windows w(960,640,EX_SHOWCONSOLE);          //传入窗的宽，高，控制台
	w.setwindowtitle("欢迎来到小型教务管理系统！");

	Management m;
	m.run();

	return w.exec();                           //防闪退
}