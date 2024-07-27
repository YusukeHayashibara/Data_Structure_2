#include <stdio.h>

void ShellSort(int *array, int size){
    int i, j, h  = 1, aux;
    while(h < size/3){
        h = 3 * h + 1;
    }

    while(h > 0){
        for(i = h; i < size; i++){
            aux = array[i];
            j = i;
            while(j >= h && aux < array[j - h]){
                array[j] = array[j - h];
                j = j - h;
            }
            array[j] = aux;
        }
        h = (h - 1) / 3;
    }
}

int main() {
    //example
    int array[7] = {0, 7, 389, 78, 3, 12, 90};

    ShellSort(array, 7);

    for (int i = 0; i < 7; i++) {
        printf("%d  ", array[i]);
    }

    return 0;
}