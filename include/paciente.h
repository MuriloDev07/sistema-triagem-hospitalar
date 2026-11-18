#ifndef PACIENTE_H
#define PACIENTE_H

#define MAX_PACIENTES 50
#define TAM_NOME 100
#define TAM_DOC 20

// Níveis de prioridade da triagem (Manchester simplificado)
#define RISCO_VERMELHO 1 // Emergência
#define RISCO_AMARELO  2 // Urgente
#define RISCO_VERDE    3 // Pouco urgente
#define RISCO_AZUL     4 // Não urgente

// Status do paciente no fluxo
#define STATUS_AGUARDANDO     0
#define STATUS_EM_ATENDIMENTO 1
#define STATUS_ATENDIDO       2

// Valida se os dados básicos antes do cadastro são aceitáveis
int paciente_validar_dados(const char nome[], int idade, int nivel_risco);

// Exibe os dados formatados de um único paciente no terminal
void paciente_exibir_resumo(int id, const char nome[], int idade, const char doc[], int risco, int status);

#endif