#include <iostream>
#include "MSqlite.h"

int main()
{

	MSqlite ms;
	ms.OpenDatabase("./createTableTest.db");
	if (!ms.ExectSQL("create table hello('a' int,'b' text,primary key(a,b))"))
	{
		printf("Create Table Failed,Error:%s\n", ms.GetLastError().c_str());
	}
	printf("Create Table Success!\n");
	return 0;
}