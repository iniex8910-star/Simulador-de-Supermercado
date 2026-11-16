#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;
 

struct Produto {
    int codigo;
    string nome;
    double preco;
};
 
struct noPilha {
    Produto* produto;
    noPilha* proximo;
};
 
struct Pilha {
    noPilha* topo;
};
 
struct noLista {
    Produto* produto;
    noLista* proximo;
};
 
struct Lista {
    noLista* cabeca;
};
 

void pausar(int milissegundos) {
    clock_t inicio = clock();
    while (clock() - inicio < milissegundos * CLOCKS_PER_SEC / 1000) {
    }
}
 

void carregando(string mensagem = "Processando", int pontos = 3) {
    cout << mensagem;
    for (int i = 0; i < pontos; i++) {
        cout << "." << flush;
        pausar(400);
    }
    cout << endl;
}
 

void mostrarProduto(Produto p) {
    cout << "[" << p.codigo << "] " << p.nome << " - R$ " << p.preco << endl;
}
 

void inserirNaLista(Lista* lista, Produto p) {
    noLista* novo = new noLista;
    novo->produto = new Produto;
    *novo->produto = p;
    novo->proximo = nullptr;
 
    if (lista->cabeca == nullptr) {
        lista->cabeca = novo;
    } else {
        noLista* atual = lista->cabeca;
        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}
 

bool removerDaLista(Lista* lista, int codigo) {
    noLista* anterior = nullptr;
    noLista* atual = lista->cabeca;
 
    while (atual != nullptr && atual->produto->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == nullptr) {
        return false;
    }
    if (anterior == nullptr) {
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    delete atual->produto;
    delete atual;
    atual = nullptr;
    return true;
}
 

noLista* buscarNaLista(Lista* lista, int codigo) {
    noLista* atual = lista->cabeca;
    while (atual != nullptr && atual->produto->codigo != codigo) {
        atual = atual->proximo;
    }
    return atual;
}
 

void listarCatalogo(Lista* lista) {
    noLista* atual = lista->cabeca;
    while (atual != nullptr) {
        mostrarProduto(*atual->produto);
        atual = atual->proximo;
    }
}
 

int contarRecursivo(noLista* no) {
    if (no == nullptr) {
        return 0;
    }
    return 1 + contarRecursivo(no->proximo);
}
 
void liberarLista(Lista* lista) {
    while (lista->cabeca != nullptr) {
        noLista* remover = lista->cabeca;
        lista->cabeca = remover->proximo;
        delete remover->produto;
        delete remover;
        remover = nullptr;
    }
}
 

void empilhar(Pilha* pilha, Produto p) {
    noPilha* novo = new noPilha;
    novo->produto = new Produto;
    *novo->produto = p;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}
 

bool desempilhar(Pilha* pilha, Produto& removido) {
    if (pilha->topo == nullptr) {
        return false;
    }
    noPilha* no = pilha->topo;
    removido = *no->produto;
    pilha->topo = no->proximo;
    delete no->produto;
    delete no;
    no = nullptr;
    return true;
}
 

double somarRecursivo(noPilha* no) {
    if (no == nullptr) {
        return 0;
    }
    return no->produto->preco + somarRecursivo(no->proximo);
}
 

void listarCarrinho(Pilha* pilha) {
    noPilha* atual = pilha->topo;
    int itens = 0;
    while (atual != nullptr) {
        mostrarProduto(*atual->produto);
        itens++;
        atual = atual->proximo;
    }
    cout << "Itens: " << itens << " | Total: R$ "
         << somarRecursivo(pilha->topo) << endl;
}
 

void liberarPilha(Pilha* pilha) {
    Produto descartado;
    while (desempilhar(pilha, descartado)) {
    }
}
 

void cadastrarProduto(Lista* catalogo) {
    Produto p;
    cout << "Codigo: ";
    cin >> p.codigo;
    if (buscarNaLista(catalogo, p.codigo) != nullptr) {
        cout << "Ja existe produto com esse codigo.\n";
        return;
    }
    cout << "Nome: ";
    cin.ignore();
    getline(cin, p.nome);
    cout << "Preco: ";
    cin >> p.preco;
    inserirNaLista(catalogo, p);
    cout << "Produto cadastrado.\n";
}
 

void removerProduto(Lista* catalogo) {
    int codigo;
    cout << "Codigo a remover: ";
    cin >> codigo;
    if (removerDaLista(catalogo, codigo)) {
        cout << "Produto removido.\n";
    } else {
        cout << "Produto nao encontrado.\n";
    }
}
 

void mostrarCatalogo(Lista* catalogo) {
    cout << "--- Catalogo ---\n";
    listarCatalogo(catalogo);
    cout << "Total de produtos: " << contarRecursivo(catalogo->cabeca) << endl;
}
 

void adicionarAoCarrinho(Lista* catalogo, Pilha* carrinho) {
    int codigo;
    cout << "Codigo do produto: ";
    cin >> codigo;
    noLista* achado = buscarNaLista(catalogo, codigo);
    if (achado == nullptr) {
        cout << "Produto nao encontrado.\n";
        return;
    }
    empilhar(carrinho, *achado->produto);
    cout << "Adicionado ao carrinho: " << achado->produto->nome << endl;
}
 

void desfazerUltimoItem(Pilha* carrinho) {
    Produto removido;
    if (desempilhar(carrinho, removido)) {
        cout << "Removido do carrinho: " << removido.nome << endl;
    } else {
        cout << "Carrinho vazio.\n";
    }
}
 

void adicionarExemplo(Lista* catalogo, int codigo, string nome, double preco) {
    Produto p;
    p.codigo = codigo;
    p.nome = nome;
    p.preco = preco;
    inserirNaLista(catalogo, p);
}
 

void carregarExemplos(Lista* catalogo) {
    adicionarExemplo(catalogo, 30, "Arroz 5kg", 24.90);
    adicionarExemplo(catalogo, 10, "Feijao 1kg", 8.50);
    adicionarExemplo(catalogo, 50, "Leite 1L", 5.20);
    adicionarExemplo(catalogo, 20, "Macarrao", 4.75);
    adicionarExemplo(catalogo, 40, "Cafe 500g", 16.90);
    adicionarExemplo(catalogo, 60, "Acucar 1kg", 5.40);
}
 

void exibirMenu() {
    cout << "\n===== SUPERMERCADO =====\n";
    cout << "1 Cadastrar produto\n";
    cout << "2 Remover produto\n";
    cout << "3 Listar catalogo\n";
    cout << "4 Adicionar ao carrinho\n";
    cout << "5 Desfazer ultimo item do carrinho\n";
    cout << "6 Ver carrinho\n";
    cout << "0 Sair\n";
}
 

void executarOpcao(int opcao, Lista* catalogo, Pilha* carrinho) {
    if (opcao == 1) cadastrarProduto(catalogo);
    else if (opcao == 2) removerProduto(catalogo);
    else if (opcao == 3) mostrarCatalogo(catalogo);
    else if (opcao == 4) adicionarAoCarrinho(catalogo, carrinho);
    else if (opcao == 5) desfazerUltimoItem(carrinho);
    else if (opcao == 6) listarCarrinho(carrinho);
    else if (opcao == 0) cout << "Ate logo!\n";
    else cout << "Opcao invalida.\n";
}
 
int main() {
    Lista catalogo = {nullptr};
    Pilha carrinho = {nullptr};
    int opcao;
 
    cout << fixed << setprecision(2); 
    carregando("Iniciando sistema", 5);
    carregarExemplos(&catalogo);
 
    do {
        exibirMenu();
        cout << "Opcao: ";
        cin >> opcao;
        if (cin.fail()) { 
            cin.clear();
            cin.ignore(1000, '\n');
            opcao = -1;
        }
        carregando();
        executarOpcao(opcao, &catalogo, &carrinho);
    } while (opcao != 0);
 
    liberarLista(&catalogo);
    liberarPilha(&carrinho);
    return 0;
}
 