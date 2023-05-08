
#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar os dados de um produto
typedef struct produto {
    int codigo; // código do produto
    char nome[50]; // nome do produto
    int quantidade; // quantidade em estoque
    float preco; // preço do produto
} produto;

// Função para ler os dados de um produto do teclado
produto ler_produto() {
    produto p;
    printf("Digite o codigo do produto: ");
    scanf("%d", &p.codigo);
    printf("Digite o nome do produto: ");
    scanf("%s", p.nome);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &p.quantidade);
    printf("Digite o preco do produto: ");
    scanf("%f", &p.preco);
    return p;
}

// Função para mostrar os dados de um produto na tela
void mostrar_produto(produto p) {
    printf("Codigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Quantidade: %d\n", p.quantidade);
    printf("Preco: %.2f\n", p.preco);
}

// Função para buscar um produto pelo código em um vetor de produtos
// Retorna o índice do produto no vetor, ou -1 se não encontrar
int buscar_produto(produto vetor[], int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (vetor[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Função para ordenar um vetor de produtos pelo código em ordem crescente
// Usa o algoritmo de seleção
void ordenar_produto(produto vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i; // índice do menor elemento
        for (int j = i + 1; j < n; j++) {
            if (vetor[j].codigo < vetor[min].codigo) {
                min = j;
            }
        }
        // troca o elemento na posição i pelo menor encontrado
        produto aux = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = aux;
    }
}

// Função para inserir um novo produto em um vetor de produtos
// Retorna o novo tamanho do vetor, ou -1 se não houver espaço
int inserir_produto(produto vetor[], int n, int max) {
    if (n == max) { // vetor cheio
        return -1;
    }
    produto p = ler_produto(); // lê o novo produto
    int pos = buscar_produto(vetor, n, p.codigo); // busca se já existe um produto com o mesmo código
    if (pos != -1) { // produto já existe
        printf("Erro: ja existe um produto com esse codigo.\n");
        return n;
    }
    vetor[n] = p; // insere o novo produto no final do vetor
    n++; // incrementa o tamanho do vetor
    ordenar_produto(vetor, n); // ordena o vetor pelo código
    return n;
}

// Função para remover um produto de um vetor de produtos pelo código
// Retorna o novo tamanho do vetor, ou -1 se não encontrar o produto
int remover_produto(produto vetor[], int n) {
    int codigo;
    printf("Digite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);
    int pos = buscar_produto(vetor, n, codigo); // busca a posição do produto no vetor
    
    if (pos == -1) { // produto não encontrado
        printf("Erro: nao existe um produto com esse codigo.\n");
        return n;
    }
    for (int i = pos; i < n - 1; i++) { // desloca os elementos à direita do produto removido uma posição para a esquerda
        vetor[i] = vetor[i + 1];
    }
    n--; // decrementa o tamanho do vetor
    return n;
}

// Função para mostrar todos os produtos de um vetor na tela
void mostrar_todos(produto vetor[], int n) {
    for (int i = 0;

    i < n; i++) { // percorre o vetor de produtos
        printf("Produto %d:\n", i + 1);
        mostrar_produto(vetor[i]); // mostra os dados do produto na posição i
        printf("\n");
    }
}

// Função para atualizar a quantidade em estoque de um produto pelo código
// Retorna 1 se a atualização foi bem sucedida, ou 0 se não encontrar o produto
int atualizar_quantidade(produto vetor[], int n) {
    int codigo, quantidade;
    printf("Digite o codigo do produto a ser atualizado: ");
    scanf("%d", &codigo);
    printf("Digite a nova quantidade em estoque: ");
    scanf("%d", &quantidade);
    int pos = buscar_produto(vetor, n, codigo); // busca a posição do produto no vetor
    if (pos == -1) { // produto não encontrado
        printf("Erro: nao existe um produto com esse codigo.\n");
        return 0;
    }
    vetor[pos].quantidade = quantidade; // atualiza a quantidade do produto na posição encontrada
    return 1;
}

// Função para mostrar o menu de opções do programa
void mostrar_menu() {
	printf("====== CONTROLE DE ESTOQUE ======	\n");
    printf("Escolha uma opcao:\n");
    printf("1 - Inserir um novo produto\n");
    printf("2 - Remover um produto pelo codigo\n");
    printf("3 - Mostrar todos os produtos\n");
    printf("4 - Atualizar a quantidade em estoque de um produto pelo codigo\n");
    printf("5 - Sair do programa\n");
}

// Função principal do programa
int main() {
    int opcao; // opção escolhida pelo usuário
    int n = 0; // número de produtos no vetor
    int max = 100; // capacidade máxima do vetor
    produto vetor[max]; // vetor de produtos

    do {
        mostrar_menu(); // mostra o menu de opções
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: // inserir um novo produto
                n = inserir_produto(vetor, n, max);
                if (n == -1) {
                    printf("Erro: nao ha espaco para inserir mais produtos.\n");
                } else {
                    printf("Produto inserido com sucesso.\n");
                }
                break;
            case 2: // remover um produto pelo código
                n = remover_produto(vetor, n);
                if (n == -1) {
                    printf("Erro: nao foi possivel remover o produto.\n");
                } else {
                    printf("Produto removido com sucesso.\n");
                }
                break;
            case 3: // mostrar todos os produtos
                mostrar_todos(vetor, n);
                break;
            case 4: // atualizar a quantidade em estoque de um produto pelo código
                if (atualizar_quantidade(vetor, n)) {
                    printf("Quantidade atualizada com sucesso.\n");
                } else {
                    printf("Erro: nao foi possivel atualizar a quantidade.\n");
                }
                break;
            case 5: // sair do programa
                printf("Obrigado por usar o programa. Ate mais!\n");
                break;
            default: // opção inválida
                printf("Erro: opcao invalida.\n");
                break;
        }
        printf("\n");
    } while (opcao != 5); // repete até o usuário escolher sair

    return 0;
}
