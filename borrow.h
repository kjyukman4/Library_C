#ifndef __BORROW__
#define __BORROW__
#include "common.h"
#include "etc.h"
#include "book.h"

void Rental_Main();
int Rental_Menu();
int Rental_Book();
borrow* Borrow(int, int);
int Return_Main();
void Search_Borrow(char *);
void Return_Borrow();
#endif
