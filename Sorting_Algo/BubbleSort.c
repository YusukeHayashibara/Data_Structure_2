#include <stdio.h>

void bubbleSort(int *array, int newSize) {
    int aux, count;

    while (newSize > 1) {
        // counting how many swaps occured in each interaction.
        //so if the count in the interaction of swap is equal 
        //to zero in the end, it means that the array is alredy sorted.
        count = 0;
        for (int i = 0; i < newSize - 1; i++) {
            if (array[i] > array[i + 1]) {
                aux = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
                count++;
            }
        }
        //decreasing the size of array, to avoid unnecessaray camparisons,
        //because during each interaction the greatest number will already be in the 
        //end of the array.
        newSize--;
        if (count == 0) {
            return; 
        }
    }
}

int main() {
    //example
    int array[7] = {0, 7, 389, 78, 3, 12, 90};

    bubbleSort(array, 7);

    for (int i = 0; i < 7; i++) {
        printf("%d  ", array[i]);
    }

    return 0;
}
