#include "Produto.h"
#include <stdio.h>

Prod *cadastrarProd(char *codProd) {
    Prod *produto = malloc(sizeof(Prod));

    if (produto == NULL) return NULL;

    int qtdEstoque;
    double preco;
    char descricao[51];

    strcpy(produto->codProd, codProd);
    printf("Digite a descricao do produto, 50 char maximo: ");
    fgets(descricao, 51, stdin);
    descricao[strcspn(descricao, "\n")] = '\0';
    printf("Digite o preco do produto: ");
    scanf("%lf", &preco);
    limpaBuffer();
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &qtdEstoque);

    strcpy(produto->descricaoProd, descricao);
    produto->precoProd = preco;
    produto->qtdEstoqueProd = qtdEstoque;

    return produto;
}

void destroyProd(Prod *produto) { free(produto); }

void exibirProd(Prod *produto) {

    printf("codigo produto: %s\n", produto->codProd);
    printf("descricao do produto: %s\n", produto->descricaoProd);
    printf("preco do produto: %.2f\n", produto->precoProd);
    printf("quantidade em estoque: %d\n", produto->qtdEstoqueProd);
}

void alterarProd(Prod *produto) {
    if (produto == NULL) {
        printf("Produto nao encontrado para alteracao\n");
        return;
    }
    int decisao;

    printf("1 - Apenas preco\n");
    printf("2 - Apenas a quantidade em estoque\n");
    printf("3 - Preco e quantidade em estoque\n");
    printf("0 - sair\n");
    printf("O que deseja alterar: ");
    scanf("%d", &decisao);
    limpaBuffer();

    switch (decisao) {
    case 1:
        printf("Digite o novo preco do produto: ");
        scanf("%lf", &produto->precoProd);
        break;
    case 2:
        printf("Digite a nova quantidade em estoque: ");
        scanf("%d", &produto->qtdEstoqueProd);
        break;
    case 3:
        printf("Digite o novo preco do produto: ");
        scanf("%lf", &produto->precoProd);
        printf("Digite a nova quantidade em estoque: ");
        scanf("%d", &produto->qtdEstoqueProd);
        break;
    case 0:
        break;
    default:
        printf("opcao invalida");
        break;
    }
}
