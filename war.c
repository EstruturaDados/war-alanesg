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

//Exibe o mapa (estado atual dos territorios). Usa const pois nao modifica. */
    void exibirMapa(const Territorio *mapa, int qtd) {
        printf("\n--- MAPA ATUAL ---\n");
        for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | cor: %s | Tropas: %d\n",
         i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

//função para ataque com dois ponteiros: (atacante e defensor)
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

 // Missões estratégicas
    #define TOTAL_MISSOES 3 
    char *templatesMissao[TOTAL_MISSOES] = {
        "Conquistar %d territorios",
        "Eliminar todas as tropas da cor %s",
        "Possuir pelo menos %d tropas no total"
    };

// sorteia uma missão e aloca dinamicamente a string destino
//destinoPtr é um ponteiro para char* onde será guardado o endereço alocado
    void atribuirMissao(char **destinoPtr, char *missoes[], int totalMissoes,
    const char *corJogador, const char *corOponente, int qtdTerritorios) {
        int idx = rand() % totalMissoes;
        char buffer[120];

        if(idx == 0) {
            int n = (qtdTerritorios >= 3) ? 3 : qtdTerritorios;
            sprintf(buffer, missoes[idx], n);
        } else if (idx == 1) {
            sprintf(buffer, missoes[idx], corOponente);
        } else if (idx == 2) {
            int m = (qtdTerritorios * 2 > 10) ? qtdTerritorios * 2 : 10;
            sprintf(buffer, missoes[idx], m);
        } else {
            strcpy(buffer, "Missao desconhecida");
        }


        //aloca dinamicamente a string da missão
        *destinoPtr = malloc(strlen(buffer) + 1);
        if (!*destinoPtr) {
            printf("ERRO: memoria insuficiente para missao.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(*destinoPtr, buffer);
    }

    //Exibe a missão (parametro de passagem por valor)
    void exibirMissao(const char *missao) {
        printf("\n--- MISSÃO SORTEADA ---\n%s\n", missao);
    }


    //verifica se a missão foi cumprida.
    int verificarMissao(const char *missao, Territorio *mapa, int tamanho, const char *corJogador) {
       // 01-Conquistar N territorios
        if(strstr(missao, "Conquistar") != NULL) {
            int n;
            if (sscanf(missao, "Conquistar %d territorios", &n) == 1) {
                int cont = 0;
                for (int i = 0; i < tamanho; i++) if(strcmp(mapa[i].cor, corJogador) ==0) cont++;
                return (cont >= n) ? 1 : 0;
            }
        }

        //02- Eliminar todas as tropas da cor x -> PEGAR A COR NO FINAL DA STRING
        if(strstr(missao, "Eliminar todas as tropas da cor") != NULL) {
            char corAlvo[20];
            if(sscanf(missao, "Eliminar todas as tropas da cor %s", corAlvo) == 1) {
                for (int i = 0; i < tamanho; i++) {
                    if (strcmp(mapa[i].cor, corAlvo) == 0 && mapa[i].tropas > 0) {
                        return 0;
                    }
                }
                return 1; // nenhuma tropa da cor alvo
            }
        }

        //03- possuir pelo menos M tropas no total
        if (strstr(missao, "Possuir pelo menos") != NULL) {
            int m;
            if(sscanf(missao, "Possuir pelo menos %d tropas no total", &m) == 1) {
            int soma = 0;
            for (int i =0; i < tamanho; i++) if (strcmp(mapa[i].cor, corJogador) == 0) soma += mapa[i].tropas;
            return (soma >= m) ? 1 : 0;
            }
        }

        return 0; // se a missao não for reconhecida, não foi cumprida;
    }


 //libera a memoriado alocada dinamicamente
    void liberarMemoria(Territorio *mapa, char *missao1, char *missao2) {
        if (mapa) free (mapa);
        if (missao1) free(missao1);
        if (missao2) free(missao2);
    }


 //função para ler o índice do jogador:
 int lerIndice(const char *msg) {
    int idx, c;
    while(1) {
        printf("%s", msg);
        if (scanf("%d", &idx) !=1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        return idx;
    }
 }
//------------------------------------------------

//Função principal MAIN
int main(void) {
    srand((unsigned)time(NULL)); 

    int qtd;
    printf("Bem vindo(a!) quantos territorios deseja cadastrar?  ");
    while(scanf("%d", &qtd) != 1 || qtd <= 0) {
        printf("Valor invalido. Digite um inteiro positivo:  ");
        int c; while ((c = getchar()) != '\n' && c != EOF);
    }
    int c; while ((c = getchar()) != '\n' && c != EOF); // limpa o buffer
     
//Pede as cores dos dois jogadores
    char corJogador1[10], corJogador2[10];
    printf("Jogador 1 - informe a cor (ex: vermelho): ");
    fgets(corJogador1, sizeof(corJogador1), stdin);
    corJogador1[strcspn(corJogador1, "\n")] = 0;

    printf("Jogador 2 - informe a cor (ex: azul): ");
    fgets(corJogador2, sizeof(corJogador2), stdin);
    corJogador2[strcspn(corJogador2, "\n")] = 0;

//Aloca e cadastra o mapa
    Territorio *mapa = alocarMapa(qtd);
    cadastrarTerritorios(mapa, qtd);

// Atribui e exibe missões 
    char *missao1 = NULL;
    char *missao2 = NULL;

    atribuirMissao(&missao1, templatesMissao, TOTAL_MISSOES, corJogador1, corJogador2, qtd);
    atribuirMissao(&missao2, templatesMissao, TOTAL_MISSOES, corJogador2, corJogador1, qtd);

    printf("\nMiSSÕES SORTEADAS:\n");
    printf("Jogador 1 (%s): ", corJogador1); exibirMissao(missao1);
    printf("Jogador 2 (%s): ", corJogador2); exibirMissao(missao2);

//Escolhendo atacante e defensor:
    int a = lerIndice("\nEscolha o indice do territorio ATACANTE: ");
    int d = lerIndice("Escolha o indice do territorio DEFENSOR: ");

//validando índices
    if (a < 0 || a >= qtd || d < 0 || d >= qtd) {
        printf("Índice invalido. Abortando ataque.\n");
    } else if (a == d) {
        printf("Nao é possivel atacar o mesmo territorio. Abortando ataque.\n", mapa[a].cor);
    } else {
        atacar(&mapa[a], &mapa[d]);
        exibirMapa(mapa, qtd); /* exibir pos-ataque */
    }

//Verifica missões de ambos os jogadores depois do ataque
    int venceu1 = verificarMissao(missao1, mapa, qtd, corJogador1);
    int venceu2 = verificarMissao(missao2, mapa, qtd, corJogador2);

    if(venceu1 && !venceu2) {
        printf("\n--- JOGADOR 1 (%s) cumpriu sua missao e VENCEU!\n", corJogador1 );  
    } else if (venceu2 && !venceu1) {
        printf("\n --- Jogador 2 (%s) cumpriu sua missão e VENCEU!\n", corJogador2);
    } else if (venceu1 && venceu2){
        printf("\nAmbos venceram. Empate.\n");
    } else {
        printf("\nNinguém cumpriu a missão. Iniciar outra rodada.");
    }

    liberarMemoria(mapa, missao1, missao2);
    return 0;
}

