//
// Created by Ruseg on 25.04.2025.
//

#pragma once

void ReadData(int *m, int ***B, int **C);
void WriteInputData(int m, int **B, int *C);
void WriteOutputData(int m, int *C, bool flag);
bool CheckCondition(int m, int**B, const int *C);
int FindMin(int i, int m, int **B);
void ReplaceValue(int m, int **B, int *C);
void ClearMemory(int m, int **B, int *C);
