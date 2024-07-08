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
    int num_transacoes;
    struct bloco *anterior; // chain entre os blocos em sequência

} bloco; 

typedef struct blockchain { // struct para conexão dos blocos
    bloco *head;  // primeiro bloco
    bloco *atual; // bloco atual
    int t_max_bloco; // tamanho máximo do bloco
    int num_blocos;
} blockchain;

pessoa *definir_pessoa(const char *nome) {
    pessoa *p = (pessoa *)malloc(sizeof(pessoa)); //alocando memória
    if (p == NULL) {
        error("Erro ao alocar memória para pessoa");
        return -1;
    }
    strcpy(p->nome, nome); // função que copia o valor lido para o vetor nome
    p->conta_b = 0;// todo mundo começa com valor 0 na conta
    return p; // retorna valor
}

blockchain *definir_blockchain (int t_bloco) {

    blockchain *a = (blockchain *)malloc(sizeof(blockchain));
    blockchain *bc = (blockchain *)malloc(sizeof(blockchain));
    if (a == NULL) return -1;

    // inicialização da estrutura
    a->head = NULL;
    a->atual = NULL;
    a->tam_max_bloco = t_bloco;
    a->num_blocos = 0;
    bc->head = NULL;
    bc->atual = NULL;
    bc->tam_max_bloco = t_bloco;
    bc->num_blocos = 0;

    return bc;

}
bloco *definir_bloco (int id_bloco) {
    bloco b = (bloco *)malloc(sizeof(bloco));
    if (b == NULL) return -1;

    // inicialização da estrutura
    b->id_bloco = id_bloco;
    b->quant_transacoes = 0;
    b->num_transacoes = 0;
    b->anterior = NULL;

    return b;

}

void add_transacao (blockchain *a, pessoa *pagador, pessoa *recebedor, int dinheiro) {
void add_transacao (blockchain *bc, pessoa *pagador, pessoa *recebedor, int dinheiro) {

    // caso a blockchain esteja vazia ou o bloco atual esteja cheio (a ideia é criar um bloco novo, no geral)
    if (a->atual == NULL || a->atual->quant_transacoes >= a->tam_max_bloco) {
    if (bc->atual == NULL || bc->atual->num_transacoes >= bc->tam_max_bloco) {

        bloco *novo_bloco = definir_bloco(a->quant_blocos++); // passa o id como parâmetro
        novo_bloco->anterior = a->atual; // direciona o bloco atual (NULL ou cheio) na chain
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


int main(){
    pessoa p; // chamando struct pessoa
    int t_bloco, quantidade_membros;

    printf("seja bem vindo ao processo de transições\n");
    printf("Digite a quantidade de membros interessados em paticipar\n");
    scanf("%d", &quantidade_membros);
    printf("Digite a quantidade máxima de transações\n");
    scanf("%d", &t_bloco);


    blockchain *bc = definir_blockchain(t_bloco); // inicializa a fila blockchain

    pessoa *membros[quantidade_membros];
    for (int i = 0; i < quantidade_membros; i++) { // repetição para recolher informações de cada pessoa
        char nome[N];
        printf("Digite o nome do membro %d: ", i + 1);
        scanf("%s", nome);
        membros[i] = definir_pessoa(nome);
    }

    int opcao;
    do {                   // switch case para o usuário escolher o que ele quer
        printf("\nEscolha uma opção:\n");
        printf("1. Adicionar transação\n");
        printf("2. Exibir transações de um membro\n");
        printf("3. Calcular saldos\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char remetente_nome[N], destinatario_nome[N];
                float valor;
                printf("Digite o nome do remetente: ");
                scanf("%s", remetente_nome);
                printf("Digite o nome do destinatário: ");
                scanf("%s", destinatario_nome);
                printf("Digite o valor: ");
                scanf("%f", &valor);

                pessoa *remetente = NULL;
                pessoa *destinatario = NULL;
                for (int i = 0; i < quantidade_membros; i++) {
                    if (strcmp(membros[i]->nome, remetente_nome) == 0) {
                        remetente = membros[i];
                    }
                    if (strcmp(membros[i]->nome, destinatario_nome) == 0) {
                        destinatario = membros[i];
                    }
                }

                if (remetente && destinatario) {
                    add_transacao(bc, remetente, destinatario, valor);
                } else {
                    printf("Membros não encontrados.\n");
                }
                break;
            }
            case 2: {
                char nome[N];
                printf("Digite o nome do membro: ");
                scanf("%s", nome);
                exibir_transacoes(bc, nome);
                break;
            }
            case 3: {
                calcular_saldos(bc);
                break;
            }
            case 4: {
                printf("Saindo...\n");
                break;
            }
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 4);


   

   
}
