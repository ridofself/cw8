/* test.c */

#include <stdio.h> /* printf remove */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include <malloc.h> /* free */

static unsigned int testCount;

void test_test()
	{
	assert(1);
	testCount++;
	}

#include "user.h"

void test_user_new()
	{
	char *name = "Testname";
	struct user newUser = user_new(name, "");

	assert(!strcmp(newUser.name, name));
	testCount++;

	name = "b@dN@me_ ";
	newUser = user_new(name, "");
	assert(strcmp(newUser.name, name));
	testCount++;

	name = "ThereIsTwentyOneChars";
	newUser = user_new(name, "");
	assert(strcmp(newUser.name, name));
	testCount++;
	}

void test_user_save()
	{
	char *name = "Testname";
	struct user newUser = user_new(name, "");

	assert(!user_save(newUser));
	testCount++;

	assert(user_save(newUser) == -1);
	testCount++;

	user_load(newUser.name); /* cleans up user file */
	}

void test_user_load()
	{
	char *name = "Testname";
	struct user loadedUser;
	char *unsavedUser_name = "Willnotwork";
	struct user newUser = user_new(name, "");

	user_save(newUser);
	loadedUser = user_load(name);
	assert(!strcmp(name, loadedUser.name));
	testCount++;

	loadedUser = user_load(unsavedUser_name);
	assert(strcmp(unsavedUser_name, loadedUser.name));
	testCount++;

	loadedUser = user_load(name);
	assert(strcmp(name, loadedUser.name));
	testCount++;

	name = "ThereIsTwentyOneChars";
	newUser = user_load(name);
	assert(strcmp(newUser.name, name));
	testCount++;
	}

void test_user_name_check()
	{
	char *name = "Testname";

	assert(!user_name_check(name));
	testCount++;

	user_save(user_new(name, ""));
	assert(user_name_check(name) == -2);
	user_load(name); /* cleanup user */
	testCount++;
	

	name = "ThereIsTwentyOneChars";
	assert(user_name_check(name) == -1);
	testCount++;
	}

#include "value.h"

void test_value_copy()
	{
	char *testString = "name=Biggs&job=Merc";
	char *value = value_copy(testString, "name");

	assert(!strcmp("Biggs", value));
	free(value);
	testCount++;

	value = value_copy(testString, "job");
	assert(!strcmp("Merc", value));
	free(value);
	testCount++;

	value = value_copy(testString, "doesnotexist");
	assert(!strcmp("", value));
	free(value);
	testCount++;

	testString = "keywithnovalue=";
	value = value_copy(testString, "keywithnovalue");
	assert(!strcmp("", value));
	free(value);
	testCount++;
	/*
	testString = "no&pairs&in&string";
	value = value_copy(testString, "pairs");
	assert(!strcmp("", value));
	free(value);
	testCount++;

	testString = "badstring";
	value = value_copy(testString, "bad");
	assert(!strcmp("", value));
	free(value);
	testCount++;
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
	printf("testing...\n\n");
	test_all();
	printf("\nall of %d tests passed\n\n", testCount);
	return 0;
	}

/* end of test.c */
