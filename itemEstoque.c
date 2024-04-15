#include "itemEstoque.h"

/*  Interface de usuario que obtem os dados do item a ser inserido
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: Passa os dados do item para a funcao de insercao na arvore
*/
void formCadastro(FILE* arq){
    itemEstoque item;
    printf("------INSERCAO------\n");
    printf("Codigo: ");
    scanf("%d%*c",&item.codigo);
    printf("\nNome: ");
    scanf("%[^\n]%*c", item.nome);
    printf("\nMarca: ");
    scanf("%[^\n]%*c", item.marca);
    printf("\nCategoria: ");
    scanf("%[^\n]%*c", item.categoria);
    printf("\nEstoque: ");
    scanf("%d%*c",&item.qntEstoque);
    printf("\nPreco: ");
    scanf("%f%*c",&item.preco);

    if(buscaPosicao(arq,item.codigo) != -1) printf("*Erro* Item [%d] [%s] ja existe\n",item.codigo,item.nome);

    else insere(arq,le_no(arq,1),item);
}

/*  Interface que guia o usuario na remocao do item
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: Passa as informacoes para a funcao de remocao
*/
void formRemocao(FILE* arq){
    cabecalho* cab = le_cabecalho(arq);
    no* x = le_no(arq,cab->raiz);
    int codigo;
    printf("------REMOCAO------\n");
    printf("Produtos cadastrados:\n");
    printf("cod | nome | marca | categoria | estoque | preco\n");
    in_ordem(arq,x);
    printf("\nCodigo a ser removido: ");
    scanf("%d%*c",&codigo);
    remover(arq,codigo);
}

/*  Realiza a modificacao do item dado o codigo do mesmo e a opcao a ser modificada
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto, codigo do item a ser alterado, opt=1 modifica preco, opt=2 quantidade
*   Pos-condicao: Realiza o processo de modificacao do item
*/
void modificarItem(FILE* arq, int codigo, int opt){
    no* aux = le_no(arq,buscaPosicao(arq,codigo));
    if(buscaPosicao(arq,codigo) == -1) printf("Item nao encontrado\n");
    else{
        if(aux->pos == -1 || aux->livre != 0) printf("Item nao encontrado\n");
        else if(aux->pos != -1 && aux->livre == 0){ //Caso o item exista
            //Modificar preco
            if(opt == 1){
                    printf("Preco atual: %0.2f\nNovo preco: ",aux->item.preco);
                    scanf("%f%*c",&aux->item.preco);
            }
            //modificar qnt estoque
            else if(opt == 2){
                    printf("Estoque atual: %d\nNovo Estoque: ",aux->item.qntEstoque);
                    scanf("%d%*c",&aux->item.qntEstoque);
            }
            escreve_no(arq,aux,aux->pos);
            printf("\nSalvo com sucesso\n");
        }
    }
}

/*  Interface que guia o usuario na modificao do item
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: O item e modificado
*/
void formAtualizaProduto(FILE* arq){
    cabecalho* cab = le_cabecalho(arq);
    no* x = le_no(arq,cab->raiz);
    int opt; //Opcao do menu
    int cod; //codigo do item
    printf("------MODIFICAR------\n");
    do{
        printf("[1] - Ver lista de produtos\n");
        printf("[2] - Modificar preco\n");
        printf("[3] - Modificar quantidade\n");
        printf("[0] - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d%*c",&opt);
        switch(opt){
                case 0: break;

                case 1: printf("cod | nome | marca | categoria | estoque | preco\n");
                        in_ordem(arq,x);
                break;

                case 2: printf("Codigo: "); scanf("%d%*c",&cod); modificarItem(arq,cod,1);
                break;

                case 3: printf("Codigo: "); scanf("%d%*c",&cod); modificarItem(arq,cod,2);
                break;

                default: printf("\nOpcao nao encontrada\n");
                break;
        }
    } while(opt != 0);
}

/*  Interface que exibe as informacoes dos itens para o usuario
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: Exibe as informacoes dos itens
*/
void formListaInfoProduto(FILE* arq){
    int opt,cod,n;
    cabecalho* cab = le_cabecalho(arq);
    no* x = le_no(arq,cab->raiz); //Carrega o No raiz
    printf("------VISUALIZAR------\n");
    do{
        printf("[1] - Exibir todos os produtos\n");
        printf("[2] - Exibir por codigo\n");
        printf("[0] - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d%*c",&opt);
        switch(opt){
            case 0: break;

            case 1: printf("cod | nome | marca | categoria | estoque | preco\n");
                    in_ordem(arq,x); //Exibe os informacoes de todos os itens da arvore
            break;

            case 2: printf("Codigo: ");
                    scanf("%d%*c",&cod);
                    n = buscaPosicao(arq,cod);
                    if(n != -1){    //Caso o codigo exista
                        no* aux = le_no(arq,n);
                        if(aux->livre == 0){
                            printf("cod | nome | marca | categoria | estoque | preco\n");
                            printf("%d | %s | %s | %s | %d | %0.2f\n",aux->item.codigo,aux->item.nome,aux->item.marca,aux->item.categoria,aux->item.qntEstoque,aux->item.preco);
                        }
                    }
                    else printf("Codigo nao encontrado\n");
            break;
            default: printf("\nOpcao nao encontrada\n");
            break;
        }
    } while(opt != 0);
}

/*  Interface que exibe os niveis da arvore
*   Pre-condicao: Arquivo binario com a arvore aberto
*   Pos-condicao: Chama a funcao que faz a impressao por niveis
*/
void formImprimeArvore(FILE* arq){
    cabecalho *cab = le_cabecalho(arq);
    no* raiz = le_no(arq,cab->raiz);
    printf("------ARVORE BINARIA------\n");
    imprimirPorNiveis(arq,raiz);
}

/*  Interface que mostrará ao usuario as posicoes livres na arvore
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: As posicoes livres sao exibidas na tela
*/
void formListarLivres(FILE* arq){
    no* x = le_no(arq,1);
    printf("------POSICOES LIVRES------\n");
    printLivres(arq,x,1);
    printf("\n");
}

/*  Funcao auxiliar que troca ',' por '.' para o preco do item
*   Pre-condicao: String a ser alterada
*   Pos-condicao: Retorna a String alterada
*/
char* swapChar(char* str){
    int tam = strlen(str);
    for(int i =0; i < tam; i++)
        if(str[i] == ',') str[i] = '.';
    return str;
}

/*  Interface que ajuda o usuario a carregar um arquivo de texto
*   Pre-condicao: Arquivo binario com dados da arvore e cabecalho ja aberto
*   Pos-condicao: As operacoes em lote sao realizadas
*/
void formCarregaArquivo(FILE* arq){
    char nomeArquivo[50]; char linhaArquivo[255];
    char dados[255][255];
    FILE *arq_dados;
    char *pch,aux=0;
    itemEstoque item;

    printf("------CARREGAR ARQUIVO------\n");
    printf("\nNome do arquivo:");
    scanf("%[^\n]%*c", nomeArquivo);

    arq_dados = fopen(nomeArquivo,"r");
    if(arq_dados == NULL) printf("Arquivo nao encontrado\n");

    else{
        printf("----------------------\n");
        printf("Lin|      Descricao\n");
        printf("----------------------\n");

         int countLinha = 1;
         while(fgets(linhaArquivo,255,arq_dados) != NULL){

                if (linhaArquivo[strlen(linhaArquivo)-1] == '\n') linhaArquivo[strlen(linhaArquivo)-1] = '\0'; //Caso possua um espaco a mais no final da linha
                int k=0;
                //Separa as palavras nos ';'
                pch = strtok(linhaArquivo,";");
                while(pch != NULL){
                    strcpy(dados[k++],pch);
                    pch = strtok (NULL, ";");
                }
                //Insercao
                if(linhaArquivo[0] == 'I'){
                    item.codigo = atoi(dados[1]);
                    strcpy(item.nome,dados[2]);
                    strcpy(item.marca,dados[3]);
                    strcpy(item.categoria,dados[4]);
                    item.qntEstoque = atoi(dados[5]);
                    swapChar(dados[6]);
                    item.preco = atof(dados[6]);
                    printf("%2d | ",countLinha++);
                    if(buscaPosicao(arq,item.codigo) != -1) printf("*Erro* Item [%d] [%s] ja existe\n",item.codigo,item.nome);
                    else insere(arq,le_no(arq,1),item);
                }

                //Alteracao
                else if( linhaArquivo[0] == 'A'){
                    //Se o ultimo caractere da linha for ';' quer dizer que nao havera alteracao de preco
                    if(linhaArquivo[strlen(linhaArquivo)-1] == ';') aux = 1;
                    if(buscaPosicao(arq,atoi(dados[1])) == -1) printf("*Erro* Item [%d] nao encontrado\n",atoi(dados[1]));
                    else{
                        no* alteracao = le_no(arq,buscaPosicao(arq,atoi(dados[1])));
                        if(alteracao->pos != -1){ //Se o item existe
                            if(k == 3){ //Alteracao de apenas um atributo
                                if(aux == 1) alteracao->item.qntEstoque = atoi(dados[2]);
                                else alteracao->item.preco = atof(swapChar(dados[2]));
                            }

                            else if(k == 4){ //Alteracao de dois atributos
                                alteracao->item.qntEstoque = atoi(dados[2]);
                                alteracao->item.preco = atof(swapChar(dados[3]));
                            }
                            escreve_no(arq,alteracao,alteracao->pos);
                            printf("%2d | ",countLinha++);
                            printf("Item [%d] [%s] alterado\n",alteracao->item.codigo,alteracao->item.nome);
                        }
                        else{
                            printf("%2d | ",countLinha++);
                            printf("*Erro* Item [%d] nao encontrado\n",atoi(dados[1]));
                        }
                    }
                }

                //Remocao
                else{
                    printf("%2d | ",countLinha++);
                    remover(arq,atoi(dados[1]));
                }
         }
    }
}
