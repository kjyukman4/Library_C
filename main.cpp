#include "main.h"

book** g_book;
borrow** g_borrow;
customer** g_customer;

int numofbook;		// ��ϵ� å ����
int numofborrow;	// �뿩�� å ����
int numofcustomer;	// ���Ե� ȸ�� ��

char Current_User[100];		//���� ������ ���� �й�

int main() {
	system("color 02");
	MM menu;

	g_book = (book**)malloc(sizeof(book*));
	g_borrow = (borrow**)malloc(sizeof(borrow*));
	g_customer = (customer**)malloc(sizeof(customer*));

	while ((menu = (MM)mainmenu()) != EXIT) {
		switch (menu) {
		case JOIN:
			Join_Customer();
			break;
		case LOGIN: //ID:admin (������ �α���)
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
 mainmain(): ���θ޴�
-------------------------------------------------*/
int mainmenu() {
	int n;
	printf("\n>> ������ ���� <<\n");
	printf("\n1. ȸ������\t 2. �α���\t 3. ���α׷� ����\t \n");
	printf("\n��ȣ�� �����ϼ��� :");
	scanf("%d", &n);

	return n;
}

/*-------------------------------------------------
 Login(): �α���
-------------------------------------------------*/
void Login()
{
	int i;
	char id[10], passward[50];
	printf("\nID:");
	scanf("%s", id);
	if (strcmp(id, "admin") == 0) {
		strcpy(Current_User, "admin");
		adminmain();
		return;
	}
	else {
		printf("passward:");
		scanf("%s", passward);
		for (i = 0; i < numofcustomer; i++) {
			if ((strcmp(id, g_customer[i]->num) == 0) && (strcmp(passward, g_customer[i]->pwd) == 0)) {
				strcpy(Current_User, g_customer[i]->num);
				//person(g_client[i]);
				return;

			}
		}
		if (i == numofcustomer) {
			printf("ȸ�������� ��ġ���� �ʽ��ϴ�.\n");
		}
	}
}

/*-------------------------------------------------
 adminmain(): ������ ����
-------------------------------------------------*/
int adminmain() {
	AM menu;
	int i, k, state;
	while (menu = (AM)adminmenu()) {
		switch (menu) {
		case REGISTER:
			//Register();
			break;
		case BDELETE:
			//Bdelete();
			break;
		case RENTAL:
			//Rental();
			break;
		case RETURN:
			//Return();
			break;
		case SEARCH:
			/*
			if ((state = search()) == 1) {
				return 1;
			}
			*/
			break;
		case CLIST:
			//Clist();
			break;
		case LOGOUT:
			//strcpy(NUM, "");
			return 0;
		default:
			printf("�߸��Է�\n");
		}
	}
	return 0;
}

/*-------------------------------------------------
 adminmain(): ������ ����
-------------------------------------------------*/
int adminmenu() {
	int n;
	system("cls");
	printf("\n>> ������ �޴� <<\n\n");
	printf("\n1. ���� ���\t 2. ���� ����\n3. ���� �뿩\t 4. ���� �ݳ�\n5. ���� �˻�\t 6. ȸ�� ���\n7. �α� �ƿ�\t");
	printf("\n��ȣ�� �����ϼ��� :");
	scanf("%d", &n);

	return n;
}