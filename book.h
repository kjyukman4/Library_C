#ifndef __BOOK__
#define __BOOK__
#include "common.h"

namespace BM {
	enum MENU { NAME = 1, ISBN, QUIT };
}
namespace BSM {
	enum MENU { NAME = 1, COMPANY, ISBN, WRITER, ALL, QUIT };
}
void Register_Book();
book* Info_Input_Book();
void Sort_Book();
void Delete_Book_Main();
int Delete_Book_Menu();
int Delete_Book();
void Search_Main();
int Search_Menu();
int Search_Book(char *, int);


#endif