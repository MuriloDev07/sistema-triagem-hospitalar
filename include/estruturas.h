#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "paciente.h"

// Inicializa os vetores e contadores da triagem
void triagem_inicializar(void);

// Cadastra um novo paciente na fila estática (retorna o ID gerado ou -1 se cheia)
int triagem_cadastrar(const char nome[], int idade, const char doc[], int nivel_risco);

// Chama o próximo paciente com maior urgência (retorna o índice no vetor ou -1 se vazia)
int triagem_chamar_proximo(void);

// Finaliza o atendimento de um paciente pelo ID (retorna 1 se sucesso, 0 se não encontrado)
int triagem_finalizar_atendimento(int id);

// Busca a posição de um paciente no vetor pelo ID (retorna índice ou -1 se não existir)
int triagem_buscar_por_id(int id);

// Lista todos os pacientes cadastrados no momento
void triagem_listar_todos(void);

// Retorna a quantidade atual de pacientes aguardando
int triagem_total_aguardando(void);

#endif