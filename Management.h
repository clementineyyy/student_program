#pragma once
#include"Windows.h"
#include"PushButton.h"
#include "Student.h"
#include "Table.h"
#include "BasicWidget.h"
#include "LineEdit.h"
#include <vector>
#include <memory>

class Management         //��������ΪManagement����
{
	enum Operator        //ö��
	{
		Show,            //����
		Insert,
		Delete,
		Modify,
		Search,
		Rate,
		Sort,
		Exit,
		Menu
	};

public:   //ð��
	Management();
	//����������
	void run();          
	//�˵����з���ֵ��ѡ����һ�����й���
	int menu();
	//1.��ʾ���е�ѧ����Ϣ
	void showinfo();    
	//2.���ѧ����Ϣ
	void add();
    //3.ɾ��ѧ����Ϣ
	void del();
	//4.�޸�ѧ����Ϣ
	void modify();
	//5.��ѯѧ����Ϣ��������������ѯ�Ͱ�ѧ�Ų�ѯ
	void search();
	//6.�ɼ�ͳ�ƣ���������γ�����һ�������Σ�ͳ�Ƴ��ڴ˷����ε�ѧ�����
	void rate();
	//7.���򣺰��ɼ�����/������ʾѧ���������������������򷽷���
	void sort();

	void drawBackground();
	void eventLoop();

	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);
	void updateShowTable();

private:
	int m_op;
	IMAGE m_bk;

	std::vector<std::unique_ptr<PushButton>> menu_btns;

public:
	void swap(auto a, auto b);
	void bubble(int flag);
	void insert(int flag);
	void select(int flag);

private:
	//��ȡ�ļ�������ѧ����Ϣ
	std::string m_header;
	std::vector<Student> vec_stu;
	std::vector<Student> vec_sort;

private:
	//�鿴ѧ�����
	std::unique_ptr<Table> m_showTable;
	//���ѧ����Ť
	std::unique_ptr<PushButton> m_addBtn;
	std::unique_ptr<LineEdit> m_addEdit;
	//ɾ��ѧ����ť
	std::unique_ptr<PushButton> m_delBtn;
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr<Table> m_delTable;
	//�޸�ѧ����ť
	std::unique_ptr<LineEdit> m_modifyEdit;
	std::vector<std::unique_ptr<LineEdit>> m_stuEdits;
	bool isFind = false;
	std::vector<Student>::iterator m_modifyIt;
	//��ѯѧ����ť
	std::unique_ptr<LineEdit> m_numberEdit;
	std::unique_ptr<LineEdit> m_nameEdit;
	std::unique_ptr<Table> m_numberTable;
	std::unique_ptr<Table> m_nameTable;
	std::unique_ptr<PushButton> m_numberBtn;
	std::unique_ptr<PushButton> m_nameBtn;
	//�ɼ�ͳ�ư�ť
	std::unique_ptr<LineEdit> m_subjectEdit;
	std::unique_ptr<Table> m_stuTable;
	std::unique_ptr<PushButton> m_searchBtn;
	//����ť
	std::unique_ptr<LineEdit> m_sortEdit;
	std::unique_ptr<Table> m_sortTable;
};


