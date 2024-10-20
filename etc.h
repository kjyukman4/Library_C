#ifndef __ETC__
#define __ETC__
#include <time.h>
#include "common.h"

cTime Current_Time();

void Finput_Book();
void Finput_Borrow();
void Finput_Customer();
void Call_Book();
void Call_Borrow();
void Call_Customer();
book* Book_Load(FILE**);
borrow* Borrow_Load(FILE**);
customer* Customer_Load(FILE**);
#endif