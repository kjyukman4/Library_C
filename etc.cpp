#include "etc.h"
extern book** g_book;
extern borrow** g_borrow;
extern customer** g_customer;
extern int numofbook;
extern int numofborrow;
extern int numofcustomer;

/*-------------------------------------------------
 Current_Time(): 현재(시스템) 시간
-------------------------------------------------*/
cTime Current_Time() {
	cTime ctime;
	struct tm* t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);


	ctime.year = t->tm_year + 1900;
	ctime.month = t->tm_mon + 1;
	ctime.day = t->tm_mday;
	ctime.hour = t->tm_hour;
	ctime.minute = t->tm_min;
	ctime.second = t->tm_sec;

	return ctime;
}

/*-------------------------------------------------
 Finput_Book(): 도서정보 파일 입력
-------------------------------------------------*/
void Finput_Book() {
	FILE* ibkp;
	int i = 0;
	ibkp = fopen("book.txt", "w");
	while (i < numofbook) {
		fprintf(ibkp, "%.lf %s %s %s %s %s %d\n", g_book[i]->Bnum, g_book[i]->name, g_book[i]->company, g_book[i]->writer, g_book[i]->ISBN, g_book[i]->place, g_book[i]->state);
		i++;
	}
	fclose(ibkp);
}

/*-------------------------------------------------
 Finput_Borrow(): 대여도서정보 파일 입력
-------------------------------------------------*/
void Finput_Borrow() {
	FILE* ibp;
	int i = 0;
	ibp = fopen("borrow.txt", "w");
	while (i < numofborrow) {
		fprintf(ibp, "%s %s %.lf %d %d %d %d %d %d %d %d %d %d %d %d\n", g_borrow[i]->num, g_borrow[i]->state, g_borrow[i]->Bnum, g_borrow[i]->rnt.year, g_borrow[i]->rnt.month,
			g_borrow[i]->rnt.day, g_borrow[i]->rnt.hour, g_borrow[i]->rnt.minute, g_borrow[i]->rnt.second, g_borrow[i]->rtn.year, g_borrow[i]->rtn.month, g_borrow[i]->rtn.day,
			g_borrow[i]->rtn.hour, g_borrow[i]->rtn.minute, g_borrow[i]->rtn.second);
		i++;
	}
	fclose(ibp);
}

/*-------------------------------------------------
 Finput_Customer(): 회원정보 파일 입력
-------------------------------------------------*/
void Finput_Customer() {
	FILE* icp;
	int i = 0;
	icp = fopen("customer.txt", "w");
	while (i < numofcustomer) {
		fprintf(icp, "%s %s %s %s %s\n", g_customer[i]->num, g_customer[i]->pwd, g_customer[i]->name, g_customer[i]->adr, g_customer[i]->Pnum);
		i++;
	}
	fclose(icp);
}

/*-------------------------------------------------
 Call_Book(): 도서정보 구조체 삽입
-------------------------------------------------*/
void Call_Book() {
	FILE* obkp;
	obkp = fopen("book.txt", "r");
	if (obkp != NULL) {
		printf("도서목록 불러오기 완료!\n");
		while (1) {
			if (numofbook == 0) {
				g_book[0] = (book*)malloc(sizeof(book));
			}
			else {
				g_book = (book**)realloc(g_book, (numofbook + 1) * sizeof(book*));
			}
			g_book[numofbook] = Book_Load(&obkp);
			if (g_book[numofbook] == NULL) {
				break;
			}
			else {
				numofbook++;
			}
		}
		fclose(obkp);
	}
}

/*-------------------------------------------------
 Call_Borrow(): 대여도서정보 구조체 삽입
-------------------------------------------------*/
void Call_Borrow() {
	FILE* obp;
	obp = fopen("borrow.txt", "r");
	if (obp != NULL) {
		printf("대여목록 불러오기 완료!\n\n");
		while (1) {
			if (numofborrow == 0) {
				g_borrow[0] = (borrow*)malloc(sizeof(borrow));
			}
			else {
				g_borrow = (borrow**)realloc(g_borrow, (numofborrow + 1) * sizeof(borrow*));
			}
			g_borrow[numofborrow] = Borrow_Load(&obp);
			if (g_borrow[numofborrow] == NULL) {
				break;
			}
			else {
				numofborrow++;
			}
		}
		fclose(obp);
	}
	
}

/*-------------------------------------------------
 Call_Customer(): 회원정보 구조체 삽입
-------------------------------------------------*/
void Call_Customer() {
	FILE* ocp;
	ocp = fopen("customer.txt", "r");
	if (ocp != NULL) {
		printf("회원목록 불러오기 완료!\n");
		while (1) {
			if (numofcustomer == 0) {
				g_customer[0] = (customer*)malloc(sizeof(customer));
			}
			else {
				g_customer = (customer**)realloc(g_customer, (numofcustomer + 1) * sizeof(customer*));
			}
			g_customer[numofcustomer] = Customer_Load(&ocp);

			if (g_customer[numofcustomer] == NULL) {
				break;
			}
			else {
				numofcustomer++;
			}
		}
		fclose(ocp);
	}
}

/*-------------------------------------------------
 Book_Load(FILE**): 도서정보 파일로부터 가져오기 
-------------------------------------------------*/
book* Book_Load(FILE** obkp) {
	book* BKP;
	int res,state;
	BKP = (book*)malloc(sizeof(book));
	res = fscanf(*obkp, "%lf %s %s %s %s %s %d", &BKP->Bnum, BKP->name, BKP->company, BKP->writer, BKP->ISBN, BKP->place, &state);
	BKP->state = state ? true : false;
	if (res == EOF) {
		return NULL;
	}
	return BKP;
}

/*-------------------------------------------------
 Borrow_Load(FILE**): 대여도서정보 파일로부터 가져오기
-------------------------------------------------*/
borrow* Borrow_Load(FILE** obp) {
	borrow* BP;
	int res,state;
	BP = (borrow*)malloc(sizeof(borrow));
	res = fscanf(*obp, "%s %d %lf %d %d %d %d %d %d %d %d %d %d %d %d", BP->num, &state, &BP->Bnum, &BP->rnt.year, &BP->rnt.month,
		&BP->rnt.day, &BP->rnt.hour, &BP->rnt.minute, &BP->rnt.second, &BP->rtn.year, &BP->rtn.month, &BP->rtn.day, &BP->rtn.hour, &BP->rtn.minute, &BP->rtn.second);
	BP->state = state ? true : false;
	if (res == EOF) {
		return NULL;
	}
	return BP;
}

/*-------------------------------------------------
 Customer_Load(FILE**): 회원정보 파일로부터 가져오기
-------------------------------------------------*/
customer* Customer_Load(FILE** ocp) {
	customer* CP;
	int res;
	CP = (customer*)malloc(sizeof(customer));
	res = fscanf((*ocp), "%s %s %s %s %s", CP->num, CP->pwd, CP->name, CP->adr, CP->Pnum);
	if (res == EOF) {
		return NULL;
	}
	return CP;
}
