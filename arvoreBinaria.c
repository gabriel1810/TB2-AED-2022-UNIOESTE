#include "arvoreBinaria.h"

/*  Faz o percurso em ordem na arvore, imprimindo os dados
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No raiz da arvore valido
*   Pos-condicao: Imprime as informacoes de todos os itens da arvore em ordem
*/
void in_ordem(FILE* arq,no* aux){
    if(aux->pos != -1){
        in_ordem(arq,le_no(arq,aux->esq));
        if(aux->livre == 0) printf("%d | %s | %s | %s | %d | %0.2f\n",aux->item.codigo,aux->item.nome,aux->item.marca,aux->item.categoria,aux->item.qntEstoque,aux->item.preco);
        in_ordem(arq,le_no(arq,aux->dir));
    }
}

/*  Retorna a posicao do ultimo No da arvore
*   Pre-condicao: Arquivo de dados aberto e populado com dados
*   Pos-condicao: Posicao do ultimo No
*/
int ultimoIns(FILE* arq){
    no* x = malloc(sizeof(no));
    //Apenas um warning, por enquanto.
    fseek(arq,-sizeof(no),SEEK_END);
    fread(x,sizeof(no),1,arq);
    return x->pos;
}

/*  Percorre a arvore em ordem, imprimindo as posicoes livres
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No raiz da arvore valido
*   Pos-condicao: Imprime as posicoes livres na arvore
*/
void printLivres(FILE* arq,no* aux, int i){
    if(i <= ultimoIns(arq)){
        no* aux = le_no(arq,i);
        int num = aux->pos;
        if(aux->livre != 0 && num != -1) printf("%d ",num);
        printLivres(arq,aux,i+1);
    }
}

/*  Percorre a arvore Buscando o maior codigo de item na arvore
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No da arvore para iniciar a procura
*   Pos-condicao: Retorna o item cujo o codigo e o maior dado o No inicial
*/
itemEstoque maximo(FILE* arq,no* aux){
    while(le_no(arq,aux->dir)->pos != -1) aux = le_no(arq,aux->dir);
    return aux->item;
}

/*  Percorre a arvore Buscando o menor codigo de item na arvore
*   Pre-condicao: Arquivo de dados aberto e populado com dados, No da arvore para iniciar a procura
*   Pos-condicao: Retorna o item cujo o codigo e o menor dado o No inicial
*/
itemEstoque minimo(FILE* arq,no* aux){
    while(le_no(arq,aux->esq)->pos != -1) aux = le_no(arq,aux->esq);
    return aux->item;
}

/*  Escreve o cabecalho no arquivo binario
*   Pre-condicao: Arquivo de dados aberto, e um cabecalho valido a ser escrito
*   Pos-condicao: O cabecalho e escrito no arquivo
*/
void escreve_cabecalho(FILE* arq, cabecalho* cab){
    fseek(arq,0,SEEK_SET);
    fwrite(cab,sizeof(cabecalho),1,arq);
}

/*  Inicia a arvore binaria com cabecalho no arquivo
*   Pre-condicao: Arquivo de dados aberto
*   Pos-condicao: Cria uma nova arvore, escrevendo o cabecalho no arquivo pela primeira vez
*/
void cria_arvore_vazia(FILE* arq){
    cabecalho* cab = (cabecalho*) malloc(sizeof(cabecalho));
    cab->raiz = 1;
    cab->pos_livre = 1;
    escreve_cabecalho(arq,cab);
    free(cab);
}

/*  Busca a posicao de um item na arvore, dado seu codigo
*   Pre-condicao: Arquivo binario da arvore aberto e com cabecalho, o codigo do item
*   Pos-condicao: Retorna a posicao do item na arvore
*/
int buscaPosicao(FILE* arq,int codigo){
    if(codigo == -1) return -1;
    int pos_procura = 1;    //Posicao inicial da procura
    no* aux;
    for(pos_procura = 1; ;pos_procura++){
        aux = le_no(arq,pos_procura);
         if(aux->pos != -1 && aux->livre ==0){
            if(aux->item.codigo == codigo) return aux->pos;
         }
         else if(aux->pos == -1) return -1;
    }
}

/*  Le um no da arvore binaria na posicao especificada
*   Pre-condicao: Arquivo de dados aberto e populado com dados, posicao a ser lida do arquivo
*   Pos-condicao: Retorna o No resultante da busca
*/
no* le_no(FILE* arq, int pos) {
    no* x = malloc(sizeof(no));
    x->pos = x->dir = x->esq = x->livre = -1;    //Define que o No e null
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no),SEEK_SET);
    fread(x,sizeof(no),1,arq);  //Popula o No, caso seja nulo vai continuar como pos -1
    return x;
}

/*  Le um no da arvore binaria na posicao especificada
*   Pre-condicao: Arquivo de dados aberto e populado com dados, posicao a ser lida do arquivo
*   Pos-condicao: Retorna o No resultante da busca
*/
void escreve_no(FILE* arq, no* x, int pos){
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no),SEEK_SET);
    fwrite(x,sizeof(no),1,arq);
}

/*  Le o cabecalho do arquivo de dados
*   Pre-condicao: Arquivo de dados com cabecalho já existente e aberto
*   Pos-condicao: Retorna o cabecalho presente no arquivo binario
*/
cabecalho* le_cabecalho(FILE* arq){
    cabecalho* cab = (cabecalho*)malloc(sizeof(cabecalho));
    fseek(arq,0,SEEK_SET);
    fread(cab,sizeof(cabecalho),1,arq);
    return cab;
}

/*  Funcao que cuida da insercao do item na arvore
*   Pre-condicao: Arquivo binario da arvore aberto e com cabecalho, o item a ser inserido
*   Pos-condicao: O item e inserido no arquivo
*/
int insere(FILE* arq, no* raiz, itemEstoque item){
    cabecalho *cab = le_cabecalho(arq);
    if(raiz->pos == -1 || raiz->pos == cab->pos_livre || cab->pos_livre == 1){
        no* aux = le_no(arq,cab->pos_livre);
        raiz->pos = cab->pos_livre;

        if(aux->livre == -1) cab->pos_livre = cab->pos_livre+1;
        else if(aux->livre != -1) cab->pos_livre = aux->livre;

        raiz->dir = raiz->esq = -1;
        raiz->item = item;
        raiz->livre = 0;
        escreve_cabecalho(arq,cab);
        escreve_no(arq,raiz,raiz->pos);
        printf("Item [%d] [%s] inserido na posicao %d\n",item.codigo,item.nome,raiz->pos);
        return raiz->pos;
    }

    else if(item.codigo < raiz->item.codigo){
        raiz->esq = insere(arq,le_no(arq,raiz->esq),item);
        escreve_no(arq,raiz,raiz->pos);
        return raiz->pos;
    }

    else{
       raiz->dir = insere(arq,le_no(arq,raiz->dir),item);
       escreve_no(arq,raiz,raiz->pos);
       return raiz->pos;
    }
}

/*  Funcao recursiva que remove um No da arvore
*   Pre-condicao: Arquivo binario da arvore ja aberto e com cabecalho, No da arvore (raiz),codigo do item a ser removido
*   Pos-condicao: O item e removido da arvore
*/
int remove_no(FILE* arq, no* aux ,int codigo){
    cabecalho* cab = le_cabecalho(arq);
    if(aux->pos == -1 ) return -1;

    if(codigo < aux->item.codigo){
        aux->esq = remove_no(arq,le_no(arq,aux->esq),codigo);
        escreve_no(arq,aux,aux->pos);
    }

    else if( codigo > aux->item.codigo){
         aux->dir = remove_no(arq,le_no(arq,aux->dir),codigo);
         escreve_no(arq,aux,aux->pos);
    }

    else{
        if(aux->esq == -1 && aux->dir == -1){
            aux->livre = cab->pos_livre;
            escreve_no(arq,aux,aux->pos);
            cab->pos_livre = aux->pos;
            escreve_cabecalho(arq,cab);
            return -1;
        }
        else if(aux->esq == -1){
            aux->item = minimo(arq,le_no(arq,aux->dir));
            escreve_no(arq,aux,aux->pos);
            aux->dir = remove_no(arq,le_no(arq,aux->dir),aux->item.codigo);
            escreve_no(arq,aux,aux->pos);
        }
        else{
            aux->item = maximo(arq,le_no(arq,aux->esq));
            escreve_no(arq,aux,aux->pos);
            aux->esq = remove_no(arq,le_no(arq,aux->esq),aux->item.codigo);
            escreve_no(arq,aux,aux->pos);
        }
    }
    return aux->pos;
}

/*  Remove um item da arvore dado seu codigo
*   Pre-condicao: Arquivo binario da arvore ja aberto e com cabecalho, codigo do item a ser removido
*   Pos-condicao: O item e removido da arvore e a posicao livre atualizada
*/
void remover(FILE* arq,int id){
    int pos = buscaPosicao(arq,id);
    no* aux = le_no(arq,pos);
    if(pos == -1) printf("\nCodigo nao encontrado\n");
    else{
        remove_no(arq,le_no(arq,1),id);
        printf("Item [%d] [%s] removido\n",aux->item.codigo,aux->item.nome);
    }
}

/*  Funcao auxilar para calcular a altura da raiz da arvore ate o ultimo No
*   Pre-condicao: Arquivo bianrio com a arvore, No da arvore
*   Pos-condicao: Retorna a altura da arvore
*/
int calcAltura(FILE* arq,no* aux){
    //Se for null
    if (aux->pos == -1 || aux->livre !=0) return 0;

    else {
        //Calcula altura das subarvores
        int alturaEsq = calcAltura(arq,le_no(arq,aux->esq));
        int alturaDir = calcAltura(arq,le_no(arq,aux->dir));

        //Retorna maior altura+1
        if (alturaEsq > alturaDir) return (alturaEsq + 1);
        else return (alturaDir + 1);
    }
}

/*  Imprime os Nos de determinado nivel
*   Pre-condicao: Arquivo binario com a arvore, No da arvore e o nivel a ser impresso
*   Pos-condicao: Todos os Nos presentes no nivel sao impressos
*/
void imprimeNivel(FILE* arq, no* aux, int level){
    if (aux->pos == -1) return;
    if (level == 1){
        if(aux->livre == 0) printf("%d ", aux->item.codigo);
    }

    else if (level > 1) {
        imprimeNivel(arq,le_no(arq,aux->esq), level - 1);
        imprimeNivel(arq,le_no(arq,aux->dir), level - 1);
    }
}

/*  Funcao para imprimir a arvore por niveis
*   Pre-condicao: Arquivo binario com a arvore, No raiz da arvore
*   Pos-condicao: Os Nos da arvore sao impressos
*/
void imprimirPorNiveis(FILE* arq, no* aux){
    int h = calcAltura(arq,aux);
    int i;
    for (i = 1; i <= h; i++){
        imprimeNivel(arq,aux, i);
        printf("\n");
    }
}
