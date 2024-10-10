#ifndef __BOOK__
#define __BOOK__
#include "common.h"

typedef struct {
	double Bnum;		
	char name[100];
	char company[100];
	char writer[100];
	char ISBN[100];
	char place[100];
	bool state;		// 대여가능유무(True:가능 / False:불가능)
}book;

extern book** g_book;
extern int numofbook;

#endif