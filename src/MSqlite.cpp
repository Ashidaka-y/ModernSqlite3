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

BOOL MSqlite::OpenDatabase(const string& databaseName, const string& password, const string& tableName)
{
	if (databaseName.empty())
	{
		return FALSE;
	}
	m_sCurrentDB = databaseName;
	if (password.empty())
	{
		if (!OpenDB())
		{
			return FALSE;
		}
	}
	else
	{
		m_sPassword = password;
		if (!OpenDBHavePw())
		{
			return FALSE;
		}

	}
	return TRUE;
}

BOOL MSqlite::CloseDatabase()
{
	if (!CloseDB())
	{
		return FALSE;
	}
	return TRUE;
}

void MSqlite::Clear()
{
	m_pSqlite = NULL;
	m_sLstMsg.clear();
	m_sCurrentDB.clear();
	m_sPassword.clear();
}

BOOL MSqlite::ExectSQL(const string& sQuery, int* nRow, int* nColumn, char*** szResult)
{
	char* errmsg;
	sqlite3_get_table(m_pSqlite, sQuery.c_str(), szResult, nRow, nColumn, &errmsg);
	if (errmsg != NULL)
	{
		m_sLstMsg = errmsg;
		return FALSE;
	}
	return TRUE;
}

BOOL MSqlite::ExectSQL(const string& sQuery)
{
	char* errmsg;
	sqlite3_exec(m_pSqlite, sQuery.c_str(), NULL, NULL, &errmsg);
	if (errmsg != NULL)
	{
		m_sLstMsg = errmsg;
		return FALSE;
	}
	return TRUE;
}

string MSqlite::GetLastError()
{
	return m_sLstMsg;
}

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

BOOL MSqlite::OpenDB()
{

	if (sqlite3_open(m_sCurrentDB.c_str(), &m_pSqlite) != SQLITE_OK)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL MSqlite::OpenDBHavePw()
{
	if (sqlite3_open(m_sCurrentDB.c_str(), &m_pSqlite) != SQLITE_OK)
	{
		return FALSE;
	}
	//��ʱ�Ҳ���sqlite3_key���� :)
	//if (sqlite3_key(&m_pSqlite,m_sCurrentPW.c_str(), m_sCurrentPW.size()) != SQLITE_OK)
	//{
	//	return FALSE;
	//}
	return TRUE;
}

BOOL MSqlite::CloseDB()
{
	if (sqlite3_close(m_pSqlite) != SQLITE_OK)
	{
		return FALSE;
	}
	m_pSqlite = NULL;
	return TRUE;
}

void MSqlite::FreeTable(char** pResult)
{

	sqlite3_free_table(pResult);
}