CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -I./include -I./parser
BISON = bison
FLEX = flex

OBJS = parser/parser.o parser/lex.yy.o src/ast.o src/interp.o src/main.o

all: kotlinlite

kotlinlite: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

parser/parser.o: parser/parser.c parser/parser.h include/ast.h
parser/lex.yy.o: parser/lex.yy.c parser/parser.h include/ast.h
src/ast.o: src/ast.c include/ast.h
src/interp.o: src/interp.c include/interp.h include/ast.h
src/main.o: src/main.c include/ast.h include/interp.h parser/parser.h

parser/parser.c parser/parser.h: src/parser.y | parser
	$(BISON) -d -o parser/parser.c $<

parser/lex.yy.c: src/lexer.l parser/parser.h | parser
	$(FLEX) -o $@ $<

parser:
	mkdir -p parser

clean:
	rm -f kotlinlite src/*.o parser/*.o parser/*.c parser/*.h
	rm -rf parser

.PHONY: all clean
