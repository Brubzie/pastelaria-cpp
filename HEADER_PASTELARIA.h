#ifndef HEADER_PASTELARIA
#define HEADER_PASTELARIA

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Funções
void limpar() {
    #ifdef _WIN32 // <= Identifica se o SO utilizado é Windows
        system("cls");
    #else // Caso não seja, ele executará o seguinte comando
        system("clear");
    #endif
}

void pausar() {
    #ifdef _WIN32 // <= Identifica se o SO utilizado é Windows
        system("pause");
    #else // Caso não seja, ele executará o seguinte comando
        cout << "Pressione ENTER para continuar...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    #endif
}


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
    Node* proximo;
    Node* anterior;
};

struct ListaPedidos {
    Node* primeiro;
    Node* ultimo;
    int tamanho;
    Ingredientes ingredientesDisponiveis;
};

void inicializar(ListaPedidos* lista) {
    lista->primeiro = nullptr;
    lista->ultimo = nullptr;
    lista->tamanho = 0;

    // Ingredientes dos PastÃ©is
    lista->ingredientesDisponiveis.queijo = 50000; // 50kg
    lista->ingredientesDisponiveis.presunto = 20000; // 20kg
    lista->ingredientesDisponiveis.frango = 10000; // 10kg
}

void destruir(ListaPedidos* lista) {
    while (lista->primeiro != nullptr) {
        Node* aux = lista->primeiro;
        lista->primeiro = lista->primeiro->proximo;
        delete aux;
    }

    lista->ultimo = nullptr;
    lista->tamanho = 0;
}

bool verificarIngredientes(ListaPedidos* lista, int queijo, int presunto, int frango) {
    // Verifica se hÃ¡ ingredientes o suficiente
    return (lista->ingredientesDisponiveis.queijo >= queijo &&
            lista->ingredientesDisponiveis.presunto >= presunto &&
            lista->ingredientesDisponiveis.frango >= frango);
}

void usarIngredientes(ListaPedidos* lista, int queijo, int presunto, int frango) {
    // Subtrair os ingredientes utilizados
    lista->ingredientesDisponiveis.queijo -= queijo;
    lista->ingredientesDisponiveis.presunto -= presunto;
    lista->ingredientesDisponiveis.frango -= frango;
}

void cadastrarPedido(ListaPedidos* lista, Pedido* pedido) {
    Node* novo = new Node{ *pedido, nullptr, nullptr };

    if (lista->primeiro == nullptr) {
        lista->primeiro = novo;
        lista->ultimo = novo;
    } else {
        lista->ultimo->proximo = novo;
        novo->anterior = lista->ultimo;
        lista->ultimo = novo;
    }

    lista->tamanho++;

    cout << endl << "Pedido cadastrado com sucesso!" << endl;

    pausar();
}

void editarPedido(ListaPedidos* lista, int senha) {
    Node* atual = lista->primeiro;

    while (atual != nullptr && atual->pedido.senhaDoPedido != senha) {
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << endl << "[ERRO] Pedido nÃ£o encontrado!" << endl;
        pausar();
        return; // Retorna se 'atual' Ã© nulo
    }

    lista->ingredientesDisponiveis.massa += (atual->pedido.pasteisDePizza + atual->pedido.pasteisDeQueijo + atual->pedido.pasteisDeFrango + atual->pedido.pasteisDeVento) * 30;
    lista->ingredientesDisponiveis.queijo += atual->pedido.pasteisDeQueijo * 50;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    cout << "==== EdiÃ§Ã£o do Pedido ====" << endl;
    cout << "Informe o novo nome do cliente: ";
    getline(cin, atual->pedido.nomeDoCliente);

    int quantidadePizza, quantidadeQueijo, quantidadeFrango, quantidadeVento;

    cout << "PastÃ©is de pizza comprados: ";
    cin >> quantidadePizza;
    
    cout << "PastÃ©is de queijo comprados: ";
    cin >> quantidadeQueijo;
    
    cout << "PastÃ©is de frango comprados: ";
    cin >> quantidadeFrango;
    
    cout << "PastÃ©is de vento comprados: ";
    cin >> quantidadeVento;

    // Calcular a quantidade total de cada ingrediente
    int totalMassa = quantidadePizza * 30 + quantidadeQueijo * 50;
    int totalQueijo = quantidadeQueijo * 50;
    int totalFrango = quantidadeFrango * 30 + quantidadeVento * 30;

    if (verificarIngredientes(lista, totalMassa, totalQueijo, totalFrango)) {
        usarIngredientes(lista, totalMassa, totalQueijo, totalFrango);
    } else {
        cout << endl << "[ERRO] Ingredientes insuficientes!" << endl;
    }

    cout << "Informe a nova quantidade de Coca-Cola comprada: ";
    cin >> atual->pedido.refriCoca;

    cout << "Informe a nova quantidade de Pepsi comprada: ";
    cin >> atual->pedido.refriPepsi;

    cout << endl << "Pedido editado com sucesso!" << endl;

    pausar();
}

void removerPedido(ListaPedidos* lista, int senha) {
    Node* atual = lista->primeiro;

    while (atual != nullptr && atual->pedido.senhaDoPedido != senha) {
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "[ERRO] Pedido nÃ£o encontrado!" << endl;
        return; // Retorna se 'atual' Ã© nulo
    }

    // Adicionar os ingredientes utilizados de volta
    lista->ingredientesDisponiveis.massa += (atual->pedido.pasteisDePizza + atual->pedido.pasteisDeQueijo + atual->pedido.pasteisDeFrango + atual->pedido.pasteisDeVento) * 30;
    lista->ingredientesDisponiveis.queijo += atual->pedido.pasteisDeQueijo * 50;

    // Remover o pedido da lista
    if (atual->anterior != nullptr) {
        atual->anterior->proximo = atual->proximo;
    } else {
        lista->primeiro = atual->proximo;
    }

    if (atual->proximo != nullptr) {
        atual->proximo->anterior = atual->anterior;
    } else {
        lista->ultimo = atual->anterior;
    }

    delete atual;
    lista->tamanho--;

    cout << endl << "Pedido entregue removido com sucesso!" << endl;

    pausar();
}

void mostrarPedidos(ListaPedidos* lista) {
    Node* atual = lista->primeiro;

    ofstream arquivo;

    try {
        arquivo.open("pedidos.txt");
        if(!arquivo) {
            throw runtime_error("NÃ£o foi possÃ­vel abrir o arquivo.");
        }
        // InformaÃ§Ãµes do arquivo
        arquivo << "==== Pedidos ====" << endl;

        if (atual != nullptr) {
            while (atual != nullptr) {
                arquivo << "Senha do Pedido: " << atual->pedido.senhaDoPedido << endl;
                arquivo << "Cliente: " << atual->pedido.nomeDoCliente << endl;
                arquivo << "Quantidade de PastÃ©is de Pizza: " << atual->pedido.pasteisDePizza << endl;
                arquivo << "Quantidade de PastÃ©is de Queijo: " << atual->pedido.pasteisDeQueijo << endl;
                arquivo << "Quantidade de PastÃ©is de Frango: " << atual->pedido.pasteisDeFrango << endl;
                arquivo << "Quantidade de PastÃ©is de Vento: " << atual->pedido.pasteisDeVento << endl;
                arquivo << "Quantidade de Coca-Cola: " << atual->pedido.refriCoca << endl;
                arquivo << "Quantidade de Pepsi: " << atual->pedido.refriPepsi << endl << endl;

                atual = atual->proximo;  
            }
        } else {
            arquivo << "[ERRO] A lista de pedidos estÃ¡ vazia!" << endl;
            arquivo << "Selecione a opÃ§Ã£o 1 no menu, para cadastrar seu pedido." << endl;
        }

        arquivo.close();
    } catch(const exception& e) {
        cerr << "ERRO: " << e.what() << endl;
    }

    // Redefinir 'atual' para o inÃ­cio da lista
    atual = lista->primeiro;

    cout << "==== Pedidos ====" << endl;

    if (atual != nullptr) {
        while (atual != nullptr) {
            cout << "Cliente: " << atual->pedido.nomeDoCliente << endl;
            cout << "Quantidade de PastÃ©is de Pizza: " << atual->pedido.pasteisDePizza << endl;
            cout << "Quantidade de PastÃ©is de Queijo: " << atual->pedido.pasteisDeQueijo << endl;
            cout << "Quantidade de PastÃ©is de Frango: " << atual->pedido.pasteisDeFrango << endl;
            cout << "Quantidade de PastÃ©is de Vento: " << atual->pedido.pasteisDeVento << endl;
            cout << "Quantidade de Coca-Cola: " << atual->pedido.refriCoca << endl;
            cout << "Quantidade de Pepsi: " << atual->pedido.refriPepsi << endl << endl;

            atual = atual->proximo;  
        }
    } else {
        cout << "[ERRO] A lista de pedidos estÃ¡ vazia!" << endl;
        cout << "Selecione a opÃ§Ã£o 1 no menu, para cadastrar seu pedido." << endl;
    }

    if (atual != nullptr) cout << "RelatÃ³rio de pedidos criado com sucesso!" << endl;

    pausar();
}

#endif
