#include "NoAVL.h" // Incluir a definição da classe NoAVL que criamos anteriormente
#include <iostream>
#include <string>

class ArvoreAVL {
private:
  NoAVL *raiz;

public:
  ArvoreAVL() : raiz(nullptr) {}

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

  void percursoEmOrdem(NoAVL *no) {
    if (no == nullptr) {
      return;
    }

    percursoEmOrdem(no->esquerda);
    std::cout << "Código do produto: " << no->codigoProduto
              << ", Nome: " << no->nome << ", Quantidade: " << no->qtde
              << ", Valor unitário: " << no->valorUnitario << std::endl;
    percursoEmOrdem(no->direita);
  }

  void apresentarProdutos() {
    std::cout << "Produtos em ordem crescente de código:" << std::endl;
    percursoEmOrdem(raiz);
    std::cout << std::endl;
  }

  void inserir(int codigo, std::string nome, int qtde, float valorUnitario) {
    raiz = inserir(raiz, codigo, nome, qtde, valorUnitario);
  }

  NoAVL *buscarProdutoPorNome(NoAVL *no, const std::string &nomeProduto) {
    if (no == nullptr) {
      return nullptr;
    }

    if (no->nome == nomeProduto) {
      return no;
    }

    NoAVL *produtoEncontrado = buscarProdutoPorNome(no->esquerda, nomeProduto);
    if (produtoEncontrado != nullptr) {
      return produtoEncontrado;
    }
    return buscarProdutoPorNome(no->direita, nomeProduto);
  }

  void calcularValorEmEstoque(const std::string &nomeProduto) {
    NoAVL *produto = buscarProdutoPorNome(raiz, nomeProduto);

    if (produto == nullptr) {
      std::cout << "Produto não encontrado." << std::endl;
      return;
    }

    float valorEmEstoque = produto->qtde * produto->valorUnitario;
    std::cout << "Código do produto: " << produto->codigoProduto
              << ", Nome: " << produto->nome
              << ", Quantidade: " << produto->qtde
              << ", Valor unitário: " << produto->valorUnitario
              << ", Valor em estoque: R$" << valorEmEstoque << std::endl;
  }
};

int main() {
  ArvoreAVL arvore;
  int codigo;
  std::string nome;
  int qtde;
  float valorUnitario;

  std::cout << "Digite o código do produto: ";
  std::cin >> codigo;
  std::cin.ignore(); // Ignora o '\n' após o input numérico

  std::cout << "Digite o nome do produto: ";
  std::getline(std::cin, nome);

  std::cout << "Digite a quantidade do produto: ";
  std::cin >> qtde;

  std::cout << "Digite o valor unitário do produto: ";
  std::cin >> valorUnitario;

  std::string nomeProduto;
  std::cin.ignore(); // Ignora o '\n' após o último input numérico
  std::cout << "Digite o nome do produto para calcular o valor em estoque: ";
  std::getline(std::cin, nomeProduto);

  arvore.calcularValorEmEstoque(nomeProduto);

  arvore.inserir(codigo, nome, qtde, valorUnitario);
  arvore.apresentarProdutos();

  return 0;
}
