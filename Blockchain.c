#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#define N 100

int main() { 
    
    int id_bc, tam_bloco;

    printf("Criando as blockchains...\n\n");
    do {
        
        printf("Informe o id da blockchain (0 para terminar): ");
        scanf("%d", &id_bc);

        if (id_bc != 0) { //quando o id_bc for zero não irá criar uma blockchain
        
            printf("Informe o número de transações máximo por bloco: ");
            scanf("%d", &tam_bloco);

            blockchain* bc = criar_blockchain(id_bc, tam_bloco); //criamos a blockchain(inicialmente vazia)

            char nome_arquivo[N];
            snprintf(nome_arquivo, N, "bc%d.dat", id_bc);

            criar_arquivo(bc, nome_arquivo); //criamos o arquivo que vai salvar a blockchain
        }
    }
    while (id_bc != 0); 

    int id_transacao, id_remetente, id_destinatario;
    char nome_remetente[N], nome_destinatario[N];
    float valor;

    printf("Criando as transações...\n\n");
    do {
        
        printf("Informe o id da transação (0 para terminar): ");
        scanf("%d", &id_transacao);

        if (id_transacao != 0) { //não irá ser criada uma transação de id 0
        
            printf("Informe o id da blockchain dessa transação: ");
            scanf("%d", &id_bc);

            printf("Informe o id do membro remetente: ");
            scanf("%d", &id_remetente);

            printf("Informe o nome do membro remetente: ");
            scanf("%s", nome_remetente);

            printf("Informe o id do membro destinatário: ");
            scanf("%d", &id_destinatario);

            printf("Informe o nome do membro destinatário: ");
            scanf("%d", nome_destinatario);

            printf("Informe o valor da transação: ");
            scanf("%d", &valor);

            add_transacao (id_bc, );   
        } 
    }
    while (id_transacao != 0);

}
