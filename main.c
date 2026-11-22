#include "TreeRedBlack.h"

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void opcoes() {
    printf("1 - Cadastrar Produto\n");
    printf("2 - Buscar Produto\n");
    printf("3 - Alterar Produto\n");
    printf("4 - Mostrar Produtos em Ordem\n");
    printf("5 - Mostrar Produtos por Nivel\n");
    printf("6 - Remover Produto\n");
    printf("0 - Finalizar\n");
}

int main() {
    RBTree *arvore = initialize();

    if (arvore == NULL) {
        printf("Erro ao inicializar a arvore\n");
        return 1;
    }

    int op;
    char codProduto[21];
    bool func = 1;

    while (func == 1) {
        printf("\nEscolha uma opcao:\n");
        opcoes();
        scanf("%d", &op);
        limpaBuffer();

        switch (op) {
        case 1:
            printf("Digite o codigo do produto ate 20 char: ");
            fgets(codProduto, 21, stdin);
            codProduto[strcspn(codProduto, "\n")] = '\0';

            inserirNo(arvore, codProduto);
            break;

        case 2:
            printf("Digite o codigo do produto que deseja buscar: ");
            fgets(codProduto, 21, stdin);
            codProduto[strcspn(codProduto, "\n")] = '\0';

            Prod *achou = buscar(arvore->raiz, arvore->nil, codProduto);

            if (achou != NULL) {
                exibirProd(achou);
            } else {
                printf("Produto nao encontrado!\n");
            }
            break;

        case 3:
            printf("Digite o codigo do produto que deseja alterar: ");
            fgets(codProduto, 21, stdin);
            codProduto[strcspn(codProduto, "\n")] = '\0';

            alterarProduto(arvore, codProduto);
            break;

        case 4:
            exibirEmOrdem(arvore);
            break;

        case 5:
            porNivel(arvore);
            break;

        case 6:
            printf("Digite o codigo do produto que deseja remover: ");
            fgets(codProduto, 21, stdin);
            codProduto[strcspn(codProduto, "\n")] = '\0';

            removerNo(arvore, codProduto);
            break;

        case 0:
            destroy(arvore);
            func = 0;
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }

    return 0;
}
