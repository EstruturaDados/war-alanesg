// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h> // permite usar printf, scanf, fgets
#include <stdlib.h> // permite usar malloc/ calloc/ free
#include <string.h> //permite usar funções de string
#include <time.h>// permite gerar números aleatórios reais


// definição da estrutura(com typedef struct) chamada TERRITORIO---
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//Aloca dinamicamente 'qtd' territorios e retorna o ponteiro

Territorio* alocarMapa(int qtd) {
    Territorio *mapa = calloc(qtd, sizeof(Territorio));
    if (!mapa) {
        printf("ERRO: falha na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    return mapa;
}

//cadastra 'qtd' territorios em mapa (modifica através do ponteiro)
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    int c;
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i);
        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Quantidade de Tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 0) {
            printf("Valor invalido. Digite um inteiro nao-negativo: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
    }
}


/* Exibe o mapa (estado atual dos territorios). Usa const pois nao modifica. */
void exibirMapa(const Territorio *mapa, int qtd) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}


//funcção para ataque com dois ponteiros: (atacante e defensor)
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n--- ATAQUE: %s (%s) -> %s (%s) ---\n",
    atacante ->nome, atacante->cor, defensor->nome, defensor->cor); // a seta acessa os campos de um ponteiro
    

    //condição IF para verificar se há tropas suficiantes
    if(atacante->tropas <= 1) {
        printf("O atacante nao tem tropas suficientes para atacar!\n");
        return; // sai da função
    }

    //declarando as variaveis do atacante e defensor

    int dadoA = rand() % 6 + 1; //atacante
    int dadoD = rand() % 6 + 1; //defensor
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    //Exibição e chamada
    printf("Dado atacante: %d\n", dadoA);
    printf("Dado defensor: %d\n", dadoD);


    //condição para verificar se quem atacou venceu e o territorio conquistado
    if(dadoA > dadoD) {
        printf("O atacante venceu o combate!\n");

        //transfere cor
         strcpy(defensor->cor, atacante->cor);
       
        //tranfere metade das tropas do atacante para o defensor

        int transferencia = atacante ->tropas / 2;
        if(transferencia <1) transferencia =1;

        defensor ->tropas += transferencia;
        atacante -> tropas -= transferencia;

          printf("Conquista: %d tropas transferidas. Novo dono: %s\n",
               transferencia, defensor->cor);
    }else {
        printf("O defensor resistiu ao ataque! Atacante perde 1 tropa\n");
        atacante->tropas = (atacante->tropas > 0) ? atacante->tropas - 1 : 0;
    }
 }

 //libera a memoriado mapa
 void liberarMemoria(Territorio *mapa) {
    free(mapa);
 }


 //função para ler o índice do jogador:
 int lerIndice(const char *msg, int qtd) {
    int idx, c;
    while(1) {
        printf("%s", msg);
        if (scanf("%d", &idx) !=1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        return idx;
    }
 }
//------------------------------------------------

//Função principal MAIN
int main(void) {
    srand((unsigned)time(NULL)); 

    int qtd;
    printf("Bem vindo(a!) quantos territorios deseja cadastrar?  ");
    while(scanf("%d", &qtd) != 1 || qtd <= 0){
        printf("Valor invalido. Digite um inteiro positivo:  ");
        int c; while ((c = getchar()) != '\n' && c != EOF);
    }
    int c; while ((c = getchar()) != '\n' && c != EOF); // limpa o buffer
     

    Territorio *mapa = alocarMapa(qtd);

    cadastrarTerritorios(mapa, qtd);

    exibirMapa(mapa, qtd);


    //Escolhendo atacante e defensor:
     int a = lerIndice("\nEscolha o indice do territorio ATACANTE: ", qtd);
    int d = lerIndice("Escolha o indice do territorio DEFENSOR: ", qtd);

   
    if (a == d) {
        printf("Nao eh possivel atacar o mesmo territorio. Abortando ataque.\n");
    } else if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
        printf("Nao eh possivel atacar um territorio da mesma cor (%s). Abortando ataque.\n", mapa[a].cor);
    } else {
        atacar(&mapa[a], &mapa[d]);
        exibirMapa(mapa, qtd); /* exibir pos-ataque */
    }

    liberarMemoria(mapa);
    return 0;
}



// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
