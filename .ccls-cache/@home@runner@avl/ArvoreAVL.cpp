#include "ArvoreAVL.h"
#include <algorithm>
#include <iostream>

ArvoreAVL::ArvoreAVL() : raiz(nullptr) {}

int obterAltura(NoAVL *no) {
  if (no == nullptr) {
    return 0;
  }
  return no->altura;
}

int obterFatorBalanceamento(NoAVL *no) {
  return obterAltura(no->esquerda) - obterAltura(no->direita);
}

NoAVL *rotacaoDireita(NoAVL *y) {
  NoAVL *x = y->esquerda;
  NoAVL *T2 = x->direita;

  x->direita = y;
  y->esquerda = T2;

  y->altura = std::max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
  x->altura = std::max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;

  return x;
}

NoAVL *rotacaoEsquerda(NoAVL *x) {
  NoAVL *y = x->direita;
  NoAVL *T2 = y->esquerda;

  y->esquerda = x;
  x->direita = T2;

  x->altura = std::max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
  y->altura = std::max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;

  return y;
}

NoAVL *inserir(NoAVL *no, int codigo, std::string nome, int qtde,
               float valorUnitario) {
  if (no == nullptr) {
    return new NoAVL(codigo, nome, qtde, valorUnitario);
  }

  if (codigo < no->codigoProduto) {
    no->esquerda = inserir(no->esquerda, codigo, nome, qtde, valorUnitario);
  } else if (codigo > no->codigoProduto) {
    no->direita = inserir(no->direita, codigo, nome, qtde, valorUnitario);
  } else {
    return no;
  }

  no->altura =
      1 + std::max(obterAltura(no->esquerda), obterAltura(no->direita));

  int fatorBalanceamento = obterFatorBalanceamento(no);

  if (fatorBalanceamento > 1) {
    if (codigo < no->esquerda->codigoProduto) {
      return rotacaoDireita(no);
    } else {
      no->esquerda = rotacaoEsquerda(no->esquerda);
      return rotacaoDireita(no);
    }
  }

  if (fatorBalanceamento < -1) {
    if (codigo > no->direita->codigoProduto) {
      return rotacaoEsquerda(no);
    } else {
      no->direita = rotacaoDireita(no->direita);
      return rotacaoEsquerda(no);
    }
  }
  return no;
}
// Dentro da classe ArvoreAVL

void ArvoreAVL::percursoEmOrdem(NoAVL* no) {
    if (no == nullptr) {
        return;
    }

    percursoEmOrdem(no->esquerda);
    std::cout << "Código do produto: " << no->codigoProduto
              << ", Nome: " << no->nome
              << ", Quantidade: " << no->qtde
              << ", Valor unitário: " << no->valorUnitario << std::endl;
    percursoEmOrdem(no->direita);
}


void ArvoreAVL::apresentarProdutos() {
    std::cout << "Produtos em ordem crescente de código:" << std::endl;
    percursoEmOrdem(this->raiz);
    std::cout << std::endl;
}

NoAVL* ArvoreAVL::inserir(NoAVL* no, int codigo, std::string nome, int qtde, float valorUnitario) {
  raiz = inserir(raiz, codigo, nome, qtde, valorUnitario);
}

NoAVL* ArvoreAVL::buscarProdutoPorNome(NoAVL* no, const std::string& nomeProduto) {
    if (no == nullptr) {
        return nullptr;
    }

    if (no->nome == nomeProduto) {
        return no;
    }

    NoAVL* produtoEncontrado = buscarProdutoPorNome(no->esquerda, nomeProduto);
    if (produtoEncontrado != nullptr) {
        return produtoEncontrado;
    }
    return buscarProdutoPorNome(no->direita, nomeProduto);
}

void ArvoreAVL::calcularValorEmEstoque(const std::string& nomeProduto) {
    NoAVL* produto = buscarProdutoPorNome(this->raiz, nomeProduto);

  if (produto == nullptr) {
    std::cout << "Produto não encontrado." << std::endl;
    return;
  }

  float valorEmEstoque = produto->qtde * produto->valorUnitario;
  std::cout << "Código do produto: " << produto->codigoProduto
            << ", Nome: " << produto->nome << ", Quantidade: " << produto->qtde
            << ", Valor unitário: " << produto->valorUnitario
            << ", Valor em estoque: R$" << valorEmEstoque << std::endl;
}