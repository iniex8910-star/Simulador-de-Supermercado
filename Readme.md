Simulador de Supermercado
Descrição do sistema

Programa em C++ de console que simula um supermercado. O operador cadastra e remove produtos do catálogo, busca produtos por código, monta o carrinho de um cliente, coloca o cliente na fila do caixa e atende os clientes na ordem de chegada. Também é possível ver o catálogo ordenado por preço. Todas as estruturas de dados foram implementadas à mão, com new e delete.

Tema escolhido

Supermercado: catálogo de produtos, carrinho de compras e fila de caixa.

Menu

1 Cadastrar produto
2 Remover produto
3 Listar catalogo
4 Buscar produto pela lista
5 Adicionar ao carrinho
6 Desfazer ultimo item do carrinho
7 Ver carrinho
8 Buscar produto pela arvore
9 Entrar na fila
10 Atender proximo cliente da fila
11 Ordenar catalogo por preco (Bubble Sort)
0 Sair

Estruturas de dados utilizadas

Catalogo (cada produto fica nas duas estruturas):
Lista encadeada: noLista -> noLista -> ... -> null
Arvore binaria de busca: noArvore (esquerda e direita), chave = codigo

Carrinho (Pilha, LIFO):
topo -> noPilha -> noPilha -> ... -> null

Caixa (Fila, FIFO):
inicio -> noFila -> noFila -> ... -> fim

Fluxo:
Lista (opcao 5, copia o produto) -> Pilha
Pilha (opcao 9, soma o total e esvazia o carrinho) -> Fila
Lista (opcao 11, copia para ordenar) -> vetor temporario -> Bubble Sort

Por que cada uma:
Lista: catalogo que cresce e encolhe, mantem a ordem de cadastro.
Arvore: busca por codigo mais rapida que na lista (O(log n) em media).
Pilha: desfazer o ultimo item do carrinho (o ultimo que entrou sai primeiro).
Fila: atender os clientes na ordem de chegada (o primeiro que entrou sai primeiro).

Como compilar e executar

g++ -std=c++11 -o supermercado supermercado.cpp
./supermercado

Divisão de responsabilidades

Daniel: (funções, ponteiros, memória dinâmica, lista, pilha e fila)
Wilson: (árvore binária de busca)
Matheus Renan: (algoritmo de ordenação)
Hermano: (algoritmo de busca)

Onde cada requisito está no código

Funções: cada função tem uma responsabilidade só. Passagem por valor em mostrarProduto, por referência em desempilhar e desenfileirar, e parâmetro default em carregando.
Ponteiros: nós ligados por proximo, esquerda e direita; estruturas passadas por ponteiro (Lista*, Pilha*, Fila*, Arvore*); uso de & no main ao chamar executarOpcao.
Recursividade: inserirNaArvore, buscarNaArvore, removerDaArvore, liberarArvore, contarRecursivo e somarRecursivo.
Memória dinâmica: new em inserirNaLista, empilhar, enfileirar e inserirNaArvore; delete nas funções de remoção e nas funções liberar.
Lista: inserirNaLista, removerDaLista, listarCatalogo e buscarNaLista.
Pilha: empilhar, desempilhar e listarCarrinho.
Fila: enfileirar, desenfileirar, finalizarCompra e atenderCliente.
Árvore: inserirNaArvore, buscarNaArvore e removerDaArvore.
Ordenação: bubbleSort e ordenarCatalogo.
Busca: buscarNaLista (sequencial) e buscarNaArvore.




Documento
https://docs.google.com/document/d/1Xc2E42nuHv5BGsV6y1LQtEmxCnofKH-derM4wf-ttYQ/edit?usp=sharing