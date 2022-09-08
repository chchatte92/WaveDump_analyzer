/* 
 * the usual silly things..
 */

// $Id: uti.cc,v 1.6 2001/07/02 09:07:34 ballestr Exp $

#include <iostream>
#include <cstdio>
using namespace std;

#include "uti.h"

int pkNAF (int n, int a, int f)
{
    int _i = ((n & Nmask) << Npos) | ((a & Amask) << Apos) | (f & Fmask);
#if 0
    cout << hex << Nmask <<' '<< Amask <<' '<< Fmask <<dec<<endl;
    cout << "NAF(" << n << ',' << a << ',' << f << ") = 0x";
    cout << hex << _i << dec << endl;
#endif
    return _i;
}

int printNAF (short i)
{
    int f = (i & Fmask);
    int a = (i >> Apos) & Amask;
    int n = (i >> Npos) & Nmask;
    int qe = (i >> (Npos + Apos)) & 1;
    int eol = (i >> (Npos + Apos + 1)) & 1;
    printf ("NAF=%2d,%2d,%2d QE=%d EOL=%d\n", n, a, f, qe, eol);
    return i;
}

unsigned char *itos (int v, unsigned char *buf, int len) //CHECK!!
{
    unsigned char *p=buf + len;
    int j;
    for (int i = 0; i < len; i++) {
    j=len-1-i;
//	*(--p) = *(reinterpret_cast<unsigned char *>(&v) + i);
	*(--p) = *(reinterpret_cast<unsigned char *>(&v) + j);
    }
    // prhex(buf,len);
    return buf;
}

int stoi (const unsigned char *buf, int len) // CHECK !!
{
    register const unsigned char   *p= buf + len;
    register int  v = 0;
    int j;
    for (int i = 0; i < len; i++) {
    j=len-1-i;
//	*(reinterpret_cast<unsigned char *>(&v) + i) = *(--p);
	*(reinterpret_cast<unsigned char *>(&v) + j) = *(--p);
    }
    //   cout << '[' << hex << v <<dec << "] ";
    return v;
}



void stoli (long int *v, const unsigned char *buf, int len)
{
    const unsigned char   *p = buf + len;

    *v = 0;
    for (int i = 0; i < len; i++) {
    int j;
    j=len-1-i;
//	*(reinterpret_cast<unsigned char *>(v) + i) = *(--p);
	*(reinterpret_cast<unsigned char *>(v) + j) = *(--p);
    }
    //   cout << '[' << hex << v <<dec << "] ";
}

unsigned char   *NAFtos (const int n, const int a, const int f, unsigned char *buf)
{
    *(buf + 0) = static_cast<unsigned char>(f) & Fmask;
    *(buf + 1) = static_cast<unsigned char>(a) & Amask;
    *(buf + 2) = static_cast<unsigned char>(n) & Nmask;
//    prhex(buf,3);
    return buf;
}

void prhex (const void *buf, int len)
{
    const unsigned char *p=static_cast<const unsigned char *> (buf);
    for (int i = 0; i < len; i++) 
    {
	printf ("%02x ", *p++);
    }
}

void pritg (const void *buf, int len)
{
    const unsigned char *p=static_cast<const unsigned char *> (buf);
    for (int i = 0; i < len; i++) 
    {
	printf ("%d ", *p++);
    }
    printf ("\n");
}

// This is a hack to get the thing compiled

extern  "C" {
// this is to fool the stupid libf2c
    void    MAIN__ (void) {
    }
}

int binary_print(int n) {
        // print binary with leading zeros
        cout << "binary: ";
        for (int i=31; i>=0; i--) {
            int bit = ((n >> i) & 1);
//            if(i>0 && 4*(int)((i+1)/4) == i+1) cout << " ";
            if(i>0 && 8*(int)((i+1)/8) == i+1) cout << " ";
	    cout << bit;
        }
        cout << endl;
    return 0;
}

int char_binary_print(unsigned char *c, int len) {
        // print binary with leading zeros
        cout << "char binary: ";
        for (int j=0; j<len; j++) {
//        for (int j=len-1; j>=0; j--) {
	for (int i=7; i>=0; i--) {
            int bit = ((c[j] >> i) & 1);
	    cout << bit;
        }
	cout << " ";
	}
        cout << endl;
    return 0;
}

int char_binary_print_file(unsigned char *c, int len, FILE * pFile) {
        for (int j=0; j<len; j++) {
//        for (int j=len-1; j>=0; j--) {
	for (int i=7; i>=0; i--) {
            int bit = ((c[j] >> i) & 1);
	    fprintf(pFile,"%i",bit);
        }
	fprintf(pFile," ");
	}
	fprintf(pFile,"\n");
    return 0;
}

/*char *reverseit(char *array, int len)
{
	if(len<2) return array;
	char *inv_array; int mid=0;
	mid = (len-1)/2;
	for(int i=0,j=len-1; i <=mid; i++,j--)
	{
	  inv_array[i] = array[j];
	  inv_array[j] = array[i];
	}
  return inv_array;
}*/


int stoim (char *buf, int len) // CHECK !!
{
    register char *p= buf + len;
    register int   v= 0;
    int j;
    for (int i = 0; i < len; i++) {
    j=len-1-i;
//	*(reinterpret_cast<char *>(&v) + i) = *(--p);
	*(reinterpret_cast<char *>(&v) + j) = *(--p);
    }
    //   cout << '[' << hex << v <<dec << "] ";
    return v;
}

int stoisb(char *buf, int len, int pos) // CHECK !!
{
    register char *p= buf + len;
    register int   v= 0;
    int j=len-1-pos;
	*(reinterpret_cast<char *>(&v) + j) = *(--p);
    return v;
}

int batin(int b15, int b14, int b13, int b12, int b11, int b10, int b9, int b8, int b7, int b6, int b5, int b4, int b3, int b2, int b1, int b0)
{
    	int reg=0;
	if(b0>0) reg|=1<<1;
	if(b1>0) reg|=1<<2;
	if(b2>0) reg|=1<<3;
	if(b3>0) reg|=1<<4;
	if(b4>0) reg|=1<<5;
	if(b5>0) reg|=1<<6;
	if(b6>0) reg|=1<<7;
	if(b7>0) reg|=1<<8;
	if(b8>0) reg|=1<<9;
	if(b9>0) reg|=1<<10;
	if(b10>0) reg|=1<<11;
	if(b11>0) reg|=1<<12;
	if(b12>0) reg|=1<<13;
        if(b13>0) reg|=1<<14;
        if(b14>0) reg|=1<<15;
	if(b15>0) reg|=1<<16;
	reg>>=1;
    return reg;
}

int batin32(int b31, int b30, int b29, int b28, int b27, int b26, int b25, int b24, int b23, int b22, int b21, int b20, int b19, int b18, int b17, int b16,
int b15, int b14, int b13, int b12, int b11, int b10, int b9, int b8, int b7, int b6, int b5, int b4, int b3, int b2, int b1, int b0)
{
    	int reg=0;
	if(b0>0) reg|=1<<0;
	if(b1>0) reg|=1<<1;
	if(b2>0) reg|=1<<2;
	if(b3>0) reg|=1<<3;
	if(b4>0) reg|=1<<4;
	if(b5>0) reg|=1<<5;
	if(b6>0) reg|=1<<6;
	if(b7>0) reg|=1<<7;
	if(b8>0) reg|=1<<8;
	if(b9>0) reg|=1<<9;
	if(b10>0) reg|=1<<10;
	if(b11>0) reg|=1<<11;
	if(b12>0) reg|=1<<12;
        if(b13>0) reg|=1<<13;
        if(b14>0) reg|=1<<14;
	if(b15>0) reg|=1<<15;
	if(b16>0) reg|=1<<16;
	if(b17>0) reg|=1<<17;
	if(b18>0) reg|=1<<18;
	if(b19>0) reg|=1<<19;
	if(b20>0) reg|=1<<20;
	if(b21>0) reg|=1<<21;
	if(b22>0) reg|=1<<22;
	if(b23>0) reg|=1<<23;
	if(b24>0) reg|=1<<24;
	if(b25>0) reg|=1<<25;
	if(b26>0) reg|=1<<26;
	if(b27>0) reg|=1<<27;
	if(b28>0) reg|=1<<28;
        if(b29>0) reg|=1<<29;
        if(b30>0) reg|=1<<30;
	if(b31>0) reg|=1<<31;
	reg>>=1;
    return reg;
}


/*unsigned char *itoia (unsigned int v, unsigned char *buf, unsigned int len) //CHECK!!
{
    unsigned char *p=buf + len;
    int j;
    for (int i = 0; i < len; i++) {
    j=len-1-i;
//	*(--p) = *(reinterpret_cast<unsigned char *>(&v) + i);
	*(--p) = *(reinterpret_cast<unsigned char *>(&v) + j);
    }
    // prhex(buf,len);
    return buf;
}

unsigned int iatoi (const unsigned char *buf, unsigned int len) // CHECK !!
{
    register const unsigned char   *p= buf + len;
    register unsigned int v = 0;
    int j;
    for (int i = 0; i < len; i++) {
    j=len-1-i;
//	*(reinterpret_cast<unsigned char *>(&v) + i) = *(--p);
	*(reinterpret_cast<unsigned char *>(&v) + j) = *(--p);
    }
    //   cout << '[' << hex << v <<dec << "] ";
    return v;
}*/

