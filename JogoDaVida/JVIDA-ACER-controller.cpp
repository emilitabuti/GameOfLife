//JVIDA-ACER - Projeto Jogo da Vida –
//29/10/2023
//Grupo:Acer
/*
-Andre Garrido
-Caroline Campos
-Emili Vieira
-Rafael Turaca
*/

#include "JVIDA-ACER-controller.h"
#include "JVIDA-ACER-view.cpp"
#include<stdio.h>
#include<time.h>

void criarmundo()
{	
	int i , j; 
	for(i=0; i < tamanho; i++)       
		for(j=0 ; j < tamanho; j++)
		{
			celula[i][j] = '.' ;
		}
}


void menuprincipal()
{	
	int opc, i , j;
	do
	{
		opc = mostramenuprincipal(); 
		switch(opc)
		{
			case 1:
				colocarcelula();
				system("cls");
				mostramundo();
				break;
			case 2:
				mostramundo();
				break;
			case 3:
				msgvizinha();
				mostramundo();
				break;
			case 4:
				criarmundo();
				mostramundo();
				break;
			case 5:
				geracao();
				break;
			case 6:
				gravaCelulas();
				iniciaListas();
				criarmundo();
				carregaConfig();
				//a partir do array LConfig, refazer a Lista ligada original 
				//(usando a instrução malloc para cada célula e refazendo as ligações, etc)
				break;
			case 7:
				recuperaCelulas();
				break;
			case 0:
				break;
		}
		
	}while(opc != 0);
}

void vizinha()
{
	int i , j;
	for(i=0; i < tamanho; i++)       
		for(j=0 ; j < tamanho; j++)
		{
			if(celula[i][j] == 'O')
				{
					if(celula[i-1][j] != 'O')
					{
						celula[i-1][j] = '+';
						carregaMorto(i-1, j);
					}
					if(celula[i+1][j] != 'O')
					{
						celula[i+1][j] = '+';
						carregaMorto(i+1, j);
					}
					if(celula[i][j-1] != 'O')
					{
						celula[i][j-1] = '+';
						carregaMorto(i, j-1);
					}	
					if(celula[i][j+1] != 'O')
					{
						celula[i][j+1] = '+';
						carregaMorto(i, j+1);
					}
					
					if(celula[i-1][j-1] != 'O')
					{
						celula[i-1][j-1] = '+';
						carregaMorto(i-1, j-1);
					}
					if(celula[i+1][j+1] != 'O')
					{
						celula[i+1][j+1] = '+';
						carregaMorto(i+1, j+1);
					}
					if(celula[i+1][j-1] != 'O')
					{
						celula[i+1][j-1] = '+';
						carregaMorto(i+1, j-1);
					}
					if(celula[i-1][j+1] != 'O')
					{
						celula[i-1][j+1] = '+';
						carregaMorto(i-1, j+1);
					}
				}
			if(celula[i][j] == '+')
				{
					if(celula[i-1][j] != 'O')
						if(celula[i+1][j] != 'O')
							if(celula[i][j-1] != 'O')
								if(celula[i][j+1] != 'O')
									if(celula[i-1][j-1] != 'O')
										if(celula[i+1][j+1] != 'O')
											if(celula[i+1][j-1] != 'O')
												if(celula[i-1][j+1] != 'O')
													celula[i][j] = '.';
				}
		}
}

void geracao()
{
	int i, j, cont, passo,qtdger, tempo, fase;
 
	qtdger = recebergeracao();
	tempo = recebertempo();
	fase = 1;
	
	while(fase <= qtdger)
	{
	
	for(i=0; i < tamanho; i++)       
		for(j=0 ; j < tamanho; j++)
		{
			
			if(celula[i][j] == 'O')
				{
					cont = 0;
					if(celula[i-1][j] == 'O')
						cont++;
					if(celula[i+1][j] == 'O')
						cont++;
					if(celula[i][j-1] == 'O')
						cont++;
					if(celula[i][j+1] == 'O')
						cont++;
					
					if(celula[i-1][j-1] == 'O')
						cont++;
					if(celula[i+1][j+1] == 'O')
						cont++;
					if(celula[i+1][j-1] == 'O')
						cont++;
					if(celula[i-1][j+1] == 'O')
						cont++;	
					
					if(cont == 2 || cont == 3)
						carregaVivoProx(i, j);
				
				}
			else if(celula[i][j] == '.' ||celula[i][j] == '+')
				{
					cont = 0;
					if(celula[i-1][j] == 'O')
						cont++;
					if(celula[i+1][j] == 'O')
						cont++;
					if(celula[i][j-1] == 'O')
						cont++;
					if(celula[i][j+1] == 'O')
						cont++;
					
					if(celula[i-1][j-1] == 'O')
						cont++;
					if(celula[i+1][j+1] == 'O')
						cont++;
					if(celula[i+1][j-1] == 'O')
						cont++;
					if(celula[i-1][j+1] == 'O')
						cont++;
					
					if(cont == 3)
						carregaVivoProx(i, j);
				}	
		}
	criarmundo();
	pvivo = pmorto = NULL;
	totvivo = totmorto = 0;
	pvivo = pvivoprox;
	totvivo = totvivoprox;
	transfere();
	vizinha();
	mostramundo();
	
	pvivoprox = NULL;
	totvivoprox = 0;
	
	apresentageracao(fase);
	if(tempo == 0)
	{
		passo = passoapasso();
		if(passo == 0)
			break;
	}
	else	
		espera(tempo);
	fase++;
	}
}


void espera(time_t atraso)//funcao de tempo de espera (em segundos)
{
	time_t lt1, lt2;

	lt1 = time(NULL);
	lt2 = lt1;
	
	while (difftime(lt2, lt1) < atraso)
		lt2 = time(NULL);
	
}

void carregaVivo(int i, int j)
{
	
	TipoCel *aux = (TipoCel*) malloc(sizeof(TipoCel));
	
 	if (aux == NULL)
 	{
		apresentamensagem("Sem espaço na memoria para inclusao de celula viva\n");
 		return; 
 	}
 	
	aux->lin = i; 
	aux->col = j;
	
	if(totvivo == 0) 
 	{
		pvivo = aux; 
 		pvivo->next = NULL; 
 	}
 	else //lista não vazia
 	{
 		aux->next = pvivo; 
 		pvivo = aux; 
 	}
 	totvivo++; 
}



void excluiLVivo(int ii, int jj)
{
	TipoCel *aux, *aux2; //define 2 ponteiros auxiliares
	aux = pvivo;
	aux2 = aux; //guarda a célula como sendo a anterior
	if (totvivo > 0)
	{
		while (aux->lin != ii || aux->col != jj)
		{
			aux2 = aux;
			aux = aux->next;
		}
		if (aux->lin == ii && aux->col == jj)
		{
			if (aux2 == aux) //se é o primeiro da lista
				pvivo = aux->next;
			else
				aux2->next = aux->next;
			free(aux);
		}
	totvivo--;
	}
}

void excluiLMorto(int ii, int jj)
{
	TipoCel *aux, *aux2; //define 2 ponteiros auxiliares
	aux = pmorto;
	aux2 = aux; //guarda a célula como sendo a anterior
	if (totmorto > 0)
	{
		while (aux->lin != ii || aux->col != jj)
		{
			aux2 = aux;
			aux = aux->next;
		}
		if (aux->lin == ii && aux->col == jj)
		{
			if (aux2 == aux) //se é o primeiro da lista
				pvivo = aux->next;
			else
				aux2->next = aux->next;
			free(aux);
		}
	totmorto--;
	}
}

void carregaMortosViz()
{
	int k, i, ii, jj;
	struct
	{
		int li, co; //linha e coluna
	} a,b,c,d,e,f,g,h; //celulas vizinhas
	//libera lista de mortos
	totmorto = 0;
	TipoCel *aux;
	aux = pvivo;
	if (totvivo == 0)
		return;
	do
	{
		ii = aux->lin;
		jj = aux->col;
		
		a.li = ii-1; 		a.co = jj-1;
		b.li = ii-1; 		b.co = jj;
		c.li = ii-1; 		c.co = jj+1;
		d.li = ii; 			d.co = jj-1;
		e.li = ii; 			e.co = jj+1;
		f.li = ii+1; 		f.co = jj-1;
		g.li = ii+1; 		g.co = jj;
		h.li = ii+1; 		h.co = jj+1;
		
		carregaMorto(a.li, a.co);
		carregaMorto(b.li, b.co);
		carregaMorto(c.li, c.co);
		carregaMorto(d.li, d.co);
		carregaMorto(e.li, e.co);
		carregaMorto(f.li, f.co);
		carregaMorto(g.li, g.co);
		carregaMorto(h.li, h.co);
		
		if(aux->next == NULL)
			break;
		aux = aux->next;
		
	}while(1);
}

void carregaMorto(int ii, int jj)
{
	if ((ii < 0) || (jj < 0)) //celula inexistente
		return;
	if ((ii >= tamanho) || (jj >=tamanho)) //celula inexistente
		return;
	if(celula[ii][jj] == 'O') //celula viva
		return;
	if (VerifMorto(ii, jj) == 1)
		return;
	//inclui na lista de mortos-vizinhos
	TipoCel *aux = (TipoCel*) malloc(sizeof(TipoCel));
	if (aux == NULL)
	{
		apresentamensagem("Sem espaço na memoria para inclusao de celula morta-vizinha\n");
		return;
	}
	aux->lin = ii;
	aux->col = jj;
	if(totmorto == 0) //se a lista está vazia
	{
		pmorto = aux;
		pmorto->next = NULL;
	}
	else //lista não vazia
	{
		aux->next = pmorto;
		pmorto = aux; //o inicio da lista passa a ser a nova celula
	}
	totmorto++;
}




int VerifMorto(int ii, int jj)
{
	TipoCel *aux;
	aux = pmorto;
	if (totmorto == 0)
		return 0;
	do
	{
		if (aux->lin == ii && aux->col == jj)
			return 1;
		aux = aux->next;
	} while (aux != NULL);
	return 0;
}






void carregaVivoProx(int ii, int jj)
{
	TipoCel *aux = (TipoCel*) malloc(sizeof(TipoCel));
	if (aux == NULL)
	{
		apresentamensagem("Sem espaço na memoria para inclusao de celula viva para a proxima geracao\n");
		return;
	}
	aux->lin = ii;
	aux->col = jj;
	if(totvivoprox == 0) //se a lista está vazia
	{
		pvivoprox = aux;
		pvivoprox->next = NULL;
	}
	else //lista não vazia
	{
		aux->next = pvivoprox;
		pvivoprox = aux; //o inicio da lista passa a ser a nova celula
	}
	totvivoprox++;
}

void liberaLista(TipoCel *aux, int tot)
{
	if(aux == NULL || tot == 0) //já está liberada
		return;
	TipoCel *aux2;
	do
	{
		aux2 = aux;
		aux = aux->next;
		free(aux2); //libera memoria
	}while(aux != NULL);
}


//inicia todas as listas vazias
void iniciaListas()
{
 liberaLista(pvivo, totvivo);
 liberaLista(pmorto, totmorto);
 liberaLista(pvivoprox, totvivoprox);
 pvivo = pmorto = pvivoprox = NULL; //ponteiros vazios
 totvivo = totmorto = totvivoprox = 0; //inicialmente listas vazias
}




//limpa matriz
//varre lista de vivos da proxima geracao
//coloca O no lugar



void transfere()
{
	TipoCel *aux;
	for(int i = 1; i<=tamanho; i++)
		for(int j = 1; j<=tamanho; j++)
			celula[i][j] = '.';
			
	aux = pvivoprox;
	while(totvivoprox>0)
	{
		celula[aux->lin][aux->col]='O';
		pvivoprox=aux->next;
		free(aux);
		aux = pvivoprox;
		totvivoprox--;
	}	
}

//Calcula a qtde de vizinhos (de celulas vivas e mortas)
//e executa o processo para chegar à proxima geração
void atualizaViz()
{
 int i, j, ii, jj, vii, vjj, ct;
 liberaLista(pvivoprox, totvivoprox);
 pvivoprox = NULL; //ponteiros vazios
 if (pvivo == NULL)
 return;
 //vizinhos vivos das celulas vivas
 TipoCel *aux, *aux2;
 aux = pvivo;
 do
 {
 ct = 0; //contador de vizinhos da celula (ii,jj)
 ii = aux->lin;
 jj = aux->col;
 aux2 = pvivo;
 do
 {
 vii = aux2->lin;
 vjj = aux2->col;
 if (vii != ii || vjj != jj) //se não for a mesma célula
 if(abs(ii-vii)<=1 && abs(jj-vjj)<=1) //se é vizinho
 ct++;
 aux2 = aux2->next;
 } while(aux2 != NULL);
 //ATITUDE sobre a célula viva conforme a qtd.de vizinhos
 if (ct == 2 || ct == 3)
 carregaVivoProx(ii,jj); //sobrevive na próxima geração
 //else
 // carregaMortoProx(ii,jj); //morre na próxima geração
 aux = aux->next;
 } while(aux != NULL);
 if (pmorto == NULL)
 return;
 //vizinhos vivos das celulas mortas
 aux = pmorto;
 do
 {
 ct = 0; //contador de vizinhos da celula (ii,jj)
 ii = aux->lin;
 jj = aux->col;
 aux2 = pvivo;
 do
 {
 vii = aux2->lin;
 vjj = aux2->col;
 if(abs(ii-vii)<=1 && abs(jj-vjj)<=1) //se é vizinho
 ct++;
 aux2 = aux2->next;
 } while(aux2 != NULL);
 //ATITUDE sobre a célula morta conforme a qtd.de vizinhos vivos
 if (ct == 3)
 carregaVivoProx(ii,jj); //nasce na próxima geração
 aux = aux->next;
 } while(aux != NULL);
}

//grava a Lista atual de células vivas
void gravaCelulas()
{
 int k, i, ni;
 k = qtconf;
 if (totvivo == 0)
 	return;
 //carrega o vetor Lvivo com a lista atual de vivos (somente para gravação)
 TipoCel *aux;
 aux = pvivo;
 ni = 0; //indice do vetor L da estrutura Lvivo
 do
 {
 Lvivo.L[ni].lin = aux->lin;
 Lvivo.L[ni].col = aux->col;
 ni++;
 aux = aux->next;
 } while (aux != NULL);
 Lvivo.cont = totvivo;
 LConfig[k].TL = Lvivo;
 FILE *fp;
 if((fp = fopen("CONFIG_INIC", "w")) == NULL)
 {
 apresentamensagem("ERRO: O arquivo CONFIG_INIC nao pode ser aberto para gravacao");
 return;
 }
 for(i = 0; i <= qtconf; i++)
 {
 if (fwrite(&LConfig[i], sizeof(TipoLista), 1, fp) != 1)
 {
 apresentamensagem("Erro na gravacao do arquivo CONFIG_INIC");
 fclose(fp);
 return;
 }
 }
 fclose(fp);
 qtconf++;
 apresentamensagem("Configuracao gravada OK");
}

//carrega o arquivo contendo todas as configurações iniciais que foram gravadas em disco.
void carregaConfig()
{
 int k;
 FILE *fp;
 if((fp = fopen("CONFIG_INIC", "r")) != NULL)
 {
 //pesquisa a quantidade de configurações cadastradas
 qtconf = 0;
 k = 0;
 while(!feof(fp)) //enquanto não for fim de arquivo
 {
 if (fread(&LConfig[k], sizeof(TipoLista), 1, fp) != 1)
 {
 fclose(fp);
 return;
 }
 qtconf++;
 k++;
 }
 fclose(fp);
 }
}

void recuperaCelulas()
{
 int i, j, k, ni;
 if (qtconf == 0)
 {
 apresentamensagem("Nao existe configuracao a recuperar");
 return;
 }
 k = ultrecup + 1; //índice de LConfig onde estão as células a serem recuperadas
 if (k >= qtconf)
 k = 0; //volta ao primeiro conjunto de celulas
 Lvivo = LConfig[k].TL; //obtem a lista das células a serem recuperadas
 ultrecup = k;
 //recupera a Lista ligada de celulas vivas
free(pvivo);
totvivo = 0;
pvivo = NULL;
 for(ni = 0; ni < Lvivo.cont; ni++)
 carregaVivo(Lvivo.L[ni].lin, Lvivo.L[ni].col); //esta função voce já deve possuir
//finalmente voce deve Atualizar a Matriz com estas células recuperadas e depois apresenta-la na tela.
}

//Limpa o deposito de gerações iniciais
//(gera o arquivo se o deposito ainda não existe
/*void limpaGer()
{
 if(qtconf > 0)
 {
 if (rconfirma("Confirma exclusao das configuracoes iniciais? s,<n>: ") == 0)
 return;
 }
 qtconf = 0; //nenhuma configuracao gravada
 ultrecup = -1; //ultimo índice recuperado
 deletaConfig();
 apresentamensagem("O deposito de geracoes iniciais esta vazio");
}*/

//remove o arquivo de configurações iniciais
void deletaConfig()
{
 if(remove("CONFIG_INIC") != 0)
 {
 apresentamensagem("ERRO: O arquivo CONFIG_INIC nao pode ser removido");
 return;
 }
 qtconf = 0;
 apresentamensagem("O arquivo CONFIG_INIC foi removido OK");
}