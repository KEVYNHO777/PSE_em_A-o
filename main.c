

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ACOES 100

struct Acao {
    int codigo;
    char escola[100];
    char tema[50];
    char data[20];
    char publico[100];
    char responsavel[100];
    int quantidadePrevista;
    int participantes;
    int situacao;
};

struct Acao acoes[MAX_ACOES];
int totalAcoes = 0;

// Ler numeros com validacao
int lerInteiro(char mensagem[]) {
    char entrada[100];
    char *fim;
    long numero;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            return 0;
        }

        numero = strtol(entrada, &fim, 10);

        while (*fim == ' ' || *fim == '\t') {
            fim++;
        }

        if (fim != entrada && (*fim == '\n' || *fim == '\0')) {
            if (numero >= 0 && numero <= 2147483647) {
                return (int) numero;
            }
        }

        printf("Valor invalido! Digite um numero valido.\n");
    }
}

// Ler textos sem aceitar campos vazios
void lerTexto(char mensagem[], char destino[], int tamanho) {
    do {
        printf("%s", mensagem);

        if (fgets(destino, tamanho, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }

        destino[strcspn(destino, "\n")] = '\0';

        if (strlen(destino) == 0) {
            printf("Este campo nao pode ficar vazio!\n");
        }

    } while (strlen(destino) == 0);
}

// Cadastrar acao
void cadastrarAcao() {
    int codigo;
    int i;

    if (totalAcoes >= MAX_ACOES) {
        printf("Limite de acoes atingido!\n");
        return;
    }

    printf("\n===== CADASTRAR ACAO =====\n");

    codigo = lerInteiro("Codigo da acao: ");

    for (i = 0; i < totalAcoes; i++) {
        if (acoes[i].codigo == codigo) {
            printf("Erro: codigo ja cadastrado!\n");
            return;
        }
    }

    acoes[totalAcoes].codigo = codigo;

    lerTexto("Nome da escola: ", acoes[totalAcoes].escola, 100);
    lerTexto("Tema da acao: ", acoes[totalAcoes].tema, 50);
    lerTexto("Data da acao: ", acoes[totalAcoes].data, 20);
    lerTexto("Publico-alvo: ", acoes[totalAcoes].publico, 100);
    lerTexto("Responsavel: ", acoes[totalAcoes].responsavel, 100);

    acoes[totalAcoes].quantidadePrevista =
        lerInteiro("Quantidade prevista de participantes: ");

    acoes[totalAcoes].participantes = 0;
    acoes[totalAcoes].situacao = 1;

    totalAcoes++;

    printf("\nAcao cadastrada com sucesso!\n");
}

// Mostrar uma acao
void mostrarAcao(int i) {
    printf("\nCodigo: %d\n", acoes[i].codigo);
    printf("Escola: %s\n", acoes[i].escola);
    printf("Tema: %s\n", acoes[i].tema);
    printf("Data: %s\n", acoes[i].data);
    printf("Publico-alvo: %s\n", acoes[i].publico);
    printf("Responsavel: %s\n", acoes[i].responsavel);
    printf("Quantidade prevista: %d\n",
           acoes[i].quantidadePrevista);
    printf("Participantes: %d\n", acoes[i].participantes);

    if (acoes[i].situacao == 1) {
        printf("Situacao: Planejada\n");
    } else if (acoes[i].situacao == 2) {
        printf("Situacao: Concluida\n");
    } else {
        printf("Situacao: Cancelada\n");
    }
}

// Listar acoes
void listarAcoes() {
    int i;

    printf("\n===== LISTA DE ACOES =====\n");

    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < totalAcoes; i++) {
        mostrarAcao(i);
    }
}

// Pesquisar acao
void pesquisarAcao() {
    int opcao;
    int codigo;
    int i;
    int encontrou = 0;
    char pesquisa[100];

    printf("\n===== PESQUISAR ACAO =====\n");
    printf("1 - Pesquisar por codigo\n");
    printf("2 - Pesquisar por escola\n");
    printf("3 - Pesquisar por tema\n");

    opcao = lerInteiro("Escolha: ");

    if (opcao == 1) {
        codigo = lerInteiro("Digite o codigo: ");

        for (i = 0; i < totalAcoes; i++) {
            if (acoes[i].codigo == codigo) {
                mostrarAcao(i);
                encontrou = 1;
            }
        }

    } else if (opcao == 2 || opcao == 3) {
        lerTexto("Digite o nome para pesquisar: ", pesquisa, 100);

        for (i = 0; i < totalAcoes; i++) {
            if (opcao == 2 &&
                strstr(acoes[i].escola, pesquisa) != NULL) {
                mostrarAcao(i);
                encontrou = 1;
            }

            if (opcao == 3 &&
                strstr(acoes[i].tema, pesquisa) != NULL) {
                mostrarAcao(i);
                encontrou = 1;
            }
        }

    } else {
        printf("Opcao de pesquisa invalida!\n");
        return;
    }

    if (!encontrou) {
        printf("Nenhuma acao encontrada.\n");
    }
}

// Atualizar situacao
void atualizarSituacao() {
    int codigo;
    int novaSituacao;
    int i;

    printf("\n===== ATUALIZAR SITUACAO =====\n");

    codigo = lerInteiro("Codigo da acao: ");

    for (i = 0; i < totalAcoes; i++) {
        if (acoes[i].codigo == codigo) {

            printf("1 - Planejada\n");
            printf("2 - Concluida\n");
            printf("3 - Cancelada\n");

            novaSituacao = lerInteiro("Nova situacao: ");

            if (novaSituacao < 1 || novaSituacao > 3) {
                printf("Situacao invalida!\n");
                return;
            }

            acoes[i].situacao = novaSituacao;

            if (novaSituacao == 2) {
                int participantes;

                participantes = lerInteiro(
                    "Quantidade real de participantes: ");

                while (participantes > acoes[i].quantidadePrevista) {
                    printf("A quantidade nao pode superar a prevista.\n");
                    participantes = lerInteiro(
                        "Digite novamente: ");
                }

                acoes[i].participantes = participantes;
            }

            printf("Situacao atualizada com sucesso!\n");
            return;
        }
    }

    printf("Acao nao encontrada!\n");
}

// Registrar participantes
void registrarParticipantes() {
    int codigo;
    int quantidade;
    int i;

    printf("\n===== REGISTRAR PARTICIPANTES =====\n");

    codigo = lerInteiro("Codigo da acao: ");

    for (i = 0; i < totalAcoes; i++) {
        if (acoes[i].codigo == codigo) {

            if (acoes[i].situacao != 2) {
                printf("A acao precisa estar concluida!\n");
                return;
            }

            quantidade = lerInteiro(
                "Quantidade real de participantes: ");

            while (quantidade > acoes[i].quantidadePrevista) {
                printf("A quantidade nao pode superar a prevista.\n");
                quantidade = lerInteiro(
                    "Digite novamente: ");
            }

            acoes[i].participantes = quantidade;

            printf("Participantes registrados com sucesso!\n");
            return;
        }
    }

    printf("Acao nao encontrada!\n");
}

// Gerar resumo geral
void gerarResumo() {
    int i;
    int planejadas = 0;
    int concluidas = 0;
    int canceladas = 0;
    int totalPrevisto = 0;
    int totalParticipantes = 0;
    float percentual = 0;

    printf("\n===== RESUMO GERAL =====\n");

    for (i = 0; i < totalAcoes; i++) {

        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            concluidas++;
        } else {
            canceladas++;
        }

        totalPrevisto += acoes[i].quantidadePrevista;
        totalParticipantes += acoes[i].participantes;
    }

    if (totalPrevisto > 0) {
        percentual =
            (float) totalParticipantes / totalPrevisto * 100;
    }

    printf("Total de acoes: %d\n", totalAcoes);
    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes concluidas: %d\n", concluidas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Total previsto de participantes: %d\n", totalPrevisto);
    printf("Total de participantes: %d\n", totalParticipantes);
    printf("Percentual de participacao: %.2f%%\n", percentual);
}

// Menu principal
int main() {
    int opcao;

    do {
        printf("\n===== PSE EM ACAO =====\n");
        printf("1 - Cadastrar acao\n");
        printf("2 - Listar acoes\n");
        printf("3 - Pesquisar acao\n");
        printf("4 - Atualizar situacao\n");
        printf("5 - Registrar participantes\n");
        printf("6 - Gerar resumo geral\n");
        printf("0 - Sair\n");

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrarAcao();
                break;

            case 2:
                listarAcoes();
                break;

            case 3:
                pesquisarAcao();
                break;

            case 4:
                atualizarSituacao();
                break;

            case 5:
                registrarParticipantes();
                break;

            case 6:
                gerarResumo();
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
