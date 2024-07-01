#include <studio.h>
#include <string.h>
#include <stbool.h>
#include <stdlib.h>
#define N 100

typedef struct pessoa { // struct para cada pessoa

    char nome[N];
    float conta_b; // conta bancária de cada pessoa (pra calcular o saldo etc)

} pessoa;

typedef struct transacao { // struct para as transações

    int id_transacao; // identificador
    pessoa remetente;
    pessoa destinatario;
    float valor_pago;

} transacao;

typedef struct bloco { // struct para os blocos

    int id_bloco;
    transacao transacoes[100]; // vetor de transações (bizarro e genial)
    int num_transacoes;
    struct bloco *anterior; // chain entre os blocos em sequência

} bloco;

typedef struct blockchain { // struct para conexão dos blocos

    bloco *head;  // primeiro bloco
    bloco *atual; // bloco atual
    int t_max_bloco; // tamanho máximo do bloco
    int num_blocos;

} blockchain;

blockcahin *definir_blockchain (int t_bloco) {

    blockchain *bc = (blockchain *)mallo(sizeof(blockchain));
    if (a == NULL) return -1;

    // inicialização da estrutura
    bc->head = NULL;
    bc->atual = NULL;
    bc->tam_max_bloco = t_bloco;
    bc->num_blocos = 0;

    return a;

}

bloco *definir_bloco (int id_bloco) {

    bloco b = (bloco *)malloc(sizeof(bloco));
    if (b == NULL) return -1;

    // inicialização da estrutura
    b->id_bloco = id_bloco;
    b->num_transacoes = 0;
    b->anterior = NULL;

    return b;

}

void add_transacao (blockchain *bc, pessoa *pagador, pessoa *recebedor, int dinheiro) {

    // caso a blockchain esteja vazia ou o bloco atual esteja cheio (a ideia é criar um bloco novo, no geral)
    if (bc->atual == NULL || bc->atual->num_transacoes >= bc->tam_max_bloco) {

        bloco *novo_bloco = definir_bloco(bc->num_blocos++); // passa o id como parâmetro
        novo_bloco->anterior = bc->atual; // direciona o bloco atual (NULL ou cheio) na chain, atrás do novo_bloco
        bc->atual = novo_bloco; // o atual bloco na blockchain agora é o novo bloco

        if (bc->head == NULL) bc->head = novo_bloco; // se o primeiro bloco não existir na blockchain, atribuir o novo

    }

    // atualização da nova transação
    transacao nova_transacao;
    nova_transacao.id_transacao = bc->atual->num_transacoes; // adicionando o id
    nova_transacao.remetente = *remetente; // inserindo os nomes dos usuários da transação
    nova_transacao.destinatario = *destinatario; // ''
    nova_transacao.valor_pago = dinheiro; // gravando o valor transferido

    // atualização das contas bancárias (saldo)
    remetente->conta_b -= dinheiro;
    destinatario->conta_b += dinheiro;

    // atualização da transação ao bloco atual
    bc->atual->transacoes[bc->atual->num_transacoes++] = nova_transacao; // insere no próximo índice do vetor de transações

}


