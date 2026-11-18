#ifndef UI_H
#define UI_H

// Exibe o banner inicial e o menu principal, retornando a opção escolhida
int ui_exibir_menu_principal(void);

// Fluxo interativo para ler dados do teclado e realizar o cadastro com triagem_cadastrar()
void ui_fluxo_novo_cadastro(void);

// Fluxo interativo para buscar e exibir um paciente por ID
void ui_fluxo_buscar_paciente(void);

// Limpa o buffer de entrada (evita bugs clássicos do scanf com strings)
void ui_limpar_buffer(void);

#endif