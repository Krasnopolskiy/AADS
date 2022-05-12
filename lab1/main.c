#include "stdio.h"
#include "stdlib.h"

#include "lib/vector.h"
#include "lib/matrix.h"
#include "lib/io_utils.h"

int sum_digits(int n) {
    n = abs(n);
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main()
{
    int m = scan_size("m: ");
    matrix src, res;
    matrix_init(&src, m);
    matrix_init(&res, m);

    matrix_scan(&src);

    for (int i = 0; i < m; i++) {
        vector current = src.rows[i];
        int last = sum_digits(current.data[current.used - 1]);

        for (int j = 0; j < current.used; j++)
            if (sum_digits(current.data[j]) == last)
                vector_push(&res.rows[i], current.data[j]);
    }

    printf("Source matrix:\n");
    matrix_print(&src);
    printf("Result matrix:\n");
    matrix_print(&res);

    matrix_free(&src);
    matrix_free(&res);
    return 0;
}