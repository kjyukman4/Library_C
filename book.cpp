#include "book.h"

extern book** g_book;
extern borrow** g_borrow;
extern int numofbook;
extern int numofborrow;
int Unique_Book_Num = 1;	// �̹�ȣ�� ó������ ����ǰ� �Ŀ� ������ ������ȣ�������� ��ü�Ǿߵȴ�

/*-------------------------------------------------
 Register_Book(): ���� ���
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
	Sort_Book();
	Finput_Book();
}

/*-------------------------------------------------
 Info_Input_Book(): ���� ���� �Է�
-------------------------------------------------*/
book* Info_Input_Book() {
	int i = 0;
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
					break;
				}
			}
			if (i == 13) break;
		}
	}
	printf("����ó:");
	scanf("%s", b->place);
	b->Bnum = Unique_Book_Num;
	b->state = true;
	Unique_Book_Num++;
	return b;
}

/*-------------------------------------------------
 Sort_Book(): ���� ����
-------------------------------------------------*/
void Sort_Book() {
	book* min;
	int i, j;
	double B = 1000000;
	for (i = 0; i < numofbook; i++) {
		for (j = i; j < numofbook; j++) {
			if (strcmp(g_book[i]->ISBN, g_book[j]->ISBN) == 1) {
				min = g_book[i];
				g_book[i] = g_book[j];
				g_book[j] = min;
			}
		}
	}
	
	/*
	for (i = 0; i < numofbook; i++) {
		if (g_book[i]->state == false) {
			M = g_book[i]->Bnum;
		}
		g_book[i]->Bnum = B;
		B++;
		if (g_book[i]->state == false) {
			for (j = 0; j < numofborrow; j++) {
				if (g_borrow[j]->Bnum == M) {
					g_borrow[j]->Bnum = g_book[i]->Bnum;
					break;
				}
			}
		}
	}
	*/
}

/*-----------------------------------------------------------
 Delete_Book_Main(): ���� ���� ����
-----------------------------------------------------------*/
void Delete_Book_Main() {
	BM::MENU menu;
	char Bname[100];
	

	while (menu = (BM::MENU)Delete_Book_Menu()) {
		switch (menu) {
		case BM::NAME:
			printf("������ �Է�:");
			scanf("%s", Bname);

			if (Search_Book(Bname, 0) != 1) {
				Delete_Book();
			}

			break;

		case BM::ISBN:
			printf("ISBN �Է�:");
			scanf("%s", Bname);

			if (Search_Book(Bname, 2) != 1) {
				Delete_Book();
			}

			break;
		case BM::QUIT:
			printf("���� ���� ���");
			return ;
		default:
			printf("\n�߸��� ���� �Է��Ͽ����ϴ�.\n");
			break;
		}
	}
}

/*-----------------------------------------------------------
 Delete_Book_Menu(): ���� ���� �޴�
-----------------------------------------------------------*/
int Delete_Book_Menu() {
	int n;

	printf("\n>> ���� ���� <<\n");
	printf("\n1. ������ �˻� 2. ISBN �˻�\n3. �ڷΰ���\n");
	printf("��ȣ�� �Է��ϼ���:");
	scanf("%d", &n);

	return n;
}

/*-----------------------------------------------------------
 Delete_Book(): ���� ����
-----------------------------------------------------------*/
int Delete_Book() {
	int i,j;
	char c;
	double Bnum;

	printf("���� ��ȣ �Է�:");
	scanf("%lf", &Bnum);
	printf("������ ���� �Ͻðڽ��ϱ�?<Y/N>");
	fflush(stdin);
	scanf("%c", &c);
	
	if (c == 'Y') {
		if (numofbook == 1) {
			g_book[0] = NULL;
			numofbook--;
			printf("������ �����Ǿ����ϴ�.\n\n");
		}
		else {
			for (i = 0; i < numofbook; i++) {
				if (Bnum == g_book[i]->Bnum) {
					break;
				}
			}
			for (j = i; j < numofbook; j++) {
				g_book[j] = g_book[j + 1];
			}
			g_book = (book**)realloc(g_book, (numofbook - 1) * sizeof(book*));
			numofbook--;
			printf("������ �����Ǿ����ϴ�.\n\n");
			Sort_Book();
		}
	}
	else {
		printf("����մϴ�..\n");
	}
	Finput_Book();
	return 0;
}

/*-----------------------------------------------------------
 Search_Main(): ���� ��ȸ ����
-----------------------------------------------------------*/
void Search_Main() {
	BSM::MENU menu;
	int j = 0;
	char Bname[100], company[100], ISBN[100], writer[100];
	if (numofbook != 0) {
		while (menu = (BSM::MENU)Search_Menu()) {
			switch (menu) {
			case BSM::NAME:
				printf("������ �Է�:");
				scanf("%s", Bname);
				Search_Book(Bname, 0);
				break;
			case BSM::COMPANY:
				printf("���ǻ�� �Է�:");
				scanf("%s", company);
				Search_Book(Bname, 1);
				break;
			case BSM::ISBN:
				printf("ISBN �Է�:");
				scanf("%s", ISBN);
				Search_Book(Bname, 2);
				break;
			case BSM::WRITER:
				printf("���ڸ� �Է�:");
				scanf("%s", writer);
				Search_Book(Bname, 3);
				break;
			case BSM::ALL:
				Search_Book((char*)"", 4);
				break;
			case BSM::QUIT:
				printf("�ڷΰ��ϴ�..\n");
				return ;
			default:
				printf("�߸��Է�");
				break;
			}
		}
	}
	else {
		printf("\n��ϵ� ������ �����ϴ�.\n");
	}
}

/*-----------------------------------------------------------
 Search_Menu(): ���� ��ȸ �޴�
-----------------------------------------------------------*/
int Search_Menu() {
	int n;
	printf("\n>> ���� �˻� <<\n\n");
	printf("1. ������ �˻�\t2. ���ǻ�� �˻�\n3. ISBN �˻�\t4. ���ڸ� �˻�\n5. ��ü�˻�\t6. ������\n");
	scanf("%d", &n);
	return n;
}

/*-----------------------------------------------------------
 Search_Book(char *, int state): ��� ���� ��ȸ

 state : <0> ������ �˻�
		 <1> ���ǻ�� �˻�
		 <2> ISBN �˻�
		 <3> ���ڸ� �˻�
		 <4> ��ü �˻�
-----------------------------------------------------------*/
int Search_Book(char *Bname, int state) {
	int i = 0,cnt = 0;

	printf(">> �˻� ��� <<\n");

	if (state == 0) {
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->name) == 0 && g_book[i]->state == true) {
				printf("\n������ȣ:%-10.lf\t ������:%-10s\n���ǻ�:%-10s\t ����:%-10s\nISBN:%-10s\t ����ó:%-10s\n�뿩���� ����:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, "Y");
				cnt++;
			}
			i++;
		}
	}
	else if (state == 1) {
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->company) == 0 && g_book[i]->state == true) {
				printf("\n������ȣ:%-10.lf\t ������:%-10s\n���ǻ�:%-10s\t ����:%-10s\nISBN:%-10s\t ����ó:%-10s\n�뿩���� ����:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, "Y");
				cnt++;
			}
			i++;
		}
	}
	else if (state == 2) {
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->ISBN) == 0 && g_book[i]->state == true) {
				printf("\n������ȣ:%-10.lf\t ������:%-10s\n���ǻ�:%-10s\t ����:%-10s\nISBN:%-10s\t ����ó:%-10s\n�뿩���� ����:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, "Y");
				cnt++;
			}
			i++;
		}
	}
	else if(state == 3){
		while (i < numofbook) {
			if (strcmp(Bname, g_book[i]->writer) == 0 && g_book[i]->state == true) {
				printf("\n������ȣ:%-10.lf\t ������:%-10s\n���ǻ�:%-10s\t ����:%-10s\nISBN:%-10s\t ����ó:%-10s\n�뿩���� ����:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, "Y");
				cnt++;
			}
			i++;
		}
	}
	else {
		while (i < numofbook) {
			if (g_book[i]->state == true) {
				printf("\n������ȣ:%-10.lf\t ������:%-10s\n���ǻ�:%-10s\t ����:%-10s\nISBN:%-10s\t ����ó:%-10s\n�뿩���� ����:%-10s\n\n",
					g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, "Y");
				cnt++;
			}
			i++;
		}
	}

	if (cnt == 0) {
		printf("������ �����ϴ�..\n");
		return 1;
	}
	return 0;
}