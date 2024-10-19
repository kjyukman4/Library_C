#ifndef __MAIN__ 
#define __MAIN__
#include "book.h"
#include "borrow.h"
#include "customer.h"
#include "admin.h"

namespace MM {
	enum MENU { JOIN = 1, LOGIN, QUIT };
}

int MainMenu();
void Login();

#endif
