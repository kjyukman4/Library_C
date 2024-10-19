#ifndef __COMMON__
#define __COMMON__
#define ERR_PRN printf("잘못입력\n")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}cTime;

typedef struct {
	double Bnum;
	char name[100];
	char company[100];
	char writer[100];
	char ISBN[100];
	char place[100];
	bool state;		// 대여가능유무(True:가능 / False:불가능)
}book;

typedef struct {
	char num[100];
	bool state;		// 대여가능유무(True:가능 / False:불가능)
	double Bnum;
	cTime rnt;
	cTime rtn;
}borrow;

typedef struct {
	char num[100];		// 학번(ID)
	char pwd[100];		// 비밀번호
	char name[100];		// 이름
	char adr[100];		// 거주지
	char Pnum[100];		// 핸드폰번호
}customer;




#endif
