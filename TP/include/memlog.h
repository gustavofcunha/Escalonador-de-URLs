#ifndef MEMLOGH
#define MEMLOGH

#include <stdio.h>
#include <time.h>

typedef struct memlog{
	FILE * log;
	clockid_t clk_id;
	struct timespec inittime;
	long count;
	int fase;
	int ativo;
} memlog_tipo;

static memlog_tipo ml;

#define MLATIVO 1
#define MLINATIVO 0

int iniciaMemLog(char * nome);
int ativaMemLog();
int desativaMemLog();
int defineFaseMemLog(int f);
int leMemLog(long int pos, long int tam, int id);
int escreveMemLog(long int pos, long int tam, int id);
int finalizaMemLog();

#endif