    // Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
    // --- Constantes Globais ---
    // Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define NUM_CONTINENTES 5
int sua_cor; // Sorteia entre 1 e 5
int missao_id;
    // --- Estrutura de Dados ---
    // Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

    // --- Protótipos das Funções ---
    // Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
void simularAtaque(struct Territorio mapa[], int totalTerritorios);
void criar_mapa_inicial(struct Territorio mapa[], int totalTerritorios);
void definir_missao(struct Territorio mapa[], int totalTerritorios);
void exibir_mapa(struct Territorio mapa[], int totalTerritorios);

    // --- Função Principal (main) ---
    // Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    srand(time(NULL));

    struct Territorio mapa[NUM_CONTINENTES];
    int totalTerritorios = NUM_CONTINENTES;
        //criar o mapa inicial
    criar_mapa_inicial(mapa, totalTerritorios);
        //exibir o mapa inicial
    exibir_mapa(mapa, totalTerritorios);
        //definir missao
    definir_missao(mapa, totalTerritorios);
        //simular ataque
    simularAtaque(mapa, totalTerritorios);

    return 0;
}
    // --- Implementação das Funções ---
    // Função para criar o mapa inicial, solicitando ao usuário os dados de cada território.
void criar_mapa_inicial(struct Territorio mapa[], int totalTerritorios) {
    
    printf("===========================================\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");
        //laço para cadastrar os territórios
    for(int i = 1; i <= NUM_CONTINENTES; i++) {
        printf("--- Cadastrando território %d ---\n", i);
        printf("Nome do território: ");
        scanf("%s", mapa[i-1].nome);
        printf("Cor do exército que domina o território: ");
        scanf("%s", mapa[i-1].cor);
        printf("Número de tropas no território: ");
        scanf("%d", &mapa[i-1].tropas);
    }
}
    // Função para exibir o mapa atual, mostrando os territórios, suas cores e número de tropas.
void exibir_mapa(struct Territorio mapa[], int totalTerritorios){

    printf("===========================================\n");
    printf("   Mapa mundo - Estado atual   \n");
    printf("===========================================\n");

    //laço para exibir os territórios cadastrados
    
    for(int i = 1; i <= totalTerritorios; i++) {
        printf(" %d. %s, exercito %s, Tropas: %d\n", i, mapa[i-1].nome, mapa[i-1].cor, mapa[i-1].tropas);
    }
}
    //Função para definir a missão do jogador
void definir_missao(struct Territorio mapa[], int totalTerritorios){
        // 1. Sorteamos a cor do jogador
    int a = rand() % totalTerritorios;
    int b;
        // 2. Sorteamos o alvo, garantindo que seja diferente do jogador
    do {
        b = rand() % totalTerritorios;
    } while (a == b);
        // 3. Atribuímos às variáveis globais (usando índices de 0 a 4)
    sua_cor = a; 
    missao_id = b;
        // 4. Exibimos buscando os nomes no mapa
    printf("--- SUA MISSÃO (EXERCITO %s) ---\n", mapa[sua_cor].cor);
    printf("Destruir o exército %s!\n", mapa[missao_id].cor);

}
// Função para simular um ataque entre dois territórios, rolando dados e atualizando tropas.
void simularAtaque(struct Territorio mapa[], int totalTerritorios) {
    int opcao1, opcao2;

    do{
        printf("--- MENU DE AÇÕES ---\n");
        printf("1. Atacar\n");
        printf("2. Verificar MISSÃO\n");
        printf("0. Sair do jogo\n");
        printf("===========================================\n");
            //implementar a lógica de ataque
        printf("Escolha sua ação: ");
        scanf("%d", &opcao1);
        switch(opcao1){
            case 1:
                int dado_atacante = rand() % 6 + 1;
                int dado_defensor = rand() % 6 + 1;

                printf("--- FASE DE ATAQUE ---\n");
                printf("Escolha o território de atacante(1 a 5, ou 0 para sair) (1-%d):\n", totalTerritorios);
                scanf("%d", &opcao1);
                printf("Escolha o território defensor(1 a 5) (1-%d): \n", totalTerritorios);
                scanf("%d", &opcao2);
                printf("===========================================\n");

                    //implementar a lógica de ataque
                printf("--- RESULTADO DA BATALHA ---\n");
                printf("O atacante do território %s rodou um dado e tirou: %d\n", mapa[opcao1-1].nome, dado_atacante);
                printf("O defensor do território %s rodou um dado e tirou: %d\n", mapa[opcao2-1].nome, dado_defensor);
                    // Criamos "apelidos" que apontam para os endereços dos territórios escolhidos
                struct Territorio *atq = &mapa[opcao1 - 1];
                struct Territorio *def = &mapa[opcao2 - 1];
                if(dado_atacante > dado_defensor){
                    printf("VITÓRIA! O defensor perdeu 1 tropa.\n");
                    def->tropas -= 1;
                        // --- LÓGICA DE CONQUISTA ---
                    if(def->tropas <= 0) {
                        printf("!!! CONQUISTA !!!\n");
                        printf("O exercito %s dominou %s!\n", atq->cor, def->nome);
                        
                            // 1. Muda a cor do dono
                        strcpy(def->cor, atq->cor); 
                        
                            // 2. Transfere tropas (ex: move 1 tropa do atacante para o novo território)
                        def->tropas = 1;
                        atq->tropas--;
                        
                        printf("O territorio %s agora pertence aos %s e tem %d tropa.\n", def->nome, def->cor, def->tropas);
                    }
                }else{
                    printf("DERROTA! O atacante perdeu 1 tropa.\n");
                    atq->tropas -= 1;
                
                }
                printf("===========================================\n");

                exibir_mapa(mapa, totalTerritorios);
                break;
            case 2:
                printf("Verificando missão...\n");
                if(mapa[missao_id-1].tropas <= 0){
                    printf("Parabéns! Você cumpriu sua missão de destruir o exército %s!\n", mapa[missao_id-1].cor);
                    opcao1 = 0; // Sair do jogo
                }else{
                    printf("Missão não cumprida ainda. Continue tentando!\n");
                }
                break;
            case 0:
                printf("Saindo do jogo. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        exibir_mapa(mapa, totalTerritorios);
        
    }while(opcao1!=0);

}


