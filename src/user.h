/* user.h */

#define NAME_LENGTH 20
#define HASH_LENGTH 40 /* number of chars in sha-1 value */

struct user { 	char name[NAME_LENGTH];
		char password[HASH_LENGTH]; };

struct user user_new(const char *, const char *);
int user_save(struct user);
struct user user_load(char *);
int user_name_check(char *);

/* end of user.h */
