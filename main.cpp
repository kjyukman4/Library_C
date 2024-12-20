#include "main.h"

namespace MM {
	enum MENU { JOIN = 1, LOGIN, QUIT };
}

book** g_book;
borrow** g_borrow;
customer** g_customer;

int numofbook;		// 등록된 책 수량
int numofborrow;	// 대여한 책 수량
int numofcustomer;	// 가입된 회원 수

char Current_User[100];		//현재 접속한 유저 학번

int main() {
	system("color 02");
	MM::MENU menu;

	FILE* ocp;
	FILE* obkp;
	FILE* obp;

	g_book = (book**)malloc(sizeof(book*));
	g_borrow = (borrow**)malloc(sizeof(borrow*));
	g_customer = (customer**)malloc(sizeof(customer*));
	
	Call_Book();
	Call_Borrow();
	Call_Customer();
	
	printf("numofbook:%d\n", numofbook);
	printf("numofborrow:%d\n", numofborrow);
	printf("numofcustomer:%d\n\n", numofcustomer);

	while ((menu = (MM::MENU)MainMenu()) != MM::QUIT) {
		system("cls");
		switch (menu) {
		case MM::JOIN:
			Join_Customer();
			break;
		case MM::LOGIN: //ID:admin (관리자 로그인)
			Login();
			break;
		default:
			ERR_PRN;
			break;
		}
	}
	free(g_book);
	free(g_borrow);
	free(g_customer);
	return 0;
}

/*-------------------------------------------------
 MainMain(): 메인메뉴
-------------------------------------------------*/
int MainMenu() {
	int n;
	printf("\n>> 도서관 서비스 <<\n");
	printf("\n1. 회원가입\t 2. 로그인\t 3. 프로그램 종료\t \n");
	printf("\n번호를 선택하세요 : ");
	scanf("%d", &n);
	return n;
}

/*-------------------------------------------------
 Login(): 로그인
-------------------------------------------------*/
void Login()
{
	int i;
	char id[10], passward[50];
	printf("\nID:");
	scanf("%s", id);
	if (strcmp(id, "admin") == 0) {
		strcpy(Current_User, "admin");
		system("cls");
		AdminMain();
		return;
	}
	else {
		printf("passward:");
		scanf("%s", passward);
		for (i = 0; i < numofcustomer; i++) {
			if ((strcmp(id, g_customer[i]->num) == 0) && (strcmp(passward, g_customer[i]->pwd) == 0)) {
				strcpy(Current_User, g_customer[i]->num);
				system("cls");
				CustomerMain();
				return;
			}
		}
		if (i == numofcustomer) {
			system("cls");
			printf("회원정보가 일치하지 않습니다.\n");
		}
	}
}