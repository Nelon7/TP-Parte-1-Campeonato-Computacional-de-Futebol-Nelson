#ifndef BDTIMES_H
#define BDTIMES_H
#include "BDPartidas.h"

typedef struct time
{
   int id;
   char nome[20];

   int V;
   int E;
   int D;
   int GM;
   int GS;
   int S;
   int PG;
} Time;

typedef struct bdtime{
   Time times[10];
} BDTimes;

//Carrega os times do arquivos csv
BDTimes* carregar_times(const char *arquivo, BDPartida *p);

//imprime o nome de cada time
void imprimir_times(BDTimes *bd);

//Faz uma consulta para procurar times utilizando busca com prefixos
void consultar_time(char *busca,BDTimes *times);

//Print de tabela tabulada de cada time e suas pontuações
void consultar_class(BDTimes *bd);

//busca um time por id e o retorna
char *buscar_time(BDTimes *bd, int id);

#endif