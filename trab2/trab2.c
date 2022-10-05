/* Aluno: Lucas Vilar Carneiro DRE 119108874 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

typedef struct tno {
    int chave;
    struct tno *prox;
} tno;

void init(struct tno *no) {
    no->chave = -1;
    no->prox = NULL;
}

int insere(struct tno *no, int x) {
    if (no->chave == -1) {
        no->chave = x;
        return 1;
    }
    while (no->prox != NULL) {
        no = no->prox;
    }
    if (no->prox == NULL) {
        tno* novo = malloc(sizeof(tno *));
        no->prox = novo;
        no = no->prox;
        no->chave = x;
        no->prox = NULL;
        return 1;
    }
    else {
        return 0;
    }
}

struct tno *remover(struct tno *no, int x) {
    if (no->chave == x) {
        if (no->prox == NULL) {
            no->chave = -1;
            return no;
        } else {
            // printf("aquidqw\n");
            tno* antigo = no;
            no = no->prox;
            free(antigo);
            return no;
        }
    }
    while (no->prox != NULL) {
        tno* antigo = no;
        no = no->prox;
        if (no->chave == x) {
            // printf("TA PRINTADO AQIQ\n");
            if (no->prox == NULL) {
                antigo->prox = NULL;
                return antigo;
            } else {
                tno* antigo = no;
                no = no->prox;
                free(antigo);
                return no;
            }
        }
    }
    return NULL;
}

int getChaves(struct tno *no, int *chaves) {
    if (no->chave < 0) {
        return 0;
    }
    int tam = 1;
    while (no->prox != NULL) {
        chaves[tam-1] = no->chave;
        no = no->prox;
        tam++;
    }
    chaves[tam-1] = no->chave;
    return tam;
}

int tamanho(struct tno *no) {
    if (no->chave < 0) {
        return 0;
    }
    int tam = 1;
    while (no->prox != NULL) {
        no = no->prox;
        tam++;
    }
    return tam;
}

int main(int argc, char **argv) {
    int qt;
    scanf("%d", &qt);
    tno vsai[qt];
    tno vent[qt];
    // Inicializa as listas encadeadas de entrada
    for (int i = 0; i < qt; i++) {
        init(vsai+i);
        init(vent+i);
    }
    // Insere os valores nas listas encadeadas
    int ent, sai;
    while(scanf("%d %d", &sai, &ent) != EOF) { 
        insere(vsai+sai-1, ent-1);
        insere(vent+ent-1, sai-1);
    }

    // Vetor auxiliar para quantidade de entradas de cada index
    int tamanhos[qt];
    for (int i = 0; i < qt; i++) {
        tamanhos[i] = tamanho(vent+i);
    }
    for (int i = 0; i < qt; i++) {
        int index;
        for (int i = 0; i < qt; i++) {
            if (tamanhos[i] == 0) {
                tamanhos[i] = -1;
                printf("%d ", i+1); // Printa os vertices na ordem correta
                index = i;
                break;
            }
        }
        int *chaves = malloc(tamanho(vsai+index)*sizeof(int)); // Vetor auxiliar para guardar as chaves da lista encadeada que precisamos
        int tam = getChaves(vsai+index, chaves); // Preenche vetor auxiliar com chaves da lista encadeada
        int chave;
        for (int i = 0; i < tam; i++) {
            chave = chaves[i];
            vent[chave] = *remover(vent+chave, index); // Remove as entradas de cada index conforme o necessario
            tamanhos[chave]--;  
        }
    }
    return 0;
}