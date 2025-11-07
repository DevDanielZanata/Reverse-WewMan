# 🧩 WewMan — Engenharia Reversa / Análise de Crackme

Repositório com a documentação e os artefatos da análise do desafio **WewMan**. O objetivo foi entender o fluxo do binário, reconstruir as funções relevantes (XOR, operações de bytes) e reproduzir o algoritmo de validação do serial.

> Documentação base: `Documentação WewMan.pdf`. :contentReference[oaicite:0]{index=0}

---

## 📘 Descrição do Projeto

O desafio **WewMan** é um crackme que exige análise combinada (estática com IDA e dinâmica com debuggers) para identificar a rotina de verificação de serial. Nesta análise foram renomeadas funções, compreendidas operações de XOR e manipulações de bytes (LOBYTE / LOW BYTE), e reproduzida a lógica que gera a sequência final usada como serial.

---

## 🔍 Etapas da Análise (resumo)

### 1. Inspeção inicial da `_main`
- Começou-se pela `_main`, identificando diversas chamadas de função.
- A função extensa `sub_401470` foi renomeada para **ALOCAR** por aparentar tratar alocação de memória — porém foi deixada de lado temporariamente por sua complexidade.

### 2. Identificação do input mínimo
- A partir de um loop na `_main`, foi identificado que o programa exige **pelo menos 4 caracteres** no CMD para prosseguir. Logo, renomeou-se `v6` para **Input**.

### 3. Análise da função `XOR` (sub_4011A0 renomeada)
- A função XOR foi analisada e simplificada no papel para entender seu comportamento sobre cada caractere.
- Renomearam-se variáveis para facilitar leitura e documentação.

### 4. Recuperação da string/Referência `aCrakme1`
- A referência `aCrakme1` foi investigada e confirmada como referência a uma *string*.  
- Ao inspecionar essa referência, foi possível identificar a **chave original** embutida no binário.

### 5. Simplificação e reprodução
- A lógica da função foi traduzida e simplificada em steps práticos (XOR por par de caracteres) e validada com exemplos:
  - Exemplo de pares XOR:
    - `'d' ^ 'C' = 0x27`
    - `'a' ^ 'r' = 0x13`
    - `'n' ^ 'a' = 0x0F`
    - `'i' ^ 'c' = 0x0A`
    - `'e' ^ 'k' = 0x0E`
    - `'l' ^ 'M' = 0x21`
  - A palavra usada no exemplo: `daniel`.

### 6. Função `Operação` e LOBYTE
- A função `sub_401280` (renomeada para **Operação**) contém a etapa final de transformação dos bytes.
- O uso de `LOBYTE` e operações `& 0xF` foram estudados — resultando na conversão para nibble/hex e montagem do serial final.
- Após aplicar a transformação aos valores obtidos pelo XOR e preencher zeros à esquerda, a sequência final testada foi: `7 3 F A E 1` (em hexadecimal). Ao inserir a sequência com os zeros iniciais no campo de Serial, o crackme aceitou (Cracked).

---

## 🧪 Resultado prático

- Através da análise da função XOR e da aplicação dos passos de `Operação` (incluindo `LOBYTE` e o `& 0xF`), foi possível gerar a sequência final de serial (`7 3 F A E 1`) que valida o programa.
- Notou-se a importância de preencher os zeros à esquerda ao obter valores em hexadecimal antes de submeter.

---

## 🛠 Ferramentas e recursos usados

- IDA Pro — análise estática (renomeação de funções, exploração de referências).
- Debugger (x32dbg ou similar) — execução dinâmica e inspeção de registradores/stack.
- Pesquisa em fóruns (StackOverflow, MenteBinária) para compreender comportamentos de funções/idiomas C++ e macros como `LOBYTE`.
- Arquivo de documentação interno: `Documentação WewMan.pdf`. :contentReference[oaicite:1]{index=1}

---

## 📁 Estrutura sugerida do repositório

```
/
├─ docs/                # Documentação (Documentação WewMan.pdf)
├─ analysis/            # Notas, screenshots do IDA, logs do debugger
├─ src/                 # Código de reprodução / scripts de teste
├─ README.md            # Este arquivo
└─ LICENSE
```

---

## ⚠️ Avisos legais e éticos

- Este material destina-se a fins **educacionais** e de estudo de engenharia reversa.
- Não utilize técnicas de engenharia reversa para infringir direitos autorais ou violar sistemas sem autorização. Sempre obtenha permissão do proprietário do software.

---

## 🤝 Créditos / Agradecimentos

- **Daniel Zanata** — autor das anotações e repositório (GitHub: `Dani2116`).
- **Cestaro0** — instrução, mentoria e apoio durante o desafio; forneceu o crackme que serviu de base para esta análise. Agradecimento especial pela orientação técnica.
