#include "MSqlite.h"


MSqlite::MSqlite()
{
	m_pSqlite = NULL;
}

MSqlite::~MSqlite()
{
	if (m_pSqlite != NULL)
	{
		sqlite3_close(m_pSqlite);
	}
}

BOOL MSqlite::OpenDatabase(const string& databaseName, const string& password)
{
	if (databaseName.size() == 0)
	{
		return FALSE;
	}
	if (sqlite3_open(databaseName.c_str(), &m_pSqlite) != SQLITE_OK)
	{
		return FALSE;
	}
	if (password.size() == 0)
	{
		return TRUE;
	}
	if (sqlite3_keyword_check(password.c_str(), password.size()) != SQLITE_OK)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL MSqlite::CloseDatabase()
{
	if (sqlite3_close(m_pSqlite) != SQLITE_OK)
	{
		return FALSE;
	}
	m_pSqlite = NULL;
	return TRUE;
}

BOOL MSqlite::ExectSQL(const string& sQuery)
{
	char* errmsg;
	if (sqlite3_exec(m_pSqlite, sQuery.c_str(), NULL, NULL, &errmsg))
	{
		m_sLstMsg = errmsg;
		sqlite3_free(errmsg);
		return FALSE;
	}
	return TRUE;
}

void MSqlite::GetLastError(char* pBuffer, int nLen)
{
	strcpy_s(pBuffer, nLen, m_sLstMsg.c_str());
}
