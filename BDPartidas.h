#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

typedef struct partida
{
   int id;
   int time1;
   int time2;
   int GolsTime1;
   int GolsTime2;  
} Partida;

typedef struct bdtime BDTimes;

typedef struct bdpartida{
   Partida *partidas;
   int num;
   int cap;
} BDPartida;

//carrega as partidas do BD
BDPartida* carregar_partidas(const char* arquivo);

//realocação do vetor dinámico
void reallocate(BDPartida *bd);

//inserção do vetor dinámico
void bd_insert(BDPartida *bd,Partida p);

//busca por prefixo de partidas
void consultar_partidas(BDPartida *p, char c, char *busca, BDTimes *t);

#endif
