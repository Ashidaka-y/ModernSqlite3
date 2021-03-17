#include <windows.h>
#include <iostream>
#include "MSqlite.h"

int main()
{

	MSqlite ms;
	ms.OpenDatabase("./hello.db");
	ms.ExectSQL("create table hello('a' int,'b' text)");
	std::cout << "hellowrold" << std::endl;
	return 0;
}