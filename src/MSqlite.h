#ifndef __MSQLITE_H__
#define __MSQLITE_H__

#define SQLITE_HAS_CODEC
#include "sqlite3.h"

#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <assert.h>
#include <vector>
#include <list>
#include <map>
#include <regex>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#pragma warning(disable:4251)
#else
typedef BOOL int
#define TRUE 1
#define FLASE 0
#endif

#ifdef _DEBUG
#define ASSERT assert(FALSE)
#else
#define ASSERT 
#endif //DEBUG

#ifdef SHARED_LIB
#define MSAPI __declspec(dllexport)  
#else
#define MSAPI 
#endif

#ifdef UNICODE
typedef wstring tstring;
#define MT(x) _T(x)
#else
#define MT
typedef string tstring;
#endif

#define MAX_STR 1024

using namespace std;

class MSAPI MSqlite
{
public:
	MSqlite();
	~MSqlite();

	typedef vector<list<string>> result;
	typedef list<string> result_item;

	BOOL OpenDatabase(const string& databaseName, const string& password = "", const string& tableName = "");
	BOOL CloseDatabase();
	void Clear();

	BOOL ExectSQL(const string& sQuery, int* nRow, int* nColumn, char*** szResult);
	BOOL ExectSQL(const string& sQuery);

	result Exect(const string& sQuery);

	void FreeTable(char** pResult);

	string GetLastError();

	/*
	BOOL InitContext();
	template <typename T, typename... Arg>
	void Insert(T head, Arg... arg);
	void Insert();
	BOOL SelectTable(const string& sQuery);
	BOOL GetAllTableName();
	void SetCurrentTable(const string& tableName);
	BOOL DecodeTableInfo(const string& strTableSql);
	BOOL GetTableInfo(const string& tableName);
	BOOL CheckFiled();
	*/

protected:
	BOOL OpenDB();
	BOOL OpenDBHavePw();

	BOOL CloseDB();


private:
	sqlite3* m_pSqlite;
	string m_sLstMsg;
	string m_sCurrentDB;
	string m_sPassword;

	//string m_sCurrentTable;
	//string m_sUseTableInfo;
	//vector<string> m_vecTables;
};
#endif// __MSQLITE_H__

//BOOL MSqlite::DecodeTableInfo(const string& strTableSql)
//{
//	//std::regex rRegex("Create table ");
//	return FALSE;
//}

//BOOL MSqlite::GetAllTableName()
//{
//	string sQuery = "SELECT name FROM sqlite_master WHERE type = 'table'";
//	//string sQuery = "SELECFT name FROM sqlite_master WHERE type = 'table' order by name";
//	char** pResult = NULL;
//	int nRow, nCol;
//	if (!ExectSQL(sQuery, &nRow, &nCol, &pResult))
//	{
//		return FALSE;
//	}
//	for (int i = 1; i <= nCol; i++)
//	{
//		m_vecTables.push_back(pResult[i]);
//	}
//	FreeTable(pResult);
//	return TRUE;
//}

//BOOL MSqlite::InitContext()
//{
//
//	if (!GetAllTableName())
//	{
//		return FALSE;
//	}
//
//	for (int i = 0; i < m_vecTables.size(); i++)
//	{
//		if (!GetTableInfo(m_vecTables[i]))
//		{
//			return FALSE;
//		}
//	}
//	if (1)
//	{
//	}
//}

//void MSqlite::SetCurrentTable(const string& tableName)
//{
//	m_sCurrentTable = tableName;
//	//if (!m_sCurrentTable.empty())
//	//{
//	//	Clear();
//	//}
//	//char buf[MAX_STR] = { 0 };
//	//sprintf_s(buf, MAX_STR, "SELECFT name FROM sqlite_master WHERE type = 'table' AND name = '%s'", tableName.c_str());
//	//char** pResult = NULL;
//	//char* errmsg = NULL;
//	//int nRow, nCol;
//	//sqlite3_get_table(m_pSqlite, buf, &pResult, &nRow, &nCol, &errmsg);
//	//if (errmsg == NULL)
//	//{
//	//	if (nRow == 0)
//	//	{
//	//		return FALSE;
//	//	}
//	//	m_sCurrentTable = nRow;
//	//	sqlite3_free_table(pResult);
//	//}
//	//else
//	//{
//	//	m_sLstMsg = errmsg;
//	//	sqlite3_free(errmsg);
//	//	return FALSE;
//	//}
//	//if (!GetTableInfo(tableName))
//	//{
//	//	return FALSE;
//	//}
//}

//BOOL MSqlite::GetTableInfo(const string& tableName)
//{
//	char buf[MAX_STR] = { 0 };
//	sprintf_s(buf, MAX_STR, "SElECT * FROM sqlite_master WHERE type = 'table' AND name = '%s'", tableName.c_str());
//	char** pResult = NULL;
//	char* errmsg = NULL;
//	int nRow, nCol;
//	if (!ExectSQL(buf, &nRow, &nCol, &pResult))
//	{
//		return FALSE;
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		printf("%s - ", pResult[i]);
//	}
//	//for (int i = 0; i <= nRow; i++)
//	//{
//	//	for (int x = 0; x < nCol; x++)
//	//	{
//	//		printf("%s - ", pResult[x * i + x]);
//
//	//	}
//	//	printf("\n");
//	//}
//	//if (DecodeTableInfo())
//	{
//		return FALSE;
//	}
//	//sqlite3_get_table(m_pSqlite, buf, &pResult, &nRow, &nCol, &errmsg);
//	//if (errmsg == NULL)
//	//{
//	//	if (nRow == 0)
//	//	{
//	//		return FALSE;
//	//	}
//	//	m_sUseTableInfo = nRow;
//	//	sqlite3_free_table(pResult);
//	//}
//	//else
//	//{
//	//	m_sLstMsg = errmsg;
//	//	sqlite3_free(errmsg);
//	//	return FALSE;
//	//}
//	return TRUE;
//}

//template <typename T, typename... Arg>
//void MSqlite::Insert(T head, Arg... arg)
//{
//
//}
//
//void MSqlite::Insert()
//{}
