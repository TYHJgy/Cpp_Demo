
#include <pthread.h>
#include <vector>

using namespace std;

class TestThread
{	
	public:
		unsigned int getThreadNum();	
		vector<pthread_t> getPtid();
		void startTest(void);
	private:
		unsigned int threadNum;//线程数量
		vector<pthread_t> ptid;
};









