#include <windows.h>
#include <cstdio>
#include <cmath>

/*
 * Kadri RF A-09-24
 * Variant 16 Кол-во элементов, удовлетворяющих ( (R[i])^2 + 1 )^(1/3) > 20
 * Сначала правая половина, потом левая
 */

int FindAnswer(int *R, int start, int end) {
    int N = end - start + 1;
    if (N == 1) {                                                             // Если остался один элемент
        double value = pow(R[start] * R[start] + 1, 1.0 / 3.0);
        return (value > 20) ? 1 : 0;
    } else if (N == 2) {                                                      // Если осталось два элемента
        double value1 = pow(R[start] * R[start] + 1, 1.0 / 3.0);
        double value2 = pow(R[start + 1] * R[start + 1] + 1, 1.0 / 3.0);
        return ((value1 > 20) ? 1 : 0) + ((value2 > 20) ? 1 : 0);
    } else {                                                                  // Если больше двух элементов - рекурсия
        int mid = start + (end - start) / 2;
        return FindAnswer(R, mid + 1, end) + FindAnswer(R, start, mid);  // Правая половина + левая половина
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    int N = 0;

    printf("Введите кол-во элементов N:");
    scanf("%d", &N);

    if (N < 1) {
        printf("Error: N должен быть > 1!");
        exit(1);
    }

    int *R = new int[N];

    printf("Введите элементы Ri:\n");
    for (int i = 0; i < N; i++) scanf("%d", &R[i]);

    printf("\nВходные данные: \nКол-во элементов N: %d\nМассив R: ", N);
    for (int i = 0; i < N; i++) printf("%d ", R[i]);

    int counter = FindAnswer(R, 0, N-1);
    printf("\n\nВыходные данные:\nУдовлетворяющих условию элементов: %d\n", counter);

    delete[] R;
    return 0;
}

