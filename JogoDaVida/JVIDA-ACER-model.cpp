//JVIDA-ACER - Projeto Jogo da Vida –
//29/10/2023
//Grupo:Acer
/*
-Andre Garrido
-Caroline Campos
-Emili Vieira
-Rafael Turaca
*/ 

#include "JVIDA-ACER-model.h"
#include<stdio.h>

typedef struct cel
{
	int lin, col;
	struct cel *next;
}TipoCel;

TipoCel *pvivo, *pmorto, *pvivoprox;

typedef struct c
{
 int lin, col;
} Cel;

typedef struct list
{
 int cont; //tamanho da lista de até no máximo 400 células vivas iniciais
 Cel L[400];
} TipoLista;

TipoLista Lvivo; //esta estrutura não contem mais os ponteiros de ligação entre as células, pois elas serão gravadas sequencialmente em disco.

//Define o array LConfig[50] para a gravação em disco de até 50 listas de células vivas iniciais
struct arquivo
{
 TipoLista TL; //1 lista total
} LConfig[50];
