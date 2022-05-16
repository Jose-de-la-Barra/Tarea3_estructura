#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estructura que almacena los atacantes (asumimos largo de nombre a lo mas 100)
// prob_ataque es -1 cuando no esta definido
typedef struct {
  char nombre[100];
  int categoria;
  float prob_ataque;
} atacante;

// funciones auxiliares
int menor_4_5(atacante a1, atacante a2);
int menor_1_2(atacante a1, atacante a2);

// Version con memoria dinamica que funciona para cualquier numero de atacantes
// Asumimos que los argumentos al ejecutar el programa son correctos
int main(int argc, char *argv[])
{
  FILE *input = fopen(argv[1], "r");
  char line[1000]; // asumimos que cada linea tiene largo a lo mas 1000
  atacante *atacantes_4_5; // almacena atacantes categoria 4 o 5
  atacante *atacantes_3_con; // almacena atacantes categoria 3 con prob_ataque
  atacante *atacantes_3_sin; // almacena atacantes categoria 3 sin prob_ataque
  atacante *atacantes_1_2; // almacena atacantes categoria 1 o 2
  atacante *atacantes_ordenados; // almacenara todos los atacantes correctamente ordenados
  int count_4_5 = 0, count_3_con = 0, count_3_sin = 0, count_1_2 = 0;
  
  fgets(line, 1000, input); // ignoramos la cabecera
  // primer while para calcular los largos de los arreglos
  int categoria;
  while (fgets(line, 1000, input) != NULL) {
    strtok(line, ",");
    categoria = atoi(strtok(NULL, ","));
    if (categoria == 4 || categoria == 5) {
      count_4_5++;
    }

    if (categoria == 1 || categoria == 2) {
      count_1_2++;
    }

    if (categoria == 3) {
      char *token = strtok(NULL, ",");
      if (strcmp(token, "\n") == 0) {
        count_3_sin++;
      }
      else {
        count_3_con++;
      }
    }
  }
  fclose(input);

  input = fopen(argv[1], "r");
  atacante aux;
  int count = count_4_5 + count_1_2 + count_3_con + count_3_sin;
  // pedimos la memoria necesaria y asignamos los arreglos
  atacantes_4_5 = (atacante *)malloc(count_4_5 * sizeof(atacante));  
  atacantes_3_con = (atacante *)malloc(count_3_con * sizeof(atacante));  
  atacantes_3_sin = (atacante *)malloc(count_3_sin * sizeof(atacante));  
  atacantes_1_2 = (atacante *)malloc(count_1_2 * sizeof(atacante));  
  atacantes_ordenados = (atacante *)malloc(count * sizeof(atacante));  
  
  count_4_5 = 0;
  count_3_con = 0; 
  count_3_sin = 0; 
  count_1_2 = 0;
  
  fgets(line, 1000, input); // ignoramos la cabecera
  // segundo while para rellenar los arreglos
  while (fgets(line, 1000, input) != NULL) {
    strcpy(aux.nombre, strtok(line, ","));
    aux.categoria = atoi(strtok(NULL, ","));
    char *token = strtok(NULL, ",");
    if (strcmp(token, "\n") == 0) {
      aux.prob_ataque = -1;
    }
    else {
      aux.prob_ataque = atof(token);
    }

    if (aux.categoria == 4 || aux.categoria == 5) {
      atacantes_4_5[count_4_5] = aux;
      count_4_5++;
    }
    else if (aux.categoria == 3 && aux.prob_ataque == -1) {
      atacantes_3_sin[count_3_sin] = aux;
      count_3_sin++;
    }
    else if (aux.categoria == 3 && aux.prob_ataque != -1) {
      atacantes_3_con[count_3_con] = aux;
      count_3_con++;
    }
    else {
      atacantes_1_2[count_1_2] = aux;
      count_1_2++;
    }
  }
  // ordenamos atacantes categoria 4 o 5 (usamos bubble sort)

  for (int i = 0; i < count_4_5; i++) {
    for (int j = 0; j < count_4_5 - 1 - i; j++) {
      if (menor_4_5(atacantes_4_5[j], atacantes_4_5[j+1])) { 
        // swap entre atacantes_4_5[j] y atacantes_4_5[j+1]
        aux = atacantes_4_5[j];
        atacantes_4_5[j] = atacantes_4_5[j+1];
        atacantes_4_5[j+1] = aux;
      }
    }
  }  

  // ordenamos atacantes categoria 1 o 2 (usamos bubble sort)

  for (int i = 0; i < count_1_2; i++) {
    for (int j = 0; j < count_1_2 - 1 - i; j++) {
      if (menor_1_2(atacantes_1_2[j], atacantes_1_2[j+1])) { 
        // swap entre atacantes_1_2[j] y atacantes_1_2[j+1]
        aux = atacantes_1_2[j];
        atacantes_1_2[j] = atacantes_1_2[j+1];
        atacantes_1_2[j+1] = aux;
      }
    }
  } 

  // ordenamos por separado atacantes categoria 3 con prob_ataque y sin prob_ataque (usamos bubble sort)

  for (int i = 0; i < count_3_con; i++) {
    for (int j = 0; j < count_3_con - 1 - i; j++) {
      if (atacantes_3_con[j].prob_ataque < atacantes_3_con[j+1].prob_ataque) { 
        // swap entre atacantes_3_con[j] y atacantes_3_con[j+1]
        aux = atacantes_3_con[j];
        atacantes_3_con[j] = atacantes_3_con[j+1];
        atacantes_3_con[j+1] = aux;
      }
    }
  } 

  for (int i = 0; i < count_3_sin; i++) {
    for (int j = 0; j < count_3_sin - 1 - i; j++) {
      if (strcmp(atacantes_3_sin[j].nombre, atacantes_3_sin[j+1].nombre) > 0) { 
        // swap entre atacantes_3_sin[j] y atacantes_3_sin[j+1]
        aux = atacantes_3_sin[j];
        atacantes_3_sin[j] = atacantes_3_sin[j+1];
        atacantes_3_sin[j+1] = aux;
      }
    }
  } 

  // escribimos el ordenamiento final en atacantes_ordenados

  count = 0;
  for(int i = 0; i < count_4_5; i++) {
    atacantes_ordenados[count] = atacantes_4_5[i];
    count++;
  }

  // ----- aplicamos las reglas de la categoria 3 -----
  for(int i = 0; i < count_3_con/2; i++) {
    atacantes_ordenados[count] = atacantes_3_con[i];
    count++;
  }

  for(int i = 0; i < count_3_sin; i++) {
    atacantes_ordenados[count] = atacantes_3_sin[i];
    count++;
  }

  for(int i = count_3_con/2; i < count_3_con; i++) {
    atacantes_ordenados[count] = atacantes_3_con[i];
    count++;
  }
  // ----------

  for(int i = 0; i < count_1_2; i++) {
    atacantes_ordenados[count] = atacantes_1_2[i];
    count++;
  }

  // escribimos los N mas peligrosos al archivo de salida
  FILE *output = fopen(argv[3], "w");
  int N = atoi(argv[2]);
  for (int i = 0; i < N; i++) {
    fputs(atacantes_ordenados[i].nombre, output);
    fputs("\n", output);
  }

  fclose(output);
  // liberamos la memoria dinamica que no usaremos
  free(atacantes_4_5);
  free(atacantes_3_con);
  free(atacantes_3_sin);
  free(atacantes_1_2);
  free(atacantes_ordenados);
}


/* entrega 1 si a1 tiene menor peligrosidad que a2, segun los criterios de la categoria 4 y 5; 
en caso contrario entrega 0 */
int menor_4_5(atacante a1, atacante a2)
{
  if (a1.categoria < a2.categoria) {
    return 1;
  }

  if (a1.categoria == a2.categoria) {
    if(a1.prob_ataque != -1) {
      if (a2.prob_ataque == -1) {
        return 1;
      }
      
      if(a1.prob_ataque < a2.prob_ataque || (a1.prob_ataque == a2.prob_ataque && strcmp(a1.nombre, a2.nombre) > 0)) {
        return 1;
      }
    }
    else {
      if (a2.prob_ataque == -1 && strcmp(a1.nombre, a2.nombre) > 0) {
        return 1;
      }
    }
  }

  return 0;
}

/* entrega 1 si a1 tiene menor peligrosidad que a2, segun los criterios de la categoria 1 y 2; 
en caso contrario entrega 0 */
int menor_1_2(atacante a1, atacante a2)
{
  if (a1.categoria < a2.categoria) {
    return 1;
  }

  if (a1.categoria == a2.categoria) {
    if(a1.prob_ataque != -1) {
      if (a2.prob_ataque != -1) {
        if(a1.prob_ataque < a2.prob_ataque || (a1.prob_ataque == a2.prob_ataque && strcmp(a1.nombre, a2.nombre) > 0)) {
          return 1;
        }
      }
    }
    else {
      if (a2.prob_ataque != -1) {
        return 1;
      }

      if (strcmp(a1.nombre, a2.nombre) > 0) {
        return 1;
      }
    }
  } 

  return 0;
}