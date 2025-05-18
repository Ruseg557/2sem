#include <cstdio>
#include <cmath>
#include <windows.h>

/*
 * Kadri RF A-09-24
 * Variant 16
 *  f1 №16 (sin(x) + cos(x))^2 / 33.5^(2/3) + (3/7)^(1/2) - x = 0.846395
 *  f2 №19 ( 1 - (1/4) * x^2 )^(1/2) + 4e^(-x-1.5) - (2/3) - x = 0.70816
 *
 *  Метод деления пополам
 *  Метод хорд
 */

using namespace std;

double f1(double x) {
    return pow((sin(x) + cos(x)), 2) / pow(33.5, (2.0/3.0)) + pow((3.0/7.0),(1.0/2.0)) - x;
}

double f2(double x) {
    return pow((1 - (1.0/4.0) * pow(x,2)),(1.0/2.0)) + 4 * exp(-x-1.5) - (2.0/3.0) - x;
}

double Bisection(double (*func)(double), double a, double b, double eps, int &iterations) {
    iterations = 0;
    double x;
    do {
        x = (a + b) / 2;
        if (func(a) * func(x) < 0)
            b = x;
        else
            a = x;
        iterations++;
    } while ((b - a) >= eps);
    return (a + b) / 2;
}

double Chords(double f(double), double a, double b, double eps, int &iterations) {
    iterations = 0;
    while(fabs(b - a) > eps) {
        iterations++;
        a = a - (b - a) * f(a) / (f(b) - f(a));
        b = b - (a - b) * f(b) / (f(a) - f(b));
    }
    return b;
}

bool hasRoot(double (*func)(double), double a, double b) {
    return func(a) * func(b) < 0;
}

void WriteOutput(double f(double), double A, double B, int N, double *epsilons) {
    if (!hasRoot(f, A, B)) {
        printf("Нет корней на отрезке AB.\n");
    } else {

        printf("| %-12s  | %-16s  | %-9s  | %-16s   | %-9s  |\n",
               "Погрешность", "Корень (бисек.)", "Итераций", "Корень (хорды)", "Итераций");
        printf("|----------------------------------------------------------------------------|\n");

        for (int i = 0; i < N; i++) {
            int iter_bisect = 0, chords_iter = 0;
            double root_bisect = Bisection(f, A, B, epsilons[i], iter_bisect);
            double root_chords = Chords(f, A, B, epsilons[i], chords_iter);

            if (!(isnan(root_chords) && isnan(root_bisect))) {
                printf("| %-12.10f | %-16.6f | %-9d | %-16.6f | %-9d |\n",
                       epsilons[i], root_bisect, iter_bisect, root_chords, chords_iter);
            }
            else if (!(isnan(root_chords))) {
                printf("| %-12.10f | %-16.6f | %-9d | %-16s | %-9d |\n",
                       epsilons[i], root_bisect, iter_bisect, "-", chords_iter);
            }
            else if (!(isnan(root_bisect))) {
                printf("| %-12.10f | %-16s | %-9d | %-16.6f | %-9d |\n",
                       epsilons[i], "-", iter_bisect, root_chords, chords_iter);
            }
            else {
                printf("| %-12.10f | %-16s | %-9d | %-16s | %-9d |\n",
                       epsilons[i], "-", iter_bisect, "-", chords_iter);
            }
        }
    }
}

int main() {
    double A, B;
    int N;

    SetConsoleOutputCP(CP_UTF8);

    printf("Введите A и B (0 < A < B < 2): \n A: ");
    scanf("%lf", &A);
    printf("B: ");
    scanf("%lf", &B);
    if (!(A > 0 && B > A && B < 2)) {
        printf("Ошибка: некорректные границы отрезка (A; B). (0 < A < B < 2)");
        exit(1);
    }

    printf("Введите N (1 <= N <= 10): ");
    scanf("%d", &N);
    if (!(N >= 1 && N <= 10)) {
        printf("Ошибка: N должно быть в диапазоне от 1 до 10.");
        exit(1);
    }

    double epsilons[10];
    for (int i = 0; i < N; i++) {
        epsilons[i] = pow(10, -(i + 1));
    }

    printf("\nПервая функция:\n");
    WriteOutput(f1, A, B, N, epsilons);

    printf("\nВторая функция:\n");
    WriteOutput(f2, A, B, N, epsilons);

    return 0;
}