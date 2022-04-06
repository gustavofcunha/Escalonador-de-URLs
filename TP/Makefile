CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/principal.o $(OBJ)/ListaEncadeada.o $(OBJ)/FilaEncadeada.o $(OBJ)/Escalonador.o $(OBJ)/memlog.o
HDRS = $(INC)/Celula.h $(INC)/ListaEncadeada.h $(INC)/FilaEncadeada.h $(INC)/Escalonador.h $(INC)/memlog.h $(INC)/msgassert.h 
CFLAGS = -std=c++11 -Wall -I$(INC)

EXE = $(BIN)/principal

all: $(EXE)

$(BIN)/principal: $(OBJS)
	$(CC) -g -o $(BIN)/principal $(OBJS) $(LIBS)

$(OBJ)/principal.o: $(HDRS) $(SRC)/principal.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/principal.o -c $(SRC)/principal.cpp 

$(OBJ)/ListaEncadeada.o: $(HDRS) $(SRC)/ListaEncadeada.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/ListaEncadeada.o -c $(SRC)/ListaEncadeada.cpp 

$(OBJ)/FilaEncadeada.o: $(HDRS) $(SRC)/FilaEncadeada.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/FilaEncadeada.o -c $(SRC)/FilaEncadeada.cpp 

$(OBJ)/Escalonador.o: $(HDRS) $(SRC)/Escalonador.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/Escalonador.o -c $(SRC)/Escalonador.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -g -o $(OBJ)/memlog.o -c $(SRC)/memlog.c
	
clean:
	rm $(EXE) $(OBJS)