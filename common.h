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
	double Bnum;		// 도서번호
	char name[100];		// 도서이름
	char company[100];	// 출판사
	char writer[100];	// 저자
	char ISBN[100];		// ISBN
	char place[100];	// 소장처
	bool state;			// 대여가능유무(True:가능 / False:불가능)
}book;

typedef struct {
	char num[100];		// 대여 학번
	bool state;			// 대여가능유무(True:가능 / False:불가능)
	double Bnum;		// 도서번호
	cTime rnt;			// 대여일
	cTime rtn;			// 반납일
}borrow;

typedef struct {
	char num[100];		// 학번(ID)
	char pwd[100];		// 비밀번호
	char name[100];		// 이름
	char adr[100];		// 거주지
	char Pnum[100];		// 핸드폰번호
}customer;




#endif
