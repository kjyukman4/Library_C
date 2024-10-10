#ifndef __MAIN__ 
#define __MAIN__
#include "book.h"
#include "borrow.h"
#include "customer.h"

typedef enum MMENU { JOIN = 1, LOGIN, EXIT} MM;
typedef enum AMENU { REGISTER = 1, BDELETE, RENTAL, RETURN, SEARCH, CLIST, LOGOUT} AM;


int mainmenu();
void Login();
int adminmain();
int adminmenu();
#endif
