# Pastelaria do seu Zé

Bem-vindo ao projeto **Pastelaria do seu Zé**, um sistema de controle de pedidos desenvolvido em C++. Este projeto foi criado para gerenciar os pedidos de uma pastelaria fictícia, permitindo o cadastro, edição, exibição e remoção de pedidos, além de verificar a disponibilidade de ingredientes necessários para a preparação dos pastéis.

## Funcionalidades

- **Cadastro de Pedidos**: Permite o registro de novos pedidos, incluindo informações sobre o cliente e os itens comprados.
- **Edição de Pedidos**: Permite a modificação de um pedido existente.
- **Exibição de Pedidos**: Exibe todos os pedidos registrados na lista.
- **Remoção de Pedidos**: Remove um pedido da lista após sua entrega.
- **Verificação de Ingredientes**: Confirma se há ingredientes suficientes para preparar os pastéis solicitados.

## Tecnologias Utilizadas

- **C++**: Linguagem principal utilizada para o desenvolvimento do sistema.
- **Arquivos de Cabeçalho (.h)**: Para modularização do código.
- **Manipulação de Strings e Arquivos**: Para gerenciar dados do cliente e gerar relatórios.

## Estrutura do Projeto

O projeto é organizado da seguinte forma:

- **main.cpp**: Arquivo principal do projeto, onde a lógica do menu e as interações com o usuário ocorrem.
- **include/HEADER_PASTELARIA.h**: Arquivo de cabeçalho que contém as definições das estruturas e funções utilizadas no projeto.
- **src/**: Diretório onde você pode colocar as implementações das funções definidas no arquivo de cabeçalho.

## Como Executar

1. Clone o repositório para a sua máquina local.
   ```bash
   git clone https://github.com/Brubzie/pastelaria-cpp
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd pastelaria-cpp
   ```
3. Compile o código:
   ```bash
   g++ -o pastelaria main.cpp -I include/
   ```
4. Execute o programa:
   ```bash
   ./pastelaria
   ```

## Uso

Após executar o programa, você será apresentado ao menu principal:

- **1 - Cadastrar Pedido**: Insira os detalhes do pedido, incluindo o nome do cliente e as quantidades de pastéis e refrigerantes.
- **2 - Editar Pedido**: Informe a senha do pedido que deseja editar.
- **3 - Mostrar Pedidos**: Exibe todos os pedidos cadastrados.
- **4 - Pedido Entregue**: Remova um pedido informando a senha correspondente.
- **5 - Sair**: Encerra o programa.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests para melhorias no projeto.

## Autor

<p align="center">
   <a href="https://github.com/Brubzie">
      <img src="https://avatars.githubusercontent.com/Brubzie" width="15%">
   </a>
</p>