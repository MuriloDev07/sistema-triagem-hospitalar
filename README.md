# Sistema de Triagem e Atendimento Hospitalar (CLI)

Sistema de gerenciamento de triagem e atendimento médico de urgência desenvolvido em **Linguagem C (C11)** para a Unidade II das disciplinas de **Linguagem de Programação I** e **Laboratório de Programação I** (Ciência da Computação — UEPB).

O projeto simula um fluxo de pronto-atendimento baseado no **Protocolo de Manchester**, priorizando casos críticos sem perder a rastreabilidade, o histórico de atendimento e a integridade dos dados.

---

## 🎯 Funcionalidades e Arquitetura

O sistema foi projetado de forma modular (`include/` e `src/`) para evoluir incrementalmente até contemplar os principais recursos de gerenciamento de memória e estruturas de dados em C:

* **Classificação de Risco:** Priorização por níveis de urgência (`VERMELHO`, `AMARELO`, `VERDE`, `AZUL`).
* **Estruturas de Dados Aplicadas:**
  * **Fila de Prioridade:** Controle da ordem de atendimento respeitando a gravidade.
  * **Pilha (LIFO):** Histórico de operações recentes com suporte a *Desfazer (Undo)*.
  * **Lista Encadeada:** Gerenciamento dinâmico de pacientes em leitos de observação.
  * **Árvore Binária de Busca (ABB):** Indexação rápida ($O(\log n)$) de prontuários finalizados.
* **Persistência em Disco:** Salvamento e recuperação de registros na pasta `data/`.

Para detalhes completos sobre a divisão de módulos e o fluxo de evolução, consulte [`docs/arquitetura.md`](docs/arquitetura.md).

---

## 🛠️ Pré-requisitos

Para compilar e executar localmente, você precisará de:
* Compilador **GCC** (suporte ao padrão C11)
* **Make** *(opcional, mas recomendado)*
* **Docker** *(opcional, para execução em ambiente isolado)*

---

## 🚀 Como Compilar e Executar

### Opção 1: Usando Make (Linux / macOS / WSL)

```bash
# Compilar o projeto
make

# Compilar e executar o sistema
make run

# Limpar arquivos compilados (build/ e bin/)
make clean

# Ver todos os comandos disponíveis
make help
```

### Opção 2: Compilação Manual via GCC (Windows / Linux)

Caso não tenha o `make` instalado no seu sistema:

```bash
mkdir -p bin
gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o bin/triagem
./bin/triagem
```

### Opção 3: Usando Docker

Para garantir um ambiente padronizado independente do sistema operacional:

```bash
# Construir a imagem
docker build -t sistema-triagem .

# Executar em modo interativo persistindo a pasta data/
docker run -it --rm -v $(pwd)/data:/app/data sistema-triagem
```

---

## 🤝 Fluxo de Contribuição da Equipe

1. Crie uma nova branch a partir da `main`:
   ```bash
   git checkout -b feature/nome-da-sua-tarefa
   ```
2. Implemente e teste suas alterações garantindo compilação sem warnings (`make`).
3. Envie sua branch e abra um **Pull Request** para revisão antes do merge na `main`.

---

## 👥 Equipe

* **Murilo** — Arquitetura, Integração e Árvore de Busca (`estruturas.c` / CI)
* **Cauã Max** — Interface CLI e Pilha de Histórico (`ui.c` / `main.c` / `estruturas.c`)
* **Guilherme** — Filas de Prioridade e Listas Encadeadas (`estruturas.c`)
* **Bento** — Validações de Domínio e Persistência de Arquivos (`paciente.c` / `arquivo.c`)