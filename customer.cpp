#include "customer.h"

extern book** g_book;
extern customer** g_customer;
extern int numofbook;
extern int numofcustomer;

/*-------------------------------------------------
 CustomerMain(): 회원 메인
-------------------------------------------------*/
int CustomerMain() {
	CM::MENU menu;
	int state;
	while (menu = (CM::MENU)CustomerMenu()) {
		switch (menu) {
		case CM::SEARCH:
			/*
			if ((state = search()) == 1) {
				return 1;
			}
			*/
			break;
		case CM::BLIST:
			//Blist();
			break;
		case CM::MODIFY:
			//modify();
			break;
		case CM::DELETE:
			/*
			if ((state = Cdelete()) == 1) {
				return 0;
			}
			*/
		case CM::LOGOUT:
			printf("로그아웃합니다.\n");
			return 0;
		default:
			printf("잘못입력\n");
		}
	}
	return 0;
}

/*-------------------------------------------------
 CustomerMenu(): 회원 메뉴
-------------------------------------------------*/
int CustomerMenu() {
	int n;
	printf("\n>> 회원 메뉴 <<\n\n");
	printf("1. 도서 검색\t 2. 대여 목록\n3. 개인정보수정\t 4. 회원 탈퇴\n5. 로그 아웃\t 6. 프로그램 종료 \n");
	printf("\n번호를 선택하세요 :");
	scanf("%d", &n);

	return n;
}

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

/*-----------------------------------------------------------
 Customer_Search_Main(): 고객 조회 메인
-----------------------------------------------------------*/
void Customer_Search_Main() {
	CSM::MENU menu;
	int i, j = 0;
	char name[100];
	if (numofcustomer != 0) {
		while (1) {
			switch (menu = (CSM::MENU)Customer_Search_Menu()) {
			case CSM::NAME:
				printf("이름 입력:");
				scanf("%s", name);
				Search_Customer(name, 0);
				break;
			case CSM::NUM:
				printf("학번 입력:");
				scanf("%s", name);
				Search_Customer(name, 1);
				break;
			case CSM::ALL:
				Search_Customer((char *)"", 2);
				break;
			case CSM::QUIT:
				printf("회원 조회 취소");
				return ;
			default:
				printf("잘못입력");
				break;
			}
		}
		
	}
	else {
		printf("\n등록된 회원이 없습니다.\n");
	}
}

/*-----------------------------------------------------------
 Customer_Search_Menu(): 고객 조회 메뉴
-----------------------------------------------------------*/
int Customer_Search_Menu() {
	int n;
	printf("\n>> 회원 목록 <<\n\n");
	printf("1. 이름 검색\t2. 학번 검색\n3. 전체 검색\t4. 이전 메뉴\n");
	scanf("%d", &n);
	return n;
}

/*-----------------------------------------------------------
 Search_Customer(char*, int state): 고객 조회
  state : <0> 이름 검색
		  <1> 학번 검색
		  <2> 전체 검색
-----------------------------------------------------------*/
int Search_Customer(char* name, int state) {
	int i, j = 0;
	
	printf(">> 검색 결과 <<\n\n");
	if (state == 0) {
		for (i = 0; i < numofcustomer; i++) {
			if (strcmp(name, g_customer[i]->name) == 0) {
				printf("학번:%s\n이름:%s\n주소:%s\n전화번호:%s\n\n", g_customer[i]->num, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
				j++;
			}
		}
	}
	else if (state == 1) {
		for (i = 0; i < numofcustomer; i++) {
			if (strcmp(name, g_customer[i]->num) == 0) {
				printf("학번:%s\n이름:%s\n주소:%s\n전화번호:%s\n\n", g_customer[i]->num, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
				j++;
			}
		}
	}
	else {
		for (i = 0; i < numofcustomer; i++) {
			printf("학번:%s\n이름:%s\n주소:%s\n전화번호:%s\n\n", g_customer[i]->num, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
			j++;
		}
	}
	if (j == numofbook) {
		printf("등록된 회원이 없습니다.\n");
	}
}