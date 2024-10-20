#include "borrow.h"

extern book** g_book;
extern borrow** g_borrow;
extern customer** g_customer;
extern int numofbook;
extern int numofborrow;
extern int numofcustomer;

/*-----------------------------------------------------------
 Rental_Main(): ���� �뿩 ����
-----------------------------------------------------------*/
void Rental_Main() {
	BM::MENU menu;
	char Bname[100];

	while (menu = (BM::MENU)Rental_Menu()) {}
	switch (menu) {
	case BM::NAME:
		printf("������ �Է�:");
		scanf("%s", Bname);
		if (Search_Book(Bname, 0) != 1) {
			Rental_Book();
		}
		break;
	case BM::ISBN:
		printf("ISBN �Է�:");
		scanf("%s", Bname);
		if (Search_Book(Bname, 2) != 1) {
			Rental_Book();
		}
		break;
	case BM::QUIT:
		printf("���� �뿩 ���");
		return ;
	default:
		printf("\n�߸��� ���� �Է��Ͽ����ϴ�.\n");
		break;
	}
}

/*-----------------------------------------------------------
 Rental_Menu(): ���� �뿩 �޴�
-----------------------------------------------------------*/
int Rental_Menu() {
	int n;

	printf("\n>> ���� �뿩 <<\n");
	printf("\n1. ������ �˻� 2. ISBN �˻�\n3. �ڷΰ���\n");
	printf("��ȣ�� �Է��ϼ���:");
	scanf("%d", &n);

	return 0;
}

/*-----------------------------------------------------------
 Rental_Book(): ���� �뿩
-----------------------------------------------------------*/
int Rental_Book() {
	int i = 0,j;
	double Bnum;
	char num[100];
	printf("\n�й� �Է�\n:");
	scanf("%s", num);
	while (i < numofcustomer) {
		if (strcmp(num, g_customer[i]->num) == 0) {
			printf("������ȣ �Է�:\n");
			scanf("%lf", &Bnum);
			j = 0;
			for (j = 0; j < numofbook; j++) {
				if (Bnum == g_book[j]->Bnum) {
					printf("������ �뿩�Ͽ����ϴ�.\n");
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
			}
			if (j == numofbook) {
				printf("�ٽ��Է��ϼ���.\n");
				break;
			}
		}
		i++;
	}
	if (i == numofcustomer) {
		printf("��ġ�ϴ� ȸ���̾����ϴ�.\n");
	}
	return 0;
}

/*-----------------------------------------------------------
 *Borrow(int , int ): ������ ȸ������ ������ å �뿩
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
 Return_Main(): ���� �ݳ�
-----------------------------------------------------------*/
int Return_Main() {
	int i = 0, j = 0;
	bool P = false;
	char num[100];

	printf(">> ���� �ݳ� <<\n");
	printf("�й��� �Է��ϼ���:");
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
		printf("�ݳ��� �����������ϴ�.\n");
		return 1;
	}
	return 0;
}
/*-----------------------------------------------------------
 Search_Borrow(char* ): ���� ���� �˻�
-----------------------------------------------------------*/
void Search_Borrow(char* num) {
	int i,j;
	i = 0;
	printf("\n>> ȸ���� �뿩 ��� <<\n\n");
	while (i < numofborrow) {
		if (strcmp(num, g_borrow[i]->num) == 0 && g_borrow[i]->state == false) {
			for (j = 0; j < numofbook; j++) {
				if (g_borrow[i]->Bnum == g_book[j]->Bnum) break;
			}
			printf("������ȣ:%.lf ,������:%s\n�뿩��:%d.%d.%d,%d:%d:%d\n�ݳ���:%d.%d.%d,%d:%d:%d\n\n", g_borrow[i]->Bnum, g_book[i]->name
				, g_borrow[i]->rnt.year, g_borrow[i]->rnt.month, g_borrow[i]->rnt.day, g_borrow[i]->rnt.hour, g_borrow[i]->rnt.minute, g_borrow[i]->rnt.second
				, g_borrow[i]->rtn.year, g_borrow[i]->rtn.month, g_borrow[i]->rtn.day, g_borrow[i]->rtn.hour, g_borrow[i]->rtn.minute, g_borrow[i]->rtn.second);
		}
		i++;
	}
}

/*-----------------------------------------------------------
 Return_Borrow(): ���� ���� �ݳ�
-----------------------------------------------------------*/
void Return_Borrow() {
	int i = 0,j;
	double Bnum;

	printf("�ݳ��� ������ȣ�� �Է��ϼ���:");
	scanf("%lf", &Bnum);
	while (i < numofbook) {
		if (Bnum == g_book[i]->Bnum && g_book[i]->state == false) {
			j = 0;
			while (j < numofborrow) {
				if (Bnum == g_borrow[j]->Bnum && g_borrow[i]->state == false) {
					printf("������ �ݳ��Ͽ����ϴ�.\n");
					g_book[i]->state = true;
					g_borrow[j]->state = true;
					Finput_Book();
					Finput_Book();
					return;
				}
				j++;
			}
		}
		i++;
	}
}