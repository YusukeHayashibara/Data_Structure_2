#include <stdio.h>

void countingSort(int* array, int tamanho){
    int min, max;
    min = array[0];
    max = array[0];
    for(int i = 1; i < tamanho; i++){
        if (array[i] < min)
            min = array[i];
        if (array[i] > max)
            max = array[i];    
    }

    int auxArray[max - min + 1];

    for(int i = 0; i <= max - min; i++){
        auxArray[i] = 0;
    }

    for(int i = 0; i < tamanho; i++){
        auxArray[array[i] - min]++;
    }

    int index = 0;
    for(int i = 0; i < max - min + 1; i++){
        while(auxArray[i] > 0){
            array[index++] = i + min; // Restore the original value by adding min
            auxArray[i]--; // Decrease the count
        }
    }
}

int main() {
    // Example array
    int array[7] = {0, 7, 389, 78, 3, 12, 90};
    long tamanho = sizeof(array) / sizeof(array[0]);

    // Perform Counting Sort
    countingSort(array, tamanho);

    // Print sorted array
    printf("Sorted array: ");
    for (long i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
