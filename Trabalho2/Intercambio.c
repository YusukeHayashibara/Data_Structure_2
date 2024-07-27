#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
    char nome[100];
    float media;
    int numRep; // número de reprovações.
};
typedef struct Aluno Aluno;

// Função para ler os dados de entrada, como média, nome e número de reprovações.
void lerDados(int numAplica, Aluno **alunos) {
    *alunos = (Aluno*)malloc(numAplica * sizeof(Aluno));
    if (*alunos == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < numAplica; i++){
        scanf("%f", &(*alunos)[i].media);
        scanf("%d", &(*alunos)[i].numRep);
        scanf("%s", (*alunos)[i].nome);
    }
}

//insertion sort (opcao 1)...
void InsertionSort(Aluno *lista, int tamanho) {
    int i, j;
    Aluno chave;

    for(i = 1; i < tamanho; i++) {
        chave = lista[i];
        j = i - 1;
        
        // faz comparações dos alunos seguindo os critérios: maior média, menor num de reprovações e por fim ordem alfabética.
        while (j >= 0 && (lista[j].media < chave.media || (lista[j].media == chave.media && lista[j].numRep > chave.numRep)
        || (lista[j].media == chave.media && lista[j].numRep == chave.numRep && strcmp(lista[j].nome, chave.nome) > 0))) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = chave;
    }
}

// Função para trocar dois elementos
void troca(Aluno *a1, Aluno *a2) {
    Aluno temp = *a1;
    *a1 = *a2;
    *a2 = temp;
}

// ordena heap
void heapify(Aluno *lista, int n, int i) {
    int maior = i; 
    int esq = 2*i + 1, dir = 2* i + 2; 

    // verificação dos filhos, com os critérios de ordenação
    if (esq < n && 
        (lista[esq].media < lista[maior].media || 
         (lista[esq].media == lista[maior].media && lista[esq].numRep > lista[maior].numRep) ||
         (lista[esq].media == lista[maior].media && lista[esq].numRep == lista[maior].numRep && strcmp(lista[esq].nome, lista[maior].nome) > 0)))
        maior = esq;

    if (dir < n && 
        (lista[dir].media < lista[maior].media || 
         (lista[dir].media == lista[maior].media && lista[dir].numRep > lista[maior].numRep) ||
         (lista[dir].media == lista[maior].media && lista[dir].numRep == lista[maior].numRep && strcmp(lista[dir].nome, lista[maior].nome) > 0)))
        maior = dir;

    // Se o maior não é o pai, troca com o pai
    if (maior != i) {
        troca(&lista[i], &lista[maior]);
        heapify(lista, n, maior);
    }
}

//HeapSort (opção 2)...
void heapSort(Aluno *lista, int n) {
    // heap inicial
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(lista, n, i);

    // tira o elemento da raíz e repete o processo recursivamente.
    for (int i = n - 1; i > 0; i--) {
        troca(&lista[0], &lista[i]);
        heapify(lista, i, 0);
    }
}

// Retorna o número de alunos que foram selecionados para a bolsa
int numSelecionados(Aluno *lista, int numVaga, int tamanho) {
    int cont = 0;
    int i = 0;

    if (numVaga < tamanho) {
        //primeira checagem para ver se o aluno nao possui mais de 10 reprovações.
        while (cont < numVaga && i < tamanho) {
            if (lista[i].numRep <= 10)
                //add contador para ver quantos estao sendo selecionados
                cont++;
            i++;    
        }
        int j = i;
        i = i - 1;
        //checando caso em que o último que foi aprovado tem a mesma nota que o próximo, se sim, ambos devem ser chamados
        //repete isso até não ter mais ninguém com as mesmas notas.
        while (j < tamanho && lista[i].media == lista[j].media && lista[i].numRep == lista[j].numRep) {
            j++;
            cont++;
        }
    }
    //caso em que o número de aplicações é menor que o número de vagas
    //caso isso ocorra, o programa deve selecionar todos os inscritos, exceto aqueles que possuem mais
    // que dez reprovações.
    else {
        while (cont < tamanho && i < tamanho) {
            if (lista[i].numRep <= 10)
                cont++;
            i++;
        }
    }

    return cont;
}

//funcao para imprimir os alunos selecionados.
void imprimeSelecionados(Aluno *lista, int numSelecionados) {
    int cont = 0;
    int i = 0;
    while (cont < numSelecionados) {
        if (lista[i].numRep <= 10) {
            printf("%s\n", lista[i].nome);
            cont++;
        }
        i++;
    }
}

int main (){
    Aluno *alunos;
    int option;    // método de ordenação escolhida.
    int numAplica; // número de alunos que aplicaram a bolsa.
    int numVaga;   // número de vagas.
    int numSelecionado;

    scanf("%d", &option);
    scanf("%d", &numAplica);
    scanf("%d", &numVaga);

    // Verifique se o número de vagas é válido
    if (numVaga <= 0) {
        printf("Número de vagas inválido.\n");
        return 1;
    }

    // Chamada da função para ler os dados dos alunos
    lerDados(numAplica, &alunos);

    // Verificar a opção escolhida
    if(option == 1) { // Insertion Sort
        InsertionSort(alunos, numAplica);
        numSelecionado = numSelecionados(alunos, numVaga, numAplica);
        printf("%d\n", numSelecionado);
        imprimeSelecionados(alunos, numSelecionado);
    } else if(option == 2) { // Heap Sort
        heapSort(alunos, numAplica);
        numSelecionado = numSelecionados(alunos, numVaga, numAplica);
        printf("%d\n", numSelecionado);
        imprimeSelecionados(alunos, numSelecionado);
    } else {
        printf("Nenhuma opção foi escolhida.\n");
    }

    free(alunos); // Liberar memória alocada dinamicamente

    return 0;
}
