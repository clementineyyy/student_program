#include "Management.h"
#include "Student.h"
#include "Table.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <vector>

using namespace std;

Management::Management()
{
	readFile("studentinfo.txt");
	::loadimage(&m_bk, "OIP-C.jpg", Windows::width(), Windows::height());
	::settextstyle(20, 0, "����");
	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("��ʾ����ѧ��"));
	menu_btns.emplace_back(new PushButton("���ѧ��"));
	menu_btns.emplace_back(new PushButton("ɾ��ѧ��"));
	menu_btns.emplace_back(new PushButton("�޸�ѧ��"));
	menu_btns.emplace_back(new PushButton("��ѯѧ��"));
	menu_btns.emplace_back(new PushButton("�ɼ�ͳ��"));
	menu_btns.emplace_back(new PushButton("ѧ������"));
	menu_btns.emplace_back(new PushButton("�˳�ϵͳ"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		//�����޸�/�趨��ť��С
		menu_btns[i]->setFixedSize(300, 70);
		int bx = (Windows::width() - menu_btns[i]->width()) / 2;
		int vspace = (Windows::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}

	//��ʼ���鿴ѧ���ı��
	m_showTable.reset(new Table);
	m_showTable->setRowCount(12);
	m_showTable->setHeader(m_header);
	updateShowTable();

	//������
	m_showTable->move((Windows::width() - m_showTable->width()) / 2, 80);

	//���ѧ��
	m_addBtn.reset(new PushButton("���", 670, 260, 80, 40));
	m_addEdit.reset(new LineEdit(150, 260, 500, 40));
	m_addEdit->setTitle("������ѧ����Ϣ");
	m_addEdit->setHitText("�밴��\n<ѧ�� ���� �༶ �ߵ���ѧ ���ݽṹ ��ѧӢ��>\n��ʽ����ѧ����Ϣ");

	//����ѧ��ɾ��ѧ��
	m_delBtn.reset(new PushButton("ɾ��", 670, 260, 80, 40));
	m_delEdit.reset(new LineEdit(150, 260, 500, 40));
	m_delEdit->setTitle("������ɾ��ѧ��ѧ��");
	m_delEdit->setHitText("������ɾ��ѧ��ѧ��");
	m_delTable.reset(new Table);
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x() - 120, m_delEdit->y() + 120);
	m_delTable->setRowCount(1);

	//�޸�ѧ����Ϣ
	m_modifyEdit.reset(new LineEdit(150, 260, 500, 40));
	m_modifyEdit->move((Windows::width() - m_modifyEdit->width()) / 2, 260);
	//int x = (Windows::width() - 100 * 6) / 2;
	for (int i = 0; i < 6; i++)
	{
		m_stuEdits.emplace_back(new LineEdit);
		m_stuEdits[i]->setFixedSize(150, 40);
		m_stuEdits[i]->move(i * m_stuEdits[i]->width() + 20, m_modifyEdit->y() + 50);
	}
	m_modifyIt = vec_stu.end();

	//��ѯ����������ѯ�Ͱ�ѧ�Ų�ѯ
	m_numberEdit.reset(new LineEdit(150, 260, 300, 40));
	m_numberEdit->move(75, 260);
	m_nameEdit.reset(new LineEdit(150, 260, 300, 40));
	m_nameEdit->move(600, 260);
	m_numberTable.reset(new Table);
	m_numberTable->setHeader(m_header);
	m_numberTable->move(m_numberEdit->x() - 120, m_numberEdit->y() + 120);
	m_numberTable->setRowCount(1);
	m_nameTable.reset(new Table);
	m_nameTable->setHeader(m_header);
	m_nameTable->move(m_nameEdit->x() - 120, m_nameEdit->y() + 120);
	m_nameTable->setRowCount(1);
	m_numberBtn.reset(new PushButton("��ѧ�Ų�ѯ", 125, 400, 180, 40));
	m_nameBtn.reset(new PushButton("��������ѯ", 650, 400, 180, 40));

	//�ɼ�ͳ��
	m_subjectEdit.reset(new LineEdit(150, 260, 300, 40));
	m_subjectEdit->move((Windows::width() - textwidth("�������ѯ�Ŀ�Ŀ�ͷ�����")) / 2 - 25, 40);
	m_subjectEdit->setTitle("�������Ŀ�Ͳ�ѯ�ķ�����");
	m_subjectEdit->setHitText("�밴��\n<��Ŀ ��ͷ� ��߷�>\n��ʽ������Ϣ");
	m_stuTable.reset(new Table);
	m_stuTable->setHeader(m_header);
	m_stuTable->move(m_subjectEdit->x() - 300, m_subjectEdit->y() + 100);
	m_stuTable->setRowCount(12);
	m_searchBtn.reset(new PushButton("ͳ��", 400, 580, 180, 40));

	//����
	m_sortEdit.reset(new LineEdit(150, 260, 300, 40));
	m_sortEdit->move((Windows::width() - textwidth("�������ѯ�Ŀ�Ŀ")) / 2 - 50, 300);
	m_sortEdit->setTitle("����������Ŀ�Ŀ");
	m_sortEdit->setHitText("����������Ŀ�Ŀ");
	m_sortTable.reset(new Table);
	m_sortTable->setHeader(m_header);
	m_sortTable->move(m_subjectEdit->x() - 300, m_subjectEdit->y() + 100);
	m_sortTable->setRowCount(12);
}

void Management::run()
{
	//��ȡ�˵��ķ���ֵ��֪��ִ���ĸ�����
	m_op = Menu;
	Windows::beginDraw();
	while (true)
	{
		Windows::clear();
		drawBackground();
		if (Windows::hasMsg())
		{
			switch (Windows::getMsg().message)
			{
			case WM_KEYDOWN:
				//���°���
				//Ҫ�۽�С�ͽ������ϵͳ���ڣ���ESC�˳�����������������
				if (Windows::getMsg().vkcode == VK_ESCAPE)
				{
					m_op = Menu;
				}
				break;
			default:
				//������
				eventLoop();
				break;
			}
		}
		switch (m_op)
		{
		case Menu:
			m_op = menu();
			break;
		case Management::Show:
			//����0
			showinfo();
			break;
		case Management::Insert:
			//����1
			add();
			break;
		case Management::Delete:
			//����2
			del();
			break;
		case Management::Modify:
			//����3
			modify();
			break;
		case Management::Search:
			//����4
			search();
			break;
		case Management::Rate:
			//����5
			rate();
			break;
		case Management::Sort:
			//����6
			sort();
			break;
		case Management::Exit:
			//�˳�ϵͳ
			saveFile("test.txt");
			exit(666);
			break;
		default:
			break;
		}
		Windows::flushDraw();
		Windows::getMsg().message = 0;
	}
	Windows::endDraw();
}

int Management::menu()
{
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return Menu;
}

void Management::showinfo()
{
	m_showTable->show();
	::settextstyle(20, 0, "����");
}

void Management::add()
{
	settextstyle(40, 15, "����");
	settextcolor(BLACK);
	const char* title = "������ѧ����Ϣ<ѧ�� ���� �༶ �ߵ���ѧ ���ݽṹ ��ѧӢ��>";
	outtextxy((Windows::width()-textwidth(title))/2, 150, title);
	m_addBtn->show();
	m_addEdit->show();
	auto str = m_addEdit->text();
	if (m_addBtn->isClicked()&&!str.empty())
	{
		vec_stu.push_back(Student::fromSting(str));
		std::replace(str.begin(), str.end(), ' ', '\t');
		m_showTable->insertData(str);
		//����ӵ���Ϣд���ļ�
		FILE* fp;
		errno_t err= fopen_s(&fp,"studentinfo.txt","a+");
		if (err==0)
		{
			fputc('\n', fp);
			fputs(str.c_str(), fp);
		}
		fclose(fp);
		m_addEdit->clear();
	}
	::settextstyle(20, 0, "����");
}

void Management::del()
{
	settextstyle(40, 15, "����");
	settextcolor(BLACK);
	const char* title = "������Ҫɾ����ѧ����ѧ��";
	outtextxy((Windows::width() - textwidth(title)) / 2, 150, title);
	m_delBtn->show();
	m_delEdit->show();
	if (m_delTable->rowCount() != 0)
		m_delTable->show();
	auto& str = m_delEdit->text();
	while (m_delEdit->textChanged())
	{
		m_delEdit->setTitle("������ɾ��ѧ��ѧ��");
		m_delEdit->setHitText("������ɾ��ѧ��ѧ��");
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {return std::to_string(stu.number) == str; });
		if (it == vec_stu.end())
		{
			std::string s = "�Բ���û���ҵ�ѧ��Ϊ" + str + "��ѧ����Ϣ,����������";
			m_delEdit->setTitle("ɾ��ʧ�ܣ�");
			m_delEdit->setHitText(s);
			//ɾ��֮�������������Żᵯ����ʾ����Ҫ���ɾ����ť�����������ظ�����
			auto& str = m_delEdit->text();
			continue;
		}
		else
		{
			m_delTable->insertData(it->formatInfo());
		}
	}
	if (m_delBtn->isClicked())
	{
		auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {return std::to_string(stu.number) == str; });
		if (it != vec_stu.end())
		{
			m_delEdit->clear();
			m_delTable->clear();
		}
		vec_stu.erase(it, vec_stu.end());
		updateShowTable();
		m_op = Menu;
	}
	::settextstyle(20, 0, "����");
}

void Management::modify()
{
	settextstyle(40, 15, "����");
	settextcolor(BLACK);
	const char* title = "������Ҫ�޸ĵ�ѧ����ѧ��";
	outtextxy((Windows::width() - textwidth(title)) / 2, 150, title);
	m_modifyEdit->show();
	if (isFind)
	{
		for (auto& e : m_stuEdits)
		{
			e->show();
		}
	}
	if (m_modifyEdit->textChanged())
	{
		auto& str = m_modifyEdit->text();
		std::stringstream ss(str);
		uint32 number;
		ss >> number;
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
		{
			return stu.number == number;
		});
		if (it == vec_stu.end())
		{
			m_modifyIt = vec_stu.end();
			isFind = false;
		}
		else
		{
			m_stuEdits[0]->setText(std::to_string(it->number));
			m_stuEdits[1]->setText(it->name);
			m_stuEdits[2]->setText(it->grade);
			m_stuEdits[3]->setText(std::to_string(it->math));
			m_stuEdits[4]->setText(std::to_string(it->datastructure));
			m_stuEdits[5]->setText(std::to_string(it->english));

			isFind = true;
			m_modifyIt = it;
		}
	}
	if (isFind&& m_modifyIt != vec_stu.end())
	{
		for (int i = 0; i < 6; i++)
		{
			if (m_stuEdits[i]->textChanged())
			{
				switch (i)
				{
				case 0:
					m_modifyIt->number = atoi(m_stuEdits[i]->text().data());
					break;
				case 1:
					m_modifyIt->name = m_stuEdits[i]->text().data();
					break;
				case 2:
					m_modifyIt->grade = m_stuEdits[i]->text().data();
					break;
				case 3:
					m_modifyIt->math = atoi(m_stuEdits[i]->text().data());
					break;
				case 4:
					m_modifyIt->datastructure = atoi(m_stuEdits[i]->text().data());
					break;
				case 5:
					m_modifyIt->english = atoi(m_stuEdits[i]->text().data());
					break;
				default:
					break;
				}
				updateShowTable();
			}
		}
	}
	::settextstyle(20, 0, "����");
	//�޸��갴ESC����showinfo�鿴����
}

void Management::search()
{
	settextstyle(40, 15, "����");
	settextcolor(BLACK);
	const char* title = "��ѡ��ѧ�Ų�ѯ���ǰ�������ѯ";
	outtextxy((Windows::width() - textwidth(title)) / 2, 150, title);
	m_numberEdit->show();
	m_nameEdit->show();
	m_numberBtn->show2();
	m_nameBtn->show2();
	settextcolor(BLACK);
	//��ѧ�Ų���
	if (m_numberTable->rowCount() != 0)
	{
		m_numberTable->show();
		m_numberTable->move(50, 500);
	}
	if (m_numberEdit->textChanged())
	{
		auto& str = m_numberEdit->text();
		std::stringstream ss(str);
		uint32 number;
		ss >> number;
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
			{
				return stu.number == number;
			});
		if (it == vec_stu.end())
		{
			isFind = false;
			std::string s = "û���ҵ���λѧ��������������������ѧ�ţ�";
			//outtextxy((Windows::width() - textwidth(title)) / 2, 150, "û���ҵ���λѧ����");
			m_numberEdit->setTitle("��ѯʧ�ܣ�");
			m_numberEdit->setHitText(s);
			//��ʱ���ǵ���༭������ǰ�ť,������ѯʧ����ʾ����
			//
		}
		else
		{
			isFind = true;
			m_numberTable->insertData(it->formatInfo());
			//��ѯ�ɹ���ֱ��չʾ��񣬵��ǲ�����Ҫ��������İ�ť�����¼
		}
	}
	if (m_numberBtn->isClicked())
	{
		//cout << "ok" << endl;
		m_numberEdit->clear();
		m_numberTable->clear();
	}
	//����������
	if (m_nameTable->rowCount() != 0)
	{
		m_nameTable->show();
		m_nameTable->move(50, 500);
	}
	if (m_nameEdit->textChanged())
	{
		auto& str = m_nameEdit->text();
		std::stringstream ss(str);
		std::string name;
		ss >> name;
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
			{
				return stu.name == name;
			});
		if (it == vec_stu.end())
		{
			isFind = false;
			std::string s = "û���ҵ���λѧ��������������������������";
			m_nameEdit->setTitle("��ѯʧ�ܣ�");
			m_nameEdit->setHitText(s);
			//��ʱ���ǵ���༭������ǰ�ť,������ѯʧ����ʾ����
		}
		else
		{
			//cout << "yes" << endl;
			isFind = true;
			m_nameTable->insertData(it->formatInfo());
			//��ѯ�ɹ���ֱ��չʾ��񣬵��ǲ�����Ҫ��������İ�ť�����¼
		}
	}
	if (m_nameBtn->isClicked())
	{
		m_nameEdit->clear();
		m_nameTable->clear();
	}

	::settextstyle(20, 0, "����");
}

void Management::rate()
{
	//�ɼ�ͳ��
	settextstyle(40, 15, "����");
	settextcolor(BLACK);
	const char* title = "�������ѯ�Ŀ�Ŀ�ͷ�����";
	outtextxy((Windows::width() - textwidth(title)) / 2, 0, title);
	m_subjectEdit->show();
	m_searchBtn->show2();
	settextcolor(BLACK);
	if (m_stuTable->rowCount() != 0)
	{
		m_stuTable->show();
	}
	auto str = m_subjectEdit->text();
	if (m_subjectEdit->textChanged())
	{
		std::replace(str.begin(), str.end(), ' ', '\t');
		auto res = Table::split(str);
		if (res[0] == "�ߵ���ѧ")
		{
			int  b = atoi(res[1].data()), c = atoi(res[2].data());
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
				{
					return true;
				});
			while (it != vec_stu.end())
			{
				if (it->math >= b && it->math <= c)
				{
					m_stuTable->insertData(it->formatInfo());
					//������Ϣ������
				}
				it++;
			}
		}
		else if (res[0] == "���ݽṹ")
		{
			int  b = atoi(res[1].data()), c = atoi(res[2].data());
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
				{
					return true;
				});
			while (it != vec_stu.end())
			{
				if (it->datastructure >= b && it->datastructure <= c)
				{
					m_stuTable->insertData(it->formatInfo());
					//������Ϣ������
				}
				it++;
			}
		}
		else
		{
			int  b = atoi(res[1].data()), c = atoi(res[2].data());
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
				{
					return true;
				});
			while (it != vec_stu.end())
			{
				if (it->english >= b && it->english <= c)
				{
					m_stuTable->insertData(it->formatInfo());
					//������Ϣ������
				}
				it++;
			}
		}
	}
	if (m_searchBtn->isClicked())
	{
		m_subjectEdit->clear();
		m_stuTable->clear();
		//ͳ����һ�ſ�Ŀ֮��һ��Ҫ���°�ť�� ��Ȼ��һ��ͳ�ƵĽṹ���ڱ����ŵĺ���
	}
	::settextstyle(20, 0, "����");
}

void Management::sort()
{
	settextstyle(40, 15, "����");
	settextcolor(BLACK);
	const char* title = "����������Ŀ�Ŀ";
	outtextxy((Windows::width() - textwidth(title)) / 2, 200, title);
	m_sortEdit->show();
	auto str = m_sortEdit->text();
	vec_sort = vec_stu;
	if (m_sortEdit->textChanged())
	{
		if (str == "�ߵ���ѧ")
		{
			int num = 0;
			srand((unsigned)time(NULL));
			num = rand() % 3;
			//���������0��2
			switch (num)
			{
			case 0:
				bubble(1);
				break;
			case 1:
				insert(1);
				break;
			case 2:
				select(1);
				break;
			default:
				break;
			}
			vec_stu = vec_sort;
			m_stuTable->show();
			updateShowTable();
		}
		else if (str == "���ݽṹ")
		{
			int num = 0;
			srand((unsigned)time(NULL));
			num = rand() % 3;
			//���������0��2
			switch (num)
			{
			case 0:
				bubble(2);
				break;
			case 1:
				insert(2);
				break;
			case 2:
				select(2);
				break;
			default:
				break;
			}
			vec_stu = vec_sort;
			m_stuTable->show();
			updateShowTable();
		}
		else
		{
			int num = 0;
			srand((unsigned)time(NULL));
			num = rand() % 3;
			//���������0��2
			switch (num)
			{
			case 0:
				bubble(3);
				break;
			case 1:
				insert(3);
				break;
			case 2:
				select(3);
				break;
			default:
				break;
			}
			vec_stu = vec_sort;
			m_stuTable->show();
			updateShowTable();
		}
	}
	::settextstyle(20, 0, "����");
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
	m_showTable->event();

	m_addBtn->event();
	m_addEdit->event();

	m_delBtn->event();
	m_delEdit->event();
	m_delTable->event();

	m_modifyEdit->event();
	for (auto& e : m_stuEdits)
	{
		e->event();
	}

	m_numberBtn->event();
	m_nameBtn->event();
	m_numberEdit->event();
	m_nameEdit->event();
	m_numberTable->event();
	m_nameTable->event();

	m_searchBtn->event();
	m_subjectEdit->event();
	m_stuTable->event();

	m_sortEdit->event();
	m_sortTable->event();
}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open())
	{
		return;
	}
	//��ȡ��ͷ
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;
	//cout << buf << endl;
	//��ȡ����
	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);
		Student stu;
		stringstream ss(data);
		ss >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.datastructure >> stu.english;
		vec_stu.push_back(stu);
		//cout << stu.number << stu.name << stu.grade << stu.math << stu.datastructure << stu.english << endl;
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);
	if (!write.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}
	//д��ͷ
	m_header += "\n";
	write.write(m_header.c_str(), m_header.size());
	//д����
	for (auto& val : vec_stu)
	{
		std::string info = val.formatInfo();
		write.write(info.c_str(), info.size());
	}
	write.close();
}

void Management::updateShowTable()
{
	m_showTable->clear();
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
}

void Management::swap(auto a, auto b)
{
	int i = (a - vec_sort.begin()), j = (b - vec_sort.begin());
	Student tmp = vec_sort[i];
	vec_sort[i] = vec_sort[j];
	vec_sort[j] = tmp;
}

void Management::bubble(int flag)
{
	if (flag == 1)
	{
		//����ߵ���ѧ
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		for (auto end = vec_sort.end() - 1; end > vec_sort.begin(); end--)
		{
			for(auto i = vec_sort.begin();i<end;i++)
				if (i->math > (i + 1)->math)
				{
					swap(i, i + 1);
				}
		}
	}
	else if (flag == 2)
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		for (auto end = vec_sort.end() - 1; end > vec_sort.begin(); end--)
		{
			for (auto i = vec_sort.begin(); i < end; i++)
				if (i->datastructure > (i + 1)->datastructure)
				{
					swap(i, i + 1);
				}
		}
	}
	else
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		for (auto end = vec_sort.end() - 1; end > vec_sort.begin(); end--)
		{
			for (auto i = vec_sort.begin(); i < end; i++)
				if (i->english > (i + 1)->english)
				{
					swap(i, i + 1);
				}
		}
	}
}

void Management::insert(int flag)
{
	if (flag == 1)
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		for (auto i = vec_sort.begin() + 1; i < vec_sort.end(); i++)
		{
			auto j = i - 1;
			for (j = i - 1; j >vec_sort.begin() && j->math > (j + 1)->math; j--)
			{
				swap(j, j + 1);
			}
			if (j == vec_sort.begin() && j->math > (j + 1)->math)
			{
				swap(j, j + 1);
			}
		}
	}
	else if (flag == 2)
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		for (auto i = vec_sort.begin() + 1; i < vec_sort.end(); i++)
		{
			auto j = i - 1;
			for (j = i - 1; j > vec_sort.begin() && j->datastructure > (j + 1)->datastructure; j--)
			{
				swap(j, j + 1);
			}
			if (j == vec_sort.begin() && j->datastructure > (j + 1)->datastructure)
			{
				swap(j, j + 1);
			}
		}
	}
	else
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		for (auto i = vec_sort.begin() + 1; i < vec_sort.end(); i++)
		{
			auto j = i - 1;
			for (j = i - 1; j > vec_sort.begin() && j->english > (j + 1)->english; j--)
			{
				swap(j, j + 1);
			}
			if (j == vec_sort.begin() && j->english > (j + 1)->english)
			{
				swap(j, j + 1);
			}
		}
	}
}

void Management::select(int flag)
{
	if (flag == 1)
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		std::vector<Student>::iterator minIndex;
		for (auto i = vec_sort.begin(); i < vec_sort.end() - 1; i++)
		{
			minIndex = i;
			for (auto j = i + 1; j < vec_sort.end(); j++)
			{
				if (j->math < minIndex->math)
				{
					minIndex = j;
				}
			}
			swap(i, minIndex);
		}
	}
	else if (flag == 2)
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		std::vector<Student>::iterator minIndex;
		for (auto i = vec_sort.begin(); i < vec_sort.end() - 1; i++)
		{
			minIndex = i;
			for (auto j = i + 1; j < vec_sort.end(); j++)
			{
				if (j->datastructure < minIndex->datastructure)
				{
					minIndex = j;
				}
			}
			swap(i, minIndex);
		}
	}
	else
	{
		if (vec_sort.size() == 0 || vec_sort.size() < 2)
		{
			return;
		}
		std::vector<Student>::iterator minIndex;
		for (auto i = vec_sort.begin(); i < vec_sort.end() - 1; i++)
		{
			minIndex = i;
			for (auto j = i + 1; j < vec_sort.end(); j++)
			{
				if (j->english < minIndex->english)
				{
					minIndex = j;
				}
			}
			swap(i, minIndex);
		}
	}
}