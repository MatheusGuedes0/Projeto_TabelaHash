typedef struct data Data;
typedef struct item Item;
typedef struct celula Celula;
typedef struct hash Hash;


#define TABLESIZE 50

Hash * cria_tabela();
void libera_tabela(Hash *h);
int hashing_divisao(int issn);
int verifica_tabela_vazia(Hash *h);
void imprime_item(Item *item);
void imprime_tabela(Hash *h);
void insere_tratamento_lista_encadeada(Hash *h, int issn, char titulo[], int telefoneA,int dia, int mes, int ano, int RA);
void altera_data_tabela(Hash *h, Item *i,int issn, int dia, int mes, int ano);
Item * busca_tratamento_lista_encadeada(Hash *h, int issn);
void remove_tratamento_lista_encadeada(Hash *h, int issn);
