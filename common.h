#ifndef __COMMON__
#define __COMMON__
#define ERR_PRN printf("�߸��Է�\n")
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
	bool state;		// �뿩��������(True:���� / False:�Ұ���)
}book;

typedef struct {
	char num[100];
	bool state;		// �뿩��������(True:���� / False:�Ұ���)
	double Bnum;
	cTime rnt;
	cTime rtn;
}borrow;

typedef struct {
	char num[100];		// �й�(ID)
	char pwd[100];		// ��й�ȣ
	char name[100];		// �̸�
	char adr[100];		// ������
	char Pnum[100];		// �ڵ�����ȣ
}customer;




#endif
