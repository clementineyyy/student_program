#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x,y,w,h)
{

}

void LineEdit::show()
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
	::lstrcpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(RGB(255, 255, 0));
	//按钮上居中显示文字
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(m_x, ty, m_text.c_str());
	//点击自己弹出对话框
	if (isClicked())
	{
		char buf[128];
		InputBox(buf, 128, m_hitText.data(), m_title.data());
		if (buf[0] != '\0')
			m_text = buf;
	}
}

bool LineEdit::textChanged()
{
	if (m_text.empty())
		return false;
	if (m_prevText == m_text)
	{
		return false;
	}
	m_prevText = m_text;
	return true;
}
