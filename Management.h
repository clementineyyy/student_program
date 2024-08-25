#pragma once
#include"Windows.h"
#include"PushButton.h"
#include "Student.h"
#include "Table.h"
#include "BasicWidget.h"
#include "LineEdit.h"
#include <vector>
#include <memory>

class Management         //定义了名为Management的类
{
	enum Operator        //枚举
	{
		Show,            //逗号
		Insert,
		Delete,
		Modify,
		Search,
		Rate,
		Sort,
		Exit,
		Menu
	};

public:   //冒号
	Management();
	//启动管理类
	void run();          
	//菜单，有返回值，选择哪一个下列功能
	int menu();
	//1.显示所有的学生信息
	void showinfo();    
	//2.添加学生信息
	void add();
    //3.删除学生信息
	void del();
	//4.修改学生信息
	void modify();
	//5.查询学生信息：包含按姓名查询和按学号查询
	void search();
	//6.成绩统计：输入任意课程名和一个分数段，统计出在此分数段的学生情况
	void rate();
	//7.排序：按成绩升序/降序显示学生数据排序结果（多种排序方法）
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
	//读取文件，保存学生信息
	std::string m_header;
	std::vector<Student> vec_stu;
	std::vector<Student> vec_sort;

private:
	//查看学生表格
	std::unique_ptr<Table> m_showTable;
	//添加学生按扭
	std::unique_ptr<PushButton> m_addBtn;
	std::unique_ptr<LineEdit> m_addEdit;
	//删除学生按钮
	std::unique_ptr<PushButton> m_delBtn;
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr<Table> m_delTable;
	//修改学生按钮
	std::unique_ptr<LineEdit> m_modifyEdit;
	std::vector<std::unique_ptr<LineEdit>> m_stuEdits;
	bool isFind = false;
	std::vector<Student>::iterator m_modifyIt;
	//查询学生按钮
	std::unique_ptr<LineEdit> m_numberEdit;
	std::unique_ptr<LineEdit> m_nameEdit;
	std::unique_ptr<Table> m_numberTable;
	std::unique_ptr<Table> m_nameTable;
	std::unique_ptr<PushButton> m_numberBtn;
	std::unique_ptr<PushButton> m_nameBtn;
	//成绩统计按钮
	std::unique_ptr<LineEdit> m_subjectEdit;
	std::unique_ptr<Table> m_stuTable;
	std::unique_ptr<PushButton> m_searchBtn;
	//排序按钮
	std::unique_ptr<LineEdit> m_sortEdit;
	std::unique_ptr<Table> m_sortTable;
};


