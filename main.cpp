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
	MM::MMENU menu;

	g_book = (book**)malloc(sizeof(book*));
	g_borrow = (borrow**)malloc(sizeof(borrow*));
	g_customer = (customer**)malloc(sizeof(customer*));

	while ((menu = (MM::MMENU)MainMenu()) != MM::EXIT) {
		switch (menu) {
		case MM::JOIN:
			Join_Customer();
			break;
		case MM::LOGIN: //ID:admin (������ �α���)
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
 MainMain(): ���θ޴�
-------------------------------------------------*/
int MainMenu() {
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
			printf("ȸ�������� ��ġ���� �ʽ��ϴ�.\n");
		}
	}
}

/*-------------------------------------------------
 AdminMain(): ������ ����
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
			printf("�߸��Է�\n");
		}
	}
	return 0;
}

/*-------------------------------------------------
 AdminMain(): ������ �޴�
-------------------------------------------------*/
int AdminMenu() {
	int n;
	system("cls");
	printf("\n>> ������ �޴� <<\n\n");
	printf("\n1. ���� ���\t 2. ���� ����\n3. ���� �뿩\t 4. ���� �ݳ�\n5. ���� �˻�\t 6. ȸ�� ���\n7. �α� �ƿ�\t");
	printf("\n��ȣ�� �����ϼ��� :");
	scanf("%d", &n);

	return n;
}

/*-------------------------------------------------
 CustomerMain(): ȸ�� ����
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
			printf("�߸��Է�\n");
		}
	}
	return 0;
}

/*-------------------------------------------------
 CustomerMenu(): ȸ�� �޴�
-------------------------------------------------*/
int CustomerMenu() {
	int n;
	printf("\n>> ȸ�� �޴� <<\n\n");
	printf("1. ���� �˻�\t 2. �뿩 ���\n3. ������������\t 4. ȸ�� Ż��\n5. �α� �ƿ�\t 6. ���α׷� ���� \n");
	printf("\n��ȣ�� �����ϼ��� :");
	scanf("%d", &n);

	return n;
}