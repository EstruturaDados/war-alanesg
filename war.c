// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definição da estrutura(com typedef struct) chamada TERRITORIO---
typedef struct {
    char nome[30];
    char corExercito[10];
    int tropas;
} Territorio;

//Função principal MAIN
int main() {
    Territorio territorios[5]; // declara um array de 5 elementos

    //MENSAGEM INICIAL
    printf("Bem vindo(a!) Cadastre seus Territorios para prosseguir >>\n");

    //Para cadastrar os territórios:
    for(int i = 0; i < 5; i++) { // loop for
        printf("Cadastro do Territorio %d\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin); //sizeof é usado para passar o tam. máx. da string
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; //strcspn remove o caractere de nova linha do final da string

        printf("Cor do Exercito: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin); // o fgets lê uma linha de texto e armazena na variável
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = 0;

        printf("Quantidade de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // limpa o buffer do teclado
        printf("\n");
    };

    //Para Exibir os dados (Nome, cor do exercito e quantidade de tropas)
    printf("Territorios Cadastrados:\n");
    for(int i = 0; i < 5; i++) {
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Quantidade de tropas: %d\n\n", territorios[i].tropas);
    };

    return 0;
}


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
