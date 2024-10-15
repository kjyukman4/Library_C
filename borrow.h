#ifndef __BORROW__
#define __BORROW__
#include "common.h"

typedef struct {
	char num[100];
	bool state;		// 대여가능유무(True:가능 / False:불가능)
	double Bnum;
	cTime rnt;
	cTime rtn;
}borrow;


#endif
