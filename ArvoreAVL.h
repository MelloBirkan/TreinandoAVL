#pragma once
#include <string>
#include "NoAVL.h"

class ArvoreAVL {
private:
    NoAVL* raiz;

    NoAVL* inserir(NoAVL* no, int codigo, std::string nome, int qtde, float valorUnitario);
    NoAVL* rotacaoDireita(NoAVL* y);
    NoAVL* rotacaoEsquerda(NoAVL* x);
    int obterAltura(NoAVL* no);
    int obterFatorBalanceamento(NoAVL* no);
    void percursoEmOrdem(NoAVL* no);
    NoAVL* buscarProdutoPorNome(NoAVL* no, const std::string& nomeProduto);

public:
    ArvoreAVL();

    void inserir(int codigo, std::string nome, int qtde, float valorUnitario);
    void apresentarProdutos();
    void calcularValorEmEstoque(const std::string& nomeProduto);
};
