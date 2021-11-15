#include "Test_volatile.h"
#include "Debug_printf.h"


int i = 10;
volatile int b = 10;
void * test_volatile_run1(void * data){
	i++;
	b++;
	return NULL;
}
void * test_volatile_run2(void * data){

	int j = i;	//(1)语句
	DEBUG("j=%d",j);	
	sleep(1);
	int k = i;	//(2)语句
	DEBUG("k=%d",k);
	return NULL;
}


void Test_volatile::test_volatile(){
	pthread_t pd1;
	pthread_t pd2;

	pthread_create(&pd1,NULL,test_volatile_run1,NULL);
	pthread_create(&pd2,NULL,test_volatile_run2,NULL);
}



























