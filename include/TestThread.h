/*
同步与互斥
	1、互斥是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的。
	2、同步是指在互斥的基础上（大多数情况），通过其它机制实现访问者对资源的有序访问。
	3、同步其实已经实现了互斥，所以同步是一种更为复杂的互斥。
	4、互斥是一种特殊的同步。

pthread_exit和pthread_cancel的区别
	前者退出当前线程，后者退出指定线程。

互斥锁
	互斥量本质上说是一把锁，在访问共享资源前对互斥量进行加锁，在访问完成后释放互斥量。
	对互斥量进行枷锁以后，其他视图再次对互斥量加锁的线程都会被阻塞直到当前线程释放该互斥锁。
	如果释放互斥量时有一个以上的线程阻塞，那么所有该锁上的阻塞线程都会变成可运行状态，	第一个变成运行状态的线程可以对互斥量加锁，
	其他线程就会看到互斥量依然是锁着，只能再次阻塞等待它重新变成可用，这样，一次只有一个线程可以向前执行。

读写锁
	读写锁与互斥锁类似，不过读写锁拥有更高的并行性。互斥量要么是锁住状态，要么是不加锁状态，而且一次只有一个线程可以对其加锁。
	读写锁有3种状态：读模式下加锁状态，写模式下加锁状态，不加锁状态。
	一次只有一个线程可以占有写模式的读写锁，但是多个线程可以同时占有读模式的读写锁。
	当读写锁是写加锁状态时，在这个锁被解锁之前，所有视图对这个锁加锁的线程都会被阻塞。
	当读写锁在读加锁状态时，所有试图以读模式对它进行加锁的线程都可以得到访问权，但是任何希望以写模式对此锁进行加锁的线程都会阻塞，
	直到所有的线程释放它们的读锁为止。

条件变量
	条件变量是线程可用的另一种同步机制。
	互斥量用于上锁，条件变量则用于等待，并且条件变量总是需要与互斥量一起使用，运行线程以无竞争的方式等待特定的条件发生。
	条件变量本身是由互斥量保护的，线程在改变条件变量之前必须首先锁住互斥量。
	其他线程在获得互斥量之前不会察觉到这种变化，因为互斥量必须在锁定之后才能计算条件。

信号量
	线程的信号和进程的信号量类似，使用线程的信号量可以高效地完成基于线程的资源计数。
	信号量实际上是一个非负的整数计数器，用来实现对公共资源的控制。
	在公共资源增加的时候，信号量就增加,公共资源减少的时候，信号量就减少,只有当信号量的值大于0的时候，才能访问信号量所代表的公共资源。


*/

#include <pthread.h>
#include <vector>

using namespace std;

class TestThread
{	
	public:
		unsigned int getThreadNum();	
		vector<pthread_t> getPtid();
		void startTest(void);
		void test_thread_lock(void);
		void test_pthread_join(void);			
		void test_pthread_exit(void);
		void test_pthread_cancel(void);			//
		void test_pthread_rwlock(void);			//测试读写锁
		void test_pthread_cond(void);			//测试条件变量
		void test_pthread_sem(void); 			//测试信号量
	private:
		unsigned int threadNum;//线程数量
		vector<pthread_t> ptid;
};









