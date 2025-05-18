#include <cstdio>
#include <iostream>
#include <cstring>
#include <windows.h>

#define MAXLEN 50

/*
 * Kadri RF A-09-24
 * Variant 16
 * Дан текстовый файл с несколькими строками. Найти номер последнего предложения, где есть слово,
 * которое состоит только из цифр, или вывести сообщение, что такого предложения нет.
 */

int main() {
    SetConsoleOutputCP(CP_UTF8);

    unsigned char ch; //текущий считанный символ 0..255
    int sentence_num = 0; //номер текущего слова
    char word[MAXLEN + 2] = ""; //текущее слово
    char sentence[500] = ""; //динамич. строка для предложения
    char answer_sentence[500] = "Предложение, где есть слово, которое состоит только из цифр, отсутствует";
    int answer_num = 0;
    int i; //индекс текущего символа в word
    bool digit_flag = true;
    bool digit_in_sentence = false;

    printf("Введите имя входного файла:");
    char filename[50];
    gets(filename);
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == nullptr) {
        printf("Error: Ошибка при открытии файла %s для чтения", filename);
        fclose(inputFile);
        exit(1);
    }

    printf("Введите имя выходного файла:");
    gets(filename);
    FILE *outputFile = fopen(filename, "w");
    if (outputFile == nullptr) {
        printf("Error: Ошибка при создании файла %s для записи", filename);
        fclose(outputFile);
        exit(1);
    }

    //пока не дойдем до конца файла, считываем очередной символ
    while (!feof(inputFile)) {
        ch = fgetc(inputFile);
        if (strchr(" .,!?:;\n\r\t", ch) == nullptr) { //если текущий символ - не разделитель
            i = 0; //обнуляем индекс текущего символа в слове
            digit_flag = true;

            while (strchr(" .,!?:;\n\r\t", ch) == nullptr) { //пока текущий символ удовлетворяет этому условию
                word[i] = ch; //добавляем символ в конец текущего слова
                if (!isdigit(ch)) digit_flag = false;
                i++; //смещаем индекс
                ch = fgetc(inputFile);  //считываем новый символ
                if (i == MAXLEN) break; //если превышена длина слова - конец слова
            }

            if (digit_flag && i > 0) digit_in_sentence = true;

            word[i] = ' '; //добавляем собственный разделитель между словами
            word[i+1] = '\0'; //завершаем слово символом конца строки

            strcat(sentence, word); //конкатенция
            word[0] = '\0'; //очищаем word

            if (strchr(".!?", ch)) {
                sentence_num++;
                fprintf(outputFile, "Предложение %d: %s\n", sentence_num, sentence);

                if (digit_in_sentence) {
                    answer_num = sentence_num;
                    strcpy(answer_sentence, sentence);
                }
                digit_in_sentence = false;
                digit_flag = true;
                sentence[0] = '\0'; //очищаем sentence

            }
        }
    }

    fprintf(outputFile, "\nВсего предложений: %d\n", sentence_num);
    if (answer_num != 0) {
    fprintf(outputFile, "\nПоследнее предложение, в котором есть слово, состоящее только из цифр - предложение №%d: %s", answer_num, answer_sentence);}
    else {fprintf(outputFile, "%s", answer_sentence);}

    fclose(inputFile); //закрываем входной файл
    fclose(outputFile); //закрываем выходной файл

    return 0;
}
