#pragma once
#include <string>

class NoAVL {
public:
    int codigoProduto;
    std::string nome;
    int qtde;
    float valorUnitario;
    int altura;
    NoAVL* esquerda;
    NoAVL* direita;

    NoAVL(int codigo, std::string nomeProduto, int quantidade, float valor);
};
