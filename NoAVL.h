#include <iostream>
#include <string>

class NoAVL {
public:
    int codigoProduto;
    std::string nome;
    int qtde;
    float valorUnitario;
    int altura; // A altura é necessária para verificar o balanceamento da árvore AVL
    NoAVL* esquerda;
    NoAVL* direita;

    NoAVL(int codigo, std::string nomeProduto, int quantidade, float valor) {
        codigoProduto = codigo;
        nome = nomeProduto;
        qtde = quantidade;
        valorUnitario = valor;
        altura = 1; // Inicialmente, a altura de um nó é 1
        esquerda = nullptr;
        direita = nullptr;
    }
};


