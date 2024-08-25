#include "Student.h"
#include <sstream>

Student::Student()
{
}

Student::Student(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 datastructure, uint32 english)
	:number(number),name(name),grade(grade),math(math),datastructure(datastructure),english(english)
{
}

std::string Student::formatInfo()
{
	//
	std::stringstream ss;
	ss << number << "\t" << name << "\t" << grade << "\t" << math << "\t" << datastructure << "\t" << english << std::endl;
	return ss.str();
}

Student Student::fromSting(const std::string& str)
{
	Student stu;
	std::stringstream ss(str);
	ss >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.datastructure >> stu.english;
	return stu;
}
