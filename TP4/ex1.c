#include <stdio.h>

void printAddresses(int tab[], int size) {
    printf("Addresses of array elements:\n");
    for (int i = 0; i < size; i++) {
        printf("&tab[%d] = %p\n", i, (void*)&tab[i]);
    }
}

void printSize(int* tab) {
    printf("Size of array: %zu bytes\n", sizeof(tab));
}

int main() {
    int tab[] = {1, 2, 3, 4, 5};

    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of tab: %zu bytes\n", sizeof(tab));

    printAddresses(tab, sizeof(tab) / sizeof(tab[0]));
    printSize(tab);
    printf("%d\n", tab);

    printf("%p\n", tab);

    return 0;
}
