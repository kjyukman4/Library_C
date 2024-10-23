#include "book.h"

extern book** g_book;
extern borrow** g_borrow;
extern int numofbook;
extern int numofborrow;
int Unique_Book_Num;

/*-------------------------------------------------
 Register_Book(): 도서 등록
-------------------------------------------------*/
void Register_Book() {

	if (numofbook == 0) {
		g_book[0] = (book*)malloc(sizeof(book));
	}
	else {
		g_book = (book**)realloc(g_book, (numofbook + 1) * sizeof(book*));
	}
	g_book[numofbook] = Info_Input_Book();
	if (g_book[numofbook] != NULL) {
		numofbook++;
	}
	Finput_Book();
}

/*-------------------------------------------------
 Info_Input_Book(): 도서 정보 입력
-------------------------------------------------*/
book* Info_Input_Book() {
	int i = 0;
	book* b;
	b = (book*)malloc(sizeof(book));
	printf("\n>> 도서 등록 <<\n\n");
	printf("도서명:");
	scanf("%s", b->name);
	printf("출판사명:");
	scanf("%s", b->company);
	printf("저자명:");
	scanf("%s", b->writer);

	while (1) {
		printf("ISBN:");
		scanf("%s", b->ISBN);

		if (strlen(b->ISBN) != 13) {
			printf("ISBN은 13자리입니다.\n");
		}
		else {
			for (i = 0; i < 13; i++) {
				if (('A' <= (b->ISBN[i]) && 'Z' >= (b->ISBN[i])) || ('a' <= (b->ISBN[i]) && 'z' >= (b->ISBN[i]))) {
					printf("실패(사유:ISBN은 13자리 정수형입니다.)\n");
					break;
				}
			}
			if (i == 13) break;
		}
	}
	printf("소장처:");
	scanf("%s", b->place);
	b->Bnum = Unique_Book_Num;
	b->state = true;
	Unique_Book_Num++;
	system("cls");
	printf("도서가 등록되었습니다!!\n");
	return b;
}

/*-----------------------------------------------------------
 Delete_Book_Main(): 도서 삭제 메인
-----------------------------------------------------------*/
void Delete_Book_Main() {
	BM::MENU menu;
	char Bname[100];
	

	while (menu = (BM::MENU)Delete_Book_Menu()) {
		system("cls");
		switch (menu) {
		case BM::NAME:
			printf("도서명 입력:");
			scanf("%s", Bname);

			if (Search_Book(Bname, 0) != 1) {
				Delete_Book();
			}

			break;

		case BM::ISBN:
			printf("ISBN 입력:");
			scanf("%s", Bname);

			if (Search_Book(Bname, 2) != 1) {
				Delete_Book();
			}

			break;
		case BM::QUIT:
			printf("도서 삭제 취소");
			return ;
		default:
			printf("\n잘못된 값을 입력하였습니다.\n");
			break;
		}
	}
}

/*-----------------------------------------------------------
 Delete_Book_Menu(): 도서 삭제 메뉴
-----------------------------------------------------------*/
int Delete_Book_Menu() {
	int n;

	printf("\n>> 도서 삭제 <<\n");
	printf("\n1. 도서명 검색 2. ISBN 검색\n3. 뒤로가기\n");
	printf("번호를 입력하세요:");
	scanf("%d", &n);

	return n;
}

/*-----------------------------------------------------------
 Delete_Book(): 도서 삭제
-----------------------------------------------------------*/
void Delete_Book() {
	int i,j,k;
	char c;
	int Bnum;

	printf("도서 번호 입력:");
	scanf("%d", &Bnum);
	getchar();
	printf("정말로 삭제 하시겠습니까?<Y/N>");
	scanf("%c", &c);

	system("cls");

	if (c == 'Y') {
		if (numofbook == 1) {
			g_book[0] = NULL;
			numofbook--;
			Unique_Book_Num--;
			printf("도서가 삭제되었습니다.\n\n");
		}
		else {
			for (i = 0; i < numofbook; i++) {
				if (Bnum == g_book[i]->Bnum) {
					break;
				}
			}
			// book구조체 borrow구조체 도서번호 당겨주기
			for (j = i; j < numofbook - 1; j++) {
				g_book[j] = g_book[j + 1];
				if (g_book[j]->state == false) {
					for (k = 0; k < numofborrow; k++) {
						if (g_book[j]->Bnum == g_borrow[k]->Bnum) {
							g_borrow[k]->Bnum -= 1;
							break;
						}
					}
				}
				g_book[j]->Bnum -= 1;
			}
			g_book = (book**)realloc(g_book, (numofbook - 1) * sizeof(book*));
			numofbook--;
			Unique_Book_Num--;
			printf("도서가 삭제되었습니다.\n\n");
		}
	}
	else {
		printf("취소합니다..\n");
	}
	Finput_Book();
	Finput_Borrow();
}

/*-----------------------------------------------------------
 Search_Main(): 도서 조회 메인
-----------------------------------------------------------*/
void Search_Main() {
	BSM::MENU menu;
	int j = 0;
	char Bname[100], company[100], ISBN[100], writer[100];
	if (numofbook != 0) {
		while (menu = (BSM::MENU)Search_Menu()) {
			system("cls");
			switch (menu) {
			case BSM::NAME:
				printf("도서명 입력:");
				scanf("%s", Bname);
				Search_Book(Bname, 0);
				break;
			case BSM::COMPANY:
				printf("출판사명 입력:");
				scanf("%s", company);
				Search_Book(company, 1);
				break;
			case BSM::ISBN:
				printf("ISBN 입력:");
				scanf("%s", ISBN);
				Search_Book(ISBN, 2);
				break;
			case BSM::WRITER:
				printf("저자명 입력:");
				scanf("%s", writer);
				Search_Book(writer, 3);
				break;
			case BSM::ALL:
				Search_Book((char*)"", 4);
				break;
			case BSM::QUIT:
				printf("뒤로갑니다..\n");
				return ;
			default:
				printf("잘못입력");
				break;
			}
		}
	}
	else {
		system("cls");
		printf("\n등록된 도서가 없습니다.\n");
	}
}

/*-----------------------------------------------------------
 Search_Menu(): 도서 조회 메뉴
-----------------------------------------------------------*/
int Search_Menu() {
	int n;
	printf("\n>> 도서 검색 <<\n\n");
	printf("1. 도서명 검색\t2. 출판사명 검색\n3. ISBN 검색\t4. 저자명 검색\n5. 전체검색\t6. 나가기\n");
	scanf("%d", &n);
	return n;
}

/*-----------------------------------------------------------
 Search_Book(char *, int state): 등록 도서 조회

 state : <0> 도서명 검색
		 <1> 출판사명 검색
		 <2> ISBN 검색
		 <3> 저자명 검색
		 <4> 전체 검색
-----------------------------------------------------------*/
int Search_Book(char *Bname, int state) {
	int i = 0,cnt = 0;
	char str[100];

	printf(">> 검색 결과 <<\n");

	if (state == 0) {
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->name) == 0) {
				g_book[i]->state ?	strcpy(str, "Y") : strcpy(str, "N");
				printf("\n도서번호:%-10.lf\t 도서명:%-10s\n출판사:%-10s\t 저자:%-10s\nISBN:%-10s\t 소장처:%-10s\n대여가능 여부:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, str);
				cnt++;
			}
			i++;
		}
	}
	else if (state == 1) {
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->company) == 0) {
				g_book[i]->state ? strcpy(str, "Y") : strcpy(str, "N");
				printf("\n도서번호:%-10.lf\t 도서명:%-10s\n출판사:%-10s\t 저자:%-10s\nISBN:%-10s\t 소장처:%-10s\n대여가능 여부:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, str);
				cnt++;
			}
			i++;
		}
	}
	else if (state == 2) {
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->ISBN) == 0) {
				g_book[i]->state ? strcpy(str, "Y") : strcpy(str, "N");
				printf("\n도서번호:%-10.lf\t 도서명:%-10s\n출판사:%-10s\t 저자:%-10s\nISBN:%-10s\t 소장처:%-10s\n대여가능 여부:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, str);
				cnt++;
			}
			i++;
		}
	}
	else if(state == 3){
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->writer) == 0) {
				g_book[i]->state ? strcpy(str, "Y") : strcpy(str, "N");
				printf("\n도서번호:%-10.lf\t 도서명:%-10s\n출판사:%-10s\t 저자:%-10s\nISBN:%-10s\t 소장처:%-10s\n대여가능 여부:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, str);
				cnt++;
			}
			i++;
		}
	}
	else {
		while (i < numofbook) {
			g_book[i]->state ? strcpy(str, "Y") : strcpy(str, "N");
			printf("\n도서번호:%-10.lf\t 도서명:%-10s\n출판사:%-10s\t 저자:%-10s\nISBN:%-10s\t 소장처:%-10s\n대여가능 여부:%-10s\n\n",
				g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, str);
			cnt++;
			i++;
		}
	}

	if (cnt == 0) {
		printf("도서가 없습니다..\n");
		return 1;
	}
	return 0;
}