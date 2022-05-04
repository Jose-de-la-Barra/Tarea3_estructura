#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "Personas.h"

#define MAXPERSONAS 200

const char* PERSON_FORMAT_OUT = "%s,%ld,%Lf,%ld\n";

void sort_words(Persona* personas, int count, char *);
void category(Persona* personas, int cont, char *);
void sortNewCategory(Persona* personas, int cont, char *, FILE *, char *);

int main(int argc, char *argv[]) {
    FILE* fpin;
    fpin = fopen(argv[1], "r");
    if (fpin == NULL) return 1;

    char row[MAXPERSONAS];
    char *token;
    int cont = 0;

    // para sacar la primera línea
    fgets(row, MAXPERSONAS, fpin);
    Persona  *personas = (Persona *) malloc(sizeof(Persona));


    while (feof(fpin) != true) {
        fgets(row, MAXPERSONAS, fpin);
        Persona  *unaPersona = (Persona *) malloc(sizeof(Persona));

        // Para conseguir el nombre
        token = strtok(row, ",");
        strcpy(unaPersona -> name, token);

        // Para conseguir la categoría de peligrosidad
        token = strtok(NULL, ",");
        unaPersona -> dangerCategory = strtol(token, (char **) NULL, 0);

        // Para conseguir la probabilidad de ataque
        token = strtok(NULL, ",");
        token = strtok(token, "\npo");
        if (token != NULL) {
            unaPersona -> attackProb = strtold(token, (char **) NULL);
        }
        else unaPersona -> attackProb = -1;  // asignamos un -1 para la gente que no tiene probabilidad de ataque para diferenciar

        unaPersona -> category = 0;  // agregamos una columna de ceros para un posterior ordenamiento

        personas[cont] = *unaPersona;
        cont++;
    }

    category(personas, cont, argv[3]);
    sortNewCategory(personas, cont, argv[2], fpin, argv[3]);

    fclose(fpin);
    return 0;
}

void category(Persona *personas, int cont, char* arch_out) {
    FILE* fpout;
    fpout = fopen(arch_out, "w+");
    if (fpout == NULL) perror("Opening file");

    long int danger_category;
    long double attack_prob;

    for (int i = 0; i < cont; i++) {
        danger_category = personas[i].dangerCategory;
        attack_prob = personas[i].attackProb;
        if (danger_category == 5 && attack_prob == (long double) -1) {
            personas[i].category = 11;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 5 && attack_prob != (long double) -1) {
            personas[i].category = 10;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 4 && attack_prob == (long double) -1) {
            personas[i].category = 9;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 4 && attack_prob != (long double) -1) {
            personas[i].category = 8;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 3 && attack_prob >= (long double) 0.5){
            personas[i].category = 7;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 3 && attack_prob == (long double) -1) {
            personas[i].category = 6;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 3 && attack_prob <= (long double) 0.5 && attack_prob > (long double) 0){
            personas[i].category = 5;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 2 && attack_prob != (long double) -1) {
            personas[i].category = 4;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 2 && attack_prob == (long double) -1) {
            personas[i].category = 3;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 1 && attack_prob != (long double) -1) {
            personas[i].category = 2;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
        if (danger_category == 1 && attack_prob == (long double) -1) {
            personas[i].category = 1;
            fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
        }
    }
    fclose(fpout);
    sort_words(personas, cont, arch_out);
}

void sort_words(Persona* personas, int count, char* arch_out) {
    FILE *fpout;
    fpout = fopen(arch_out, "w+");
    if (fpout == NULL) perror("Opening file");

    long int temp;
    char temp_2[100];
    long int temp_3;
    long double temp_4;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(personas[i].name, personas[j].name) < 0) {

                temp = personas[i].category;
                personas[i].category = personas[j].category;
                personas[j].category = temp;

                strcpy(temp_2, personas[i].name);
                strcpy(personas[i].name, personas[j].name);
                strcpy(personas[j].name, temp_2);

                temp_3 = personas[i].dangerCategory;
                personas[i].dangerCategory = personas[j].dangerCategory;
                personas[j].dangerCategory = temp_3;

                temp_4 = personas[i].attackProb;
                personas[i].attackProb = personas[j].attackProb;
                personas[j].attackProb = temp_4;
            }
        }
    }
    for (int i = 0; i < count+1; i++) {
        fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb, personas[i].category);
    }
    fclose(fpout);
}

void sortNewCategory(Persona *personas, int cont, char* num_lista, FILE * fpin, char* arch_out) {
    FILE *fpout;
    fpout = fopen(arch_out, "w+");
    if (fpout == NULL) perror("Opening file");

    long int temp;
    char temp_2[100];
    long int temp_3;
    long double temp_4;

    int out_mbr = atoi(num_lista);

    for (int i = 0; i < cont; i++) {
        for (int j = 0; j < cont; j++) {
            if (personas[i].category > personas[j].category) {

                temp = personas[i].category;
                personas[i].category = personas[j].category;
                personas[j].category = temp;

                strcpy(temp_2, personas[i].name);
                strcpy(personas[i].name, personas[j].name);
                strcpy(personas[j].name, temp_2);

                temp_3 = personas[i].dangerCategory;
                personas[i].dangerCategory = personas[j].dangerCategory;
                personas[j].dangerCategory = temp_3;

                temp_4 = personas[i].attackProb;
                personas[i].attackProb = personas[j].attackProb;
                personas[j].attackProb = temp_4;
            }
        }
    }
    for (int i = 0; i < out_mbr-1; i++) {
        fprintf(fpout, "%s,%ld\n", personas[i].name, personas[i].category);
    }
    fclose(fpout);
}