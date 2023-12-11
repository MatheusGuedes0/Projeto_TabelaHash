#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FuncoesTabelaH.h"
struct data
{
    int dia;
    int mes;
    int ano;
};

struct item
{
    int issn;
    char titulo[30];
    int telefoneA;
    Data data;
    int ra;
};

// o item não será guardado diretamente, será guardada uma célula
struct celula
{
    Item item;
    Celula *prox;
};

// agora cada ponteiro aponta para a 1ª célula da lista em vez de apontar para um item
struct hash
{
    int quantidade;
    Celula **celulas;
};


Hash * cria_tabela()
{
    int i;
    Hash *h = malloc(sizeof(Hash));
    h->quantidade = 0;
    h->celulas = malloc(TABLESIZE * sizeof(Celula*)); // em vez de sizeof(Item*), agora é sizeof(Celula*)
    for(i = 0; i < TABLESIZE; i++)
        h->celulas[i] = NULL;
    return h;
}

void libera_tabela(Hash *h)
{
    int i;
    Celula *aux, *remover;
    for(i = 0; i < TABLESIZE; i++)
    {
        aux = h->celulas[i];
        // em vez de liberar um item, agora é preciso percorrer a lista liberando cada célula
        while(aux != NULL)
        {
            remover = aux;
            aux = aux->prox;
            free(remover);
        }
    }
    free(h->celulas);
    free(h);
}

int hashing_divisao(int issn)
{
    return issn % TABLESIZE;
}

int verifica_tabela_vazia(Hash *h)
{
    return h->quantidade == 0;
}

// conceito de tabela cheia não existe mais

void imprime_item(Item *item)
{
    if(item != NULL)
    {
        printf("ISSN: %d\n",item->issn);
        printf("\nTitulo: %s", item->titulo);
        printf("\nData de devolucao(dd/mm/aaaa): %d/%d/%d", item->data.dia, item->data.mes,item->data.ano);
        printf("\nRA do Aluno: %d", item->ra);
        printf("\nTelefone do Aluno: %d\n\n", item->telefoneA);

    }
    else
    {
        printf("O livro nao esta emprestado.\n");
    }
}

void imprime_tabela(Hash *h)
{
    int i;
    for(i = 0; i < TABLESIZE; i++)
    {
        if(h->celulas[i] != NULL)
        {
            Celula *aux = h->celulas[i];
            printf("Pos: %d: \n", i);
            printf("ISSN do livro emprestado: %d", aux->item.issn);
            printf("\nTitulo: %s", aux->item.titulo);
            printf("\nData de devolucao(dd/mm/aaaa): %d/%d/%d", aux->item.data.dia, aux->item.data.mes,aux->item.data.ano);
            printf("\nRA do Aluno: %d", aux->item.ra);
            printf("\nTelefone do Aluno: %d\n\n", aux->item.telefoneA);
            aux = aux -> prox;
        }

    }
}

void insere_tratamento_lista_encadeada(Hash *h, int issn, char titulo[], int telefoneA,int dia, int mes, int ano, int RA)
{
    int posicao = hashing_divisao(issn);

    Item item;
    item.issn = issn;
    strcpy(item.titulo, titulo);
    item.telefoneA = telefoneA;
    item.data.dia = dia;
    item.data.mes = mes;
    item.data.ano = ano;
    item.ra = RA;
    Celula *aux = malloc(sizeof(Celula));
    aux->item = item;

    aux->prox = h->celulas[posicao]; // aux->prox recebe tudo que já tinha na lista (inserção no começo)
    h->celulas[posicao] = aux; // o ponteiro que indica a primeira célula da lista recebe aux
    h->quantidade++; // continuamos com o campo quantidade para saber com facilidade se a tabela está vazia
}

void altera_data_tabela(Hash *h, Item *i,int issn, int dia, int mes, int ano)
{
    //int posicao = hashing_divisao(issn);
     //Item item;
i->data.dia = dia;
i->data.mes = mes;
i->data.ano = ano;

//    item.issn = i->issn;
//    strcpy(item.titulo, i->titulo);
//    item.telefoneA = i->telefoneA;
//    item.data.dia = i->data.dia;
//    item.data.mes = i->data.mes;
//    item.data.ano = i->data.ano;
//    item.ra = i->ra;
//    Celula *aux = malloc(sizeof(Celula));
//    aux->item = item;
//
//    aux->prox = h->celulas[posicao]; // aux->prox recebe tudo que já tinha na lista (inserção no começo)
//    h->celulas[posicao] = aux; // o ponteiro que indica a primeira célula da lista recebe aux
//    h->quantidade++; // continuamos com o campo quantidade para saber com facilidade se a tabela está vazia
}
Item * busca_tratamento_lista_encadeada(Hash *h, int issn)
{
    int posicao = hashing_divisao(issn);
    if(h->celulas[posicao] == NULL) // a lista da posição está vazia?
        return NULL;
    Celula *aux = h->celulas[posicao]; // percorrer até achar a chave buscada e retornar o item correspondente
    while(aux != NULL)
    {
        if(aux->item.issn == issn)
            return &aux->item;
        aux = aux->prox;
    }
    return NULL;
}

void remove_tratamento_lista_encadeada(Hash *h, int issn)
{
    int posicao = hashing_divisao(issn);
    if(h->celulas[posicao] == NULL)   // a lista da posição está vazia?
    {
        printf("Livro nao encontrado na lista de emprestimos.\n\n");
        return;
    }
    Celula *aux = h->celulas[posicao]; // início da lista
    if(aux->item.issn == issn) // remover do início
    {
        h->celulas[posicao] = aux->prox;
        h->quantidade--;
    }
    else   // encontra a célula a ser removida
    {
        Celula *anterior;
        while(aux != NULL && aux->item.issn != issn)
        {
            anterior = aux;
            aux = aux->prox;
        }
        if(aux == NULL)
            printf("Livro nao encontrado na lista de emprestimos.\n\n");
        else   // remove do meio ou final
        {
            anterior->prox = aux->prox;
            h->quantidade--;
        }
    }
    free(aux);
}
