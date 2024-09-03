// Importando bibliotecas/módulos
#include <iostream>
#include <cstdlib>
#include <locale.h> // Para definir a linguagem pt-br
#include <fstream>  // Para criar o relatório dentro de um arquivo .txt
#include <string>
#include <limits>
#include "../include/HEADER_PASTELARIA.hh" // Puxando o arquivo de cabeçalho do arquivo

using namespace std;

// Protótipo de Função
struct Ingredientes;
struct Pedido;
struct Node;
struct ListaPedidos;
void inicializar(ListaPedidos *);
void destruir(ListaPedidos *);
bool verificarIngredientes(ListaPedidos *, int, int, int);
void usarIngredientes(ListaPedidos *, int, int, int);
void cadastrarPedido(ListaPedidos *, Pedido *);
void editarPedido(ListaPedidos *, int);
void removerPedido(ListaPedidos *, int);
void mostrarPedidos(ListaPedidos *);

int main()
{
    /* Linguagem: Pt-Br */
    setlocale(LC_ALL, "portuguese");

    ios::sync_with_stdio(false);

    int menu = 0;
    char confirma;

    ListaPedidos listaPedidos;
    inicializar(&listaPedidos);

    // Cardápio
    cout << "Seja Bem-Vindo à Pastelaria do Zé!\n"
         << "__________________________________\n"
         << "|      Cardápio dos Pastéis      |\n"
         << "| Sabores:                       |\n"
         << "|                                |\n"
         << "| 1. Pizza:                      |\n"
         << "| Massa, 30 gramas de queijo, 30 |\n"
         << "| gramas de presunto, duas fatias|\n"
         << "| de tomate e orégano.           |\n"
         << "|                                |\n"
         << "| 2. Queijo:                     |\n"
         << "| Massa, 50 gramas de queijo.    |\n"
         << "|                                |\n"
         << "| 3. Frango:                     |\n"
         << "| Massa, 50 gramas de frango.    |\n"
         << "|                                |\n"
         << "| Vento:                         |\n"
         << "| Somente massa, sem recheio.    |\n"
         << "|________________________________|\n";

    do {
        // Menu
        cout << "_____________________________\n"
             << "| ========== Menu ========= |\n"
             << "| 1 - Cadastrar Pedido      |\n"
             << "| 2 - Editar Pedido         |\n"
             << "| 3 - Mostrar Pedidos       |\n"
             << "| 4 - Pedido Entregue       |\n"
             << "| 5 - Sair                  |\n"
             << "|___________________________|\n"
             << "Opção: ";

        while (!(cin >> menu)) {
            cout << "[ERRO] Informe uma opção válida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        }

        switch (menu) {
            case 1: {
                Pedido novoPedido;

                cout << "Senha: ";
                cin >> novoPedido.senhaDoPedido;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Informe o nome do cliente: ";
                getline(cin, novoPedido.nomeDoCliente); // Pode ser informado o nome completo do cliente

                int quantidadePizza, quantidadeQueijo, quantidadeFrango, quantidadeVento;

                cout << "Pastéis de pizza comprados: ";
                cin >> quantidadePizza;

                cout << "Pastéis de queijo comprados: ";
                cin >> quantidadeQueijo;

                cout << "Pastéis de frango comprados: ";
                cin >> quantidadeFrango;

                cout << "Pastéis de vento comprados: ";
                cin >> quantidadeVento;

                if (verificarIngredientes(&listaPedidos, quantidadePizza * 30, quantidadeQueijo * 50, quantidadeFrango * 30 + quantidadeVento * 30)) {
                    usarIngredientes(&listaPedidos, quantidadePizza * 30, quantidadeQueijo * 50, quantidadeFrango * 30 + quantidadeVento * 30);
                    novoPedido.pasteisDePizza = quantidadePizza;
                    novoPedido.pasteisDeQueijo = quantidadeQueijo;
                    novoPedido.pasteisDeFrango = quantidadeFrango;
                    novoPedido.pasteisDeVento = quantidadeVento;
                } else {
                    cout << "\n[ERRO] Ingredientes insuficientes para fazer os Pastéis!\n";
                }

                cout << "Informe a quantidade de Coca-Cola comprada: ";
                cin >> novoPedido.refriCoca;

                cout << "Informe a quantidade de Pepsi comprada: ";
                cin >> novoPedido.refriPepsi;

                cadastrarPedido(&listaPedidos, &novoPedido);
            } break;

            case 2: {
                int senha;

                cout << "Informe a senha do pedido que deseja editar: ";
                cin >> senha;

                editarPedido(&listaPedidos, senha);
            } break;

            case 3: {
                mostrarPedidos(&listaPedidos);
            } break;

            case 4: {
                int senhaEntregue;

                cout << "Informe a senha do pedido entregue: ";
                cin >> senhaEntregue;

                removerPedido(&listaPedidos, senhaEntregue);
            } break;

            case 5: {
                cout << "Deseja mesmo encerrar o programa e destruir a lista de pedidos? (S/N)\nOpção: ";
                cin >> confirma;

                if (confirma == 's' || confirma == 'S')
                {
                    destruir(&listaPedidos);
                    cout << "\nLista de pedidos destruida com sucesso!\n";
                    cout << "Volte sempre à Pastelaria do Zé!\nEncerrando...";

                    return 0;
                }
                else if (confirma == 'n' || confirma == 'N')
                {
                    break;
                }
                else
                {
                    cout << "[ERRO] Opção inválida!\n";
                }
            } break;

            default: {
                cout << "[ERRO] Informe uma opção válida!\n";
                cout << "Na tela 'menu', selecione uma opção entre 1 e 5.\n";
            } break;
        }
    } while (true);

    return 0;
}