//JVIDA-ACER - Projeto Jogo da Vida –
//29/10/2023
//Grupo:Acer
/*
-Andre Garrido
-Caroline Campos
-Emili Vieira 
-Rafael Turaca
*/
int tamanho;
char celula[60][60];
int mostravizinha = 0;
int totvivo, totmorto, totvivoprox;
// operações com LConfig[50]
int qtconf; //quantidade de configurações iniciais cadastradas
int ultrecup = -1; //indice da ultima configuração recuperada (de 0 a 49)
