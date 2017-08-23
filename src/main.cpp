#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i = 0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}



int main(int argc, char **argv)
{
	sqlite3* db;
	char* zErr;
	int rc;
	char* sql;

	rc = sqlite3_open("testDB.db", &db);

	if(rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	printf("Sqlite3 ver: %s\n", SQLITE_VERSION);

	sql = "create table DB( id integer primary key,"
		"                       name text, cid int)";

	rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

	if(rc != SQLITE_OK)
	{
		if(zErr != NULL)
		{
			fprintf(stderr, "SQL error: %s\n", zErr);
			sqlite3_free(zErr);
		}
	}

	sql = "insert into DB (name,id) values ('Allen Huang',1)";
	rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

	if(rc != SQLITE_OK)
	{
		if(zErr != NULL)
		{
			fprintf(stderr, "SQL error: %s\n", zErr);
			sqlite3_free(zErr);
		}
	}


	sql = "insert into DB (name,id) values ('Allen Huang 2',2)";
	rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

	if(rc != SQLITE_OK)
	{
		if(zErr != NULL)
		{
			fprintf(stderr, "SQL error: %s\n", zErr);
			sqlite3_free(zErr);
		}
	}

	sql = "insert into DB (name,id) values ('Allen Huang 3',3)";
	rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

	if(rc != SQLITE_OK)
	{
		if(zErr != NULL)
		{
			fprintf(stderr, "SQL error: %s\n", zErr);
			sqlite3_free(zErr);
		}
	}

	const char* data = "CallBack function caller";
	sql = "SELECT * FROM DB";
	rc = sqlite3_exec(db, sql, callback, NULL, &zErr);

	if(rc != SQLITE_OK)
	{
		if(zErr != NULL)
		{
			fprintf(stderr, "SQL error: %s\n", zErr);
			sqlite3_free(zErr);
		}
	}

	sqlite3_close(db);
	system("PAUSE");
	return 0;
}