#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <limits>
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

struct noFila {
    string cliente;
    double total;
    noFila* proximo;
};

struct Fila {
    noFila* inicio;
    noFila* fim;
};

struct noArvore {
    Produto* produto;
    noArvore* esquerda;
    noArvore* direita;
};

struct Arvore {
    noArvore* raiz;
};


noArvore* inserirNaArvore(noArvore* raiz, Produto p) {
    if (raiz == nullptr) {
        noArvore* novo = new noArvore;
        novo->produto = new Produto;
        *novo->produto = p;
        novo->esquerda = nullptr;
        novo->direita = nullptr;
        return novo;
    }
    if (p.codigo < raiz->produto->codigo) {
        raiz->esquerda = inserirNaArvore(raiz->esquerda, p);
    } else if (p.codigo > raiz->produto->codigo) {
        raiz->direita = inserirNaArvore(raiz->direita, p);
    }
    return raiz;
}

noArvore* buscarNaArvore(noArvore* raiz, int codigo) {
    if (raiz == nullptr) return nullptr;
    if (codigo == raiz->produto->codigo) return raiz;
    if (codigo < raiz->produto->codigo) {
        return buscarNaArvore(raiz->esquerda, codigo);
    }
    return buscarNaArvore(raiz->direita, codigo);
}

noArvore* removerDaArvore(noArvore* raiz, int codigo) {
    if (raiz == nullptr) return nullptr;
    if (codigo < raiz->produto->codigo) {
        raiz->esquerda = removerDaArvore(raiz->esquerda, codigo);
    } else if (codigo > raiz->produto->codigo) {
        raiz->direita = removerDaArvore(raiz->direita, codigo);
    } else {
        if (raiz->esquerda == nullptr || raiz->direita == nullptr) {
            noArvore* filho = raiz->esquerda ? raiz->esquerda : raiz->direita;
            delete raiz->produto;
            delete raiz;
            return filho;
        }
        noArvore* sucessor = raiz->direita;
        while (sucessor->esquerda != nullptr) sucessor = sucessor->esquerda;
        *raiz->produto = *sucessor->produto;
        raiz->direita = removerDaArvore(raiz->direita, sucessor->produto->codigo);
    }
    return raiz;
}

void liberarArvore(noArvore* raiz) {
    if (raiz == nullptr) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    delete raiz->produto;
    delete raiz;
}


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
    if (atual == nullptr) return false;
    if (anterior == nullptr) {
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    delete atual->produto;
    delete atual;
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
    if (no == nullptr) return 0;
    return 1 + contarRecursivo(no->proximo);
}

void liberarLista(Lista* lista) {
    while (lista->cabeca != nullptr) {
        noLista* remover = lista->cabeca;
        lista->cabeca = remover->proximo;
        delete remover->produto;
        delete remover;
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
    if (pilha->topo == nullptr) return false;
    noPilha* no = pilha->topo;
    removido = *no->produto;
    pilha->topo = no->proximo;
    delete no->produto;
    delete no;
    return true;
}

double somarRecursivo(noPilha* no) {
    if (no == nullptr) return 0;
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


void enfileirar(Fila* fila, string cliente, double total) {
    noFila* novo = new noFila;
    novo->cliente = cliente;
    novo->total = total;
    novo->proximo = nullptr;
    if (fila->fim == nullptr) {
        fila->inicio = novo;
    } else {
        fila->fim->proximo = novo;
    }
    fila->fim = novo;
}

bool desenfileirar(Fila* fila, string& cliente, double& total) {
    if (fila->inicio == nullptr) return false;
    noFila* no = fila->inicio;
    cliente = no->cliente;
    total = no->total;
    fila->inicio = no->proximo;
    if (fila->inicio == nullptr) {
        fila->fim = nullptr;
    }
    delete no;
    return true;
}

void liberarFila(Fila* fila) {
    string cliente;
    double total;
    while (desenfileirar(fila, cliente, total)) {
    }
}


void finalizarCompra(Pilha* carrinho, Fila* fila) {
    if (carrinho->topo == nullptr) {
        cout << "Carrinho vazio.\n";
        return;
    }
    string nome;
    cout << "Nome do cliente: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nome);
    enfileirar(fila, nome, somarRecursivo(carrinho->topo));
    liberarPilha(carrinho);
    cout << nome << " entrou na fila do caixa.\n";
}

void atenderCliente(Fila* fila) {
    string cliente;
    double total;
    if (desenfileirar(fila, cliente, total)) {
        cout << "Atendido: " << cliente << " - total R$ " << total << endl;
    } else {
        cout << "Ninguem na fila.\n";
    }
}


Produto* catalogoParaVetor(Lista* lista, int n) {
    Produto* v = new Produto[n];
    noLista* atual = lista->cabeca;
    int i = 0;
    while (atual != nullptr) {
        v[i] = *atual->produto;
        i++;
        atual = atual->proximo;
    }
    return v;
}

 
void bubbleSort(Produto* v, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].preco > v[j + 1].preco) {
                Produto temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                trocou = true;
            }
        }
        if (!trocou) break;
    }
}

 
void ordenarCatalogo(Lista* catalogo) {
    int n = contarRecursivo(catalogo->cabeca);
    if (n == 0) {
        cout << "Catalogo vazio.\n";
        return;
    }
    Produto* v = catalogoParaVetor(catalogo, n);
    bubbleSort(v, n);
    cout << "--- Catalogo ordenado por preco ---\n";
    for (int i = 0; i < n; i++) {
        mostrarProduto(v[i]);
    }
    delete[] v;
}


void buscarProdutoNoCatalogo(Lista* catalogo) {
    int codigo;
    cout << "Digite o codigo do produto que deseja buscar: ";
    if (!(cin >> codigo)) return;

    noLista* resultado = buscarNaLista(catalogo, codigo);

    if (resultado != nullptr) {
        cout << "\nProduto encontrado com sucesso!\n";
        mostrarProduto(*resultado->produto);
    } else {
        cout << "\nNenhum produto encontrado com o codigo " << codigo << ".\n";
    }
}

void cadastrarProduto(Lista* catalogo, Arvore* arvore) {
    Produto p;
    cout << "Codigo: ";
    if (!(cin >> p.codigo)) return;
    if (buscarNaLista(catalogo, p.codigo) != nullptr) {
        cout << "Ja existe produto com esse codigo.\n";
        return;
    }
    cout << "Nome: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, p.nome);
    cout << "Preco: ";
    string entrada;
    getline(cin, entrada);
    replace(entrada.begin(), entrada.end(), ',', '.');
    stringstream conversao(entrada);
    char extra;
    if (!(conversao >> p.preco) || p.preco < 0 || (conversao >> extra)) {
        cout << "Preco invalido.\n";
        return;
    }
    inserirNaLista(catalogo, p);
    arvore->raiz = inserirNaArvore(arvore->raiz, p);
    cout << "Produto cadastrado.\n";
}

void removerProduto(Lista* catalogo, Arvore* arvore) {
    int codigo;
    cout << "Codigo a remover: ";
    if (!(cin >> codigo)) return;
    if (removerDaLista(catalogo, codigo)) {
        arvore->raiz = removerDaArvore(arvore->raiz, codigo);
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
    if (!(cin >> codigo)) return;
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

void buscarProdutoNaArvore(Arvore* arvore) {
    int codigo;
    cout << "Codigo do produto: ";
    if (!(cin >> codigo)) return;
    noArvore* resultado = buscarNaArvore(arvore->raiz, codigo);
    if (resultado != nullptr) mostrarProduto(*resultado->produto);
    else cout << "Produto nao encontrado.\n";
}


void adicionarExemplo(Lista* catalogo, Arvore* arvore, int codigo, string nome, double preco) {
    Produto p;
    p.codigo = codigo;
    p.nome = nome;
    p.preco = preco;
    inserirNaLista(catalogo, p);
    arvore->raiz = inserirNaArvore(arvore->raiz, p);
}

void carregarExemplos(Lista* catalogo, Arvore* arvore) {
    adicionarExemplo(catalogo, arvore, 30, "Arroz 5kg", 24.90);
    adicionarExemplo(catalogo, arvore, 10, "Feijao 1kg", 8.50);
    adicionarExemplo(catalogo, arvore, 50, "Leite 1L", 5.20);
    adicionarExemplo(catalogo, arvore, 20, "Macarrao", 4.75);
    adicionarExemplo(catalogo, arvore, 40, "Cafe 500g", 16.90);
    adicionarExemplo(catalogo, arvore, 60, "Acucar 1kg", 5.40);
}


void exibirMenu() {
    cout << "\n===== SUPERMERCADO =====\n";
    cout << "1 Cadastrar produto\n";
    cout << "2 Remover produto\n";
    cout << "3 Listar catalogo\n";
    cout << "4 Buscar produto pela lista\n";
    cout << "5 Adicionar ao carrinho\n";
    cout << "6 Desfazer ultimo item do carrinho\n";
    cout << "7 Ver carrinho\n";
    cout << "8 Buscar produto pela arvore\n";
    cout << "9 Entrar na fila com os itens do carrinho\n";
    cout << "10 Atender proximo cliente da fila\n";
    cout << "11 Ordenar catalogo por preco (Bubble Sort)\n";
    cout << "0 Sair\n";
}

void executarOpcao(int opcao, Lista* catalogo, Pilha* carrinho, Arvore* arvore, Fila* fila) {
    if (opcao == 1) cadastrarProduto(catalogo, arvore);
    else if (opcao == 2) removerProduto(catalogo, arvore);
    else if (opcao == 3) mostrarCatalogo(catalogo);
    else if (opcao == 4) buscarProdutoNoCatalogo(catalogo);
    else if (opcao == 5) adicionarAoCarrinho(catalogo, carrinho);
    else if (opcao == 6) desfazerUltimoItem(carrinho);
    else if (opcao == 7) listarCarrinho(carrinho);
    else if (opcao == 8) buscarProdutoNaArvore(arvore);
    else if (opcao == 9) finalizarCompra(carrinho, fila);
    else if (opcao == 10) atenderCliente(fila);
    else if (opcao == 11) ordenarCatalogo(catalogo);
    else if (opcao == 0) cout << "Ate logo!\n";
    else cout << "Opcao invalida.\n";
}

int main() {
    Lista catalogo = {nullptr};
    Pilha carrinho = {nullptr};
    Arvore arvore = {nullptr};
    Fila fila = {nullptr, nullptr};
    int opcao;

    cout << fixed << setprecision(2);
    carregando("Iniciando sistema", 5);
    carregarExemplos(&catalogo, &arvore);

    do {
        exibirMenu();
        cout << "Opcao: ";
        cin >> opcao;
        if (cin.eof()) break;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcao = -1;
        }
        carregando();
        executarOpcao(opcao, &catalogo, &carrinho, &arvore, &fila);
    } while (opcao != 0);

    liberarArvore(arvore.raiz);
    arvore.raiz = nullptr;
    liberarLista(&catalogo);
    liberarPilha(&carrinho);
    liberarFila(&fila);
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
