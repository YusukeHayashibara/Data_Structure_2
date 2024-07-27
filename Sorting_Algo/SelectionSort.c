#include <stdio.h>

void swap (int *p1, int *p2){
    int aux;

    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

void SelectionSort(int *array, int size){
    int i, j, min;

    for (i = 0; i < size - 1; i++){
        min = i;
        for (j = i + 1; j < size; j++){
            if(array[j] < array[min])
                min = j;
        }
        if(min != i)
            swap(&array[min], &array[i]);
    }
}

int main() {
    //example
    int array[7] = {0, 7, 389, 78, 3, 12, 90};

    SelectionSort(array, 7);

    for (int i = 0; i < 7; i++) {
        printf("%d  ", array[i]);
    }

    return 0;
}