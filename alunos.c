#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dados.h"   
#include "utils.h"   
#include "alunos.h"

void menu_controle_pagamento()
{
    int opcao;

    do
    {
        limpar_tela();
        printf("=== CONTROLE DE PAGAMENTO ===\n\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Pagamentos\n");
        printf("3. Atualizar Pagamento\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar_aluno();
            break;
        case 2:
            listar_pagamentos();
            break;
        case 3:
            atualizar_pagamento();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida!\n");
            pausar();
        }
    } while (opcao != 0);
}

void cadastrar_aluno()
{
    if (total_alunos >= MAX_ALUNOS)
    {
        printf("Limite máximo de alunos atingido!\n");
        pausar();
        return;
    }

    limpar_tela();
    printf("=== CADASTRAR ALUNO ===\n\n");

    printf("Nome completo: ");
    getchar(); // Limpar buffer
    fgets(alunos[total_alunos].nome, MAX_STRING, stdin);
    alunos[total_alunos].nome[strcspn(alunos[total_alunos].nome, "\n")] = 0; // Remover \n

    printf("RG: ");
    scanf("%s", alunos[total_alunos].rg);

    printf("CPF: ");
    scanf("%s", alunos[total_alunos].cpf);

    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", alunos[total_alunos].data_nascimento);

    printf("Escola: ");
    getchar();
    fgets(alunos[total_alunos].escola, MAX_STRING, stdin);
    alunos[total_alunos].escola[strcspn(alunos[total_alunos].escola, "\n")] = 0;

    printf("Turma: ");
    scanf("%s", alunos[total_alunos].turma);

    printf("Telefone: ");
    scanf("%s", alunos[total_alunos].telefone);

    printf("Nome do pai: ");
    getchar();
    fgets(alunos[total_alunos].nome_pai, MAX_STRING, stdin);
    alunos[total_alunos].nome_pai[strcspn(alunos[total_alunos].nome_pai, "\n")] = 0;

    printf("Nome da mãe: ");
    fgets(alunos[total_alunos].nome_mae, MAX_STRING, stdin);
    alunos[total_alunos].nome_mae[strcspn(alunos[total_alunos].nome_mae, "\n")] = 0;

    printf("Endereço: ");
    fgets(alunos[total_alunos].endereco, MAX_STRING, stdin);
    alunos[total_alunos].endereco[strcspn(alunos[total_alunos].endereco, "\n")] = 0;

    alunos[total_alunos].valor_total = 1470.00;
    alunos[total_alunos].valor_pago = 0.0;
    alunos[total_alunos].embarque_confirmado = 0;
    alunos[total_alunos].seguro_ativo = 0;

    total_alunos++;
    printf("\nAluno cadastrado com sucesso!\n");
    pausar();
}

void listar_pagamentos()
{
    limpar_tela();
    printf("=== CONTROLE DE PAGAMENTOS ===\n\n");

    if (total_alunos == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
    }
    else
    {
        printf("%-30s %-15s %-15s %-12s %-10s %-10s\n",
               "NOME", "RG", "CPF", "NASCIMENTO", "PAGO", "TOTAL");
        printf("-------------------------------------------------------------------------------------\n");

        for (int i = 0; i < total_alunos; i++)
        {
            printf("%-30s %-15s %-15s %-12s R$%-8.2f R$%-8.2f\n",
                   alunos[i].nome, alunos[i].rg, alunos[i].cpf,
                   alunos[i].data_nascimento, alunos[i].valor_pago, alunos[i].valor_total);
        }
    }
    pausar();
}

void atualizar_pagamento()
{
    char rg[20];
    int encontrado = 0;
    float valor;

    limpar_tela();
    printf("=== ATUALIZAR PAGAMENTO ===\n\n");

    printf("RG do aluno: ");
    scanf("%s", rg);

    for (int i = 0; i < total_alunos; i++)
    {
        if (strcmp(alunos[i].rg, rg) == 0)
        {
            printf("Aluno: %s\n", alunos[i].nome);
            printf("Valor atual pago: R$ %.2f\n", alunos[i].valor_pago);
            printf("Valor total: R$ %.2f\n", alunos[i].valor_total);
            printf("Valor a adicionar: R$ ");
            scanf("%f", &valor);

            alunos[i].valor_pago += valor;
            if (alunos[i].valor_pago > alunos[i].valor_total)
            {
                alunos[i].valor_pago = alunos[i].valor_total;
            }

            printf("Pagamento atualizado! Novo valor pago: R$ %.2f\n", alunos[i].valor_pago);
            encontrado = 1;
            break;
        }
    }
}

void menu_embarque()
{
    int opcao;

    do
    {
        limpar_tela();
        printf("=== LISTA DE EMBARQUE ===\n\n");
        printf("1. Confirmar Embarque\n");
        printf("2. Listar Embarques\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            confirmar_embarque();
            break;
        case 2:
            listar_embarque();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida!\n");
            pausar();
        }
    } while (opcao != 0);
}
void confirmar_embarque()
{
    char rg[20];
    int encontrado = 0;

    limpar_tela();
    printf("=== CONFIRMAR EMBARQUE ===\n\n");

    printf("RG do aluno: ");
    scanf("%s", rg);

    for (int i = 0; i < total_alunos; i++)
    {
        if (strcmp(alunos[i].rg, rg) == 0)
        {
            printf("Aluno: %s\n", alunos[i].nome);
            printf("Status atual: %s\n", alunos[i].embarque_confirmado ? "Confirmado" : "Não confirmado");

            if (alunos[i].valor_pago < alunos[i].valor_total)
            {
                printf("ATENÇÃO: Pagamento não está em dia!\n");
                printf("Valor pago: R$ %.2f / Total: R$ %.2f\n",
                       alunos[i].valor_pago, alunos[i].valor_total);
            }

            printf("Confirmar embarque? (1-Sim / 0-Não): ");
            scanf("%d", &alunos[i].embarque_confirmado);

            printf("Embarque %s!\n", alunos[i].embarque_confirmado ? "confirmado" : "cancelado");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Aluno não encontrado!\n");
    }
    pausar();
}
void listar_embarque()
{
    limpar_tela();
    printf("=== LISTA DE EMBARQUE ===\n\n");

    if (total_alunos == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
    }
    else
    {
        printf("%-30s %-15s %-15s\n", "NOME", "RG", "EMBARQUE");
        printf("---------------------------------------------------------------\n");

        for (int i = 0; i < total_alunos; i++)
        {
            printf("%-30s %-15s %-15s\n",
                   alunos[i].nome, alunos[i].rg,
                   alunos[i].embarque_confirmado ? "CONFIRMADO" : "PENDENTE");
        }
    }
    pausar();
}
void menu_seguro_viagem()
{
    int opcao;

    do
    {
        limpar_tela();
        printf("=== SEGURO VIAGEM ===\n\n");
        printf("1. Ativar Seguro\n");
        printf("2. Listar Seguros\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            ativar_seguro();
            break;
        case 2:
            listar_seguros();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida!\n");
            pausar();
        }
    } while (opcao != 0);
}

void ativar_seguro()
{
    char rg[20];
    int encontrado = 0;

    limpar_tela();
    printf("=== ATIVAR SEGURO VIAGEM ===\n\n");

    printf("RG do aluno: ");
    scanf("%s", rg);

    for (int i = 0; i < total_alunos; i++)
    {
        if (strcmp(alunos[i].rg, rg) == 0)
        {
            printf("Aluno: %s\n", alunos[i].nome);
            printf("RG: %s\n", alunos[i].rg);
            printf("CPF: %s\n", alunos[i].cpf);
            printf("Data de nascimento: %s\n", alunos[i].data_nascimento);
            printf("Status atual do seguro: %s\n", alunos[i].seguro_ativo ? "Ativo" : "Inativo");

            printf("Ativar seguro? (1-Sim / 0-Não): ");
            scanf("%d", &alunos[i].seguro_ativo);

            printf("Seguro %s!\n", alunos[i].seguro_ativo ? "ativado" : "desativado");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Aluno não encontrado!\n");
    }
    pausar();
}
void listar_seguros()
{
    limpar_tela();
    printf("=== LISTA DE SEGUROS VIAGEM ===\n\n");

    if (total_alunos == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
    }
    else
    {
        printf("%-30s %-15s %-15s %-12s %-10s\n",
               "NOME", "RG", "CPF", "NASCIMENTO", "SEGURO");
        printf("--------------------------------------------------------------------------------\n");

        for (int i = 0; i < total_alunos; i++)
        {
            printf("%-30s %-15s %-15s %-12s %-10s\n",
                   alunos[i].nome, alunos[i].rg, alunos[i].cpf,
                   alunos[i].data_nascimento,
                   alunos[i].seguro_ativo ? "ATIVO" : "INATIVO");
        }
    }
    pausar();
}

