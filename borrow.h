#ifndef __BORROW__
#define __BORROW__
#include "common.h"

typedef struct {
	char num[100];
	bool state;		// �뿩��������(True:���� / False:�Ұ���)
	double Bnum;
	cTime rnt;
	cTime rtn;
}borrow;


#endif
