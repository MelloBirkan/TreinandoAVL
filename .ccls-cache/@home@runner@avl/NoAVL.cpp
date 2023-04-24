#include "NoAVL.h"

NoAVL::NoAVL(int codigo, std::string nomeProduto, int quantidade, float valor) {
    codigoProduto = codigo;
    nome = nomeProduto;
    qtde = quantidade;
    valorUnitario = valor;
    altura = 1;
    esquerda = nullptr;
    direita = nullptr;
}
