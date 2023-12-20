INCLUDE=./include/ 
LIBS=./lib 
SRC=./src/main.c ./src/callbacks.c ./src/quotes.c
BIN=./bin/quotescraper.exe 

default: 
	gcc $(SRC) -o $(BIN) -I $(INCLUDE) -L $(LIBS) -DIN_LIBXML -lxml2 -lz -liconv -llzma -lws2_32 -lcurl 

run: default 
	./bin/./quotescraper 