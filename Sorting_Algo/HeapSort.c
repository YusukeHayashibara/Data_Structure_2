#include <stdio.h>

// Define the type of elements in the array
typedef int elem;

// Define the structure of the list
typedef struct {
    elem *elementos; // Array of elements
    long tamanho;    // Size of the array
} lista;

void rearranja_heap(lista *l, long i, long tam_heap) {
    long fe, fd, mf;
    elem aux;

    // Identifying left and right children
    fe = (2 * i + 1 < tam_heap) ? 2 * i + 1 : -1;
    fd = (2 * i + 2 < tam_heap) ? 2 * i + 2 : -1;

    // If i is a leaf, terminate
    if (fe == -1)
        return;

    // Identifying the largest child
    mf = (fd == -1 || l->elementos[fe] > l->elementos[fd]) ? fe : fd;

    // If the value of node i is greater than or equal to the value of the largest child, terminate
    if (l->elementos[i] >= l->elementos[mf])
        return;

    // Swap element at position i with the largest child
    aux = l->elementos[i];
    l->elementos[i] = l->elementos[mf];
    l->elementos[mf] = aux;

    // Recursive call; rearrange starting from the position of the largest child
    rearranja_heap(l, mf, tam_heap); // Fix next level
}

void constroi_heap(lista *l) {
    for (long i = l->tamanho / 2 - 1; i >= 0; i--)
        rearranja_heap(l, i, l->tamanho);
}

void ordena_heap_sort(lista *l) {
    long tam_heap;
    elem aux;

    constroi_heap(l); // Build heap

    tam_heap = l->tamanho;
    while (tam_heap > 1) {
        // Swap root with last leaf
        aux = l->elementos[tam_heap - 1];
        l->elementos[tam_heap - 1] = l->elementos[0];
        l->elementos[0] = aux;
        tam_heap--; // Decrease heap
        rearranja_heap(l, 0, tam_heap);
    }
}

void heapSort(elem array[], long tamanho) {
    lista l;
    l.elementos = array;
    l.tamanho = tamanho;

    // Sort the array using heap sort
    ordena_heap_sort(&l);
}

int main() {
    // Example array
    elem array[7] = {0, 7, 389, 78, 3, 12, 90};
    long tamanho = sizeof(array) / sizeof(array[0]);

    // Perform Heap Sort
    heapSort(array, tamanho);

    // Print sorted array
    printf("Sorted array: ");
    for (long i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
