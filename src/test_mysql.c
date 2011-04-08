#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>

int main(int argc, char *argv[]) {
	if (argc != 6) {
		fprintf(stderr, "USAGE: cmd <host> <user> <passwd> <db> <query>\n");
		return 1;
	}

	char *host = argv[1];
	char *user = argv[2];
	char *passwd = argv[3];
	char *db = argv[4];
	char *query = argv[5];

	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "suggestd");

	if (!mysql_real_connect(&mysql, host, user, passwd, db, 0, NULL, 0)) {
		fprintf(stderr, "Could not connect to database. Error: %s\n", mysql_error(&mysql));
		return 1;
	}
		
	if (mysql_query(&mysql, query) != 0) {
		fprintf(stderr, "Could not execute query. Error: %s\n", mysql_error(&mysql));
		return 1;
	}

	MYSQL_RES *result = mysql_use_result(&mysql);
	unsigned int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		unsigned long *lengths = mysql_fetch_lengths(result);
	
		unsigned int i;
		for (i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_close(&mysql);
	return 0;
}
