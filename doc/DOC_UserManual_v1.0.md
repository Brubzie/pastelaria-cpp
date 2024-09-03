# Documentação do Projeto: Pastelaria do seu Zé

## Introdução

Este projeto é um sistema de controle de pedidos para a **Pastelaria do seu Zé**, implementado em C++ com o uso de estruturas de dados para gerenciar uma lista de pedidos. O sistema permite cadastrar, editar, exibir e remover pedidos, além de verificar a disponibilidade de ingredientes necessários para a preparação dos pastéis.

## Estrutura do Código

### Inclusão de Bibliotecas

O código inclui várias bibliotecas padrão do C++ e um arquivo de cabeçalho personalizado:

- **iostream**: Para operações de entrada e saída.
- **cstdlib**: Para funções utilitárias gerais.
- **locale**: Para configurar a localização e usar caracteres acentuados em português.
- **fstream**: Para operações com arquivos (criação de relatório).
- **string**: Para manipulação de strings.
- **limits**: Para definir limites nas operações de entrada.
- **HEADER_PASTELARIA.h**: Arquivo de cabeçalho que contém a declaração das funções e estruturas utilizadas.

### Estruturas de Dados

O projeto utiliza as seguintes estruturas de dados:

1. **Ingredientes**: Estrutura que define os ingredientes disponíveis na pastelaria.
2. **Pedido**: Estrutura que armazena as informações de um pedido (nome do cliente, senha, quantidade de pastéis e refrigerantes).
3. **Node**: Estrutura que representa um nó na lista de pedidos.
4. **ListaPedidos**: Estrutura que representa a lista encadeada de pedidos.

### Funções Principais

#### Protótipos de Funções

- **limpar**: Limpa a tela do console.
- **pausar**: Pausa a execução do programa para o usuário visualizar informações.
- **inicializar**: Inicializa a lista de pedidos.
- **destruir**: Libera a memória alocada pela lista de pedidos.
- **verificarIngredientes**: Verifica se há ingredientes suficientes para preparar os pastéis.
- **usarIngredientes**: Deduz os ingredientes usados na preparação dos pastéis.
- **cadastrarPedido**: Cadastra um novo pedido na lista.
- **editarPedido**: Edita as informações de um pedido existente.
- **removerPedido**: Remove um pedido da lista após a entrega.
- **mostrarPedidos**: Exibe todos os pedidos cadastrados.

### Fluxo Principal do Programa

O programa começa configurando a localidade para português (pt_BR.UTF-8) e inicializando a lista de pedidos. Ele, então, apresenta um menu com as seguintes opções:

1. **Cadastrar Pedido**: Permite ao usuário cadastrar um novo pedido, verificando a disponibilidade de ingredientes.
2. **Editar Pedido**: Permite editar um pedido existente na lista.
3. **Mostrar Pedidos**: Exibe todos os pedidos cadastrados.
4. **Pedido Entregue**: Remove um pedido da lista após a entrega.
5. **Sair**: Encerra o programa, liberando os recursos utilizados.

### Exemplo de Uso

Ao executar o programa, o usuário verá o menu com as opções acima. Para cadastrar um pedido, o usuário deve inserir o número correspondente e fornecer as informações solicitadas, como o nome do cliente e as quantidades de pastéis e refrigerantes. O sistema verificará se há ingredientes suficientes para preparar o pedido antes de confirmá-lo.

### Tratamento de Erros

O programa inclui verificações de entrada para garantir que as opções do menu sejam válidas. Se o usuário inserir uma opção inválida, o programa exibirá uma mensagem de erro e solicitará uma nova entrada.

### Finalização

Quando o usuário escolhe a opção "Sair", o programa libera os recursos alocados e encerra a execução com uma mensagem de despedida.