#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include "lex.c"
#include <cassandra.h>


char *readline(char *prompt);

static int tty = 0;


static void
cli_about()
{
	printf("You executed a command!\n");
}

static void
cli_help()
{
	return;
}

static void
cli_show(CassSession* session)
{
	const char* query = "SELECT keyspace_name FROM system_schema.keyspaces;";
    CassStatement* statement = cass_statement_new(query, 0);
	CassFuture* result_future = cass_session_execute(session, statement);

    if (cass_future_error_code(result_future) == CASS_OK) 
    {
      const CassResult* result = cass_future_get_result(result_future);
      CassIterator* iterator = cass_iterator_from_result(result);

      while (cass_iterator_next(iterator))
      {
        const CassRow* row = cass_iterator_get_row(iterator);
        const CassValue* value = cass_row_get_column_by_name(row, "keyspace_name");

        const char* keyspace_name;
        size_t keyspace_name_length;
        cass_value_get_string(value, &keyspace_name, &keyspace_name_length);
        printf("Available keyspace: '%.*s'\n", (int)keyspace_name_length, keyspace_name);
      }
	cass_result_free(result);
    cass_iterator_free(iterator);
	} 
	else 
	{
      const char* message;
      size_t message_length;
      cass_future_error_message(result_future, &message, &message_length);
      fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
    }
	cass_statement_free(statement);
    cass_future_free(result_future);
}

static void
cli_list(CassSession* session)
{
	const char* query = "SELECT * FROM system_schema.columns WHERE keyspace_name = 'test';";
    CassStatement* statement = cass_statement_new(query, 0);
	CassFuture* result_future = cass_session_execute(session, statement);

    if (cass_future_error_code(result_future) == CASS_OK) 
    {
      const CassResult* result = cass_future_get_result(result_future);
      CassIterator* iterator = cass_iterator_from_result(result);

      while (cass_iterator_next(iterator))
      {
        const CassRow* row = cass_iterator_get_row(iterator);
        const CassValue* value = cass_row_get_column_by_name(row, "table_name");

        const char* table_name;
        size_t table_name_length;
        cass_value_get_string(value, &table_name, &table_name_length);
        printf("Keyspace contents: '%.*s'\n", (int)table_name_length, table_name);
      }
	  cass_result_free(result);
      cass_iterator_free(iterator);
	} 
	else 
	{
      const char* message;
      size_t message_length;
      cass_future_error_message(result_future, &message, &message_length);
      fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
    }
	cass_statement_free(statement);
    cass_future_free(result_future);
}

static void
cli_use(CassSession* session)
{
	const char* query = "USE test;";
    CassStatement* statement = cass_statement_new(query, 0);
	CassFuture* result_future = cass_session_execute(session, statement);

    if (cass_future_error_code(result_future) == CASS_OK) 
    {
      const CassResult* result = cass_future_get_result(result_future);
      cass_result_free(result);
      printf("Keyspace set.\n");
	} 
	else 
	{
      const char* message;
      size_t message_length;
      cass_future_error_message(result_future, &message, &message_length);
      fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
    }
	cass_statement_free(statement);
    cass_future_free(result_future);
}

static void 
cli_get(CassSession* session)
{
	const char* query = "SELECT id FROM test.test_table;";
	CassStatement* statement = cass_statement_new(query, 0);
	CassFuture* result_future = cass_session_execute(session, statement);

	if (cass_future_error_code(result_future) == CASS_OK)
	{
	  const CassResult* result = cass_future_get_result(result_future);
      CassIterator* iterator = cass_iterator_from_result(result);

      while (cass_iterator_next(iterator))
      {
        const CassRow* row = cass_iterator_get_row(iterator);
        const CassValue* value = cass_row_get_column_by_name(row, "id");

        const char* col_id;
        size_t col_id_length;
        cass_value_get_string(value, &col_id, &col_id_length);
        printf("Key value: '%.*s'\n", (int)col_id_length, col_id);
      }
	  cass_result_free(result);
      cass_iterator_free(iterator);
	}
	else 
	{
      const char* message;
      size_t message_length;
      cass_future_error_message(result_future, &message, &message_length);
      fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
    }
	cass_statement_free(statement);
    cass_future_free(result_future);
}

static void
cli_insert(CassSession* session)
{
	const char* query = "INSERT INTO test.test_table (id) VALUES ('three');";
    CassStatement* statement = cass_statement_new(query, 0);
	CassFuture* result_future = cass_session_execute(session, statement);

	cass_statement_free(statement);
    cass_future_free(result_future);
}

void
cli()
{
	CassCluster* cluster = cass_cluster_new();
	CassSession* session = cass_session_new();
	cass_cluster_set_contact_points(cluster, "127.0.0.1");
	CassFuture* connect_future = cass_session_connect(session, cluster);

	char *cmdline = NULL;
	char cmd[BUFSIZE], prompt[BUFSIZE];
	int pos;

	tty = isatty(STDIN_FILENO);
	if (tty)
		cli_about();

	/* Main command line loop */
	for (;;) {
		if (cmdline != NULL) {
			free(cmdline);
			cmdline = NULL;
		}
		memset(prompt, 0, BUFSIZE);
		sprintf(prompt, "cassandra> ");

		if (tty)
			cmdline = readline(prompt);
		else
			cmdline = readline("");

		if (cmdline == NULL)
			continue;

		if (strlen(cmdline) == 0)
			continue;

		if (!tty)
			printf("%s\n", cmdline);

		if (strcmp(cmdline, "?") == 0) {
			cli_help();
			continue;
		}
		if (strcmp(cmdline, "quit") == 0 ||
		    strcmp(cmdline, "q") == 0)
			break;

		memset(cmd, 0, BUFSIZE);
		pos = 0;
		nextarg(cmdline, &pos, " ", cmd);

		if (strcmp(cmd, "about") == 0 || strcmp(cmd, "a") == 0) {
			cli_about();
			continue;
		}

		if (strcmp(cmd, "show") == 0 || strcmp(cmd, "s") == 0) {
			cli_show(session);
			continue;
		}

		if (strcmp(cmd, "list") == 0 || strcmp(cmd, "l") == 0) {
			cli_list(session);
			continue;
		}

		if (strcmp(cmd, "use") == 0 || strcmp(cmd, "u") == 0) {
			cli_use(session);
			continue;
		}

		if (strcmp(cmd, "get") == 0 || strcmp(cmd, "g") == 0) {
			cli_get(session);
			continue;
		}

		if (strcmp(cmd, "insert") == 0 || strcmp(cmd, "i") == 0) {
			cli_insert(session);
			continue;
		}

	}
}


int
main(int argc, char**argv)
{
	
	cli();
	
	
	exit(0);
}
