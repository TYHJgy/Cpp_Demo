#include <iostream>
#include <string.h>
#include "TestStruct.h"


//using namespace std;
struct Person{
	std::string name;
	int year;
	//可不可以有成员函数
	void show();
};

void Person::show(){
	std::cout<<"this is show()"<<std::endl;

}



void TestStruct::startTest(){
	std::cout<<"start"<<std::endl;
	Person person1;
	person1.name = "gy";
	person1.year = 18;

	std::cout<<"person1.name:" <<person1.name <<std::endl;

	std::cout<<"person1.year:" <<person1.year <<std::endl;
	person1.show();
}
















