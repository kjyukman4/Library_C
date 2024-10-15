#include "book.h"

extern book** g_book;
extern int numofbook;
int Unique_Book_Num = 1;	// 이번호는 처음값만 적용되고 후에 삭제된 고유번호가있으면 대체되야된다

/*-------------------------------------------------
 Register_Book(): 도서 등록
-------------------------------------------------*/
void Register_Book() {
	int i, j;
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
	//Bsort();
	//FinputBK();
}

/*-------------------------------------------------
 Info_Input_Book(): 도서 정보 입력
-------------------------------------------------*/
book* Info_Input_Book() {
	int i = 0, j;
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
					return;
				}
			}
			break;
		}
	}
	printf("소장처:");
	scanf("%s", b->place);
	b->Bnum = Unique_Book_Num;
	b->state = true;
	Unique_Book_Num++;
	return b;
}