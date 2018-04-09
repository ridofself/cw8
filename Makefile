# -*- MakeFile -*-

# target: dependencies
# 	command

CC=gcc
CFLAGS= -std=c89 -Wall -Wextra -Werror -Wpedantic

all: make_dir test cgi-bin/user.cgi

make_dir:
	[ -d ./users ] && true || mkdir users
	[ -d ./cgi-bin ] && true || mkdir cgi-bin

cgi-bin/user.cgi: src/user_cgi.o src/user.o src/value.o
	$(CC) src/user_cgi.o src/user.o src/value.o \
	-o cgi-bin/user.cgi $(CFLAGS)

src/user_cgi.o: src/user_cgi.c src/user.h
	$(CC) -c src/user_cgi.c -o src/user_cgi.o $(CFLAGS)

test: src/test.o src/user.o src/value.o
	$(CC) src/test.o src/user.o src/value.o -o test $(CFLAGS)

src/test.o: src/test.c
	$(CC) -c src/test.c -o src/test.o $(CFLAGS)

src/user.o: src/user.c
	$(CC) -c src/user.c -o src/user.o $(CFLAGS)

src/value.o: src/value.c
	$(CC) -c src/value.c -o src/value.o $(CFLAGS)

clean:
	rm -f src/*.o test* users/* cgi-bin/*
	[ -d ./users ] && rmdir users || true
	[ -d ./cgi-bin ] && rmdir cgi-bin || true
