#pragma once
#include"Configure.h"

class Windows
{
public:
	Windows(int wide, int high, int flag);       //�����ߣ�����̨
	//���ô��ڱ���
	void setwindowtitle(const std::string& title);
	int exec(); 

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//���������������ж���û����Ϣ
	inline static bool hasMsg()
	{
		return ::peekmessage(&m_msg);
	}

	inline static ExMessage& getMsg()
	{
		return m_msg;
	}

private:
	//���ھ��
	HWND m_handle;
	//��Ϣ
	inline static ExMessage m_msg;
};

