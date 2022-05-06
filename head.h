typedef struct {
    char *nombre;
    int categoria;
    float prob_ataque;
} atacante;

void inicializar_hash(atacante **hash_table);
void print_table(atacante **hash_table);
void insert_person(atacante **hash_table, atacante *persona, int index);