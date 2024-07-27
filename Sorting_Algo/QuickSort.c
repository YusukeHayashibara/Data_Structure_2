#include <stdio.h>

//Implementation of swap function to avoid repetition;
void swap (int *p1, int *p2){
    int aux;
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

//return the correct position of pivot;
int partition(int *array, int low, int high){
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high; j++){
        if (array[j] < pivot){
            i++;
            swap(&array[j], &array[i]);
        }
    }
    swap (&array[i + 1], &array[high]);
    return(i + 1);
}

void quickSort(int *array, int low, int high){
    if(low < high){
        int pivot = partition(array, low, high);

        //sorting recursively;
        quickSort(array, pivot + 1, high);
        quickSort(array, low, pivot - 1);
    }
}

int main() {
    
    int array[7] = {0, 7, 389, 78, 400, 12, 90};

    quickSort(array, 0, 6);

    for (int i = 0; i < 7; i++) {
        printf("%d  ", array[i]);
    }

    return 0;
}
