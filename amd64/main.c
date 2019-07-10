/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  architecture specific main.c
 *
 *        Version:  1.0
 *        Created:  12/11/2016 11:08:10 AM
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Tisma tisma.etf@gmail.com
 *
 * =====================================================================================
 */

#define AMD64
#include "syscalls.h"

typedef unsigned long int  u64;
typedef unsigned      int  u32;
typedef unsigned short int u16;
typedef unsigned char      u8;

typedef long int    i64;
typedef int         i32;
typedef short int   i16;
typedef signed char i8;

typedef i64 intptr;
typedef u64 uintptr;

#include "../libc-free.c"

int main(int argc, char const* argv[])
{
	return hello_run(argc, argv);
}


