#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 10
#define MAX_ALUNOS 100
#define MAX_STRING 100

typedef struct {
    char usuario[50];
    char senha[50];
    int ativo;
} Usuario;

typedef struct {
    char nome[MAX_STRING];
    char rg[20];
    char cpf[15];
    char data_nascimento[12];
    char escola[MAX_STRING];
    char turma[10];
    char telefone[20];
    char nome_pai[MAX_STRING];
    char nome_mae[MAX_STRING];
    char endereco[MAX_STRING];
    float valor_pago;
    float valor_total;
    int embarque_confirmado; 
    int seguro_ativo;
} Aluno;

Usuario usuarios[MAX_USUARIOS];
Aluno alunos[MAX_ALUNOS];
int total_usuarios = 0;
int total_alunos = 0;
char usuario_logado[50];

void inicializar_sistema();
void carregar_dados();
void salvar_dados();
int fazer_login();
void menu_principal();
void menu_usuarios();
void cadastrar_usuario();
void listar_usuarios();
void alterar_usuario();
void remover_usuario();
void menu_controle_pagamento();
void cadastrar_aluno();
void listar_pagamentos();
void atualizar_pagamento();
void menu_embarque();
void confirmar_embarque();
void listar_embarque();
void menu_seguro_viagem();
void ativar_seguro();
void listar_seguros();
void limpar_tela();
void pausar();

int main() {
    inicializar_sistema();
    carregar_dados();
    
    printf("=== SISTEMA LUMASTER TURISMO ===\n");
    printf("Controle de Excursões\n\n");
    
    if (fazer_login()) {
        menu_principal();
    }
    
    salvar_dados();
    return 0;
}

void inicializar_sistema() {
    if (total_usuarios == 0) {
        strcpy(usuarios[0].usuario, "admin");
        strcpy(usuarios[0].senha, "123");
        usuarios[0].ativo = 1;
        total_usuarios = 1;
    }
}

void carregar_dados() {
    FILE *arquivo;
    
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d", &total_usuarios);
        for (int i = 0; i < total_usuarios; i++) {
            fscanf(arquivo, "%s %s %d", usuarios[i].usuario, usuarios[i].senha, &usuarios[i].ativo);
        }
        fclose(arquivo);
    }

    arquivo = fopen("alunos.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d", &total_alunos);
        for (int i = 0; i < total_alunos; i++) {
            fscanf(arquivo, "%s %s %s %s %s %s %s %s %s %s %f %f %d %d",
                   alunos[i].nome, alunos[i].rg, alunos[i].cpf, alunos[i].data_nascimento,
                   alunos[i].escola, alunos[i].turma, alunos[i].telefone,
                   alunos[i].nome_pai, alunos[i].nome_mae, alunos[i].endereco,
                   &alunos[i].valor_pago, &alunos[i].valor_total,
                   &alunos[i].embarque_confirmado, &alunos[i].seguro_ativo);
        }
        fclose(arquivo);
    }
}

void salvar_dados() {
    FILE *arquivo;
    
    // Salvar usuários
    arquivo = fopen("usuarios.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d\n", total_usuarios);
        for (int i = 0; i < total_usuarios; i++) {
            fprintf(arquivo, "%s %s %d\n", usuarios[i].usuario, usuarios[i].senha, usuarios[i].ativo);
        }
        fclose(arquivo);
    }
    
    // Salvar alunos
    arquivo = fopen("alunos.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d\n", total_alunos);
        for (int i = 0; i < total_alunos; i++) {
            fprintf(arquivo, "%s %s %s %s %s %s %s %s %s %s %.2f %.2f %d %d\n",
                   alunos[i].nome, alunos[i].rg, alunos[i].cpf, alunos[i].data_nascimento,
                   alunos[i].escola, alunos[i].turma, alunos[i].telefone,
                   alunos[i].nome_pai, alunos[i].nome_mae, alunos[i].endereco,
                   alunos[i].valor_pago, alunos[i].valor_total,
                   alunos[i].embarque_confirmado, alunos[i].seguro_ativo);
        }
        fclose(arquivo);
    }
}

int fazer_login() {
    char usuario[50], senha[50];
    int tentativas = 3;
    
    while (tentativas > 0) {
        printf("=== LOGIN ===\n");
        printf("Usuário: ");
        scanf("%s", usuario);
        printf("Senha: ");
        scanf("%s", senha);
        
        for (int i = 0; i < total_usuarios; i++) {
            if (strcmp(usuarios[i].usuario, usuario) == 0 && 
                strcmp(usuarios[i].senha, senha) == 0 && 
                usuarios[i].ativo == 1) {
                strcpy(usuario_logado, usuario);
                printf("\nLogin realizado com sucesso!\n");
                printf("Bem-vindo(a), %s!\n", usuario_logado);
                pausar();
                return 1;
            }
        }
        
        tentativas--;
        printf("\nUsuário ou senha incorretos! Tentativas restantes: %d\n", tentativas);
        pausar();
        limpar_tela();
    }
    
    printf("Número máximo de tentativas excedido!\n");
    return 0;
}

void menu_principal() {
    int opcao;
    
    do {
        limpar_tela();
        printf("=== LUMASTER TURISMO - MENU PRINCIPAL ===\n");
        printf("Usuário logado: %s\n\n", usuario_logado);
        printf("1. Gerenciar Usuários\n");
        printf("2. Controle de Pagamento\n");
        printf("3. Lista de Embarque\n");
        printf("4. Seguro Viagem\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                menu_usuarios();
                break;
            case 2:
                menu_controle_pagamento();
                break;
            case 3:
                menu_embarque();
                break;
            case 4:
                menu_seguro_viagem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
                pausar();
        }
    } while (opcao != 0);
}

void menu_usuarios() {
    int opcao;
    
    do {
        limpar_tela();
        printf("=== GERENCIAR USUÁRIOS ===\n\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Listar Usuários\n");
        printf("3. Alterar Usuário\n");
        printf("4. Remover Usuário\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrar_usuario();
                break;
            case 2:
                listar_usuarios();
                break;
            case 3:
                alterar_usuario();
                break;
            case 4:
                remover_usuario();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
                pausar();
        }
    } while (opcao != 0);
}

void cadastrar_usuario() {
    if (total_usuarios >= MAX_USUARIOS) {
        printf("Limite máximo de usuários atingido!\n");
        pausar();
        return;
    }
    
    limpar_tela();
    printf("=== CADASTRAR USUÁRIO ===\n\n");
    
    printf("Nome de usuário: ");
    scanf("%s", usuarios[total_usuarios].usuario);
    
    // Verificar se usuário já existe
    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].usuario, usuarios[total_usuarios].usuario) == 0) {
            printf("Usuário já existe!\n");
            pausar();
            return;
        }
    }
    
    printf("Senha: ");
    scanf("%s", usuarios[total_usuarios].senha);
    usuarios[total_usuarios].ativo = 1;
    
    total_usuarios++;
    printf("\nUsuário cadastrado com sucesso!\n");
    pausar();
}

void listar_usuarios() {
    limpar_tela();
    printf("=== LISTA DE USUÁRIOS ===\n\n");
    
    if (total_usuarios == 0) {
        printf("Nenhum usuário cadastrado.\n");
    } else {
        printf("%-20s %-10s\n", "USUÁRIO", "STATUS");
        printf("----------------------------------------\n");
        for (int i = 0; i < total_usuarios; i++) {
            printf("%-20s %-10s\n", usuarios[i].usuario, 
                   usuarios[i].ativo ? "Ativo" : "Inativo");
        }
    }
    pausar();
}

void alterar_usuario() {
    char usuario[50];
    int encontrado = 0;
    
    limpar_tela();
    printf("=== ALTERAR USUÁRIO ===\n\n");
    
    printf("Nome do usuário a alterar: ");
    scanf("%s", usuario);
    
    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0) {
            printf("Nova senha: ");
            scanf("%s", usuarios[i].senha);
            printf("Usuário alterado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Usuário não encontrado!\n");
    }
    pausar();
}

void remover_usuario() {
    char usuario[50];
    int encontrado = 0;
    
    limpar_tela();
    printf("=== REMOVER USUÁRIO ===\n\n");
    
    printf("Nome do usuário a remover: ");
    scanf("%s", usuario);
    
    if (strcmp(usuario, "luciana") == 0) {
        printf("Não é possível remover o usuário principal!\n");
        pausar();
        return;
    }
    
    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0) {
            usuarios[i].ativo = 0;
            printf("Usuário removido com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Usuário não encontrado!\n");
    }
    pausar();
}

void menu_controle_pagamento() {
    int opcao;
    
    do {
        limpar_tela();
        printf("=== CONTROLE DE PAGAMENTO ===\n\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Pagamentos\n");
        printf("3. Atualizar Pagamento\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
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

void cadastrar_aluno() {
    if (total_alunos >= MAX_ALUNOS) {
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
    
    alunos[total_alunos].valor_total = 1470.00; // Valor padrão da excursão
    alunos[total_alunos].valor_pago = 0.0;
    alunos[total_alunos].embarque_confirmado = 0;
    alunos[total_alunos].seguro_ativo = 0;
    
    total_alunos++;
    printf("\nAluno cadastrado com sucesso!\n");
    pausar();
}

void listar_pagamentos() {
    limpar_tela();
    printf("=== CONTROLE DE PAGAMENTOS ===\n\n");
    
    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        printf("%-30s %-15s %-15s %-12s %-10s %-10s\n", 
               "NOME", "RG", "CPF", "NASCIMENTO", "PAGO", "TOTAL");
        printf("-------------------------------------------------------------------------------------\n");
        
        for (int i = 0; i < total_alunos; i++) {
            printf("%-30s %-15s %-15s %-12s R$%-8.2f R$%-8.2f\n",
                   alunos[i].nome, alunos[i].rg, alunos[i].cpf, 
                   alunos[i].data_nascimento, alunos[i].valor_pago, alunos[i].valor_total);
        }
    }
    pausar();
}

void atualizar_pagamento() {
    char rg[20];
    int encontrado = 0;
    float valor;
    
    limpar_tela();
    printf("=== ATUALIZAR PAGAMENTO ===\n\n");
    
    printf("RG do aluno: ");
    scanf("%s", rg);
    
    for (int i = 0; i < total_alunos; i++) {
        if (strcmp(alunos[i].rg, rg) == 0) {
            printf("Aluno: %s\n", alunos[i].nome);
            printf("Valor atual pago: R$ %.2f\n", alunos[i].valor_pago);
            printf("Valor total: R$ %.2f\n", alunos[i].valor_total);
            printf("Valor a adicionar: R$ ");
            scanf("%f", &valor);
            
            alunos[i].valor_pago += valor;
            if (alunos[i].valor_pago > alunos[i].valor_total) {
                alunos[i].valor_pago = alunos[i].valor_total;
            }
            
            printf("Pagamento atualizado! Novo valor pago: R$ %.2f\n", alunos[i].valor_pago);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Aluno não encontrado!\n");
    }
    pausar();
}

void menu_embarque() {
    int opcao;
    
    do {
        limpar_tela();
        printf("=== LISTA DE EMBARQUE ===\n\n");
        printf("1. Confirmar Embarque\n");
        printf("2. Listar Embarques\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
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

void confirmar_embarque() {
    char rg[20];
    int encontrado = 0;
    
    limpar_tela();
    printf("=== CONFIRMAR EMBARQUE ===\n\n");
    
    printf("RG do aluno: ");
    scanf("%s", rg);
    
    for (int i = 0; i < total_alunos; i++) {
        if (strcmp(alunos[i].rg, rg) == 0) {
            printf("Aluno: %s\n", alunos[i].nome);
            printf("Status atual: %s\n", alunos[i].embarque_confirmado ? "Confirmado" : "Não confirmado");
            
            if (alunos[i].valor_pago < alunos[i].valor_total) {
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
    
    if (!encontrado) {
        printf("Aluno não encontrado!\n");
    }
    pausar();
}

void listar_embarque() {
    limpar_tela();
    printf("=== LISTA DE EMBARQUE ===\n\n");
    
    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        printf("%-30s %-15s %-15s\n", "NOME", "RG", "EMBARQUE");
        printf("---------------------------------------------------------------\n");
        
        for (int i = 0; i < total_alunos; i++) {
            printf("%-30s %-15s %-15s\n",
                   alunos[i].nome, alunos[i].rg, 
                   alunos[i].embarque_confirmado ? "CONFIRMADO" : "PENDENTE");
        }
    }
    pausar();
}

void menu_seguro_viagem() {
    int opcao;
    
    do {
        limpar_tela();
        printf("=== SEGURO VIAGEM ===\n\n");
        printf("1. Ativar Seguro\n");
        printf("2. Listar Seguros\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
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

void ativar_seguro() {
    char rg[20];
    int encontrado = 0;
    
    limpar_tela();
    printf("=== ATIVAR SEGURO VIAGEM ===\n\n");
    
    printf("RG do aluno: ");
    scanf("%s", rg);
    
    for (int i = 0; i < total_alunos; i++) {
        if (strcmp(alunos[i].rg, rg) == 0) {
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
    
    if (!encontrado) {
        printf("Aluno não encontrado!\n");
    }
    pausar();
}

void listar_seguros() {
    limpar_tela();
    printf("=== LISTA DE SEGUROS VIAGEM ===\n\n");
    
    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        printf("%-30s %-15s %-15s %-12s %-10s\n", 
               "NOME", "RG", "CPF", "NASCIMENTO", "SEGURO");
        printf("--------------------------------------------------------------------------------\n");
        
        for (int i = 0; i < total_alunos; i++) {
            printf("%-30s %-15s %-15s %-12s %-10s\n",
                   alunos[i].nome, alunos[i].rg, alunos[i].cpf, 
                   alunos[i].data_nascimento, 
                   alunos[i].seguro_ativo ? "ATIVO" : "INATIVO");
        }
    }
    pausar();
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}