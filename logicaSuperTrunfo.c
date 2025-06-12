#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    unsigned long long populacao;
    double area;
    double pib;
    int pontos;
} Cidade;

void lerCidade(Cidade *c, int num) {
    printf("\nCidade %d\n", num);
    printf("Nome: "); fgets(c->nome, sizeof(c->nome), stdin);
    c->nome[strcspn(c->nome, "\n")] = 0;
    printf("Populacao: "); scanf("%llu", &c->populacao);
    printf("Area: "); scanf("%lf", &c->area);
    printf("PIB: "); scanf("%lf", &c->pib);
    printf("Pontos Turisticos: "); scanf("%d", &c->pontos);
    getchar(); // limpa buffer
}

void exibirCidade(Cidade c) {
    printf("\nCidade: %s\nPopulacao: %llu\nArea: %.2f\nPIB: %.2f\nPontos Turisticos: %d\n", c.nome, c.populacao, c.area, c.pib, c.pontos);
}

int main() {
    Cidade c1, c2;
    lerCidade(&c1, 1);
    lerCidade(&c2, 2);
    exibirCidade(c1);
    exibirCidade(c2);
    return 0;
}