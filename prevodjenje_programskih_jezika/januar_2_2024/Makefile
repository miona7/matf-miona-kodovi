CC = g++
CFLAGS = -Wall -Wextra

parser: parser.o lexer.o
	$(CC) $(CFLAGS) $^ -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

lexer.o: lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o parser.tab.* parser.output lex.yy.c parser