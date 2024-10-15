#include "main.h"

book** g_book;
borrow** g_borrow;
customer** g_customer;

int numofbook;		// 등록된 책 수량
int numofborrow;	// 대여한 책 수량
int numofcustomer;	// 가입된 회원 수

char Current_User[100];		//현재 접속한 유저 학번

int main() {
	system("color 02");
	MM::MMENU menu;

	g_book = (book**)malloc(sizeof(book*));
	g_borrow = (borrow**)malloc(sizeof(borrow*));
	g_customer = (customer**)malloc(sizeof(customer*));

	while ((menu = (MM::MMENU)MainMenu()) != MM::EXIT) {
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
	printf("\n번호를 선택하세요 :");
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
		AdminMain();
		return;
	}
	else {
		printf("passward:");
		scanf("%s", passward);
		for (i = 0; i < numofcustomer; i++) {
			if ((strcmp(id, g_customer[i]->num) == 0) && (strcmp(passward, g_customer[i]->pwd) == 0)) {
				strcpy(Current_User, g_customer[i]->num);
				//CustomerMain();
				return;

			}
		}
		if (i == numofcustomer) {
			printf("회원정보가 일치하지 않습니다.\n");
		}
	}
}

/*-------------------------------------------------
 AdminMain(): 관리자 메인
-------------------------------------------------*/
int AdminMain() {
	AM::AMENU menu;
	int i, k, state;
	while (menu = (AM::AMENU)AdminMenu()) {
		switch (menu) {
		case AM::REGISTER:
			//Register();
			break;
		case AM::BDELETE:
			//Bdelete();
			break;
		case AM::RENTAL:
			//Rental();
			break;
		case AM::RETURN:
			//Return();
			break;
		case AM::SEARCH:
			/*
			if ((state = search()) == 1) {
				return 1;
			}
			*/
			break;
		case AM::CLIST:
			//Clist();
			break;
		case AM::LOGOUT:
			//strcpy(NUM, "");
			return 0;
		default:
			printf("잘못입력\n");
		}
	}
	return 0;
}

/*-------------------------------------------------
 AdminMain(): 관리자 메뉴
-------------------------------------------------*/
int AdminMenu() {
	int n;
	system("cls");
	printf("\n>> 관리자 메뉴 <<\n\n");
	printf("\n1. 도서 등록\t 2. 도서 삭제\n3. 도서 대여\t 4. 도서 반납\n5. 도서 검색\t 6. 회원 목록\n7. 로그 아웃\t");
	printf("\n번호를 선택하세요 :");
	scanf("%d", &n);

	return n;
}

/*-------------------------------------------------
 CustomerMain(): 회원 메인
-------------------------------------------------*/
int CustomerMain() {
	CM::CMENU menu;
	int state;
	while (1) {
		switch (menu = (CM::CMENU)CustomerMenu()) {
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
			//strcpy(NUM, "");
			return 0;
		case CM::QUIT:
			return 1;
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