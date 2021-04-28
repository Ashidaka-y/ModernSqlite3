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

#ifdef _WIN32
#include <windows.h>
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
#define MSAPI ¡ª__declspec(dllexport)  
#else
#define MSAPI 
#endif

//#ifdef UNICODE
//#define tstring wstring
//#define MT(x) _T(x)
//#else
//#define MT
//#define tstring string
//#endif

//#define _T(x) L##x
#define MAX_STR 1024

using namespace std;

class MSqlite
{
public:
	MSqlite();
	~MSqlite();

	BOOL OpenDatabase(const string& databaseName, const string& password = "", const string& tableName = "");
	BOOL CloseDatabase();
	BOOL InitContext();

	void Clear();

	void SetCurrentTable(const string& tableName);

	BOOL DecodeTableInfo();

	template <typename T, typename... Arg>
	void Insert(T head, Arg... arg);
	void Insert();

	BOOL SelectTable(const string& sQuery);

	BOOL ExectSQL(const string& sQuery, int* nRow, int* nColumn, char*** szResult);
	BOOL ExectSQL(const string& sQuery);
	string GetLastError();
	BOOL GetAllTableName();
	BOOL GetTableInfo(const string& tableName);
protected:
	BOOL OpenDB();
	BOOL OpenDBHavePw();
	BOOL CloseDB();

	void FreeTable(char** pResult);

	BOOL CheckFiled();


private:
	sqlite3* m_pSqlite;
	string m_sLstMsg;
	string m_sCurrentDB;
	string m_sPassword;
	string m_sCurrentTable;
	string m_sUseTableInfo;
	vector<string> m_vecTables;
	map<string, list<tuple<string, string>>> m_mpTableInfo;
};
#endif// __MSQLITE_H__
