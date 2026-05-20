#include "BDTimes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BDPartidas.h"


//Carrega os times do arquivos csv
BDTimes* carregar_times(const char *arquivo, BDPartida *p){
   BDTimes *bd = malloc(sizeof(BDTimes)); 
   FILE *ftime = fopen(arquivo,"r");

   //Verifica se arquivo abriu
   if(ftime == NULL){
      printf("Erro ao abrir arquivo\n");
      free(bd);
      return NULL;
   }

   char linha[100];
   fgets(linha,sizeof(linha),ftime);//pula cabeçario

   int i = 0;
   while(fgets(linha,sizeof(linha),ftime)){
      //inicialização do time i
      Time t;
      t.V = 0;
      t.E = 0;
      t.D = 0;
      t.GM = 0;
      t.GS = 0;
      t.S = 0;
      t.PG = 0;

      char *dado; //var para carregar dados

      //carrega ID
      dado = strtok(linha,",");
      t.id = atoi(dado);

      //carrega Nome
      dado = strtok(NULL, "\n");
      strcpy(t.nome, dado);

      //busca por partidas com o time atual
      for(int j=0;j<p->num;j++){
         //time 1 = id
         if(p->partidas[j].time1 == t.id){
            //vitoria ou derrota ou empate
            if(p->partidas[j].GolsTime1>p->partidas[j].GolsTime2){
               t.V+=1;
            }
            else if ((p->partidas[j].GolsTime1)<(p->partidas[j].GolsTime2)){
               t.D+=1;
            }
            else{
               t.E+=1;
            }
            //Adição dos gols
            t.GM+=p->partidas[j].GolsTime1;
            t.GS+=p->partidas[j].GolsTime2;
         }
         //time 2 == id
         else if(p->partidas[j].time2 == t.id){
            //vitoria, derrota ou empate
            if(p->partidas[j].GolsTime1>p->partidas[j].GolsTime2){
               t.D+=1;
            }
            else if ((p->partidas[j].GolsTime1)<(p->partidas[j].GolsTime2)){
               t.V+=1;
            }
            else{
               t.E+=1;
            }
            //Adição dos gols
            t.GM+=p->partidas[j].GolsTime2;
            t.GS+=p->partidas[j].GolsTime1;
            
         }
      }
      //pontuação do time e saldo
      t.S = t.GM - t.GS;
      t.PG= 3*t.V + t.E;

      //salva o time
      bd->times[i] = t;
      i++;
   }

   fclose(ftime); // fecha arquivo
   return bd;
}  

//imprime o nome de cada time
void imprimir_times(BDTimes *bd){
   int i = 0;
   for(i=0;i<10;i++){
      printf("%s\n",bd->times[i].nome); 
   }
}

//Faz uma consulta para procurar times utilizando busca com prefixos
void consultar_time(char *busca, BDTimes *bd){
   //var caso não seja encontrado um time
   int erro = 1;

   //Cabeçario tabulado
   printf("\n%-3s %-15s %-3s %-3s %-3s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

   //busca times pelo seu nome sem distinção de maiúscula ou minúscula
   for(int i = 0;i<10;i++){
      //time encontrado
      if(strncasecmp(bd->times[i].nome, busca, strlen(busca)) == 0){
         //impressão tabulada dos times encontrados e atualização da var de erro
         printf("%-3d %-15s %-3d %-3d %-3d %-5d %-5d %-5d %-5d\n", bd->times[i].id, bd->times[i].nome, bd->times[i].V, bd->times[i].E, bd->times[i].D, bd->times[i].GM, bd->times[i].GS, bd->times[i].S, bd->times[i].PG);
         erro = 0;
      }
   }
   //time não encontrado
   if(erro == 1){
      printf("\n\nNENHUM TIME ENCONTRADO");
   }
}

//Print de tabela tabulada de cada time e suas pontuações
void consultar_class(BDTimes *bd){
   printf("\n%-3s %-15s %-3s %-3s %-3s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
   for(int i = 0;i<10;i++){
      printf("%-3d %-15s %-3d %-3d %-3d %-5d %-5d %-5d %-5d\n", bd->times[i].id, bd->times[i].nome, bd->times[i].V, bd->times[i].E, bd->times[i].D, bd->times[i].GM, bd->times[i].GS, bd->times[i].S, bd->times[i].PG);
   }
}

//busca um time por id e o retorna
char *buscar_time(BDTimes *bd, int id){
   return bd->times[id].nome;
}