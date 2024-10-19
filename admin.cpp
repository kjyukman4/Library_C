#include "admin.h"
/*-------------------------------------------------
 AdminMain(): ������ ����
-------------------------------------------------*/
int AdminMain() {
	AM::MENU menu;
	int i, k, state;
	while (menu = (AM::MENU)AdminMenu()) {
		switch (menu) {
		case AM::REGISTER:
			Register_Book();
			break;
		case AM::BDELETE:
			Delete_Book_Main();
			break;
		case AM::RENTAL:
			Rental_Main();
			break;
		case AM::RETURN:
			Return_Main();
			break;
		case AM::SEARCH:
			Search_Main();
			break;
		case AM::CLIST:
			Customer_Search_Main();
			break;
		case AM::LOGOUT:
			printf("�α׾ƿ��մϴ�..\n");
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