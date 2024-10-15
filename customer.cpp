#include "customer.h"

extern customer** g_customer;
extern int numofcustomer;

/*-------------------------------------------------
 Join_Customer(): ȸ������
-------------------------------------------------*/
void Join_Customer() {
	if (numofcustomer == 0) {
		g_customer[0] = (customer*)malloc(sizeof(customer));
	}
	else {
		g_customer = (customer**)realloc(g_customer, (numofcustomer + 1) * sizeof(customer*));
	}
	g_customer[numofcustomer] = Register_Customer();
	if (g_customer[numofcustomer] != NULL) {
		numofcustomer++;
	}
	Sort_Customer();
	//FinputC();
}

/*-------------------------------------------------
 * Register_Customer(): ȸ�����
-------------------------------------------------*/
customer* Register_Customer() {
	customer* c;
	c = (customer*)malloc(sizeof(customer));
	printf("\n>> ȸ�� ���� <<\n\n");
	printf("�й�:");
	scanf("%s", c->num);
	if (Dup_C_num(c->num) == true) {
		return NULL;
	}
	printf("��й�ȣ:");
	scanf("%s", c->pwd);
	printf("�̸�:");
	scanf("%s", c->name);
	printf("�ּ�:");
	scanf("%s", c->adr);
	printf("��ȭ��ȣ:");
	scanf("%s", c->Pnum);

	return c;
}

/*-------------------------------------------------
 Customer_Sort(): ȸ���� �й������� ����
-------------------------------------------------*/
void Sort_Customer() {
	customer* min;
	int i, j;

	for (i = 0; i < numofcustomer; i++) {
		for (j = i; j < numofcustomer; j++) {
			if (strcmp(g_customer[i]->num, g_customer[j]->num) == 1) {
				printf("i:%d\nj:%d\n", i, j);
				min = g_customer[i];
				g_customer[i] = g_customer[j];
				g_customer[j] = min;
			}
		}
	}
}

/*-------------------------------------------------
 Dup_C_num(char* �й�(ID)): �й�(ID)�ߺ� üũ
-------------------------------------------------*/
bool Dup_C_num(char* s) {
	int i;
	for (i = 0; i < numofcustomer; i++) {
		if (strcmp(g_customer[i]->num, s) == 0) {
			printf("ȸ�������� �Ұ��մϴ�.(����:�й�����)\n");
			return true;
		}
	}
	printf("ȸ�������� �Ϸ�Ǿ����ϴ�!\n");
	return false;
}