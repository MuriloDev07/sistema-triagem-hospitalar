#ifndef ARQUIVO_H
#define ARQUIVO_H

// Salva o estado atual da triagem em disco (retorna 1 se sucesso, 0 se erro)
int arquivo_salvar_dados(const char caminho_arquivo[]);

// Carrega os dados salvos anteriormente (retorna qtd de registros lidos ou -1 se erro)
int arquivo_carregar_dados(const char caminho_arquivo[]);

#endif