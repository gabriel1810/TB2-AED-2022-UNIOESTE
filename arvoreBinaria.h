#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Item do nó da arvore binária de busca
typedef struct{
    int codigo;
    char nome[50];
    char marca[30];
    char categoria[50];
    int qntEstoque;
    float preco;
} itemEstoque;

//Nó da arvore binaria de busca
typedef struct {
    itemEstoque item; //Item do No
    int livre;      //No em uso livre=0, caso seja apagado aponta para o ultimo no apagado antes dele
    int pos;        //Posicao do No na arvore
    int esq;        //Filho da esquerda
    int dir;        //Filho da direita
}no;

//Cabeçalho do arquivo com a arvore binaria
typedef struct{
    int pos_livre;  //Aponta para a ultima posicao livre da arvore
    int raiz;       //Guarda a raiz da arvore
} cabecalho;


/*  Faz o percurso em ordem na arvore, imprimindo os dados
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No raiz da arvore valido
*   Pos-condicao: Imprime as informacoes de todos os itens da arvore em ordem
*/
void in_ordem(FILE* arq,no* aux);

/*  Retorna a posicao do ultimo No da arvore
*   Pre-condicao: Arquivo de dados aberto e populado com dados
*   Pos-condicao: Posicao do ultimo No
*/
int ultimoIns(FILE* arq);

/*  Percorre a arvore em ordem, imprimindo as posicoes livres
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No raiz da arvore valido
*   Pos-condicao: Imprime as posicoes livres na arvore
*/
void printLivres(FILE* arq,no* aux,int i);

/*  Percorre a arvore Buscando o maior codigo de item na arvore
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No da arvore para iniciar a procura
*   Pos-condicao: Retorna o item cujo o codigo e o maior dado o No inicial
*/
itemEstoque maximo(FILE* arq,no* aux);

/*  Percorre a arvore Buscando o menor codigo de item na arvore
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No da arvore para iniciar a procura
*   Pos-condicao: Retorna o item cujo o codigo e o menor dado o No inicial
*/
itemEstoque minimo(FILE* arq,no* aux);

/*  Escreve o cabecalho no arquivo binario
*   Pre-condicao: Arquivo de dados aberto, e um cabecalho valido a ser escrito
*   Pos-condicao: O cabecalho e escrito no arquivo
*/
void escreve_cabecalho(FILE* arq, cabecalho* cab);

/*  Inicia a arvore binaria com cabecalho no arquivo
*   Pre-condicao: Arquivo de dados aberto
*   Pos-condicao: Cria uma nova arvore, escrevendo o cabecalho no arquivo pela primeira vez
*/
void cria_arvore_vazia(FILE* arq);

/*  Busca a posicao de um item na arvore, dado seu codigo
*   Pre-condicao: Arquivo binario da arvore aberto e com cabecalho, o codigo do item
*   Pos-condicao: Retorna a posicao do item na arvore
*/
int buscaPosicao(FILE* arq,int codigo);

/*  Le um no da arvore binaria na posicao especificada
*   Pre-condicao: Arquivo de dados aberto e populado com dados, posicao a ser lida do arquivo
*   Pos-condicao: Retorna o No resultante da busca
*/
no* le_no(FILE* arq, int pos);

/*  Escreve um no 'x' na posicao especificada por 'pos' no arquivo de dados
*   Pre-condicao: Arquivo de dados aberto, um No valido a ser escrito no arquivo e uma posicao
*   Pos-condicao: O No e escrito no arquivo de dados
*/
void escreve_no(FILE* arq, no* x, int pos);

/*  Le o cabecalho do arquivo de dados
*   Pre-condicao: Arquivo de dados com cabecalho já existente e aberto
*   Pos-condicao: Retorna o cabecalho presente no arquivo binario
*/
cabecalho* le_cabecalho(FILE* arq);

/*  Funcao que cuida da insercao do item na arvore
*   Pre-condicao: Arquivo binario da arvore aberto e com cabecalho, o item a ser inserido
*   Pos-condicao: O item e inserido no arquivo
*/
int insere(FILE* arq, no* raiz,itemEstoque item);

/*  Funcao recursiva que remove um No da arvore
*   Pre-condicao: Arquivo binario da arvore ja aberto e com cabecalho, No da arvore (raiz),codigo do item a ser removido
*   Pos-condicao: O item e removido da arvore
*/
int remove_no(FILE* arq, no* aux ,int codigo);

/*  Remove um item da arvore dado seu codigo
*   Pre-condicao: Arquivo binario da arvore ja aberto e com cabecalho, codigo do item a ser removido
*   Pos-condicao: O item e removido da arvore e a posicao livre atualizada
*/
void remover(FILE* arq, int id);

/*  Funcao auxilar para calcular a altura da raiz da arvore ate o ultimo No
*   Pre-condicao: Arquivo bianrio com a arvore, No da arvore
*   Pos-condicao: Retorna a altura da arvore
*/
int calcAltura(FILE* arq,no* aux);

/*  Imprime os Nos de determinado nivel
*   Pre-condicao: Arquivo binario com a arvore, No da arvore e o nivel a ser impresso
*   Pos-condicao: Todos os Nos presentes no nivel sao impressos
*/
void imprimeNivel(FILE* arq, no* aux, int level);

/*  Funcao para imprimir a arvore por niveis
*   Pre-condicao: Arquivo binario com a arvore, No raiz da arvore
*   Pos-condicao: Os Nos da arvore sao impressos
*/
void imprimirPorNiveis(FILE* arq, no* aux);

#endif //ARVOREBINARIA_H_INCLUDED
