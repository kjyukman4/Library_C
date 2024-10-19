#ifndef __ADMIN__
#define __ADMIN__

#include "book.h"
#include "borrow.h"
#include "customer.h"

namespace AM {
	enum MENU { REGISTER = 1, BDELETE, RENTAL, RETURN, SEARCH, CLIST, LOGOUT };
}

int AdminMain();
int AdminMenu();

#endif