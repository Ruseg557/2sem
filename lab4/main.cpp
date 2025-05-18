#include <stdio.h>  // printf, scanf
#include <conio.h>  // getch
#include <cmath>   // fabs, pow, ceil, log, exp, sqrt
#include <cstdlib> // randomize, rand
#include <windows.h> // SetConsoleOutputCP(1251); SetConsoleCP(1251);

const double xx[7] = {0.00001, -0.99, -1, -0.1, 0.1, 1, 0.99};

int main()
{
    int n, i, k, z;
    double e, sl, sum, f, *x;
    SetConsoleOutputCP(CP_UTF8);
    srand(0);

    printf("Введите e=? ");
    scanf("%lf", &e);
    if (e < 1e-13 || e > 0.11) {
        printf("Некорректная точность e (0..0.1]! \nPress any key");
        getch();
        return 0;
    }
    fflush(stdin);

    printf("Введите n=? ");
    scanf("%d", &n);
    if (n < 1 || n > 20) {
        printf("Некорректное количество n [1..20]! \nPress any key");
        getch();
        return 0;
    }
    fflush(stdin);

    x = new double[n];

    printf("Введите %d значений X из интервала (-1,+1):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%lf", &x[i]);

        if (fabs(x[i]) >= 1) {
            x[i] = xx[rand() % 7];
            if (fabs(x[i]) == 1) {
                x[i] = x[i] * (rand() % 100) / 100;
                if (x[i] == 0) x[i] = e;
            }
            printf("Некорректное значение заменено на %15.10lf\n", x[i]);
        }
    }

    z = ceil(fabs(log(e) / log(10.0))) + 1;

    printf("e = %*.*lf\n", z + 2, z, e);
    printf(" N |        X         |      Sum(X)      |  K   |       F(X)       |  Sum(X)-F(X)\n");
    for (i = 1; i < 88; i++) printf("=");
    printf("\n");

    for (i = 0; i < n; i++) {
        // Вычисление суммы ряда
        sum = sl = x[i] / 2;  // Первое слагаемое
        k = 2;

        while (fabs(sl) >= e && k != 1000) {
            sl *= -1 * x[i] * (2 * k - 1) / (2 * k);
            sum += sl;
            k++;
        }

        f = (1 - 1 / sqrt(1 + x[i]));  // Контрольная сумма

        printf("%2d |%17.*lf |%17.*lf |%5d |%17.*lf |%17.*lf\n",
               i + 1, z, x[i], z, sum, k, z, f, z, fabs(sum - f));
    }

    delete[] x;

    printf("Нажмите любую клавиш у - Press any key");
    getch();
    return 0;
}
