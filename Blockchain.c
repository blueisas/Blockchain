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
    int quant_transacoes;
    struct bloco *anterior; // chain entre os blocos em sequência

} bloco;

typedef struct blockchain { // struct para conexão dos blocos

    bloco *head;  // primeiro bloco
    bloco *atual; // bloco atual
    int t_max_bloco; // tamanho máximo do bloco
    int num_blocos;

} blockchain;

blockcahin *definir_blockchain (int t_bloco) {

    blockchain *a = (blockchain *)mallo(sizeof(blockchain));
    if (a == NULL) return -1;

    // inicialização da estrutura
    a->head = NULL;
    a->atual = NULL;
    a->tam_max_bloco = t_bloco;
    a->num_blocos = 0;

    return a;

}

bloco *definir_bloco (int id_bloco) {

    bloco b = (bloco *)malloc(sizeof(bloco));
    if (b == NULL) return -1;

    // inicialização da estrutura
    b->id_bloco = id_bloco;
    b->quant_transacoes = 0;
    b->anterior = NULL;

    return b;

}

void add_transacao (blockchain *a, pessoa *pagador, pessoa *recebedor, int dinheiro) {

    // caso a blockchain esteja vazia ou o bloco atual esteja cheio (a ideia é criar um bloco novo, no geral)
    if (a->atual == NULL || a->atual->quant_transacoes >= a->tam_max_bloco) {

        bloco *novo_bloco = definir_bloco(a->quant_blocos++); // passa o id como parâmetro
        novo_bloco->anterior = a->atual; // direciona o bloco atual (NULL ou cheio) na chain

    }

}


