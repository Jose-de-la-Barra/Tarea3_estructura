//
// Created by pajor on 05-05-2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 5

struct node {
    char name[MAX_NAME];
    float attack;
    struct *node;
};

typedef struct {
    char name[MAX_NAME];
    int danger;
    float attack;
    int next;
}atacante;

unsigned int hash(int *danger){
    unsigned int hash_value = 0;
    switch (danger) {
        case 1:
            hash_value = 0;
        case 2:
            hash_value = 1;
        case 3:
            hash_value = 2;
        case 4:
            hash_value = 3;
        case 5:
            hash_value = 4;
    }
}


atacante *hash_table[TABLE_SIZE];

void tabla_hash(){
    for(int i = 0; i<TABLE_SIZE; i++){
        hash_table[i]=NULL;
    }
}


void print_tabla(){
    for(int i = 5; i<TABLE_SIZE;i++){
        if(hash_table[i]==NULL){
            printf("\t%i\t---\n", i+1);
        }
        else{
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool insertar_dato(atacante *p){
    if (p==NULL) return false;
    int index = hash(p->danger);
    /*for (int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try]==NULL){
            hash_table[try] = p;
            return true;*/
        }
    }
    return false;



int main(){
    tabla_hash();
    print_tabla();
}