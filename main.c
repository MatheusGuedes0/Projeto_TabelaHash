#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncoesTabelaH.h"
int main()
{
    Hash *h = cria_tabela();
    Item *i;
    int opcao,opcao2,confirmacao, dia,mes,ano,issn,RA, telefoneA;
    char titulo[30];

    printf("Bem vindo ao sistema da biblioteca UTFPR!\n");
    do
    {
        printf("Escolha uma opcao:\n");
        printf("[1]Realizar um emprestimo\n[2]Consultar emprestimos\n[3]Renovar emprestimo\n[4]excluir emprestimo\n[5]Sair do sistema\n");
        setbuf(stdin, NULL);
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            do
            {
                do
                {
                    printf("Informe o ISSN do livro: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &issn);
                    if(busca_tratamento_lista_encadeada(h, issn) !=NULL)
                    {
                        printf("Esse livro ja encontra-se emprestado!!\n");
                    }
                }
                while(busca_tratamento_lista_encadeada(h, issn) !=NULL);
                printf("Informe o titulo do livro: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]s", titulo);
                printf("Informe o RA do aluno: ");
                setbuf(stdin, NULL);
                scanf("%d", &RA);
                printf("Informe o Telefone do aluno: ");
                setbuf(stdin, NULL);
                scanf("%d", &telefoneA);
                printf("Informe a data de devolucao do livro(dd/mm/aaaa): ");
                setbuf(stdin, NULL);
                scanf("%d/%d/%d", &dia, &mes, &ano);

                printf("Confirmar dados?\n[1]SIM\t[2]NAO: ");
                setbuf(stdin, NULL);
                scanf("%d", &confirmacao);
            }
            while(confirmacao !=1);

            insere_tratamento_lista_encadeada(h,issn,titulo,telefoneA,dia,mes,ano,RA);
            break;
        case 2:
            printf("[1]Consultar emprestimo por ISSN\n[2]Consultar todos os emprestimos\n[3]Voltar\nOpcao: ");
            setbuf(stdin, NULL);
            scanf("%d", &opcao2);
            printf("\n");
            switch(opcao2)
            {
            case 1:
                printf("Informe o ISSN do livro a ser consultado: ");
                scanf("%d", &issn);
                i = busca_tratamento_lista_encadeada(h, issn);

                imprime_item(i);
                break;
            case 2:
                if(verifica_tabela_vazia(h) != 0)
                {
                    printf("\nNenhum Livro emprestado ate o momento!!\n");
                }
                else
                {
                    imprime_tabela(h);

                }
                break;
            case 3:
                //Nesse case, volta para o Menu anterior
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
            }
            break;
        case 3:

            printf("Informe o ISSN do livro que deseja alterar: ");
            scanf("%d", &issn);
            if(busca_tratamento_lista_encadeada(h, issn) == NULL)
            {
                printf("\nEsse livro nao esta emprestado!\n\n");
            }
            else
            {
                i  = busca_tratamento_lista_encadeada(h, issn);
                printf("Informe nova data de devolucao para o emprestimo do livro com ISSN: %d(dd/mm/aaaa): ", issn);
                scanf("%d/%d/%d", &dia, &mes, &ano);
                altera_data_tabela(h, i,issn,dia,mes,ano);
            }
            break;
        case 4:
            printf("Informe o ISSN do livro que deseja excluir: ");
            scanf("%d", &issn);
            remove_tratamento_lista_encadeada(h, issn);
            break;
        case 5:
            break;
        default:
            printf("\nOpcao invalida!!\n");
            break;
        }
    }
    while(opcao != 5);

    libera_tabela(h);
    free(i);
    return 0;
}
