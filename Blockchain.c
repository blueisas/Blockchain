#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX 50

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
