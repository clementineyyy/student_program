#pragma once
#include <easyx.h>

class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget(){}
	int width();
	int height();
	void setFixedSize(int w, int h);
	int x();
	int y();
	void move(int x, int y);
	//�ж�����Ƿ��ڵ�ǰ��ť��
	bool isin();
	//�ж�����Ƿ����˰�ť
	bool isClicked();
	//�麯��
	virtual void show() = 0;
	virtual void event();
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);

protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;

	COLORREF cur_c = RGB(102, 178, 255);
	COLORREF normal_c = RGB(102, 178, 255);
	COLORREF hover_c = RGB(255, 204, 229);
};

