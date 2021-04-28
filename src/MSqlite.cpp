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
	if (InitContext())
	{
		return FALSE;
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
	m_sCurrentTable.clear();
	m_sUseTableInfo.clear();
	m_mpTableInfo.clear();
}

void MSqlite::SetCurrentTable(const string& tableName)
{
	m_sCurrentTable = tableName;
	//if (!m_sCurrentTable.empty())
	//{
	//	Clear();
	//}
	//char buf[MAX_STR] = { 0 };
	//sprintf_s(buf, MAX_STR, "SELECFT name FROM sqlite_master WHERE type = 'table' AND name = '%s'", tableName.c_str());
	//char** pResult = NULL;
	//char* errmsg = NULL;
	//int nRow, nCol;
	//sqlite3_get_table(m_pSqlite, buf, &pResult, &nRow, &nCol, &errmsg);
	//if (errmsg == NULL)
	//{
	//	if (nRow == 0)
	//	{
	//		return FALSE;
	//	}
	//	m_sCurrentTable = nRow;
	//	sqlite3_free_table(pResult);
	//}
	//else
	//{
	//	m_sLstMsg = errmsg;
	//	sqlite3_free(errmsg);
	//	return FALSE;
	//}
	//if (!GetTableInfo(tableName))
	//{
	//	return FALSE;
	//}
}

BOOL MSqlite::GetTableInfo(const string& tableName)
{
	char buf[MAX_STR] = { 0 };
	sprintf_s(buf, MAX_STR, "SElECT * FROM sqlite_master WHERE type = 'table' AND name = '%s'", tableName.c_str());
	char** pResult = NULL;
	char* errmsg = NULL;
	int nRow, nCol;
	if (!ExectSQL(buf, &nRow, &nCol, &pResult))
	{
		return FALSE;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%s - ", pResult[i]);
	}
	//for (int i = 0; i <= nRow; i++)
	//{
	//	for (int x = 0; x < nCol; x++)
	//	{
	//		printf("%s - ", pResult[x * i + x]);

	//	}
	//	printf("\n");
	//}
	if (DecodeTableInfo())
	{
		return FALSE;
	}
	//sqlite3_get_table(m_pSqlite, buf, &pResult, &nRow, &nCol, &errmsg);
	//if (errmsg == NULL)
	//{
	//	if (nRow == 0)
	//	{
	//		return FALSE;
	//	}
	//	m_sUseTableInfo = nRow;
	//	sqlite3_free_table(pResult);
	//}
	//else
	//{
	//	m_sLstMsg = errmsg;
	//	sqlite3_free(errmsg);
	//	return FALSE;
	//}
	return TRUE;

}

BOOL MSqlite::DecodeTableInfo()
{
	return FALSE;
}

template <typename T, typename... Arg>
void MSqlite::Insert(T head, Arg... arg)
{

}

void MSqlite::Insert()
{}

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
	//暂时找不到sqlite3_key函数 :)
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

BOOL MSqlite::InitContext()
{

	if (!GetAllTableName())
	{
		return FALSE;
	}

	for (int i = 0; i < m_vecTables.size(); i++)
	{
		if (!GetTableInfo(m_vecTables[i]))
		{
			return FALSE;
		}
	}
	if (1)
	{
	}
}

BOOL MSqlite::GetAllTableName()
{
	string sQuery = "SELECT name FROM sqlite_master WHERE type = 'table'";
	//string sQuery = "SELECFT name FROM sqlite_master WHERE type = 'table' order by name";
	char** pResult = NULL;
	int nRow, nCol;
	if (!ExectSQL(sQuery, &nRow, &nCol, &pResult))
	{
		return FALSE;
	}
	for (int i = 1; i <= nCol; i++)
	{
		m_vecTables.push_back(pResult[i]);
	}
	FreeTable(pResult);
	return TRUE;
}

void MSqlite::FreeTable(char** pResult)
{
	sqlite3_free_table(pResult);
	//sqlite3_free(pResult);
}



