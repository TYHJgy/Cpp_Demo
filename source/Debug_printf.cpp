
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include "Debug_printf.h"

//==============================================================================================================

void printf_time(){
	char _time1[20] = {0};
	char _time2[64] = {0};
	struct timeval tv;
	struct tm * local_time;

	gettimeofday(&tv, NULL); 
	local_time = localtime(&tv.tv_sec); 
	strftime(_time1, 20, "%Y-%m-%d %H:%M:%S", local_time);  
	snprintf(_time2, 64, "%s.%d",_time1,(int)(tv.tv_usec));
	printf("[%s]",_time2);
}







