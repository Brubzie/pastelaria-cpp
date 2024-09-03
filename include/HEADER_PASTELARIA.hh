#ifndef HEADER_PASTELARIA_HH
#define HEADER_PASTELARIA_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Estruturas
struct Ingredientes {
    int massa;
    int queijo;
    int presunto;
    int tomate;
    int frango;
};

struct Pedido {
    string nomeDoCliente;
    int senhaDoPedido;
    int pasteisDePizza;
    int pasteisDeQueijo;
    int pasteisDeFrango;
    int pasteisDeVento;
    int refriCoca;
    int refriPepsi;
};

struct Node {
    Pedido pedido;
    Node *proximo;
    Node *anterior;
};

struct ListaPedidos {
    Node *primeiro;
    Node *ultimo;
    int tamanho;
    Ingredientes ingredientesDisponiveis;
};

// Funções
inline void inicializar(ListaPedidos *lista) {
    lista->primeiro = nullptr;
    lista->ultimo = nullptr;
    lista->tamanho = 0;

    // Ingredientes dos Pastéis
    lista->ingredientesDisponiveis.queijo = 50000;   // 50kg
    lista->ingredientesDisponiveis.presunto = 20000; // 20kg
    lista->ingredientesDisponiveis.frango = 10000;   // 10kg
}

inline void destruir(ListaPedidos *lista) {
    while (lista->primeiro != nullptr)
    {
        Node *aux = lista->primeiro;
        lista->primeiro = lista->primeiro->proximo;
        delete aux;
    }

    lista->ultimo = nullptr;
    lista->tamanho = 0;
}

inline bool verificarIngredientes(ListaPedidos *lista, int queijo, int presunto, int frango) {
    // Verifica se há ingredientes o suficiente
    return (lista->ingredientesDisponiveis.queijo >= queijo &&
            lista->ingredientesDisponiveis.presunto >= presunto &&
            lista->ingredientesDisponiveis.frango >= frango);
}

inline void usarIngredientes(ListaPedidos *lista, int queijo, int presunto, int frango) {
    // Subtrair os ingredientes utilizados
    lista->ingredientesDisponiveis.queijo -= queijo;
    lista->ingredientesDisponiveis.presunto -= presunto;
    lista->ingredientesDisponiveis.frango -= frango;
}

inline void cadastrarPedido(ListaPedidos *lista, Pedido *pedido) {
    Node *novo = new Node{*pedido, nullptr, nullptr};

    if (lista->primeiro == nullptr)
    {
        lista->primeiro = novo;
        lista->ultimo = novo;
    }
    else
    {
        lista->ultimo->proximo = novo;
        novo->anterior = lista->ultimo;
        lista->ultimo = novo;
    }

    lista->tamanho++;

    cout << "\nPedido cadastrado com sucesso!\n";
}

inline void editarPedido(ListaPedidos *lista, int senha) {
    Node *atual = lista->primeiro;

    while (atual != nullptr && atual->pedido.senhaDoPedido != senha)
    {
        atual = atual->proximo;
    }

    if (atual == nullptr)
    {
        cout << "\n[ERRO] Pedido não encontrado!\n";
        return; // Retorna se 'atual' é nulo
    }

    lista->ingredientesDisponiveis.massa += (atual->pedido.pasteisDePizza + atual->pedido.pasteisDeQueijo + atual->pedido.pasteisDeFrango + atual->pedido.pasteisDeVento) * 30;
    lista->ingredientesDisponiveis.queijo += atual->pedido.pasteisDeQueijo * 50;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "==== Edição do Pedido ====\n";
    cout << "Informe o novo nome do cliente: ";
    getline(cin, atual->pedido.nomeDoCliente);

    int quantidadePizza, quantidadeQueijo, quantidadeFrango, quantidadeVento;

    cout << "Pastéis de pizza comprados: ";
    cin >> quantidadePizza;

    cout << "Pastéis de queijo comprados: ";
    cin >> quantidadeQueijo;

    cout << "Pastéis de frango comprados: ";
    cin >> quantidadeFrango;

    cout << "Pastéis de vento comprados: ";
    cin >> quantidadeVento;

    // Calcular a quantidade total de cada ingrediente
    int totalMassa = quantidadePizza * 30 + quantidadeQueijo * 50;
    int totalQueijo = quantidadeQueijo * 50;
    int totalFrango = quantidadeFrango * 30 + quantidadeVento * 30;

    if (verificarIngredientes(lista, totalMassa, totalQueijo, totalFrango))
    {
        usarIngredientes(lista, totalMassa, totalQueijo, totalFrango);
    }
    else
    {
        cout << '\n'
             << "[ERRO] Ingredientes insuficientes!\n";
    }

    cout << "Informe a nova quantidade de Coca-Cola comprada: ";
    cin >> atual->pedido.refriCoca;

    cout << "Informe a nova quantidade de Pepsi comprada: ";
    cin >> atual->pedido.refriPepsi;

    cout << '\n'
         << "Pedido editado com sucesso!\n";
}

inline void removerPedido(ListaPedidos *lista, int senha) {
    Node *atual = lista->primeiro;

    while (atual != nullptr && atual->pedido.senhaDoPedido != senha)
    {
        atual = atual->proximo;
    }

    if (atual == nullptr)
    {
        cout << "[ERRO] Pedido não encontrado!\n";
        return; // Retorna se 'atual' é nulo
    }

    // Adicionar os ingredientes utilizados de volta
    lista->ingredientesDisponiveis.massa += (atual->pedido.pasteisDePizza + atual->pedido.pasteisDeQueijo + atual->pedido.pasteisDeFrango + atual->pedido.pasteisDeVento) * 30;
    lista->ingredientesDisponiveis.queijo += atual->pedido.pasteisDeQueijo * 50;

    // Remover o pedido da lista
    if (atual->anterior != nullptr)
    {
        atual->anterior->proximo = atual->proximo;
    }
    else
    {
        lista->primeiro = atual->proximo;
    }

    if (atual->proximo != nullptr)
    {
        atual->proximo->anterior = atual->anterior;
    }
    else
    {
        lista->ultimo = atual->anterior;
    }

    delete atual;
    lista->tamanho--;

    cout << '\n'
         << "Pedido entregue removido com sucesso!\n";
}

inline void mostrarPedidos(ListaPedidos *lista) {
    Node *atual = lista->primeiro;

    ofstream arquivo;

    try
    {
        arquivo.open("pedidos.txt");
        if (!arquivo)
        {
            throw runtime_error("Não foi possível abrir o arquivo.");
        }
        // Informações do arquivo
        arquivo << "==== Pedidos ====\n";

        if (atual != nullptr)
        {
            while (atual != nullptr)
            {
                arquivo << "Senha do Pedido: " << atual->pedido.senhaDoPedido << '\n';
                arquivo << "Cliente: " << atual->pedido.nomeDoCliente << '\n';
                arquivo << "Quantidade de Pastéis de Pizza: " << atual->pedido.pasteisDePizza << '\n';
                arquivo << "Quantidade de Pastéis de Queijo: " << atual->pedido.pasteisDeQueijo << '\n';
                arquivo << "Quantidade de Pastéis de Frango: " << atual->pedido.pasteisDeFrango << '\n';
                arquivo << "Quantidade de Pastéis de Vento: " << atual->pedido.pasteisDeVento << '\n';
                arquivo << "Quantidade de Coca-Cola: " << atual->pedido.refriCoca << '\n';
                arquivo << "Quantidade de Pepsi: " << atual->pedido.refriPepsi << "\n";

                atual = atual->proximo;
            }
        }
        else
        {
            arquivo << "[ERRO] A lista de pedidos está vazia!\n";
            arquivo << "Selecione a opção 1 no menu, para cadastrar seu pedido.\n";
        }

        arquivo.close();
    }
    catch (const exception &e)
    {
        cerr << "ERRO: " << e.what() << '\n';
    }

    // Redefinir 'atual' para o início da lista
    atual = lista->primeiro;

    cout << "==== Pedidos ====" << '\n';

    if (atual != nullptr)
    {
        while (atual != nullptr)
        {
            cout << "Cliente: " << atual->pedido.nomeDoCliente << '\n';
            cout << "Quantidade de Pastéis de Pizza: " << atual->pedido.pasteisDePizza << '\n';
            cout << "Quantidade de Pastéis de Queijo: " << atual->pedido.pasteisDeQueijo << '\n';
            cout << "Quantidade de Pastéis de Frango: " << atual->pedido.pasteisDeFrango << '\n';
            cout << "Quantidade de Pastéis de Vento: " << atual->pedido.pasteisDeVento << '\n';
            cout << "Quantidade de Coca-Cola: " << atual->pedido.refriCoca << '\n';
            cout << "Quantidade de Pepsi: " << atual->pedido.refriPepsi << "\n\n";

            atual = atual->proximo;
        }
    }
    else
    {
        cout << "[ERRO] A lista de pedidos está vazia!\n";
        cout << "Selecione a opção 1 no menu, para cadastrar seu pedido.\n";
    }

    if (atual != nullptr)
        cout << "RelatÃ³rio de pedidos criado com sucesso!\n";
}

#endif