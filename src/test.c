/* test.c */

#include <stdio.h> /* printf remove */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include <malloc.h> /* free */

static unsigned int testCount;

void test_test()
{
	printf("test suite works");
	assert(1);
	testCount++;
	printf(" ...OK\n");
}

#include "user.h"

void test_user_new()
{
	char *name = "Testname";
	struct user newUser = user_new(name, "");

	printf("\ntest user_new():\n");

	printf("allows good name");
	assert(!strcmp(newUser.name, name));
	testCount++;
	printf(" ...OK\n");

	printf("prevents bad name");
	name = "b@dN@me_ ";
	newUser = user_new(name, "");
	assert(strcmp(newUser.name, name));
	testCount++;
	printf(" ...OK\n");

	printf("prevents long name");
	name = "ThereIsTwentyOneChars";
	newUser = user_new(name, "");
	assert(strcmp(newUser.name, name));
	testCount++;
	printf(" ...OK\n");
}

void test_user_save()
{
	char *name = "Testname";
	struct user newUser = user_new(name, "");

	printf("\ntest user_save():\n");

	printf("returns no error when run normally");
	assert(!user_save(newUser));
	testCount++;
	printf(" ...OK\n");

	printf("won't overwrite an existing file");
	assert(user_save(newUser) == -1);
	testCount++;
	printf(" ...OK\n");

	user_load(newUser.name); /* cleans up user file */
}

void test_user_load()
{
	char *name = "Testname";
	struct user loadedUser;
	char *unsavedUser_name = "Willnotwork";
	struct user newUser = user_new(name, "");

	printf("\ntest user_load():\n");

	printf("a saved user file can be loaded");
	user_save(newUser);
	loadedUser = user_load(name);
	assert(!strcmp(name, loadedUser.name));
	testCount++;
	printf(" ...OK\n");

	printf("does not attempt to load fake user");
	loadedUser = user_load(unsavedUser_name);
	assert(strcmp(unsavedUser_name, loadedUser.name));
	testCount++;
	printf(" ...OK\n");

	printf("loading a user file deletes it");
	loadedUser = user_load(name);
	assert(strcmp(name, loadedUser.name));
	testCount++;
	printf(" ...OK\n");

	printf("does not attempt to check long user name");
	name = "ThereIsTwentyOneChars";
	newUser = user_load(name);
	assert(strcmp(newUser.name, name));
	testCount++;
	printf(" ...OK\n");
}

void test_user_name_check()
{
	char *name = "Testname";

	printf("\ntest user_name_check():\n");

	printf("unused user name is available");
	assert(!user_name_check(name));
	testCount++;
	printf(" ...OK\n");

	printf("used name fails check");
	user_save(user_new(name, ""));
	assert(user_name_check(name) == -2);
	user_load(name); /* cleanup user */
	testCount++;
	printf(" ...OK\n");
	

	printf("long name fails check");
	name = "ThereIsTwentyOneChars";
	assert(user_name_check(name) == -1);
	testCount++;
	printf(" ...OK\n");
}

#include "value.h"

void test_value_copy()
{
	char *testString = "name=Biggs&job=Merc";
	char *value = value_copy(testString, "name");

	printf("\ntest value_copy():\n");

	printf("proper value returns from querystring, key");
	assert(!strcmp("Biggs", value));
	free(value);
	testCount++;
	printf(" ...OK\n");

	printf("proper value returns from deeper key");
	value = value_copy(testString, "job");
	assert(!strcmp("Merc", value));
	free(value);
	testCount++;
	printf(" ...OK\n");

	printf("blank value returns from fake key");
	value = value_copy(testString, "doesnotexist");
	assert(!strcmp("", value));
	free(value);
	testCount++;
	printf(" ...OK\n");

	printf("blank value returns when there is no value");
	testString = "keywithnovalue=";
	value = value_copy(testString, "keywithnovalue");
	assert(!strcmp("", value));
	free(value);
	testCount++;
	printf(" ...OK\n");
/*
	printf("blank value returns when there is not k,v pair");
	testString = "no&pairs&in&string";
	value = value_copy(testString, "pairs");
	assert(!strcmp("", value));
	free(value);
	testCount++;
	printf(" ...OK\n");

	printf("blank value returns when bad querystring provided");
	testString = "badstring";
	value = value_copy(testString, "bad");
	assert(!strcmp("", value));
	free(value);
	testCount++;
	printf(" ...OK\n");
*/
}

void test_all()
	{
	test_test();
	test_user_new();
	test_user_save();
	test_user_load();
	test_user_name_check();
	test_value_copy();
	}

int main()
{
	printf("begin testing\n\n");
	test_all();
	printf("\nall of %d tests passed\n\n", testCount);
	return 0;
}

/* end of test.c */
