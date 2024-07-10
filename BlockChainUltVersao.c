#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct { //struct para cada membro
    int id; //importante ter um identificador único para cada membro da blockchain já que podem ter nomes iguais
    char nome[MAX];
} Membro;

typedef struct {
    int id;
    int remetente_id;
    int destinatario_id;
    int valor;
} Transacao;

typedef struct Bloco {
    int id;
    Transacao* transacoes;
    int transacao_count;
    struct Bloco* proximo;
} Bloco;

typedef struct {
    int id;  //identificador para sabermos qual blockchain, já que o programa deve suportar mais de uma
    Bloco* primeiro_bloco;
    Bloco* ultimo_bloco;
    int bloco_tamanho;
    Membro* membros;
    int membro_count;
    int transacao_count;
} Blockchain;

Blockchain* criar_blockchain(int id, int bloco_tamanho) { //cria a blockchain e tem como parâmetro seu id e o número máximo de transações por bloco
    Blockchain* bc = (Blockchain*)malloc(sizeof(Blockchain));
    if (bc == NULL) return NULL;

    // inicialização da estrutura
    bc->id = id;
    bc->primeiro_bloco = NULL;
    bc->ultimo_bloco = NULL;
    bc->bloco_tamanho = bloco_tamanho;
    bc->membros = NULL;
    bc->membro_count = 0;
    bc->transacao_count = 0;
    return bc;
}

Bloco* criar_bloco(int id, int bloco_tamanho) {
    Bloco* bloco = (Bloco*)malloc(sizeof(Bloco));
    if (bloco == NULL) return NULL;

    // inicialização da estrutura
    bloco->id = id;
    bloco->transacoes = (Transacao*)malloc(sizeof(Transacao) * bloco_tamanho); 
    bloco->transacao_count = 0;
    bloco->proximo = NULL;
    return bloco;
}

void adicionar_membro(Blockchain* bc, int id, const char* nome) {
    bc->membros = (Membro*)realloc(bc->membros, sizeof(Membro) * (bc->membro_count + 1)); // Realoca memória para adicionar um novo membro
    bc->membros[bc->membro_count].id = id; // Define o ID do novo membro começando de 1
    strcpy(bc->membros[bc->membro_count].nome, nome); // Copia o nome do novo membro
    bc->membro_count++; // Incrementa o contador de membros na blockchain
}

int encontrar_membro_id(Blockchain* bc, int membro_id) {
    for (int i = 0; i < bc->membro_count; i++) {
        if (bc->membros[i].id == membro_id) { 
            return membro_id; // Retorna o ID do membro se encontrado
        }
    }
    return -1; // Membro nao encontrado
}

void adicionar_transacao(Blockchain* bc, int remetente_id, int destinatario_id, int valor) {
    Bloco* bloco = bc->ultimo_bloco; // Obtém o último bloco da blockchain
    if (bloco == NULL || bloco->transacao_count >= bc->bloco_tamanho) { // Verifica se precisa criar um novo bloco
        Bloco* novo_bloco = criar_bloco((bloco == NULL) ? 1 : bloco->id + 1, bc->bloco_tamanho); // Cria um novo bloco se necessário
        bc->ultimo_bloco = novo_bloco; // Atualiza o ponteiro para o último bloco na blockchain
        if (bloco == NULL)
        {
            bc->primeiro_bloco = novo_bloco;
        }
        else
        {
            bloco->proximo = novo_bloco; // Define o proximo do bloco atual como o novo bloco criado
        }
        bloco = novo_bloco; // Define o bloco atual como o novo bloco criado
    }

    Transacao* transacao = &bloco->transacoes[bloco->transacao_count++]; // Obtém a próxima posição no array de transações do bloco
    transacao->id = bc->transacao_count + 1; // Define o ID da transação
    transacao->remetente_id = remetente_id; // Define o ID do remetente
    transacao->destinatario_id = destinatario_id; // Define o ID do destinatário
    transacao->valor = valor; // Define o valor da transação

    bc->transacao_count++;
}

void imprimir_transacoes(Blockchain* bc, int membro_id) {
    Bloco* bloco = bc->primeiro_bloco; // Começa a partir do primeiro bloco na blockchain
    int count = 0;
    char* membro_nome = "Desconhecido";

    // Encontra o nome do membro
    for (int j = 0; j < bc->membro_count; j++) {
        if (bc->membros[j].id == membro_id) {
            membro_nome = bc->membros[j].nome;
            break;
        }
    }

    while (bloco != NULL) { // Percorre todos os blocos a partir do primeiro
        for (int i = 0; i < bloco->transacao_count; i++) {
            Transacao* t = &bloco->transacoes[i];
            if (t->remetente_id == membro_id || t->destinatario_id == membro_id) { // Verifica se o membro está envolvido na transação
                char* remetente_nome = "Desconhecido";
                char* destinatario_nome = "Desconhecido";

                // Encontra o nome do remetente
                for (int j = 0; j < bc->membro_count; j++) {
                    if (bc->membros[j].id == t->remetente_id) {
                        remetente_nome = bc->membros[j].nome;
                        break;
                    }
                }

                // Encontra o nome do destinatario
                for (int j = 0; j < bc->membro_count; j++) {
                    if (bc->membros[j].id == t->destinatario_id) {
                        destinatario_nome = bc->membros[j].nome;
                        break;
                    }
                }

                printf("Transacao %d: %s (ID %d) pagou $%d a %s (ID %d) (Bloco %d)\n", t->id, remetente_nome, t->remetente_id, t->valor, destinatario_nome, t->destinatario_id, bloco->id);
                count++;
            }
        }
        bloco = bloco->proximo; // Move para o bloco anterior na blockchain
    }

    if (count == 0) {
        printf("Nenhuma transacao encontrada para %s (ID %d).\n", membro_nome, membro_id);
    } else {
        printf("Total de transacoes encontradas para %s (ID %d): %d\n", membro_nome, membro_id, count);
    }
}

void calcular_saldos(Blockchain* bc) {
    int* saldos = (int*)calloc(bc->membro_count, sizeof(int));

    Bloco* bloco = bc->primeiro_bloco; // Começa a partir do primeiro bloco na blockchain
    while (bloco != NULL) { // Percorre todos os blocos a partir do primeiro
        for (int i = 0; i < bloco->transacao_count; i++) {
            Transacao* t = &bloco->transacoes[i];
            // Ajusta o acesso ao array de saldos usando os IDs dos membros
            saldos[t->remetente_id - 1] -= t->valor; // Reduz o valor da transação do saldo do remetente
            saldos[t->destinatario_id - 1] += t->valor; // Adiciona o valor da transação ao saldo do destinatário
        }
        bloco = bloco->proximo; // Move para o proximo bloco na blockchain
    }

    typedef struct { // Struct auxiliar para armazenar os saldos com os IDs dos membros para facilitar a ordenação
        int id;
        int saldo;
    } SaldoMembro;
    
    SaldoMembro* saldos_membros = (SaldoMembro*)malloc(sizeof(SaldoMembro) * bc->membro_count);
    for (int i = 0; i < bc->membro_count; i++) {
        saldos_membros[i].id = i + 1; // Ajuste para o ID do membro começar de 1
        saldos_membros[i].saldo = saldos[i];
    }

    // Ordenar os membros com base nos saldos fazendo um Selection Sort (ordem decrescente)
    for (int i = 0; i < bc->membro_count - 1; i++) {
        for (int j = i + 1; j < bc->membro_count; j++) {
            if (saldos_membros[i].saldo < saldos_membros[j].saldo) {
                SaldoMembro temp = saldos_membros[i];
                saldos_membros[i] = saldos_membros[j];
                saldos_membros[j] = temp;
            }
        }
    }

    // Exibir os saldos ordenados
    printf("Saldos ordenados (do maior para o menor):\n");
    for (int i = 0; i < bc->membro_count; i++) {
        printf("%s (ID %d): Saldo %d\n", bc->membros[saldos_membros[i].id - 1].nome, saldos_membros[i].id, saldos_membros[i].saldo);
    }

    free(saldos);
    free(saldos_membros);
}

void salvar_blockchain(Blockchain* bc, const char* filename) { // Função para salvar a blockchain em um arquivo
    FILE* file = fopen(filename, "w"); // Abre o arquivo em modo de escrita
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Escreve no arquivo
    fprintf(file, "BC %d %d %d %d\n", bc->id, bc->bloco_tamanho, bc->membro_count, bc->transacao_count);
    for (int i = 0; i < bc->membro_count; i++) {
        fprintf(file, "MB %d %s\n", bc->membros[i].id, bc->membros[i].nome);
    }

    Bloco* bloco = bc->primeiro_bloco;
    while (bloco != NULL) {
        fprintf(file, "BL %d %d\n", bloco->id, bloco->transacao_count);
        for (int i = 0; i < bloco->transacao_count; i++) {
            Transacao* t = &bloco->transacoes[i];
            fprintf(file, "TR %d %d %d %d\n", t->id, t->remetente_id, t->destinatario_id, t->valor);
        }
        bloco = bloco->proximo;
    }

    fclose(file);
}

Blockchain* carregar_blockchain(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    int id, bloco_tamanho, membro_count, trans_count;
    fscanf(file, "BC %d %d %d %d\n", &id, &bloco_tamanho, &membro_count, &trans_count);

    Blockchain* bc = criar_blockchain(id, bloco_tamanho);
    for (int i = 0; i < membro_count; i++) {
        int membro_id;
        char nome[50];
        fscanf(file, "MB %d %s\n", &membro_id, nome);
        adicionar_membro(bc, membro_id, nome);
    }

    Bloco* bloco = NULL;
    int bloco_id, transacao_count;
    while (fscanf(file, "BL %d %d\n", &bloco_id, &transacao_count) == 2) {
        Bloco* novo_bloco = criar_bloco(bloco_id, bloco_tamanho);
        if (bloco == NULL)
        {
            bc->primeiro_bloco = novo_bloco;            
        }
        else
        {
            bloco->proximo = novo_bloco;
        }
        bc->ultimo_bloco = novo_bloco;
        novo_bloco->transacao_count = transacao_count;
        for (int i = 0; i < transacao_count; i++) {
            Transacao* t = &novo_bloco->transacoes[i];
            fscanf(file, "TR %d %d %d %d\n", &t->id, &t->remetente_id, &t->destinatario_id, &t->valor);
            bc->transacao_count++;
        }
        bloco = novo_bloco;
    }
    bc->ultimo_bloco = bloco;

    fclose(file);
    return bc;
}

void menu(Blockchain** blockchains, int* num_blockchains) {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Criar nova blockchain\n");
        printf("2. Adicionar membro a uma blockchain\n");
        printf("3. Adicionar transacao a uma blockchain\n");
        printf("4. Mostrar transacoes de um membro\n");
        printf("5. Calcular saldos\n");
        printf("6. Salvar blockchain em Arquivo\n");
        printf("7. Carregar blockchain de Arquivo\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int bloco_tamanho;
                printf("Digite o tamanho maximo do bloco: ");
                scanf("%d", &bloco_tamanho);
                Blockchain* bc = criar_blockchain(*num_blockchains + 1, bloco_tamanho);
                blockchains = (Blockchain**)realloc(blockchains, sizeof(Blockchain*) * (*num_blockchains + 1));
                blockchains[*num_blockchains] = bc;
                (*num_blockchains)++;
                printf("Blockchain criada com ID %d.\n", bc->id); // Imprime o ID da nova blockchain
                break;
            }
            case 2: {
                int blockchain_id;
                char nome[50];
                printf("Digite o ID da blockchain: ");
                scanf("%d", &blockchain_id);
                printf("Digite o nome do membro: ");
                scanf("%s", nome);
                if (blockchain_id > 0 && blockchain_id <= *num_blockchains) {
                    Blockchain* bc = blockchains[blockchain_id - 1];
                    adicionar_membro(bc, bc->membro_count + 1, nome);
                    printf("Membro adicionado com ID %d.\n", bc->membro_count); // Imprime o ID do novo membro
                } else {
                    printf("Blockchain nao encontrada.\n");
                }
                break;
            }
            case 3: {
                int blockchain_id, remetente_id, destinatario_id, valor;
                printf("Digite o ID da blockchain: ");
                scanf("%d", &blockchain_id);
                printf("Digite o ID do remetente da transacao: ");
                scanf("%d", &remetente_id);
                printf("Digite o ID do destinatario da transacao: ");
                scanf("%d", &destinatario_id);
                printf("Digite o valor da transacao: ");
                scanf("%d", &valor);

                if (blockchain_id > 0 && blockchain_id <= *num_blockchains) {
                    Blockchain* bc = blockchains[blockchain_id - 1];
                    // Verifica se ambos os IDs do remetente e destinatário são membros válidos na blockchain
                    if (encontrar_membro_id(bc, remetente_id) != -1 && encontrar_membro_id(bc, destinatario_id) != -1) {
                        adicionar_transacao(bc, remetente_id, destinatario_id, valor);
                    } else {
                        printf("Erro: remetente ou destinatario nao encontrado.\n");
                    }
                } else {
                    printf("Blockchain nao encontrada.\n");
                }
                break;
            }
            case 4: {
                int blockchain_id, membro_id;
                printf("Digite o ID da blockchain: ");
                scanf("%d", &blockchain_id);
                printf("Digite o ID do membro: ");
                scanf("%d", &membro_id);
                if (blockchain_id > 0 && blockchain_id <= *num_blockchains) {
                    Blockchain* bc = blockchains[blockchain_id - 1];
                    // Verifica se o ID do membro existe na blockchain
                    if (membro_id > 0 && membro_id <= bc->membro_count) {
                        imprimir_transacoes(bc, membro_id);
                    } else {
                        printf("ID do membro nao encontrado na blockchain.\n");
                    }
                } else {
                    printf("Blockchain nao encontrada.\n");
                }
                break;
            }
            case 5: {
                int blockchain_id;
                printf("Digite o ID da blockchain: ");
                scanf("%d", &blockchain_id);
                if (blockchain_id > 0 && blockchain_id <= *num_blockchains) {
                    Blockchain* bc = blockchains[blockchain_id - 1];
                    calcular_saldos(bc);
                } else {
                    printf("Blockchain nao encontrada.\n");
                }
                break;
            }
            case 6: {
                int blockchain_id;
                char filename[100];
                printf("Digite o ID da blockchain: ");
                scanf("%d", &blockchain_id);
                printf("Digite o nome do arquivo para salvar: ");
                scanf("%s", filename);
                if (blockchain_id > 0 && blockchain_id <= *num_blockchains) {
                    Blockchain* bc = blockchains[blockchain_id - 1];
                    salvar_blockchain(bc, filename);
                } else {
                    printf("Blockchain nao encontrada.\n");
                }
                break;
            }
            case 7: {
                char filename[100];
                printf("Digite o nome do arquivo para carregar: ");
                scanf("%s", filename);
                Blockchain* bc = carregar_blockchain(filename);
                if (bc != NULL) {
                    blockchains = (Blockchain**)realloc(blockchains, sizeof(Blockchain*) * (*num_blockchains + 1));
                    blockchains[*num_blockchains] = bc;
                    (*num_blockchains)++;
                }
                break;
            }
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 8);
}

int main() {
    Blockchain** blockchains = NULL;
    int num_blockchains = 0;

    menu(blockchains, &num_blockchains);

    for (int i = 0; i < num_blockchains; i++) {
        free(blockchains[i]->membros);
        Bloco* bloco = blockchains[i]->primeiro_bloco;
        while (bloco != NULL) {
            Bloco* proximo = bloco->proximo;
            free(bloco->transacoes);
            free(bloco);
            bloco = proximo;
        }
        free(blockchains[i]);
    }
    free(blockchains);

    return 0;
}