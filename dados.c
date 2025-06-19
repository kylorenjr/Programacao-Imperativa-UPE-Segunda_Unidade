#include <stdio.h>
#include <string.h>
#include "dados.h"

Usuario usuarios[MAX_USUARIOS];
Aluno alunos[MAX_ALUNOS];
int total_usuarios = 0;
int total_alunos = 0;
char usuario_logado[50];

void inicializar_sistema() {

    if (total_usuarios == 0) {
        strcpy(usuarios[0].usuario, "luciana");
        strcpy(usuarios[0].senha, "123456");
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
    
    arquivo = fopen("usuarios.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d\n", total_usuarios);
        for (int i = 0; i < total_usuarios; i++) {
            fprintf(arquivo, "%s %s %d\n", usuarios[i].usuario, usuarios[i].senha, usuarios[i].ativo);
        }
        fclose(arquivo);
    }
    
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