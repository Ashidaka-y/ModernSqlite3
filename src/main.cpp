#include <windows.h>
#include <iostream>
#include "MSqlite.h"

int main()
{

	MSqlite ms;
	ms.OpenDatabase("./hello.db");
	if (!ms.ExectSQL("create table hello('a' int,'b' text)"))
	{
		printf("%s\n", ms.GetLastError().c_str());
	}
	//if (!ms.GetAllTableName())
	//{
	//	printf("%s\n", ms.GetLastError().c_str());
	//}
	if (!ms.InitContext())
	{
		return false;
	}
	std::cout << "hellowrold" << std::endl;
	return 0;
}