#include <stdlib>
#define N 100

typedef struct { // struct para cada pessoa

    int id; //importante ter um identificador único para cada membro da blockchain já que podem ter nomes iguais
    char nome[N];
    float saldo; 

} pessoa;

typedef struct { // struct para as transações

    int id; // identificador
    pessoa remetente;
    pessoa destinatario;
    float valor;

} transacao;

typedef struct bloco { // struct para os blocos

    int id;
    transacao* transacoes; 
    int num_transacoes;
    struct bloco* proximo; // chain entre os blocos em sequência

} bloco;

typedef struct { // struct para conexão dos blocos

    int id; //identificador para sabermos de qual blockchain a transacao informada pertence, já que o programa deve suportar mais de uma
    bloco* head;  // primeiro bloco
    bloco* atual; // bloco atual
    int t_max_bloco; // tamanho máximo do bloco (número de transações por bloco)
    int num_blocos;  // quantidade de blocos

} blockchain;


//---///////////////////////////////////////////////////////////////////////////////////////////////////---

blockchain *criar_blockchain (int id, int t_bloco);
void criar_arquivo(Blockchain* bc, const char* nome_arquivo);
bloco *criar_bloco (int id_bloco, int t_bloco);
void add_transacao (blockchain *bc, pessoa *pagador, pessoa *recebedor, float dinheiro, const char* nome_arquivo);

//---------------------------------------------------------------------------------------------------------

blockchain *criar_blockchain (int id, int t_bloco) { //cria a blockchain e tem como parâmetro seu id e o número máximo de transações por bloco

    blockchain *bc = (blockchain *)malloc(sizeof(blockchain));
    if (bc == NULL) return NULL; //nao pode retornar -1 pq retorna blockchain*

    // inicialização da estrutura
    bc->id = id;
    bc->head = NULL; //blockchain inicialmente vazia
    bc->atual = NULL;
    bc->t_max_bloco = t_bloco;
    bc->num_blocos = 0;

    return bc;

}

void criar_arquivo(Blockchain* bc, const char* nome_arquivo) { //criação do arquivo para salvar a blockchain
    
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
        
    }
    
    fwrite(&bc->t_max_bloco, sizeof(int), 1, arquivo);
    fclose(arquivo);
    
}

bloco *criar_bloco (int id_bloco, int t_bloco) {
    
    bloco* b = (bloco *)malloc(sizeof(bloco)); 
    if (b == NULL) return NULL;

    // inicialização da estrutura
    b->id = id_bloco;
    b->num_transacoes = 0;
    b->transacoes = (transacao*)malloc(sizeof(transacao) * t_bloco);
    b->proximo = NULL;
    
    return b;
}


//---///////////////////////////////////////////////////////////////////////////////////////////////////---


void add_transacao (blockchain *bc, pessoa *pagador, pessoa *recebedor, float dinheiro, const char* nome_arquivo) {

    // caso a blockchain esteja vazia ou o bloco atual esteja cheio (a ideia é criar um bloco novo, no geral)
    if (bc->atual == NULL || bc->atual->num_transacoes >= bc->tam_max_bloco) {

        bloco *novo_bloco = criar_bloco(bc->num_blocos++); // passa o id como parâmetro
        bc->atual = novo_bloco; // o atual bloco na blockchain agora é o novo bloco

        if (bc->head == NULL) bc->head = novo_bloco; // se o primeiro bloco não existir na blockchain, atribuir o novo
        
    }

    // atualização da nova transação
    transacao nova_transacao;
    nova_transacao.id = bc->atual->num_transacoes; // adicionando o id
    nova_transacao.remetente = *remetente; // inserindo os nomes dos usuários da transação
    nova_transacao.destinatario = *destinatario; // ''
    nova_transacao.valor = dinheiro; // gravando o valor transferido

    // atualização das contas bancárias (saldo)
    remetente->saldo -= dinheiro;
    destinatario->saldo += dinheiro;

    // atualização da transação ao bloco atual
    bc->atual->transacoes[bc->atual->num_transacoes++] = nova_transacao; // insere no próximo índice do vetor de transações

    FILE* arquivo = fopen(nome_arquivo, "ab");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    fwrite(&nova_transacao, sizeof(transacao), 1, arquivo); //adicionamos a nova transação ao arquivo da blockchain em que ela ocorre
    fclose(arquivo);
    
}
