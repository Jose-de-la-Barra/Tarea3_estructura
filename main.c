#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"

// definimos el tamaño de nuestro hash (son 5 las categorías de los atacantes)
#define TABLE_SIZE 5

int main(int argc, char *argv[]) {
    atacante *hash[TABLE_SIZE];  // *hash[] es equivalente a **hash
    inicializar_hash(hash);  // inicializamos hash insertando NULL en cada posición de este para que más adelante no nos dé un error

    print_table(hash);
}



void inicializar_hash(atacante **hash_table) { // Ocupamos esta función para llenar los valores de los baldes del hash con NULL para que no nos dé un error
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void insert_person(atacante **hash_table, atacante *persona, int index) {  // para insertar una persona en una posición del hash, necesitamos el hash, la persona y la posición
    hash_table[index] = persona;
}

void print_table(atacante **hash_table) {  // función que imprime la tabla hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i] ->nombre);
        }
    }
}

