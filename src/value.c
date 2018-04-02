/* value.c */

#include <string.h> /* strtok */
#include <stdio.h> /* sscanf */
#include <malloc.h> /* malloc free */

char *value_copy(const char *query, const char *arg)
{
	char *pair, *key, *value, *i;
	char *scratch = malloc(strlen(query) +1);
	strcpy(scratch, query); /* avoid clobbering query string */
	
	pair = strtok(scratch, "&"); /* get first key=value */
	while ( pair )
	{
		for ( i=pair; *i!='\0'; i++) if ( *i == '=' ) break;
		if ( *i == '\0' ) return i; /* no = sign in pair */

		key = (char *)malloc(strlen(pair) +1);
		value = (char *)malloc(strlen(pair) +1);
		sscanf(pair, "%[^=]=%s", key, value);

		if ( !strcmp(key, arg) )
		{
			free(scratch);
			free(key);
			return value; /* key matches argument */
		}

		free(key);
		free(value);
		pair = strtok(NULL, "&"); /* get next pair */
	}
	*scratch = '\0'; /* repurposed to return empty string */ 
	return scratch; /* arg not found in keys */
}

/* end value.c */
