#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Estrutura para armazenar os dados de uma cidade
typedef struct {
    char estado[3]; // Sigla do estado
    char codigo[4]; // Código da carta (ex: A01)
    char nome[50]; // Nome da cidade
    unsigned long long populacao; // População total
    double area; // Área em km²
    double pib; // Produto Interno Bruto em bilhões
    int pontos_turisticos; // Número de pontos turísticos
    double densidade; // Densidade populacional calculada
    double pib_per_capita; // PIB per capita calculado
    double super_poder; // Super poder calculado
} CartaCidade;

// Função para limpar o buffer do teclado (para evitar problemas com scanf/fgets)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Função para ler os dados de uma carta do usuário
void lerCarta(CartaCidade *carta, int numero) {
    printf("\nDigite os dados da Carta %d:\n", numero);

    // Leitura do estado (2 letras)
    do {
        printf("Estado (ex: SP): ");
        scanf("%2s", carta->estado);
        limparBuffer();
    } while (!(isalpha(carta->estado[0]) && isalpha(carta->estado[1])));

    // Leitura do código da carta (ex: A01)
    do {
        printf("Código (ex: A01): ");
        scanf("%3s", carta->codigo);
        limparBuffer();
    } while (!(isalpha(carta->codigo[0]) && isdigit(carta->codigo[1]) && isdigit(carta->codigo[2])));

    // Leitura do nome da cidade
    printf("Nome da cidade: ");
    fgets(carta->nome, sizeof(carta->nome), stdin);
    carta->nome[strcspn(carta->nome, "\n")] = '\0'; // Remove o \n

    // Leitura da população (maior que zero)
    do {
        printf("População: ");
        scanf("%llu", &carta->populacao);
        limparBuffer();
    } while (carta->populacao == 0);

    // Leitura da área
    do {
        printf("Área (km²): ");
        scanf("%lf", &carta->area);
        limparBuffer();
    } while (carta->area <= 0);

    // Leitura do PIB
    do {
        printf("PIB (em bilhões): ");
        scanf("%lf", &carta->pib);
        limparBuffer();
    } while (carta->pib <= 0);

    // Leitura dos pontos turísticos
    do {
        printf("Número de pontos turísticos: ");
        scanf("%d", &carta->pontos_turisticos);
        limparBuffer();
    } while (carta->pontos_turisticos < 0);

    // Cálculo dos atributos derivados
    carta->densidade = carta->populacao / carta->area;
    carta->pib_per_capita = carta->pib / carta->populacao;
    carta->super_poder = carta->populacao + carta->area + carta->pib + carta->pontos_turisticos + carta->pib_per_capita + (1.0 / carta->densidade);
}

// Função para exibir os dados de uma carta
void exibirCarta(CartaCidade carta, int numero) {
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

// Função para comparar dois valores. Retorna:
// 0 = empate, 1 = carta1 venceu, 2 = carta2 venceu
// menorVence indica se o menor valor vence (usado para densidade)
int comparar(double a1, double a2, int menorVence) {
    if (a1 == a2) return 0;
    return (menorVence ? (a1 < a2) : (a1 > a2)) ? 1 : 2;
}

int main() {
    CartaCidade carta1, carta2;
    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);

    exibirCarta(carta1, 1);
    exibirCarta(carta2, 2);

    int escolha1, escolha2;
    printf("\nEscolha o primeiro atributo para comparar:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Populacional\n6 - PIB per Capita\n7 - Comparar Todos (incluindo Super Poder)\nOpção: ");
    scanf("%d", &escolha1);

    // Se a opção for comparar todos os atributos
    if (escolha1 == 7) {
        printf("\n--- Comparação de Todos os Atributos ---\n");
        int pontos_c1 = 0, pontos_c2 = 0;

        // Comparações individuais para cada atributo
        pontos_c1 += comparar(carta1.populacao, carta2.populacao, 0) == 1;
        pontos_c2 += comparar(carta1.populacao, carta2.populacao, 0) == 2;

        pontos_c1 += comparar(carta1.area, carta2.area, 0) == 1;
        pontos_c2 += comparar(carta1.area, carta2.area, 0) == 2;

        pontos_c1 += comparar(carta1.pib, carta2.pib, 0) == 1;
        pontos_c2 += comparar(carta1.pib, carta2.pib, 0) == 2;

        pontos_c1 += comparar(carta1.pontos_turisticos, carta2.pontos_turisticos, 0) == 1;
        pontos_c2 += comparar(carta1.pontos_turisticos, carta2.pontos_turisticos, 0) == 2;

        pontos_c1 += comparar(carta1.densidade, carta2.densidade, 1) == 1;
        pontos_c2 += comparar(carta1.densidade, carta2.densidade, 1) == 2;

        pontos_c1 += comparar(carta1.pib_per_capita, carta2.pib_per_capita, 0) == 1;
        pontos_c2 += comparar(carta1.pib_per_capita, carta2.pib_per_capita, 0) == 2;

        pontos_c1 += comparar(carta1.super_poder, carta2.super_poder, 0) == 1;
        pontos_c2 += comparar(carta1.super_poder, carta2.super_poder, 0) == 2;

        // Exibe placar e resultado final
        printf("\nPlacar Final: Carta 1 = %d pontos, Carta 2 = %d pontos\n", pontos_c1, pontos_c2);
        if (pontos_c1 > pontos_c2)
            printf("Resultado: Carta 1 venceu no geral!\n");
        else if (pontos_c2 > pontos_c1)
            printf("Resultado: Carta 2 venceu no geral!\n");
        else
            printf("Resultado: Empate geral!\n");
        return 0;
    }

    // Caso não seja comparar todos, pede o segundo atributo
    printf("\nEscolha o segundo atributo para comparar:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Populacional\n6 - PIB per Capita\nOpção: ");
    scanf("%d", &escolha2);

    double valor1_c1, valor1_c2, valor2_c1, valor2_c2;
    int menorVence1 = 0, menorVence2 = 0;

    // Seleciona o primeiro atributo com base na escolha
    switch (escolha1) {
        case 1: valor1_c1 = carta1.populacao; valor1_c2 = carta2.populacao; break;
        case 2: valor1_c1 = carta1.area; valor1_c2 = carta2.area; break;
        case 3: valor1_c1 = carta1.pib; valor1_c2 = carta2.pib; break;
        case 4: valor1_c1 = carta1.pontos_turisticos; valor1_c2 = carta2.pontos_turisticos; break;
        case 5: valor1_c1 = carta1.densidade; valor1_c2 = carta2.densidade; menorVence1 = 1; break;
        case 6: valor1_c1 = carta1.pib_per_capita; valor1_c2 = carta2.pib_per_capita; break;
        default: printf("Atributo inválido!\n"); return 1;
    }

    // Seleciona o segundo atributo com base na escolha
    switch (escolha2) {
        case 1: valor2_c1 = carta1.populacao; valor2_c2 = carta2.populacao; break;
        case 2: valor2_c1 = carta1.area; valor2_c2 = carta2.area; break;
        case 3: valor2_c1 = carta1.pib; valor2_c2 = carta2.pib; break;
        case 4: valor2_c1 = carta1.pontos_turisticos; valor2_c2 = carta2.pontos_turisticos; break;
        case 5: valor2_c1 = carta1.densidade; valor2_c2 = carta2.densidade; menorVence2 = 1; break;
        case 6: valor2_c1 = carta1.pib_per_capita; valor2_c2 = carta2.pib_per_capita; break;
        default: printf("Atributo inválido!\n"); return 1;
    }

    // Compara os dois atributos selecionados
    int vencedor1 = comparar(valor1_c1, valor1_c2, menorVence1);
    int vencedor2 = comparar(valor2_c1, valor2_c2, menorVence2);

    printf("\n--- Resultado da Comparação ---\n");

    // Lógica de decisão final
    if (vencedor1 == 0 && vencedor2 == 0)
        printf("Empate total entre as cartas!\n");
    else if ((vencedor1 == 1 && vencedor2 != 2) || (vencedor2 == 1 && vencedor1 != 2))
        printf("Carta 1 venceu!\n");
    else if ((vencedor1 == 2 && vencedor2 != 1) || (vencedor2 == 2 && vencedor1 != 1))
        printf("Carta 2 venceu!\n");
    else
        printf("Empate parcial entre as cartas!\n");

    return 0;
}
