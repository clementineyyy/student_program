#pragma once
#include"Configure.h"

class Windows
{
public:
	Windows(int wide, int high, int flag);       //窗宽，高，控制台
	//设置窗口标题
	void setwindowtitle(const std::string& title);
	int exec(); 

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//按键和鼠标操作：判断有没有消息
	inline static bool hasMsg()
	{
		return ::peekmessage(&m_msg);
	}

	inline static ExMessage& getMsg()
	{
		return m_msg;
	}

private:
	//窗口句柄
	HWND m_handle;
	//消息
	inline static ExMessage m_msg;
};

