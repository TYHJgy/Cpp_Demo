#include"TestList.h"
#include <list>
#include <iostream>

using namespace std;
void TestList::startTest()
{
    cout << "startTest" <<endl;

    list<int> the_list;
    for (int i = 0; i < 10; i++)
        the_list.push_back(i);

    cout << "\n插入一个元素到the_list第2个位置" << endl;
    the_list.insert(++the_list.begin(), 22);
#if 0
    auto it = the_list.begin();//auto 自动类型，等同于list<int>::iterator 
#else
    list<int>::iterator it = the_list.begin();//迭代器不是指针，是类模板，表现的 像 指针。
#endif
    cout << "\nthe_list:" << *it << " " ;
    ++it;
    while (it != the_list.end()){
        cout << *it << " " ;
        ++it;
    }
    cout<<endl;
    list<int> the_list2;
    cout << "\n将the_list赋值到the_list2。\n赋值前the_list2大小：" << the_list2.size() << endl;
    //the_list2.assign(8, 1);//赋值8个1
    the_list2.assign(the_list.begin(), the_list.end());//将the_list赋值到the_list2
    cout << "赋值后the_list2大小：" <<the_list2.size() << endl;
    cout << "the_list2第一个元素：" << the_list2.front() << endl;
    cout << "the_list2最后一个元素：" << the_list2.back() << endl;
    cout << "\n清空the_list" << endl;
    while (!the_list.empty()) {
        the_list.pop_front();
    }
}
