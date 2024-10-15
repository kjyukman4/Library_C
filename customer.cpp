#include "customer.h"

extern customer** g_customer;
extern int numofcustomer;

/*-------------------------------------------------
 Join_Customer(): 회원가입
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
 * Register_Customer(): 회원등록
-------------------------------------------------*/
customer* Register_Customer() {
	customer* c;
	c = (customer*)malloc(sizeof(customer));
	printf("\n>> 회원 가입 <<\n\n");
	printf("학번:");
	scanf("%s", c->num);
	if (Dup_C_num(c->num) == true) {
		return NULL;
	}
	printf("비밀번호:");
	scanf("%s", c->pwd);
	printf("이름:");
	scanf("%s", c->name);
	printf("주소:");
	scanf("%s", c->adr);
	printf("전화번호:");
	scanf("%s", c->Pnum);

	return c;
}

/*-------------------------------------------------
 Customer_Sort(): 회원을 학번순으로 정렬
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
 Dup_C_num(char* 학번(ID)): 학번(ID)중복 체크
-------------------------------------------------*/
bool Dup_C_num(char* s) {
	int i;
	for (i = 0; i < numofcustomer; i++) {
		if (strcmp(g_customer[i]->num, s) == 0) {
			printf("회원가입이 불가합니다.(사유:학번동일)\n");
			return true;
		}
	}
	printf("회원가입이 완료되었습니다!\n");
	return false;
}