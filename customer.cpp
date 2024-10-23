#include "customer.h"

namespace CM {
	enum MENU { SEARCH = 1, BLIST, MODIFY, DELETE, LOGOUT };
}
namespace CSM {
	enum MENU { NAME = 1, NUM, ALL, QUIT };
}

extern book** g_book;
extern borrow** g_borrow;
extern customer** g_customer;
extern int numofbook;
extern int numofborrow;
extern int numofcustomer;
extern char Current_User[100];

/*-------------------------------------------------
 CustomerMain(): 회원 메인
-------------------------------------------------*/
int CustomerMain() {
	CM::MENU menu;

	while (menu = (CM::MENU)CustomerMenu()) {
		system("cls");
		switch (menu) {
		case CM::SEARCH:
			Search_Main();
			break;
		case CM::BLIST:
			Search_Borrow(Current_User);
			break;
		case CM::MODIFY:
			Modify_Customer();
			break;
		case CM::DELETE:
			if (Delete_Customer() == 1) {
				return 0;
			}
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
	Finput_Customer();
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

	system("cls");
	printf("회원가입이 완료되었습니다!!\n");

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
			system("cls");
			printf("회원가입이 불가합니다.(사유:학번동일)\n");
			return true;
		}
	}
	printf("회원가입이 가능합니다!\n");
	return false;
}

/*-----------------------------------------------------------
 Customer_Search_Main(): 고객 조회 메인
-----------------------------------------------------------*/
void Customer_Search_Main() {
	CSM::MENU menu;

	char name[100];
	if (numofcustomer != 0) {
		while (menu = (CSM::MENU)Customer_Search_Menu()) {
			system("cls");
			switch (menu) {
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
void Search_Customer(char* name, int state) {
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

/*-----------------------------------------------------------
 Modify_Customer(char*, int state): 고객 정보 수정
-----------------------------------------------------------*/
void Modify_Customer() {
	int i = 0;
	char pwd[100], adr[100], Pnum[100];
	printf("\n---현재 당신의 정보---\n\n");
	while (i < numofcustomer) {
		if (strcmp(Current_User, g_customer[i]->num) == 0) {
			break;
		}
		i++;
	}
	printf("학번:%s\tpassward:%s\n이름:%s\tadress:%s\n전화번호:%s\n", g_customer[i]->num, g_customer[i]->pwd, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
	printf("\n---정보 수정 입력---\n\n");
	printf("비밀번호:");
	scanf("%s", pwd);
	printf("주소:");
	scanf("%s", adr);
	printf("전화번호:");
	scanf("%s", Pnum);
	strcpy(g_customer[i]->pwd, pwd);
	strcpy(g_customer[i]->adr, adr);
	strcpy(g_customer[i]->Pnum, Pnum);
	system("cls");
	printf("\n정보가 수정되었습니다.\n\n");
	Finput_Customer();
}

/*-----------------------------------------------------------
 Modify_Customer(char*, int state): 고객 삭제
-----------------------------------------------------------*/
int Delete_Customer() {
	int P = 0, i = 0, j;
	char c;
	printf("계정을 삭제하시겠습니까?<Y/N> : ");
	getchar();
	scanf("%c", &c);
	if (c == 'Y') {
		while (i < numofborrow) {
			if (strcmp(Current_User, g_borrow[i]->num) == 0 && g_borrow[i]->state == false) {
				system("cls");
				printf("삭제 실패(사유:도서 미반납)");
				break;
			}
			i++;
		}
		if (i == numofborrow) {
			if (numofcustomer == 1) {
				g_customer[0] = NULL;
				numofcustomer--;
				system("cls");
				printf("계정이 삭제되었습니다.\n초기화면으로 돌아갑니다..\n\n");
				Finput_Customer();
				return 1;
			}
			else {
				for (i = 0; i < numofcustomer; i++) {
					if (strcmp(Current_User, g_customer[i]->num) == 0) {
						break;
					}
				}
				for (j = i; j < numofcustomer; j++) {
					g_customer[j] = g_customer[j + 1];
				}
				g_customer = (customer**)realloc(g_customer, (numofcustomer - 1) * sizeof(customer*));
				numofcustomer--;
				strcpy(Current_User, "");
				system("cls");
				printf("계정이 삭제되었습니다.\n초기화면으로 돌아갑니다..\n\n");
				Sort_Customer();
				Finput_Customer();
				return 1;
			}
		}
	}
	else {
		system("cls");
		printf("취소합니다..\n");
	}
	return 0;
}