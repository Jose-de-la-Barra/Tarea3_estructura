// Estructura que almacena los atacantes (asumimos largo de nombre a lo mas 100)
// prob_ataque es -1 cuando no esta definido
typedef struct {
    char nombre[100];
    int categoria;
    float prob_ataque;
} atacante;