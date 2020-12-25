
#if !defined(DEBUG_PRINTF_H)
#define DEBUG_PRINTF_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//==============================================================================================================
void printf_time();

//==============================================================================================================
#define DEBUG(format,...)   printf_time();printf("[%s(%d)]%s:",__FILE__,__LINE__,__func__);printf(format"\n",##__VA_ARGS__)





#endif





