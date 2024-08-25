#include "Windows.h"
#include <iostream>

Windows::Windows(int wide, int high, int flag)
{
    m_handle=::initgraph(wide, high, flag);            //::����ʹ��ȫ�ֱ���,����HWND
    ::setbkmode(TRANSPARENT);
}

void Windows::setwindowtitle(const std::string& title)
{
    ::SetWindowText(m_handle, title.c_str());
}

int Windows::exec()
{
    return getchar();
}

int Windows::width()
{
    return ::getwidth();
}

int Windows::height()
{
    return ::getheight();
}

void Windows::clear()
{
    ::cleardevice();
}

void Windows::beginDraw()
{
    ::BeginBatchDraw();
}

void Windows::flushDraw()
{
    ::FlushBatchDraw();
}

void Windows::endDraw()
{
    ::EndBatchDraw();
}
