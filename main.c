#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024



struct node {
    char nombre[50];
    int danger;
    float attack;
    struct node *next;
};




void hash(struct node *lista_5, struct node *lista_4, struct node *lista_3, struct node *lista_2, struct node *lista_1,void imprimir_lista()){
    printf("%i---->", 5);
    imprimir_lista(lista_5);
    printf("\n");
    printf("\n");
    printf("%i---->", 4);
    imprimir_lista(lista_4);
    printf("\n");
    printf("\n");
    printf("%i---->", 3);
    imprimir_lista(lista_3);
    printf("\n");
    printf("\n");
    printf("%i---->", 3);
    imprimir_lista(lista_3);
    printf("\n");
    printf("\n");
    printf("%i---->", 2);
    imprimir_lista(lista_2);
    printf("\n");
    printf("\n");
    printf("%i---->", 1);
    imprimir_lista(lista_1);
}

void insertar_elemento(struct node **ref_lista, char* nombre,int danger, float attack)
{
    if (*ref_lista == NULL) { // caso lista vacia
        struct node *nuevo_nodo = (struct node *)malloc(sizeof(struct node));
        strcpy(nuevo_nodo->nombre, nombre);
        nuevo_nodo->danger = danger;
        nuevo_nodo->attack = attack;
        nuevo_nodo->next = NULL;
        *ref_lista = nuevo_nodo;  // aca es donde modificamos la variable lista
    }
    else { // caso lista no vacia
        struct node *lista = *ref_lista;
        struct node *it = lista;
        while(it->next != NULL) { // importante preguntar it->next != NULL y no it != NULL
            it = it->next;
        }
        struct node *nuevo_nodo = (struct node *)malloc(sizeof(struct node));
        strcpy(nuevo_nodo->nombre,nombre);
        nuevo_nodo->danger = danger;
        nuevo_nodo->attack = attack;
        nuevo_nodo->next = NULL;
        it->next = nuevo_nodo;
    }
}



void imprimir_lista(struct node *lista)
{
    // recorrido simple de la lista
    struct node *it = lista;
    while(it != NULL) {
        printf("||%s   |    %f  ||   ", it->nombre, it->attack);
        it = it->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int i = 0;
    FILE *fp = fopen(argv[1], "r");
    char line[MAX_LINE_SIZE];
    char *token;
    struct node *lista_5= NULL;
    struct node *lista_4 = NULL;
    struct node *lista_3 = NULL;
    struct node *lista_2 = NULL;
    struct node *lista_1 = NULL;

    // Leemos linea a linea
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) // el arreglo line se rellena con los caracteres de la linea
    {
        // strtok(line, ",") entrega el substring desde el comienzo hasta la primera aparicion del delimitador "," (excluyendolo)
        // Copiamos el substring al campo palabra de la estructura

        char nombre[50];
        int danger;
        float attack;


        strcpy(nombre, strtok(line, ","));
        // Obtenemos el siguiente substring
        token = strtok(NULL, ",");
        if (strcmp(token, "\n") == 0) // caso que no hay int
            danger = -1;
        else
            danger = atoi(token); // atoi convierte un string a int
        token = strtok(NULL, ",");
        if (strcmp(token, "\n") == 0) // caso que no hay int
            attack = -1;
        else {
            attack = atof(token); // atoi convierte un string a int
        }


        //hash
        switch (danger) {
            case 1:
                insertar_elemento(&lista_1, nombre, danger, attack);
                break;
            case 2:
                insertar_elemento(&lista_2, nombre, danger, attack);
                break;
            case 3:
                insertar_elemento(&lista_3, nombre, danger, attack);
                break;
            case 4:
                insertar_elemento(&lista_4, nombre, danger, attack);
                break;
            case 5:
                insertar_elemento(&lista_5, nombre, danger, attack);
                break;
        }
        i++;
    }


    hash(lista_5, lista_4,lista_3, lista_2, lista_1, imprimir_lista);

}
