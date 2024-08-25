#pragma once
#include "Configure.h"
using uint32 = unsigned int;

class Student
{
public:
	Student();
	Student(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 datastructure, uint32 english);
	//格式化数据
	std::string formatInfo();
	static Student fromSting(const std::string& str);

public:
	uint32 number;
	std::string name;
	std::string grade;
	uint32 math;
	uint32 datastructure;
	uint32 english;
};

