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

Blockchain* criar_blockchain(int id, int bloco_tamanho);

Bloco* criar_bloco(int id, int bloco_tamanho);

void adicionar_membro(Blockchain* bc, int id, const char* nome);

int encontrar_membro_id(Blockchain* bc, int membro_id);

void adicionar_transacao(Blockchain* bc, int remetente_id, int destinatario_id, int valor);

void imprimir_transacoes(Blockchain* bc, int membro_id);

void calcular_saldos(Blockchain* bc);

void salvar_blockchain(Blockchain* bc, const char* filename);

Blockchain* carregar_blockchain(const char* filename);

void menu(Blockchain** blockchains, int* num_blockchains);
