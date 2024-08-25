#include "PushButton.h"
#include "Windows.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{

}

void PushButton::show()
{
	//设置按钮颜色
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//设置字体，定义了结构体
	LOGFONT f;
	//获取当前字体设置
	gettextstyle(&f);
	//设置字体高度
	f.lfHeight = 40;
	::lstrcpy(f.lfFaceName,_T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(RGB(255, 255, 0));
	//按钮上居中显示文字
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

void PushButton::show2()
{
	//设置按钮颜色
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextstyle(40, 15, "黑体");
	//按钮上居中显示文字
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

