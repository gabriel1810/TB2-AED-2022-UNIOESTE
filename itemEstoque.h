#ifndef ITEMESTOQUE_H_INCLUDED
#define ITEMESTOQUE_H_INCLUDED
#include "arvoreBinaria.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  Interface de usuario que obtem os dados do item a ser inserido
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: Passa os dados do item para a funcao de insercao na arvore
*/
void formCadastro(FILE* arq);

/*  Interface que guia o usuario na remocao do item
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: Passa as informacoes para a funcao de remocao
*/
void formRemocao(FILE* arq);

/*  Realiza a modificacao do item dado o codigo do mesmo e a opcao a ser modificada
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto, codigo do item a ser alterado, opt=1 modifica preco, opt=2 quantidade
*   Pos-condicao: Realiza o processo de modificacao do item
*/
void modificarItem(FILE* arq, int codigo, int opt);

/*  Interface que guia o usuario na modificao do item
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: O item e modificado
*/
void formAtualizaProduto(FILE* arq);

/*  Interface que exibe as informacoes dos itens para o usuario
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: Exibe as informacoes dos itens
*/
void formListaInfoProduto(FILE* arq);

/*  Interface que exibe os niveis da arvore
*   Pre-condicao: Arquivo binario com a arvore aberto
*   Pos-condicao: Chama a funcao que faz a impressao por niveis
*/
void formImprimeArvore();

/*  Interface que mostrará ao usuario as posicoes livres na arvore
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: As posicoes livres sao exibidas na tela
*/
void formListarLivres(FILE* arq);

/*  Funcao auxiliar que troca ',' por '.' para o preco do item
*   Pre-condicao: String a ser alterada
*   Pos-condicao: Retorna a String alterada
*/
char* swapChar(char* str);

/*  Imterface que ajuda o usuario a carregar um arquivo de texto
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: As operacoes em lote sao realizadas
*/
void formCarregaArquivo(FILE* arq);


#endif // ITEMESTOQUE_H_INCLUDED
