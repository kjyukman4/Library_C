#ifndef __MAIN__ 
#define __MAIN__
#include "book.h"
#include "borrow.h"
#include "customer.h"

namespace MM { 
	enum MMENU { JOIN = 1, LOGIN, EXIT }; 
}
namespace AM {
	enum AMENU{ REGISTER = 1, BDELETE, RENTAL, RETURN, SEARCH, CLIST, LOGOUT };
}
namespace CM {
	enum CMENU { SEARCH = 1, BLIST, MODIFY, DELETE, LOGOUT, QUIT };
}

int MainMenu();
void Login();
int AdminMain();
int AdminMenu();
int CustomerMain();
int CustomerMenu();
#endif
