#include "functions.h"

/*
 * Kadri RF
 * A-09-24
 * Variant 16
 *
 * Дана матрица B из M строк и M столбцов. Кроме матрицы B, даны элементы С1, С2, ..., СM.
 * Если для всех i и j выполняется неравенство Ci > Bij,
 * заменить значение каждого элемента Сi значением минимального элемента i-ой строки матрицы B.
 */

int main() {
    int **B = nullptr, *C = nullptr;
    int m = 0;

    ReadData(&m, &B, &C);
    WriteInputData(m, B, C);
    bool flag = CheckCondition(m, B, C);
    if (flag) {
        ReplaceValue(m, B, C);
    }
    WriteOutputData(m, C, flag);
    ClearMemory(m, B, C);

    return 0;
}
