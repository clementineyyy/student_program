#include "PushButton.h"
#include "Windows.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{

}

void PushButton::show()
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
	::lstrcpy(f.lfFaceName,_T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(RGB(255, 255, 0));
	//��ť�Ͼ�����ʾ����
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

void PushButton::show2()
{
	//���ð�ť��ɫ
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextstyle(40, 15, "����");
	//��ť�Ͼ�����ʾ����
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

