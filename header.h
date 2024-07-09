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

//---///////////////////////////////////////////////////////////////////////////////////////////////////---

void add_transacao (blockchain *bc, pessoa *pagador, pessoa *recebedor, float dinheiro, const char* nome_arquivo);
