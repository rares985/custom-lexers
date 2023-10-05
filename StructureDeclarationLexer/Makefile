CC=g++
LEXC=lex
CFLAGS=-g -Wall -Wextra -std=c++11 -I
LEXNAME="main.l"
LEXOUTPUT="lex.yy.c"
MAIN_NAME="main.cpp"
HEADER_PATH="libs/"

all: run
.PHONY: clean


run: 
	@./lexer $(arg) < input

build: lex.yy
	@$(CC) $(CFLAGS) $(HEADER_PATH) $(LEXOUTPUT) $(MAIN_NAME) -o lexer

lex.yy:
	@$(LEXC) $(LEXNAME)

clean:

	@rm main -f *~ lex.yy.c

