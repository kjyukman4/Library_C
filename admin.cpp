#include "admin.h"
/*-------------------------------------------------
 AdminMain(): 관리자 메인
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
			printf("로그아웃합니다..\n");
			return 0;
		default:
			printf("잘못입력\n");
		}
	}
	return 0;
}


/*-------------------------------------------------
 AdminMain(): 관리자 메뉴
-------------------------------------------------*/
int AdminMenu() {
	int n;
	system("cls");
	printf("\n>> 관리자 메뉴 <<\n\n");
	printf("\n1. 도서 등록\t 2. 도서 삭제\n3. 도서 대여\t 4. 도서 반납\n5. 도서 검색\t 6. 회원 목록\n7. 로그 아웃\t");
	printf("\n번호를 선택하세요 :");
	scanf("%d", &n);

	return n;
}