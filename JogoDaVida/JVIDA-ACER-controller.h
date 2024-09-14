//JVIDA-ACER - Projeto Jogo da Vida –
//29/10/2023
//Grupo:Acer
/*
-Andre Garrido
-Caroline Campos
-Emili Vieira
-Rafael Turaca 
*/

void criarmundo();
void menuprincipal();
void vizinha();
void geracao();
void espera(time_t atraso);
void carregaVivo(int i, int j);
void excluiLVivo(int ii, int jj);
void excluiLMorto(int ii, int jj);
void carregaMorto(int ii, int jj);
int VerifMorto(int ii, int jj);
void carregaMortosViz();
void atualizaViz();
void iniciaListas();
void carregaVivoProx(int ii, int jj);
void liberaLista(TipoCel *aux, int tot);
void transfere();
void gravaCelulas();
void carregaConfig();
void recuperaCelulas();
void limpaGer();
void deletaConfig();