CC=g++
CFLAGS=-g -std=c++11 -I
LEXC=lex

LEXNAME="main.l"
LEXOUTPUT="lex.yy.c"
MAIN_NAME="main.cpp"
HEADER_PATH="libs/"

all: run


run: 
	@./lexer $(arg) < grammar

build: lex.yy.c
	@$(CC) $(CFLAGS) $(HEADER_PATH) $(LEXOUTPUT) $(MAIN_NAME)  -o lexer



lex.yy.c:
	@$(LEXC) $(LEXNAME)


clean:
	@rm -f *~ lex.yy.c