#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TCS 100  // Máximo de opções para votação (TCs)
#define MAX_NOME 50  // Tamanho máximo do nome de um TC

// Estrutura para armazenar os dados de cada TC
typedef struct {
    char nome[MAX_NOME];
    int votos;
} TC;

// Funções
void contabilizarVotos(TC tcs[], int num_tcs);
void gerarResultado(TC tcs[], int num_tcs);
void tratarEmpate(TC tcs[], int num_tcs);

int main() {
    int num_tcs;

    // Leitura do número de TCs
    printf("Quantos TCs estao participando da votacao? ");
    scanf("%d", &num_tcs);
    getchar();  // Limpar o buffer de entrada

    // Inicialização do array de TCs
    TC tcs[MAX_TCS];

    // Leitura dos nomes dos TCs
    for (int i = 0; i < num_tcs; i++) {
        printf("Digite o nome do TC %d: ", i + 1);
        fgets(tcs[i].nome, MAX_NOME, stdin);
        tcs[i].nome[strcspn(tcs[i].nome, "\n")] = 0;  // Remover nova linha
        tcs[i].votos = 0;  // Inicializa os votos com 0
    }

    // Contabilização dos votos
    contabilizarVotos(tcs, num_tcs);

    // Geração do arquivo de resultado
    gerarResultado(tcs, num_tcs);

    return 0;
}

// Função para contabilizar votos
void contabilizarVotos(TC tcs[], int num_tcs) {
    int voto;
    printf("\nIniciando a votacao...\n");
    printf("Digite o numero do TC para votar (0 para finalizar):\n");

    while (1) {
        printf("Voto: ");
        scanf("%d", &voto);

        // Encerrar votação se o voto for 0
        if (voto == 0) {
            break;
        }

        // Verificar se o voto é válido
        if (voto > 0 && voto <= num_tcs) {
            tcs[voto - 1].votos++;  // Contabiliza o voto para o TC
        } else {
            printf("Voto inválido!\n");
        }
    }
}

// Função para gerar o arquivo de resultado
void gerarResultado(TC tcs[], int num_tcs) {
    FILE *arquivo;
    arquivo = fopen("resultado_votacao.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "Resultado da Votacao:\n\n");

    // Escrever os resultados no arquivo
    for (int i = 0; i < num_tcs; i++) {
        fprintf(arquivo, "TC: %s - Votos: %d\n", tcs[i].nome, tcs[i].votos);
    }

    // Tratamento de empate
    tratarEmpate(tcs, num_tcs);

    fclose(arquivo);
    printf("Resultado gerado com sucesso no arquivo 'resultado_votacao.txt'\n");
}

// Função para tratar empates
void tratarEmpate(TC tcs[], int num_tcs) {
    int max_votos = 0;
    TC vencedores[MAX_TCS];
    int num_vencedores = 0;

    // Determinar o número máximo de votos
    for (int i = 0; i < num_tcs; i++) {
        if (tcs[i].votos > max_votos) {
            max_votos = tcs[i].votos;
        }
    }

    // Encontrar todos os TCs que têm o número máximo de votos (para tratar empate)
    for (int i = 0; i < num_tcs; i++) {
        if (tcs[i].votos == max_votos) {
            vencedores[num_vencedores] = tcs[i];
            num_vencedores++;
        }
    }

    // Exibir os resultados no terminal e no arquivo
    FILE *arquivo;
    arquivo = fopen("resultado_votacao.txt", "a");

    if (num_vencedores == 1) {
        printf("\nVencedor: %s com %d votos!\n", vencedores[0].nome, max_votos);
        fprintf(arquivo, "\nVencedor: %s com %d votos!\n", vencedores[0].nome, max_votos);
    } else {
        printf("\nEmpate! Os vencedores sao:\n");
        fprintf(arquivo, "\nEmpate! Os vencedores são:\n");

        for (int i = 0; i < num_vencedores; i++) {
            printf("- %s com %d votos\n", vencedores[i].nome, max_votos);
            fprintf(arquivo, "- %s com %d votos\n", vencedores[i].nome, max_votos);
        }
    }

    fclose(arquivo);
}