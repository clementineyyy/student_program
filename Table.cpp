#include "Table.h"
#include <iostream>
using namespace std;

Table::Table(int row, int col)
	:BasicWidget(0,0,0,0),m_rows(row),m_cols(col),m_curPage(0),m_maxPage(0),m_extraData(0)
{
	m_prevBtn = new PushButton("上一页");
	m_nextBtn = new PushButton("下一页");
	m_firstBtn = new PushButton("第一页");
	m_lastBtn = new PushButton("结尾页");
}

Table::~Table()
{
	delete m_prevBtn;
	delete m_nextBtn;
	delete m_firstBtn;
	delete m_lastBtn;
}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::setHeader(const std::string& header)
{
	m_header = header;
	//std::cout << "header" << header << std::endl;
	m_cols = std::count(m_header.begin(), m_header.end(), '\t') / 2 + 2;
	//std::cout << m_cols << std::endl;
	//6
	m_tw = ::textwidth("3140602001");
	m_th = ::textheight(m_header.c_str());
	//求出文字的宽度和高度
	m_gridW = m_tw + 50;
	m_gridH = m_th + 10;
	m_w = m_gridW * m_cols;
	m_h = m_gridH * (m_rows + 1);
}

void Table::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();
}

void Table::show()
{
	drawTableGrid();
	drawHeader();
	drawTableData();
}

void Table::drawTableGrid()
{
	//画横线
	setlinecolor(BLACK);
	for (size_t i = 0; i < m_rows + 1; i++)
	{
		line(m_x, m_y + i * m_gridH, m_x + m_cols * m_gridW, m_y + i * m_gridH);
	}
	//画竖线
	for (size_t i = 0; i < m_cols + 1; i++)
	{
		line(m_x + i * m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	if (m_maxPage > 0)
	{
		drawButton();
	}
}

void Table::drawButton()
{
	static bool flag = false;
	if (!flag)
	{
		m_prevBtn->move(100 + m_x, m_h + 80);
		m_nextBtn->move(m_prevBtn->x() + m_prevBtn->width(), m_prevBtn->y());
		m_firstBtn->move(m_nextBtn->x() + m_nextBtn->width(), m_nextBtn->y());
		m_lastBtn->move(m_firstBtn->x() + m_firstBtn->width(), m_firstBtn->y());
		flag = true;
	}

	m_prevBtn->show2();
	m_nextBtn->show2();
	m_firstBtn->show2();
	m_lastBtn->show2();


	settextcolor(BLACK);
	char str[30] = { 0 };
	sprintf_s(str, "第%d页/共%d页", m_curPage + 1, m_maxPage + 1);
	outtextxy(m_lastBtn->x() + m_lastBtn->width() + 100, m_lastBtn->y(), str);
}

void Table::drawTableData()
{
	//行
	settextcolor(BLACK);
	settextstyle(20, 10, "黑体");
	if (m_datas.size() == 0)
		return;
	//数据开始的位置
	int begPos = m_curPage * m_rows;
	//int begPos = 0;
	//数据结束的位置
	//int endPos = m_datas.size();
	int endPos = m_curPage * m_rows + m_rows;
	//防止越界
	if (m_curPage == m_maxPage)
	{
		endPos = begPos + m_extraData;
	}
	for (size_t i = begPos,r=0; i < endPos; i++,r++)
	{
		const auto& line_data = split(m_datas[i]);
		//列
		for (size_t k = 0; k < line_data.size(); k++)
		{
			int tx = m_x + k * m_gridW + (m_gridW - ::textwidth(line_data[k].c_str())) / 2;
			int ty = m_y + r * m_gridH + 10;
			outtextxy(tx, ty, line_data[k].c_str());
		}
	}
}

void Table::drawHeader()
{
	::rectangle(m_x, m_y - 30, m_x + m_w, m_y);
	for (size_t i = 0; i < m_cols; i++)
	{
		line(m_x + i * m_gridW, m_y - 30, m_x + i * m_gridW, m_y);
	}
	//分隔表头数据
	auto headers = split(m_header);
	/*std::cout << headers.size() << std::endl;
	for (size_t i = 0; i < headers.size(); i++)
	{
		std::cout << headers[i] << std::endl;
	}*/
	int i = 0;
	for (size_t j=0; j < headers.size();j++)
	{
		if (j == 0 || j == 3 || j == 5 || j == 7 || j == 8 || j == 9)
		{
			int spaceH = (m_gridW - ::textwidth(headers[j].c_str())) / 2;
			int spaceV = (30 - ::textheight(headers[j].c_str())) / 2;
			settextstyle(25, 10, "黑体");
			settextcolor(BLACK);
			if (j == 0)
			{
				outtextxy(m_x + i * m_gridW + spaceH, m_y - m_gridH + spaceV+8, headers[j].c_str());
			}
			else
			{
				outtextxy(m_x + i * m_gridW + spaceH, m_y - m_gridH + spaceV, headers[j].c_str());
			}
			i++;
		}
	}
}

std::vector<std::string> Table::split(std::string str, char separator)
{
	std::vector<std::string> res;
	for (size_t pos = 0; pos != std::string::npos;)
	{
		//查找指定分割字符的位置
		pos = str.find(separator);
		//取出字符串
		res.push_back(str.substr(0, pos));
	    //把剩下的字符串保存到str
		str = std::string(str.c_str() + pos + 1);
	}
	return res;
}

void Table::updatePage()
{
	if (m_rows == 0 && !m_datas.empty())
	{
		m_rows = m_datas.size();
	}
	if (m_cols == 0 && !m_datas.size())
	{
		m_cols = m_datas.front().find("\t") + 1;
	}
	if (m_rows >= m_datas.size())
	{
		m_maxPage = 0;
		m_extraData = m_datas.size();
	}
	else
	{
		m_maxPage = m_datas.size() / m_rows;
		m_extraData = m_datas.size() % m_rows;
	}
}

void Table::event()
{
	BasicWidget::event();
	m_prevBtn->event();
	m_nextBtn->event();
	m_firstBtn->event();
	m_lastBtn->event();

	if (m_prevBtn->isClicked())
	{
		if (m_curPage != 0)
		{
			m_curPage--;
		}
	}
	if (m_nextBtn->isClicked())
	{
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_firstBtn->isClicked())
	{
		m_curPage = 0;
	}
	if (m_lastBtn->isClicked())
	{
		m_curPage = m_maxPage;
	}
}
