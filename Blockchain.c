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
        Bloco* bloco = blockchains[i]->ultimo_bloco;
        while (bloco != NULL) {
            Bloco* anterior = bloco->anterior;
            free(bloco->transacoes);
            free(bloco);
            bloco = anterior;
        }
        free(blockchains[i]);
    }
    free(blockchains);

    return 0;
}
