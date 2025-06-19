#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "usuarios.h"
#include "alunos.h"
#include "utils.h"

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