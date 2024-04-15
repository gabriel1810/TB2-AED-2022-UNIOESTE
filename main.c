#ifdef _WIN32
#define LIMPA_TELA() system("cls")
#endif // _WIN32

#ifdef linux
#define LIMPA_TELA() system("clear")
#endif // linux

#define PAUSE(); printf("Pressione qualquer tecla para continuar..."); getchar();

#include "itemEstoque.h"
#include "arvoreBinaria.h"

int main(){
    FILE* arq;
    int opt;
    arq = fopen("arquivo.bin","rb+");
    if( arq == NULL){
        //Caso o arquivo de dados ainda nao exista, ele e criado e o cabecalho e escrito no comeco do arquivo
        arq = fopen("arquivo.bin","wb+");
        cria_arvore_vazia(arq);
    }
    //Fica em loop no menu principal
     do{
            LIMPA_TELA();
            printf("------MENU PRINCIPAL------\n");
            printf("[1] - cadastrar produto\n");
            printf("[2] - remover produto\n");
            printf("[3] - modificar produto\n");
            printf("[4] - visualizar informacoes de produtos\n");
            printf("[5] - imprimir arvore binaria\n");
            printf("[6] - listar posicoes livres\n");
            printf("[7] - carregar arquivo\n");
            printf("[0] - sair\n");
            printf("\nOpcao: ");
            scanf("%d%*c",&opt);

            switch(opt){
                case 0: return 0;
            break;
                case 1: LIMPA_TELA(); formCadastro(arq); PAUSE();   //Tem que ver isso, ta inserindo 120 na esquerda do 70
            break;
                case 2: LIMPA_TELA(); formRemocao(arq); PAUSE();
            break;
                case 3: LIMPA_TELA(); formAtualizaProduto(arq);
            break;
                case 4: LIMPA_TELA(); formListaInfoProduto(arq);
            break;
                case 5: LIMPA_TELA(); formImprimeArvore(arq); PAUSE();
            break;
                case 6: LIMPA_TELA(); formListarLivres(arq); PAUSE();
            break;
                case 7: LIMPA_TELA(); formCarregaArquivo(arq); PAUSE();
            break;
                default: printf("\nOpcao nao encontrada.\n");
            break;
            }
        } while(opt != 0);

    fclose(arq);
    return 0;
}
