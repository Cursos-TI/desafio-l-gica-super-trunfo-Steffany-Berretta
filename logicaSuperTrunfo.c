#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Estrutura básica da carta
typedef struct {
    char estado[3];
    char codigo[4];
    char nome[50];
    unsigned long long populacao;
    double area;
    double pib;
    int pontos_turisticos;
    double densidade;
    double pib_per_capita;
    double super_poder;
} CartaCidade;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void lerCartaComCalculos(CartaCidade *carta, int numero) {
    printf("\nCadastro da Carta %d:\n", numero);

    printf("Estado (ex: SP): ");
    scanf("%2s", carta->estado);
    limparBuffer();

    printf("Código (ex: A01): ");
    scanf("%3s", carta->codigo);
    limparBuffer();

    printf("Nome da cidade: ");
    fgets(carta->nome, sizeof(carta->nome), stdin);
    carta->nome[strcspn(carta->nome, "\n")] = '\0';

    printf("População: ");
    scanf("%llu", &carta->populacao);

    printf("Área (km²): ");
    scanf("%lf", &carta->area);

    printf("PIB (em bilhões): ");
    scanf("%lf", &carta->pib);

    printf("Pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);

    limparBuffer();

    // Cálculo dos valores derivados
    carta->densidade = carta->populacao / carta->area;
    carta->pib_per_capita = carta->pib / carta->populacao;
    carta->super_poder = carta->populacao + carta->area + carta->pib + carta->pontos_turisticos + carta->pib_per_capita + (1.0 / carta->densidade);
}

void exibirCartaComCalculos(CartaCidade carta, int numero) {
    printf("\n--- Carta %d ---\n", numero);
    printf("Estado: %s\n", carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("Nome: %s\n", carta.nome);
    printf("População: %llu\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidade);
    printf("PIB per Capita: %.6f\n", carta.pib_per_capita);
    printf("Super Poder: %.2f\n", carta.super_poder);
}

int main() {
    CartaCidade carta1, carta2;

    lerCartaComCalculos(&carta1, 1);
    lerCartaComCalculos(&carta2, 2);

    exibirCartaComCalculos(carta1, 1);
    exibirCartaComCalculos(carta2, 2);

    return 0;
}
