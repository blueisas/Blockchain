#include <stdlib>

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
