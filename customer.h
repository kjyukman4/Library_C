#ifndef __CUSTOMER__
#define __CUSTOMER__
#include "common.h"

typedef struct {
	char num[100];		// 학번(ID)
	char pwd[100];		// 비밀번호
	char name[100];		// 이름
	char adr[100];		// 거주지
	char Pnum[100];		// 핸드폰번호
}customer;



void Join_Customer();
customer* Register_Customer();
void Sort_Customer();
bool Dup_C_num(char*);
#endif
