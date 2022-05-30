#include "stdio.h"
#include "stdlib.h"

#include "lib/io.h"
#include "lib/matrix.h"

int sum_digits(int n) {
    n = abs(n);
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    int m = scanSize("m: ");
    Matrix *src = matrixScan(m);
    Matrix *res = matrixInit(m);

    for (int i = 0; i < m; i++) {
        Vector *row = src->rows[i];
        int last = sum_digits(vectorLast(row));
        for (int j = 0; j < row->size; j++)
            if (sum_digits(row->data[j]) == last)
                vectorPush(res->rows[i], row->data[j]);
    }

    printf("Source matrix:\n");
    matrixPrint(src);
    printf("Result matrix:\n");
    matrixPrint(res);

    matrixFree(src);
    matrixFree(res);
    return 0;
}
