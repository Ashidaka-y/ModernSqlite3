#ifndef __MSQLITE_H__
#define __MSQLITE_H__

#define SQLITE_HAS_CODEC
#include "sqlite3.h"

#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <assert.h>

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

//#ifdef UNICODE
//#define tstring wstring
//#define MT(x) _T(x)
//#else
//#define MT
//#define tstring string
//#endif

//#define _T(x) L##x

using namespace std;

class MSqlite
{
public:
	MSqlite();
	~MSqlite();

	BOOL OpenDatabase(const string& databaseName, const string& password = "");

	BOOL CloseDatabase();

	BOOL ExectSQL(const string& sQuery);


protected:
	void GetLastError(char* pBuffer, int nLen);

private:
	sqlite3* m_pSqlite;
	string m_sLstMsg;
};
#endif// __MSQLITE_H__
