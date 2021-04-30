#include <iostream>
#include "MSqlite.h"

int main()
{

	MSqlite ms;
	ms.OpenDatabase("./createTableTest.db");
	if (!ms.ExectSQL("create table test('a' int,'b' text,primary key(a,b))"))
	{
		printf("Create Table Failed,Error:%s\n", ms.GetLastError().c_str());
		return FALSE;
	}
	printf("Create Table Success!\n");

	if (!ms.ExectSQL("insert into test values(1,'insert1')"))
	{
		printf("Insert Failed,Error:%s\n", ms.GetLastError().c_str());
		return FALSE;
	}

	if (!ms.ExectSQL("insert into test values(2,'insert2')"))
	{
		printf("Insert Failed,Error:%s\n", ms.GetLastError().c_str());
		return FALSE;
	}

	if (!ms.ExectSQL("insert into test values(3,'insert3')"))
	{
		printf("Insert Failed,Error:%s\n", ms.GetLastError().c_str());
		return FALSE;
	}

	char** pResult;
	int nRow, nCol;
	if (!ms.ExectSQL("select * from test", &nRow, &nCol, &pResult))
	{
		printf("Select Failed,Error:%s\n", ms.GetLastError().c_str());
		return FALSE;
	}
	printf("Select Success!\n");
	for (int i = 0; i < nCol; i++)
	{
		printf("%s ", pResult[i]);
	}
	printf("\n");
	for (int x = nCol; x < nCol * nRow + nCol; x++)
	{
		printf("%s ", pResult[x]);
	}
	printf("\n");
	ms.FreeTable(pResult);
	getchar();
	return 0;
}