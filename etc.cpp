#include "etc.h"

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
