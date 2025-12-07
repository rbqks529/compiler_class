CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -I./include
BISON = bison
FLEX = flex

OBJS = src/parser.o src/lex.yy.o src/ast.o src/interp.o src/main.o

all: kotlinlite

kotlinlite: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

src/parser.o: src/parser.c src/parser.h include/ast.h
src/lex.yy.o: src/lex.yy.c src/parser.h include/ast.h
src/ast.o: src/ast.c include/ast.h
src/interp.o: src/interp.c include/interp.h include/ast.h
src/main.o: src/main.c include/ast.h include/interp.h

src/parser.c src/parser.h: src/parser.y
	$(BISON) -d -o src/parser.c $<

src/lex.yy.c: src/lexer.l src/parser.h
	$(FLEX) -o $@ $<

clean:
	rm -f kotlinlite src/*.o src/parser.c src/parser.h src/lex.yy.c

.PHONY: all clean
