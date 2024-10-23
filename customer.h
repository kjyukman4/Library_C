#ifndef __CUSTOMER__
#define __CUSTOMER__
#include "common.h"
#include "borrow.h"

int CustomerMain();
int CustomerMenu();
void Join_Customer();
customer* Register_Customer();
void Sort_Customer();
bool Dup_C_num(char*);
void Customer_Search_Main();
int Customer_Search_Menu();
void Search_Customer(char*,int);
void Modify_Customer();
int Delete_Customer();
#endif
