INCLUDE=./include/ 
LIBS=./lib 
SRC=./src/*.c
BIN=./bin/quotescraper.exe 

default: 
	gcc $(SRC) -o $(BIN) -I $(INCLUDE) -L $(LIBS) -lxml2 -lcurl -Wall

run: default 
	./bin/./quotescraper