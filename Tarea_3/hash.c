//
// Created by pajor on 05-05-2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
    char name[MAX_NAME];
    int age;
}person;

unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++){
        hash_value +=name[i];
        hash_value = (hash_value * name[i] % TABLE_SIZE);
    }
}

person *hash_table[TABLE_SIZE];

void tabla_hash(){
    for(int i = 0; i<TABLE_SIZE; i++){
        hash_table[i]=NULL;
    }
}
void print_tabla(){
    for(int i = 0; i<TABLE_SIZE;i++){
        if(hash_table[i]==NULL){
            printf("\t%i\t---\n", i);
        }
        else{
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool insertar_dato(person *p){
    if (p==NULL) return false;
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try]==NULL){
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

person *busqueda(char *name){
    int index = hash(name);
    for (int i = 0;  i<TABLE_SIZE ; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] != NULL &&
           strncmp(hash_table[try]->name, name, TABLE_SIZE)==0){
            return hash_table[try];
        }
    }
    return NULL;
}

person *borrar(char *name){
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++){
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[index] != NULL &&
            strncmp(hash_table[try]->name, name, TABLE_SIZE)==0){
            person *tmp = hash_table[try];
            hash_table[try] = NULL;
            return tmp;
        }
    }
    return NULL;
}


int main(){
    //printf("PABLO => %u\n", hash("PABLO"));
    tabla_hash();
    person pablo = {.name="Pablo", .age=22};
    person andres = {.name="Andres", .age=30};
    person margarita = {.name="Margarita", .age=66};
    person valentina = {.name="Valentina", .age=40};
    person francisca = {.name = "Francisa", .age=21};

    insertar_dato(&pablo);
    insertar_dato(&andres);
    insertar_dato(&margarita);
    insertar_dato(&valentina);
    insertar_dato(&francisca);
    print_tabla(hash_table);

    person *tmp = busqueda("Pablo");

    if (tmp == NULL){
        printf("NOT FOUND");
    }
    else{
        printf("Found %s.\n", tmp->name);
    }
    borrar("Pablo");
    tmp = busqueda("Pablo");
    if (tmp == NULL){
        printf("NOT FOUND\n");
    }
    else{
        printf("Found %s.\n", tmp->name);
    }
    print_tabla(hash_table);
}