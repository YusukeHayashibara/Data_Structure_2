#include <stdio.h>


void InsertionSort(int* array, int size){
    int i, j, key;

    for(i = 0; i < size; i++){
        key = array[i];
        j = i - 1;
        ///while key is greater, it swap unyil the end;
        while(j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int main() {
    
    int array[7] = {0, 7, 389, 78, 3, 12, 90};

    InsertionSort(array, 7);

    for (int i = 0; i < 7; i++) {
        printf("%d  ", array[i]);
    }
    return 0;
}