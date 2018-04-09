/* user.c */

#include <stdio.h> /* FILE sprintf fopen fwrite fclose remove fread */
#include <ctype.h> /* isalnum */
#include <string.h> /* strcpy */
#include "user.h" /* NAME_LENGTH struct user */

static const struct user user_empty;
static char user_folder[NAME_LENGTH] = "users/";

struct user user_new(const char *name, const char* password)
	{
	unsigned int i;
	struct user newUser;

	for ( i=0; name[i]!='\0'; i++ ) { 
		if ( i == NAME_LENGTH ) return user_empty; /* too long */
		newUser.name[i] = name[i]; } /* copy string char by char */

	newUser.name[i] = '\0'; /* null terminate the string */

	for ( i=0; newUser.name[i]!='\0'; i++ ) /* check for bad chars */
		if ( !isalnum((unsigned char) newUser.name[i]) )
			return user_empty;

	strcpy(newUser.password, password);

	return newUser;
	}

int user_save(struct user user)
	{
	FILE *file;
	char filePath[NAME_LENGTH + NAME_LENGTH];

	sprintf(filePath, "%s%s", user_folder, user.name);

	if ( (file = fopen(filePath, "r")) != NULL ) /* can file be read? */
		{
		fclose(file);
		return -1; /* file already exists, don't overwrite */
		}

	file = fopen(filePath, "wb"); /* file created */
	fwrite(&user, sizeof (struct user), 1, file); /* user saved */
	fclose(file);
	return 0;
	}

struct user user_load(char *name)
	{
	FILE *file;
	struct user user;
	char filePath[NAME_LENGTH + NAME_LENGTH];
	unsigned int i;

	for ( i=0; name[i]!='\0'; i++ )
		if ( i == NAME_LENGTH ) return user_empty; /* too long */

	sprintf(filePath, "%s%s", user_folder, name);

	if ( (file = fopen(filePath, "rb") ) == NULL )
		return user_empty; /* file does not exist */

	fread(&user, sizeof (struct user), 1, file); /* extract user */
	remove(filePath); /* no user file when user is in memory */
	fclose(file);
	return user;
	}

int user_name_check(char *name)
	{
	unsigned int i;
	FILE *file;
	char filePath[NAME_LENGTH + NAME_LENGTH];

	for ( i=0; name[i]!='\0'; i++ )
		if ( i == NAME_LENGTH ) return -1; /* too long */

	sprintf(filePath, "%s%s", user_folder, name);
	if ( (file = fopen(filePath, "r")) != NULL ) { /* can file be read? */
		fclose(file);
		return -2; } /* file already exists */

	return 0; /* file does not exist */
	}

/* end of user.c */
