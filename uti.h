//$Id: uti.h,v 1.5 2001/06/21 14:15:11 ballestr Exp $
#if !defined (UTI_H)
#define UTI_H

#include <sys/time.h>

#if defined DEBUG
#define jERR   00
#define jINFO  10
#define jDEBUG 20
#define jVERB  30
#define jVERB2 35
#define ifDEBUG(l,x) {if (DEBUG>=l) {x;};}
#else
#define ifDEBUG(l,x) {}
#endif


#define Nbits 5
#define Abits 4
#define Fbits 5
#define Nmask ((1<<Nbits) -1)
#define Npos (Fbits+Abits)
#define Amask ((1<<Abits) -1)
#define Apos (Abits+1)
#define Fmask ((1<<Fbits)-1)

#define SeriousBug "This is a serious bug - please report to Sergio\n"
#define HardFail   "This is probably an hardware failure\n"

int     pkNAF (int n, int a, int f);
int     printNAF (short i);
unsigned char   *itos (int v, unsigned char *buf, int len);
int     stoi (const unsigned char *buf, int len);
void    stoli (long int *v,const unsigned char *buf, int len);
unsigned char   *NAFtos (const int n, const int a, const int f, unsigned char *buf);
void    prhex (const void *buf, int len);
void    pritg (const void *buf, int len);
/*char *reverseit(char *array, int len);*/
int     stoim (char *buf, int len);
int     stoisb(char *buf, int len, int pos);

/*unsigned char   *itoia (unsigned int v, unsigned char *buf, unsigned int len);
unsigned int     iatoi (const unsigned char *buf, unsigned int len);*/

int batin(int b15, int b14, int b13, int b12, int b11, int b10, int b9, int b8, int b7, int b6, int b5, int b4, int b3, int b2, int b1, int b0);

int batin32(int b31, int b30, int b29, int b28, int b27, int b26, int b25, int b24, int b23, int b22, int b21, int b20, int b19, int b18, int b17, int b16,
int b15, int b14, int b13, int b12, int b11, int b10, int b9, int b8, int b7, int b6, int b5, int b4, int b3, int b2, int b1, int b0);

int      binary_print (int n);
int char_binary_print_file(unsigned char *c, int len, FILE * pFile);
int char_binary_print(unsigned char *c, int len);
//inline int char_binary_print(unsigned char *c, int len)
//{
//return char_binary_print((char*)c, len);
//}

inline float tdiff(struct timeval T1, struct timeval T2)
{
    return ( static_cast<float>(T2.tv_sec)-static_cast<float>(T1.tv_sec) ) + 
	(static_cast<float>(T2.tv_usec) - static_cast<float>(T1.tv_usec))/1000000.0;
}

inline void fstoi (const unsigned char *buf, int len, unsigned char *v)
{
    register const unsigned char   *p= buf + len;

//    for (;p>buf;++v,p) {
    for (;p>buf;++v) {
	*(v) = *(--p);
    }
    //   cout << '[' << hex << v <<dec << "] ";
}


/*inline char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}*/

#endif
