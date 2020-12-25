#pragma once
/*
list是由双向链表实现的，因此内存空间是不连续的。
只能通过指针访问数据，所以list的随机存取非常没有效率，时间复杂度为o(n);
但由于链表的特点，能高效地进行插入和删除。
list的内存空间可以是不连续，它不支持随机访问，
通过 front() 和 back() 的返回值，能分别获取当前 list 容器中的首尾元素。
除此之外，如果想访问 list 容存储的其他元素，就只能使用 list 容器的迭代器。
*/

class TestList
{
public:
	void startTest();

};

