#include "book.h"

extern book** g_book;
extern int numofbook;
int Unique_Book_Num = 1;	// �̹�ȣ�� ó������ ����ǰ� �Ŀ� ������ ������ȣ�������� ��ü�Ǿߵȴ�

/*-------------------------------------------------
 Register_Book(): ���� ���
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
 Info_Input_Book(): ���� ���� �Է�
-------------------------------------------------*/
book* Info_Input_Book() {
	int i = 0, j;
	book* b;
	b = (book*)malloc(sizeof(book));
	printf("\n>> ���� ��� <<\n\n");
	printf("������:");
	scanf("%s", b->name);
	printf("���ǻ��:");
	scanf("%s", b->company);
	printf("���ڸ�:");
	scanf("%s", b->writer);

	while (1) {
		printf("ISBN:");
		scanf("%s", b->ISBN);

		if (strlen(b->ISBN) != 13) {
			printf("ISBN�� 13�ڸ��Դϴ�.\n");
		}
		else {
			for (i = 0; i < 13; i++) {
				if (('A' <= (b->ISBN[i]) && 'Z' >= (b->ISBN[i])) || ('a' <= (b->ISBN[i]) && 'z' >= (b->ISBN[i]))) {
					printf("����(����:ISBN�� 13�ڸ� �������Դϴ�.)\n");
					return;
				}
			}
			break;
		}
	}
	printf("����ó:");
	scanf("%s", b->place);
	b->Bnum = Unique_Book_Num;
	b->state = true;
	Unique_Book_Num++;
	return b;
}