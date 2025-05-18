#include "functions.h"
#include "cstdio"
#include "windows.h"
#include "conio.h"
#include "cstdlib"

void ReadData(int *m, int ***B, int **C) {
    SetConsoleOutputCP(CP_UTF8);

    printf("Введите имя файла:");
    char filename[50];
    gets(filename);
    FILE *f = fopen(filename, "r");
    if (f == nullptr) {
        printf("Error: Ошибка при открытии файла %s для чтения\nPress any key", filename);
        getch();
        fclose(f);
        exit(1);
    }

    fscanf(f, "%d", m);
    if (!(0 < *m && *m < 21)) {
        printf("Error: m должен принадлежать отрезку [1,20]\nPress any key");
        getch();
        fclose(f);
        exit(1);
    }

    *B = new int*[*m];
    for(int i=0; i < *m; i++) {
        (*B)[i] = new int[*m];
    }
    *C = new int[*m];

    for (int i = 0; i < *m; i++) {
        for (int j = 0; j < *m; j++) {
            fscanf(f, "%d", &(*B)[i][j]);
        }
    }
    for (int i = 0; i < *m; i++) {
        fscanf(f, "%d", &(*C)[i]);
    }

    fclose(f);
}

void WriteInputData(int m, int **B, int *C) {
    FILE *f = fopen("output.txt", "w");
    if (f == nullptr) {
        printf("Ошибка при создании выходного файла");
        exit(1);
    }

    fprintf(f,"Количество строк и столбцов: %d \n", m);

    fprintf(f,"Массив C:\n");
    for (int i = 0; i < m; i++) {
        fprintf(f,"%d ", C[i]);
    }

    fprintf(f,"\n\nМатрица B:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(f,"%d ", B[i][j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

void WriteOutputData(int m, int *C, bool flag) {
    FILE *f = fopen("output.txt", "a");
    if (f == nullptr) {
        printf("Ошибка при записи в выходной файл");
        exit(1);
    }

    if (flag == 1) {
        fprintf(f, "\nИзмененный массив C:\n");
        for (int i = 0; i < m; i++) {
            fprintf(f, "%d ", C[i]);
        }
    }
    else {
        fprintf(f,"\nНеравенство выполняется не для всех ij\n");
    }
    fclose(f);
}

bool CheckCondition(int m, int**B, const int *C) {
    bool flag = true;
    for (int i=0; (i < m) && (flag == 1); i++) {
        for (int j=0; (j < m) && (flag == 1); j++) {
            if (C[i] <= B[i][j]) {
                flag = false;
            }
        }
    }
    return flag;
}

int FindMin(int i, int m, int **B) {
    int min = B[i][0];
    for (int j = 1; j < m; j++) {
        if (B[i][j] < min) {
            min = B[i][j];
        }
    }
    return min;
}

void ReplaceValue(int m, int **B, int *C) {
    for (int i = 0; i < m; i++) {
        C[i] = FindMin(i, m, B);
    }
}

void ClearMemory(int m, int **B, int*C) {
    for (int i = 0; i < m; i++) {
        delete[] B[i];
    }
    delete[] B;
    delete[] C;
}