#ifndef _MYDES_H_
#define _MYDES_H_

#include <stddef.h>
#include <stdint.h>


#define DES_KEY_SIZE    8

typedef struct
{
    uint32_t sk[32];          
}
des_context;


unsigned char *dw_des_encrypt
	(	
		const char *in_src, //输入明文
		const int in_size,//明文长度
		const char *in_key,
		unsigned char *out_dst, //输出密文
		int *out_size //密文长度
	);

unsigned char *dw_des_decrypt
	(	
		const char *in_src, //输入密文
		const int in_size,//密文长度
		const char *in_key, //输入密匙
		unsigned char *out_dst, //输出明文
		int *out_size //明文长度		
	);


void Str2Hex( const unsigned char *sSrc, unsigned char *sDest, int nSrcLen );
		
void HexStrToByte(const char* source, unsigned char* dest, int sourceLen);



#endif /* des.h */

