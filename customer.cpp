#include "customer.h"

namespace CM {
	enum MENU { SEARCH = 1, BLIST, MODIFY, DELETE, LOGOUT };
}
namespace CSM {
	enum MENU { NAME = 1, NUM, ALL, QUIT };
}

extern book** g_book;
extern borrow** g_borrow;
extern customer** g_customer;
extern int numofbook;
extern int numofborrow;
extern int numofcustomer;
extern char Current_User[100];

/*-------------------------------------------------
 CustomerMain(): ȸ�� ����
-------------------------------------------------*/
int CustomerMain() {
	CM::MENU menu;

	while (menu = (CM::MENU)CustomerMenu()) {
		system("cls");
		switch (menu) {
		case CM::SEARCH:
			Search_Main();
			break;
		case CM::BLIST:
			Search_Borrow(Current_User);
			break;
		case CM::MODIFY:
			Modify_Customer();
			break;
		case CM::DELETE:
			if (Delete_Customer() == 1) {
				return 0;
			}
		case CM::LOGOUT:
			printf("�α׾ƿ��մϴ�.\n");
			return 0;
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

/*-------------------------------------------------
 Join_Customer(): ȸ������
-------------------------------------------------*/
void Join_Customer() {
	if (numofcustomer == 0) {
		g_customer[0] = (customer*)malloc(sizeof(customer));
	}
	else {
		g_customer = (customer**)realloc(g_customer, (numofcustomer + 1) * sizeof(customer*));
	}
	g_customer[numofcustomer] = Register_Customer();
	if (g_customer[numofcustomer] != NULL) {
		numofcustomer++;
	}
	Sort_Customer();
	Finput_Customer();
}

/*-------------------------------------------------
 * Register_Customer(): ȸ�����
-------------------------------------------------*/
customer* Register_Customer() {
	customer* c;
	c = (customer*)malloc(sizeof(customer));
	printf("\n>> ȸ�� ���� <<\n\n");
	printf("�й�:");
	scanf("%s", c->num);
	if (Dup_C_num(c->num) == true) {
		return NULL;
	}
	printf("��й�ȣ:");
	scanf("%s", c->pwd);
	printf("�̸�:");
	scanf("%s", c->name);
	printf("�ּ�:");
	scanf("%s", c->adr);
	printf("��ȭ��ȣ:");
	scanf("%s", c->Pnum);

	system("cls");
	printf("ȸ�������� �Ϸ�Ǿ����ϴ�!!\n");

	return c;
}

/*-------------------------------------------------
 Customer_Sort(): ȸ���� �й������� ����
-------------------------------------------------*/
void Sort_Customer() {
	customer* min;
	int i, j;

	for (i = 0; i < numofcustomer; i++) {
		for (j = i; j < numofcustomer; j++) {
			if (strcmp(g_customer[i]->num, g_customer[j]->num) == 1) {
				printf("i:%d\nj:%d\n", i, j);
				min = g_customer[i];
				g_customer[i] = g_customer[j];
				g_customer[j] = min;
			}
		}
	}
}

/*-------------------------------------------------
 Dup_C_num(char* �й�(ID)): �й�(ID)�ߺ� üũ
-------------------------------------------------*/
bool Dup_C_num(char* s) {
	int i;
	for (i = 0; i < numofcustomer; i++) {
		if (strcmp(g_customer[i]->num, s) == 0) {
			system("cls");
			printf("ȸ�������� �Ұ��մϴ�.(����:�й�����)\n");
			return true;
		}
	}
	printf("ȸ�������� �����մϴ�!\n");
	return false;
}

/*-----------------------------------------------------------
 Customer_Search_Main(): �� ��ȸ ����
-----------------------------------------------------------*/
void Customer_Search_Main() {
	CSM::MENU menu;

	char name[100];
	if (numofcustomer != 0) {
		while (menu = (CSM::MENU)Customer_Search_Menu()) {
			system("cls");
			switch (menu) {
			case CSM::NAME:
				printf("�̸� �Է�:");
				scanf("%s", name);
				Search_Customer(name, 0);
				break;
			case CSM::NUM:
				printf("�й� �Է�:");
				scanf("%s", name);
				Search_Customer(name, 1);
				break;
			case CSM::ALL:
				Search_Customer((char *)"", 2);
				break;
			case CSM::QUIT:
				printf("ȸ�� ��ȸ ���");
				return ;
			default:
				printf("�߸��Է�");
				break;
			}
		}
		
	}
	else {
		printf("\n��ϵ� ȸ���� �����ϴ�.\n");
	}
}

/*-----------------------------------------------------------
 Customer_Search_Menu(): �� ��ȸ �޴�
-----------------------------------------------------------*/
int Customer_Search_Menu() {
	int n;
	printf("\n>> ȸ�� ��� <<\n\n");
	printf("1. �̸� �˻�\t2. �й� �˻�\n3. ��ü �˻�\t4. ���� �޴�\n");
	scanf("%d", &n);
	return n;
}

/*-----------------------------------------------------------
 Search_Customer(char*, int state): �� ��ȸ
  state : <0> �̸� �˻�
		  <1> �й� �˻�
		  <2> ��ü �˻�
-----------------------------------------------------------*/
void Search_Customer(char* name, int state) {
	int i, j = 0;
	
	printf(">> �˻� ��� <<\n\n");
	if (state == 0) {
		for (i = 0; i < numofcustomer; i++) {
			if (strcmp(name, g_customer[i]->name) == 0) {
				printf("�й�:%s\n�̸�:%s\n�ּ�:%s\n��ȭ��ȣ:%s\n\n", g_customer[i]->num, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
				j++;
			}
		}
	}
	else if (state == 1) {
		for (i = 0; i < numofcustomer; i++) {
			if (strcmp(name, g_customer[i]->num) == 0) {
				printf("�й�:%s\n�̸�:%s\n�ּ�:%s\n��ȭ��ȣ:%s\n\n", g_customer[i]->num, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
				j++;
			}
		}
	}
	else {
		for (i = 0; i < numofcustomer; i++) {
			printf("�й�:%s\n�̸�:%s\n�ּ�:%s\n��ȭ��ȣ:%s\n\n", g_customer[i]->num, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
			j++;
		}
	}
	if (j == numofbook) {
		printf("��ϵ� ȸ���� �����ϴ�.\n");
	}
}

/*-----------------------------------------------------------
 Modify_Customer(char*, int state): �� ���� ����
-----------------------------------------------------------*/
void Modify_Customer() {
	int i = 0;
	char pwd[100], adr[100], Pnum[100];
	printf("\n---���� ����� ����---\n\n");
	while (i < numofcustomer) {
		if (strcmp(Current_User, g_customer[i]->num) == 0) {
			break;
		}
		i++;
	}
	printf("�й�:%s\tpassward:%s\n�̸�:%s\tadress:%s\n��ȭ��ȣ:%s\n", g_customer[i]->num, g_customer[i]->pwd, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
	printf("\n---���� ���� �Է�---\n\n");
	printf("��й�ȣ:");
	scanf("%s", pwd);
	printf("�ּ�:");
	scanf("%s", adr);
	printf("��ȭ��ȣ:");
	scanf("%s", Pnum);
	strcpy(g_customer[i]->pwd, pwd);
	strcpy(g_customer[i]->adr, adr);
	strcpy(g_customer[i]->Pnum, Pnum);
	system("cls");
	printf("\n������ �����Ǿ����ϴ�.\n\n");
	Finput_Customer();
}

/*-----------------------------------------------------------
 Modify_Customer(char*, int state): �� ����
-----------------------------------------------------------*/
int Delete_Customer() {
	int P = 0, i = 0, j;
	char c;
	printf("������ �����Ͻðڽ��ϱ�?<Y/N> : ");
	getchar();
	scanf("%c", &c);
	if (c == 'Y') {
		while (i < numofborrow) {
			if (strcmp(Current_User, g_borrow[i]->num) == 0 && g_borrow[i]->state == false) {
				system("cls");
				printf("���� ����(����:���� �̹ݳ�)");
				break;
			}
			i++;
		}
		if (i == numofborrow) {
			if (numofcustomer == 1) {
				g_customer[0] = NULL;
				numofcustomer--;
				system("cls");
				printf("������ �����Ǿ����ϴ�.\n�ʱ�ȭ������ ���ư��ϴ�..\n\n");
				Finput_Customer();
				return 1;
			}
			else {
				for (i = 0; i < numofcustomer; i++) {
					if (strcmp(Current_User, g_customer[i]->num) == 0) {
						break;
					}
				}
				for (j = i; j < numofcustomer; j++) {
					g_customer[j] = g_customer[j + 1];
				}
				g_customer = (customer**)realloc(g_customer, (numofcustomer - 1) * sizeof(customer*));
				numofcustomer--;
				strcpy(Current_User, "");
				system("cls");
				printf("������ �����Ǿ����ϴ�.\n�ʱ�ȭ������ ���ư��ϴ�..\n\n");
				Sort_Customer();
				Finput_Customer();
				return 1;
			}
		}
	}
	else {
		system("cls");
		printf("����մϴ�..\n");
	}
	return 0;
}