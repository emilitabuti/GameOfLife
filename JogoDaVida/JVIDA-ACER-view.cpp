//JVIDA-ACER - Projeto Jogo da Vida –
//Grupo:Acer
/*
-Andre Garrido
-Caroline Campos
-Emili Vieira
-Rafael Turaca
*/

#include "JVIDA-ACER-view.h"
#include<stdio.h>
#include<iostream>

void recebetamanho()
{
	while(1)
	{
	printf("Digite o tamanho do mundo: ");
	scanf("%d", &tamanho);
	if(tamanho > 60 || tamanho < 10)
		printf("Tamanho invalido\n");
	else
		{
		printf("\nO tamanho do mundo e %d\n", tamanho);
		break;	
		}
	}
	
}

int mostramenuprincipal()
{
	int opc;
	printf("\nJOGO DA VIDA\n");
	printf("1- Inserir/excluir celula viva\n");
	printf("2- Mostrar mundo\n");
	printf("3- Mostrar/Nao mostrar celulas vizinhas-mortas\n");
	printf("4- Limpar a matriz\n");
	printf("5- Passar geracoes\n");
	printf("6- salvar geracoes iniciais\n");
	printf("7- carregar geracao salva\n");
	printf("0- Sair: ");
	scanf("%d", &opc);
	return opc;
}

void mostramundo()
{
	int i , j;
	vizinha();
	system("cls");
	printf("\n");
	printf("\t ");
	for(j = 0; j < tamanho; j++)
		printf("%2d  ", j);
	printf("\n\n");
	
	for(i = 0; i < tamanho ; i++)
	{
	printf("%2d \t", i);
	for(j = 0; j < tamanho ; j++)
		{
		if(mostravizinha == 0)
			{
			if(celula[i][j] == '+')
				printf("  . ");
			else
				printf("%3c ", celula[i][j]);
			}
		else
			printf("%3c ", celula[i][j]);
		}
	printf("\n");
	}	
	printf("Vivos: ");
	mostraLvivo();		
	printf("Mortos: ");
	mostraLmorto();

}


void colocarcelula()
{
	int l, c , op;
	printf("\nColocar celula\n");
	do
	{
	printf("\nLinha: (-1 para sair): ");
	scanf("%d", &l);
	
	if(l == -1)
		break;
	
	if(l < 0||l >= tamanho)
		{
		printf("Linha incorreta\n");
		continue;
		}
	
	
	printf("\nColuna: ");
	scanf("%d", &c);
	
	if(c >= tamanho || c < 0)
		{
		printf("Coluna incorreta\n");
		continue;
		}
	else if(celula[l][c] == 'O')
		{
		printf("Voce quer tirar a celula?(1 = sim ; 2 = nao): ");
		scanf("%d", &op);
		if(op == 2)
		{
			continue;
		}
		else if(op == 1)
		{
			celula[l][c] = '.';
			excluiLVivo(l , c);
			system("cls");
			mostramundo();
			printf("Celula apagada\n");
			continue;
		}
		else
		{
			printf("Opcao incorreta\n");
			continue;
		}
		}
	else
		{
		celula[l][c] = 'O';
		excluiLMorto(l, c);
		carregaVivo(l ,c);
		system("cls");
		mostramundo();
		continue;
		}
	
	
	
	}while(l != -1);
}

void msgvizinha()
{	
	if(mostravizinha == 0)
		mostravizinha = 1;
	else
		mostravizinha = 0;	
}


int recebergeracao()
{
	int geracao;
	while(1)
	{
	printf("Digite quantas geracoes voce deseja passar: ");
	scanf("%d", &geracao);
	if(geracao <= 0)
		{
			printf("Quantidade de geracoes invalida\n");
			continue;	
		}
	else 
		return geracao;
	}
	
}

int recebertempo()
{
	int tempo;
	while(1)
	{
	printf("\nEm qual velocidade voce quer passar, em segundos? (0 - passo a passo): ");
	scanf("%d", &tempo);
	if(tempo < 0)
		{
			printf("Tempo invalido\n");
			continue;	
		}
	else 
		return tempo;
	}
}

int passoapasso()
{
	int i;
	while(1)
	{
	printf("Digite 1 para passar para a proxima geracao(0 para interromper): ");
	scanf("%d" , &i);
	if(i != 0 && i != 1)
		{
			printf("Opcao invalida\n");
			continue;
		}
	else
		return i;
	}
	
}



void apresentamensagem(char mens[100])
{
	printf("%s\n", mens);
}

void apresentageracao(int geracao)
{
	printf("Geracao %d\n", geracao);
}


void mostraLvivo()
{
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pvivo; //inicializa esse ponteiro auxiliar
	if (totvivo > 0)
	{
		while(aux->next != NULL)
		{
			printf("|%d,%d| ", aux->lin, aux->col);
			aux = aux->next; //caminha para o próximo ponteiro
		}
	printf("|%d,%d| ", aux->lin, aux->col); //mostra a ultima celula
	}
	printf("\n");
}

void mostraLmorto()
{
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pmorto; //inicializa esse ponteiro auxiliar
	if (totmorto > 0)
	{
		while(aux->next != NULL)
		{
			printf("|%d,%d| ", aux->lin, aux->col);
			aux = aux->next; //caminha para o próximo ponteiro
		}
	printf("|%d,%d| ", aux->lin, aux->col); //mostra a ultima celula
	}
	printf("\n");
}
