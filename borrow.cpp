#include "borrow.h"

extern book** g_book;
extern borrow** g_borrow;
extern customer** g_customer;
extern int numofbook;
extern int numofborrow;
extern int numofcustomer;

namespace BM {
	enum MENU { NAME = 1, ISBN, QUIT };
}

/*-----------------------------------------------------------
 Rental_Main(): 도서 대여 메인
-----------------------------------------------------------*/
void Rental_Main() {
	BM::MENU menu;
	char Bname[100];

	while (menu = (BM::MENU)Rental_Menu()) {
		system("cls");
		switch (menu) {
		case BM::NAME:
			printf("도서명 입력:");
			scanf("%s", Bname);
			if (Search_Book(Bname, 0) != 1) {
				Rental_Book();
			}
			break;
		case BM::ISBN:
			printf("ISBN 입력:");
			scanf("%s", Bname);
			if (Search_Book(Bname, 2) != 1) {
				Rental_Book();
			}
			break;
		case BM::QUIT:
			printf("도서 대여 취소");
			return;
		default:
			printf("\n잘못된 값을 입력하였습니다.\n");
			break;
		}
	}
}

/*-----------------------------------------------------------
 Rental_Menu(): 도서 대여 메뉴
-----------------------------------------------------------*/
int Rental_Menu() {
	int n;

	printf("\n>> 도서 대여 <<\n");
	printf("\n1. 도서명 검색 2. ISBN 검색\n3. 뒤로가기\n");
	printf("번호를 입력하세요:");
	scanf("%d", &n);

	return n;
}

/*-----------------------------------------------------------
 Rental_Book(): 도서 대여
-----------------------------------------------------------*/
int Rental_Book() {
	int i = 0,j;
	double Bnum;
	char num[100];
	printf("\n학번 입력\n:");
	scanf("%s", num);
	while (i < numofcustomer) {
		if (strcmp(num, g_customer[i]->num) == 0) {
			printf("도서번호 입력:\n");
			scanf("%lf", &Bnum);
			j = 0;
			for (j = 0; j < numofbook; j++) {
				if (Bnum == g_book[j]->Bnum) {
					if (g_book[j]->state == true) {
						system("cls");
						printf("도서를 대여하였습니다.\n");
						if (numofborrow == 0) {
							g_borrow[0] = (borrow*)malloc(sizeof(borrow));
						}
						else {
							g_borrow = (borrow**)realloc(g_borrow, (numofborrow + 1) * sizeof(borrow*));
						}
						g_borrow[numofborrow] = Borrow(i, j);
						g_book[j]->state = false;
						numofborrow++;
						Finput_Book();
						Finput_Borrow();
						break;
					}
					else {
						system("cls");
						printf("대여 할 수없는 도서입니다..\n");
						break;
					}
				}
			}
			if (j == numofbook) {
				printf("다시입력하세요.\n");
			}
			break;
		}
		i++;
	}
	if (i == numofcustomer) {
		system("cls");
		printf("일치하는 회원이없습니다.\n");
	}
	return 0;
}

/*-----------------------------------------------------------
 *Borrow(int , int ): 지정된 회원에게 지정된 책 대여
-----------------------------------------------------------*/
borrow* Borrow(int i, int N) {
	borrow* B;
	int j = 0;
	B = (borrow*)malloc(sizeof(borrow));
	strcpy(B->num, g_customer[i]->num);
	B->state = false;
	B->Bnum = g_book[N]->Bnum;
	B->rnt = Current_Time();
	B->rtn = B->rnt;
	B->rtn.month++;
	if (B->rnt.month > 12) {
		B->rtn.year++;
		B->rtn.month = 1;
	}
	return B;
}

/*-----------------------------------------------------------
 Return_Main(): 도서 반납
-----------------------------------------------------------*/
int Return_Main() {
	int i = 0, j = 0;
	bool P = false;
	char num[100];

	printf(">> 도서 반납 <<\n");
	printf("학번을 입력하세요:");
	scanf("%s", num);
	while (i < numofborrow) {
		if (strcmp(num, g_borrow[i]->num) == 0 && g_borrow[i]->state == false) {
			P = true;
			Search_Borrow(num);
			Return_Borrow();
			break;
		}
		i++;
	}
	if (P == false) {
		system("cls");
		printf("반납할 도서가없습니다.\n");
		return 1;
	}
	return 0;
}
/*-----------------------------------------------------------
 Search_Borrow(char* ): 빌린 도서 검색
-----------------------------------------------------------*/
void Search_Borrow(char* num) {
	int i,j;
	i = 0;
	printf("\n>> 회원의 대여 목록 <<\n\n");
	while (i < numofborrow) {
		if (strcmp(num, g_borrow[i]->num) == 0 && g_borrow[i]->state == false) {
			for (j = 0; j < numofbook; j++) {
				if (g_borrow[i]->Bnum == g_book[j]->Bnum) break;
			}
			printf("도서번호:%.lf ,도서명:%s\n대여일:%d.%d.%d,%d:%d:%d\n반납일:%d.%d.%d,%d:%d:%d\n\n", g_borrow[i]->Bnum, g_book[i]->name
				, g_borrow[i]->rnt.year, g_borrow[i]->rnt.month, g_borrow[i]->rnt.day, g_borrow[i]->rnt.hour, g_borrow[i]->rnt.minute, g_borrow[i]->rnt.second
				, g_borrow[i]->rtn.year, g_borrow[i]->rtn.month, g_borrow[i]->rtn.day, g_borrow[i]->rtn.hour, g_borrow[i]->rtn.minute, g_borrow[i]->rtn.second);
		}
		i++;
	}
}

/*-----------------------------------------------------------
 Return_Borrow(): 빌린 도서 반납
-----------------------------------------------------------*/
void Return_Borrow() {
	int i = 0,j;
	double Bnum;

	printf("반납할 도서번호를 입력하세요:");
	scanf("%lf", &Bnum);
	while (i < numofbook) {
		if (Bnum == g_book[i]->Bnum && g_book[i]->state == false) {
			j = 0;
			while (j < numofborrow) {
				if (Bnum == g_borrow[j]->Bnum && g_borrow[i]->state == false) {
					system("cls");
					printf("도서를 반납하였습니다.\n");
					g_book[i]->state = true;
					Delete_Borrow(Bnum);
					Finput_Book();
					Finput_Borrow();
					return;
				}
				j++;
			}
		}
		i++;
	}
	if (i == numofbook) {
		system("cls");
		printf("존재하지않는 도서 입니다\n");
	}
}

/*-----------------------------------------------------------
 Delete_Borrow(): 빌린 도서 삭제
-----------------------------------------------------------*/
void Delete_Borrow(double Bnum) {
	int i,j,k;

	if (numofborrow == 1) {
		g_borrow[0] = NULL;
		numofborrow--;
	}
	else {
		for (i = 0; i < numofborrow; i++) {
			if (Bnum == g_borrow[i]->Bnum) {
				break;
			}
		}
		
		for (j = i; j < numofborrow - 1; j++) {
			g_borrow[j] = g_borrow[j + 1];
		}
		g_borrow = (borrow**)realloc(g_borrow, (numofborrow - 1) * sizeof(borrow*));
		numofborrow--;
	}
}