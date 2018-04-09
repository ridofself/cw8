/* user_cgi.c */

#include <stdio.h>
#include <stdlib.h>
#include "string.h" /* strcpy */
#include "user.h"
#include "value.h"

int main(void)
	{
	char *data;
	char name[NAME_LENGTH];
	char password[HASH_LENGTH];
	struct user newUser;

	printf("Content-Type: text/html;char *set=us-ascii\n\n");

	data = getenv("QUERY_STRING");
	if ( data == NULL ) printf("<p>null input</p>\n\n");
	else printf("<p>you done sent: %s</p>\n\n", data);

	strcpy(name, value_copy(data, "name"));
	strcpy(password, value_copy(data, "password"));
	newUser = user_new(name, password);
	printf("%s %s\n\n", newUser.name, newUser.password);
	user_save(newUser);

	printf("<a href=\"../index.html\">return to home page</a>\n\n");

	return 0;
	}

/* end of user_cgi.c */
