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
    Matrix src, res;
    matrixInit(&src, m);
    matrixInit(&res, m);

    matrixScan(&src);

    for (int i = 0; i < m; i++) {
        Vector current = src.rows[i];
        int last = sum_digits(current.data[current.used - 1]);

        for (int j = 0; j < current.used; j++)
            if (sum_digits(current.data[j]) == last)
                vectorPush(&res.rows[i], current.data[j]);
    }

    printf("Source matrix:\n");
    matrixPrint(&src);
    printf("Result matrix:\n");
    matrixPrint(&res);

    matrixFree(&src);
    matrixFree(&res);
    return 0;
}
