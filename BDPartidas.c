#include "BDPartidas.h"
#include "BDTimes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


BDPartida* carregar_partidas(const char* arquivo){
    BDPartida *bd = malloc(sizeof(BDPartida));

    bd->num = 0;    //quantidade atual no vetor dinámico
    bd->cap = 45;   //cap do vetor dinámico(num max de partidas em 1 campeonato)
    bd->partidas = malloc(sizeof(Partida)*bd->cap); //

    FILE *fpart = fopen(arquivo,"r");

    //Verifica se arquivo abriu
    if(fpart == NULL){
      printf("Erro ao abrir arquivo\n");
      free(bd->partidas);
      free(bd);
      return NULL;
    }

    char linha[100];
    fgets(linha,sizeof(linha),fpart);//pula cabeçario

    while(fgets(linha,sizeof(linha),fpart)){
        Partida p;
        char *dado;

        //carrega ID
        dado = strtok(linha,",");
        p.id = atoi(dado);

        //time1
        dado = strtok(NULL, ",");
        p.time1 = atoi(dado);

        //time2
        dado = strtok(NULL, ",");
        p.time2 = atoi(dado);

        //golstime1
        dado = strtok(NULL, ",");
        p.GolsTime1 = atoi(dado);

        //golstime2
        dado = strtok(NULL, ",");
        p.GolsTime2 = atoi(dado);

        bd_insert(bd,p); //adiciona partida ao vetor dinámico
    }

    fclose(fpart);
    return bd;
}

void reallocate(BDPartida *bd){
    bd->cap *=2; //duplica a capacidade do vetor dinámico
    bd->partidas = realloc(bd->partidas, sizeof(Partida)* bd->cap);
}

void bd_insert(BDPartida *bd,Partida p){

    if(bd->num == bd->cap){
        reallocate(bd); //realoca se a quantidade estiver no limite
    }

    bd->partidas[bd->num++] = p; //inserção e atualização do num
}

void consultar_partidas(BDPartida *p, char c, char *busca, BDTimes *t){
    int erro = 1;   //var caso não encontre partidas
    switch(c){
        //busca por mandante
        case '1':
            printf("\n%-3s %-22s %-15s\n", "ID", "Time1", "Time2");
            for(int i = 0;i<p->num;i++){
                if(strncasecmp(buscar_time(t, p->partidas[i].time1), busca, strlen(busca)) == 0){
                    printf("%-3d %-15s %d x %-2d %-15s\n", p->partidas[i].id, buscar_time(t, p->partidas[i].time1), p->partidas[i].GolsTime1, p->partidas[i].GolsTime2, buscar_time(t, p->partidas[i].time2));
                    erro = 0;
                }
            }
            if(erro == 1){
                printf("\n\nNENHUMA PARTIDA ENCONTRADA");
            }
            break;
        //busca por visitante
        case '2':
            printf("\n%-3s %-22s %-15s\n", "ID", "Time1", "Time2");
            for(int i = 0;i<p->num;i++){
                if(strncasecmp(buscar_time(t, p->partidas[i].time2), busca, strlen(busca)) == 0){
                    printf("%-3d %-15s %d x %-2d %-15s\n", p->partidas[i].id, buscar_time(t, p->partidas[i].time1), p->partidas[i].GolsTime1, p->partidas[i].GolsTime2, buscar_time(t, p->partidas[i].time2));
                    erro = 0;
                }
            }
            if(erro == 1){
                printf("\n\nNENHUMA PARTIDA ENCONTRADA");
            }
            break;
        //busca por ambos
        case '3':
            printf("\n%-3s %-22s %-15s\n", "ID", "Time1", "Time2");
            for(int i = 0;i<p->num;i++){
                if(strncasecmp(buscar_time(t, p->partidas[i].time1), busca, strlen(busca)) == 0 || strncasecmp(buscar_time(t, p->partidas[i].time2), busca, strlen(busca)) == 0){
                    printf("%-3d %-15s %d x %-2d %-15s\n", p->partidas[i].id, buscar_time(t, p->partidas[i].time1), p->partidas[i].GolsTime1, p->partidas[i].GolsTime2, buscar_time(t, p->partidas[i].time2));
                    erro = 0;
                }
            }
            if(erro == 1){
                printf("\n\nNENHUMA PARTIDA ENCONTRADA");
            }
            break;
    }
}
