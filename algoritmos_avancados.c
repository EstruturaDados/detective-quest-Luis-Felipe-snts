#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

// Estrutura de dados representando uma sala da mansão
// Renomeei alguns campos para torná-los mais intuitivos

typedef struct Sala {
    char nomeSala[50];              // Nome da sala
    struct Sala *caminhoEsquerda;   // Ponteiro para a sala à esquerda
    struct Sala *caminhoDireita;    // Ponteiro para a sala à direita
} Sala;

// Protótipos das funções
Sala* criarSala(const char* nome);
Sala* montarMapaMansao();
void limparTela();
void pausarExecucao();
void mostrarTitulo();
void mostrarDespedida();
void mostrarBoasVindas();
void explorarSalas(Sala* salaAtual);
void processarNavegacao(Sala** salaAtual, char opcao);
void mostrarCaminhosDisponiveis(Sala* salaAtual);
void verificarSalaFinal(Sala* salaAtual);
void liberarMapa(Sala* raiz);

// Função para criar uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria para sala.\n");
        exit(1);
    }

    strcpy(novaSala->nomeSala, nome);
    novaSala->caminhoEsquerda = NULL;
    novaSala->caminhoDireita = NULL;

    return novaSala;
}

// Monta toda a estrutura de salas da mansão
Sala* montarMapaMansao() {
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* quartoHospedes = criarSala("Quarto de Hospedes");
    Sala* jardim = criarSala("Jardim");
    Sala* salaJantar = criarSala("Sala de Jantar");
    Sala* escritorio = criarSala("Escritorio Secreto");
    Sala* porao = criarSala("Porao");
    Sala* terraco = criarSala("Terraco");
    Sala* quartoPrincipal = criarSala("Quarto Principal");
    Sala* banheiro = criarSala("Banheiro");

    // Ligações da árvore de salas
    hallEntrada->caminhoEsquerda = salaEstar;
    hallEntrada->caminhoDireita = cozinha;

    salaEstar->caminhoEsquerda = biblioteca;
    salaEstar->caminhoDireita = quartoHospedes;

    cozinha->caminhoEsquerda = jardim;
    cozinha->caminhoDireita = salaJantar;

    biblioteca->caminhoEsquerda = escritorio;
    biblioteca->caminhoDireita = porao;

    quartoHospedes->caminhoEsquerda = terraco;
    quartoHospedes->caminhoDireita = quartoPrincipal;

    jardim->caminhoDireita = banheiro;

    return hallEntrada;
}

void limparTela() {
    CLEAR_SCREEN();
}

void pausarExecucao() {
    printf("Pressione Enter para continuar...");
    getchar();
    getchar();
}

void mostrarTitulo() {
    printf("=== DETECTIVE QUEST ===\n\n");
}

void mostrarBoasVindas() {
    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansao e descubra pistas escondidas.\n");
    printf("Pressione Enter para comecar...");
}

void mostrarDespedida() {
    limparTela();
    printf("Obrigado por jogar Detective Quest!\n\n");
}

// Função principal de exploração
void explorarSalas(Sala* salaAtual) {
    char opcao;

    while (salaAtual != NULL) {
        limparTela();
        mostrarTitulo();

        printf("Voce esta na: %s\n\n", salaAtual->nomeSala);

        verificarSalaFinal(salaAtual);
        if (salaAtual->caminhoEsquerda == NULL && salaAtual->caminhoDireita == NULL) {
            break;
        }

        mostrarCaminhosDisponiveis(salaAtual);
        printf("Para onde deseja ir? ");
        scanf(" %c", &opcao);

        processarNavegacao(&salaAtual, opcao);
    }
}

// Exibe opções válidas de caminhos
void mostrarCaminhosDisponiveis(Sala* salaAtual) {
    printf("Caminhos disponiveis:\n");

    if (salaAtual->caminhoEsquerda != NULL)
        printf("[e] Esquerda -> %s\n", salaAtual->caminhoEsquerda->nomeSala);

    if (salaAtual->caminhoDireita != NULL)
        printf("[d] Direita  -> %s\n", salaAtual->caminhoDireita->nomeSala);

    printf("[s] Sair do jogo\n\n");
}

// Identifica salas finais
void verificarSalaFinal(Sala* salaAtual) {
    if (salaAtual->caminhoEsquerda == NULL && salaAtual->caminhoDireita == NULL) {
        printf(">>> Esta e uma sala final!\n");
        printf(">>> Nao ha mais caminhos para explorar.\n\n");
        pausarExecucao();
    }
}

// Processa movimento do jogador
void processarNavegacao(Sala** salaAtual, char opcao) {
    switch (opcao) {
        case 'e':
        case 'E':
            if ((*salaAtual)->caminhoEsquerda != NULL)
                *salaAtual = (*salaAtual)->caminhoEsquerda;
            else {
                printf("\n>>> Nao ha caminho a esquerda!\n");
                pausarExecucao();
            }
            break;

        case 'd':
        case 'D':
            if ((*salaAtual)->caminhoDireita != NULL)
                *salaAtual = (*salaAtual)->caminhoDireita;
            else {
                printf("\n>>> Nao ha caminho a direita!\n");
                pausarExecucao();
            }
            break;

        case 's':
        case 'S':
            printf("\n>>> Saindo do jogo...\n");
            *salaAtual = NULL;
            break;

        default:
            printf("\n>>> Opcao invalida!\n");
            pausarExecucao();
            break;
    }
}

// Libera memória da árvore de salas
void liberarMapa(Sala* raiz) {
    if (raiz == NULL)
        return;

    liberarMapa(raiz->caminhoEsquerda);
    liberarMapa(raiz->caminhoDireita);

    free(raiz);
}

int main() {
    Sala* inicioMapa = montarMapaMansao();  // Renomeado para clareza

    mostrarBoasVindas();
    getchar();

    explorarSalas(inicioMapa);

    mostrarDespedida();

    liberarMapa(inicioMapa);

    return 0;
}