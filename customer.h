#ifndef __CUSTOMER__
#define __CUSTOMER__
#include "common.h"

typedef struct {
	char num[100];		// �й�(ID)
	char pwd[100];		// ��й�ȣ
	char name[100];		// �̸�
	char adr[100];		// ������
	char Pnum[100];		// �ڵ�����ȣ
}customer;



void Join_Customer();
customer* Register_Customer();
void Sort_Customer();
bool Dup_C_num(char*);
#endif
