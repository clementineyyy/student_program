#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x,y,w,h)
{

}

void LineEdit::show()
{
	//���ð�ť��ɫ
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//�������壬�����˽ṹ��
	LOGFONT f;
	//��ȡ��ǰ��������
	gettextstyle(&f);
	//��������߶�
	f.lfHeight = 40;
	::lstrcpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(RGB(255, 255, 0));
	//��ť�Ͼ�����ʾ����
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(m_x, ty, m_text.c_str());
	//����Լ������Ի���
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
