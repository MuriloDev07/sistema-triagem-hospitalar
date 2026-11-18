# Arquitetura do Sistema de Triagem Hospitalar

## 1. Visão Geral e Problema Resolvido

Este documento descreve a arquitetura de software do **Sistema de Triagem e Atendimento Hospitalar**, desenvolvido em linguagem C (padrão C11) para a Unidade II das disciplinas de **Linguagem de Programação I** e **Laboratório de Programação I** (UEPB - 2026/2).

O sistema resolve o problema da organização de fluxos de urgência em unidades de pronto-atendimento, inspirando-se no **Protocolo de Manchester**. Em vez de atender pacientes apenas por ordem de chegada, o sistema prioriza casos críticos sem perder o histórico de atendimento e garantindo rastreabilidade e segurança nas operações.

---

## 2. Estratégia de Evolução Incremental (Fases)

Para alinhar o desenvolvimento em equipe ao cronograma de conteúdos da disciplina e evitar bloqueios técnicos no início do projeto, a arquitetura foi desenhada sob o princípio de **Separação entre Interface (`.h`) e Implementação (`.c`)**:

* **Fase 1 — MVP Estático (Base Atual):** Implementação funcional do fluxo completo utilizando vetores estáticos e programação modular. Permite que toda a equipe valide regras de negócio e interface CLI imediatamente.
* **Fase 2 — Modelagem Avançada e Persistência:** Refatoração dos dados primitivos para `structs`, `enums` (níveis de risco e status) e `unions` (documentos mutuamente exclusivos), além da implementação da gravação e leitura em disco (`data/`).
* **Fase 3 — Estruturas Dinâmicas e Ponteiros:** Substituição interna dos vetores estáticos em `estruturas.c` por alocação dinâmica (`malloc`/`free`) e estruturas clássicas, mantendo inalterada a interface consumida pelo `main.c` e `ui.c`.

---

## 3. Estrutura de Diretórios e Módulos

```text
sistema-triagem-hospitalar/
├── include/               # Contratos públicos (.h) — assinaturas e constantes
│   ├── paciente.h         # Regras de validação e exibição de entidades
│   ├── estruturas.h       # Gerenciamento de memória e fluxo da triagem
│   ├── arquivo.h          # Persistência e recuperação de dados em disco
│   └── ui.h               # Interface de linha de comando (CLI) e I/O
├── src/                   # Implementações privadas (.c)
│   ├── main.c             # Orquestrador do ciclo de vida da aplicação
│   ├── paciente.c
│   ├── estruturas.c
│   ├── arquivo.c
│   └── ui.c
├── data/                  # Diretório de armazenamento local (.dat / .txt)
├── docs/                  # Documentação arquitetural e diagramas
├── Makefile               # Automação de build, execução e análise de memória
└── Dockerfile             # Ambiente padronizado (GCC 13 + Make)
```

---

## 4. Responsabilidade dos Módulos e Fluxo de Dependências

O acoplamento entre os módulos segue uma hierarquia unidirecional para evitar dependências circulares:

```text
   [ main.c ]
       │
       ├──► [ ui.h / ui.c ] ──────────┐
       │                              ▼
       ├──► [ arquivo.h / .c ] ──► [ estruturas.h / .c ] ──► [ paciente.h / .c ]
```

### Detalhamento por Camada

1. **Camada de Domínio (`paciente.h` / `paciente.c`)**
   * **Papel:** Define as constantes de prioridade (`RISCO_VERMELHO` a `RISCO_AZUL`), estados do paciente (`STATUS_AGUARDANDO`, `STATUS_EM_ATENDIMENTO`, `STATUS_ATENDIDO`), validação de integridade dos dados e formatação de saída individual.
   * **Evolução:** Receberá a `struct Paciente`, `enum NivelRisco` e `union Documento` na Fase 2.

2. **Camada de Estruturas e Regras de Negócio (`estruturas.h` / `estruturas.c`)**
   * **Papel:** Encapsula o armazenamento em memória e as regras de movimentação de pacientes (cadastro, busca por ID, chamada por prioridade e finalização).
   * **Mapeamento das Estruturas de Dados (Fase 3):**
     * **Fila de Prioridade:** Ordem de chegada dentro de cada nível de urgência (FIFO por risco).
     * **Pilha (LIFO):** Histórico de ações recentes para operação de *Desfazer (Undo)* na triagem.
     * **Lista Encadeada:** Controle dinâmico de pacientes em observação/leitos.
     * **Árvore Binária de Busca (ABB):** Indexação por ID/documento para consulta rápida ($O(\log n)$) de prontuários já atendidos.

3. **Camada de Persistência (`arquivo.h` / `arquivo.c`)**
   * **Papel:** Isola operações de entrada e saída em disco (`fopen`, `fread`/`fwrite`, `fprintf`/`fscanf`), garantindo que o estado do sistema seja preservado entre execuções e gerando relatórios legíveis na pasta `data/`.

4. **Camada de Interface (`ui.h` / `ui.c`)**
   * **Papel:** Gerencia menus, leitura segura do teclado (`fgets` / limpeza de buffer) e exibição de mensagens ao operador. Não manipula diretamente vetores ou ponteiros de dados; comunica-se exclusivamente via funções de `estruturas.h`.

5. **Ponto de Entrada (`main.c`)**
   * **Papel:** Inicializa o sistema, carrega dados prévios (quando disponível), mantém o laço principal de controle de opções e garante o salvamento e liberação de memória (`free`) antes do encerramento.

---

## 5. Fluxo de Trabalho da Equipe (Git & Padrões)

Para garantir estabilidade durante o desenvolvimento paralelo:

* **Proteção da `main`:** Nenhum commit direto é realizado na branch principal. Toda alteração entra via **Pull Request (PR)** após verificação de compilação limpa.
* **Nomenclatura de Branches:**
  * `feature/<modulo-ou-tarefa>` (ex: `feature/ui-menu`, `feature/mvp-vetores`)
  * `fix/<descricao-curta>` (ex: `fix/buffer-leitura-nome`)
  * `docs/<assunto>` (ex: `docs/diagrama-fluxo`)
* **Padrão de Código e Qualidade:**
  * Compilação obrigatória sem warnings sob `-Wall -Wextra -std=c11`.
  * Nomes de funções prefixados pelo módulo (`triagem_`, `paciente_`, `ui_`, `arquivo_`) para evitar colisões no linker.
  * Toda alocação dinâmica (`malloc`/`calloc`) na Fase 3 deve possuir liberação correspondente (`free`) validada via `make memcheck` (Valgrind).