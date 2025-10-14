CC=gcc
CFLAGS=-Wall -Wextra -O2
LDLIBS=-lm

SRC=ast.c check.c eval.c main.c
GEN=lex.yy.c parser.tab.c parser.tab.h

all: calc_ast

calc_ast: $(GEN) $(SRC)
	$(CC) $(CFLAGS) -o $@ $(GEN) $(SRC) $(LDLIBS)

parser.tab.c parser.tab.h: parser.y ast.h
	bison -Wall -Wcounterexamples -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

clean:
	rm -f calc_ast $(GEN)
.PHONY: all clean
