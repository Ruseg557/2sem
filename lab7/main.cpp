#include <windows.h>
#include <cstdio>
#include <conio.h>

/*
 * Kadri RF
 * A-09-24
 * 16.Исходные данные: Сведения о заказе состоят из адреса (улица, дом, квартира) и даты (число, месяц, год) исполнения.
 * Условие поиска: Заказы, которые должны были быть выполнены 15 мая 2015 г на Московской улице.
 * Коррекция: Номер месяца 1-12, дней не более 28-31 в соответствии с месяцем. Номер квартиры положительное число.
 */

struct TOrder {
    struct {
        char Street[31], Building[5], Appartament[5];
    } Address;
    struct {
        char Day[3], Month[3], Year[5];
    } Date;
};

char *UTF8UpperCase(char *s, char *S) {
    S = strcpy(S, s);
    unsigned char *ch = (unsigned char *) S;
    while (*ch) {
        // Латинские буквы
        if (*ch >= 'a' && *ch <= 'z') {
            *ch -= 32;
            ch++;
        }
            // Русские буквы
        else if (*ch == 0xD0 && ch[1] >= 0xB0 && ch[1] <= 0xBF) {
            ch[1] -= 32;  // а-п → А-П
            ch += 2;
        } else if (*ch == 0xD1 && ch[1] >= 0x80 && ch[1] <= 0x8F) {
            *ch = 0xD0;   // р-я → Р-Я
            ch[1] += 32;
            ch += 2;
        }
            // Особый случай: 'ё' (0xD1 0x91) → 'Ё' (0xD0 0x81)
        else if (*ch == 0xD1 && ch[1] == 0x91) {
            *ch = 0xD0;
            ch[1] = 0x81;
            ch += 2;
        } else {
            ch++;  // Если символ другой, то двигаем указатель
        }
    }
    return S;
}

FILE* OpenBinFileMode(int ch) {
    char bin_filename[50];
    printf("Введите имя бинарного файла:");
    gets(bin_filename);
    FILE *fb = NULL;

    char *mode = NULL;

    switch (ch) {
        case 1: mode = "wb"; break;
        case 2: mode = "rb"; break;
        case 3: mode = "rb+"; break;
        default:
            printf("Неверный режим работы с файлом\n");
            exit(1);
    }

    fb = fopen(bin_filename, mode);
    if (fb == nullptr) {
        printf("Ошибка при работе с файлом %s\n", bin_filename);
        printf("Press ENTER");
        getch();
        exit(1);
    }

    return fb;
}

void CreateBinaryFile() {
    printf("Введите имя текстовго файла:");
    char input_filename[50];
    gets(input_filename);
    FILE *ft = fopen(input_filename, "rt");
    if (ft == nullptr) {
        printf("Error: Ошибка при открытии файла %s для чтения\nPress any key", input_filename);
        getch();
        fclose(ft);
        exit(1);
    }

    FILE *fb = OpenBinFileMode(1);

    TOrder Order;
    int kol = 0, nw = 1;
    while (nw) {
        fscanf(ft, "%s", Order.Address.Street);

        if (strcmp(Order.Address.Street, "**") == 0 || feof(ft)) { break; }

        fscanf(ft, "%s", Order.Address.Building);
        fscanf(ft, "%s", Order.Address.Appartament);

        fscanf(ft, "%s", Order.Date.Day);
        fscanf(ft, "%s", Order.Date.Month);
        fscanf(ft, "%s", Order.Date.Year);

        nw = fwrite(&Order, sizeof(Order), 1, fb);
        kol++;
    }
    if (nw != 1) { printf("Error: Ошибка при записи"); }

    fclose(ft);
    fclose(fb);

    printf("Создан двоичный файл из %d записей по %d байт\n", kol, sizeof(Order));
    printf("Press any key to continue");
    getch();
}

void FindOrder() {

    FILE *fb = OpenBinFileMode(2);

    TOrder Order;
    char SUp[30];
    int kol = 0, nr = 1;
    while (nr) {
        nr = fread(&Order, sizeof(Order), 1, fb);
        if (nr > 0)
            if (strcmp(Order.Date.Day, "15") == 0 &&
            strcmp(Order.Date.Month, "05") == 0 &&
            strcmp(Order.Date.Year, "2015") == 0 &&
            strcmp(UTF8UpperCase(Order.Address.Street, SUp), "МОСКОВСКАЯ") == 0) {
                printf("Найден заказ по адресу улица %s дом %s квартира %s от %s %s %s\n", Order.Address.Street,
                       Order.Address.Building, Order.Address.Appartament, Order.Date.Day, Order.Date.Month,
                       Order.Date.Year);
                kol++;
            }
    }
    if (kol == 0)
        printf("Данные, соответствующие запросу,не найдены\n");
    else
        printf("Всего найдено: %d\n", kol);

    fclose(fb);

    printf("Press any key to continue");
    getch();
}

void CorrectFile() {
    int MONTH_LIMIT[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    FILE *fb = OpenBinFileMode(3);

    TOrder Order;
    int kol = 0, nr = 1, nw = 1, flag;
    nr = fread(&Order, sizeof(Order), 1, fb);
    while (nr == 1 && nw == 1) {
        printf("Считана запись:\n");
        printf("%25s%10s%10s%15s.%s.%s\n", Order.Address.Street, Order.Address.Building, Order.Address.Appartament,
               Order.Date.Day, Order.Date.Month, Order.Date.Year);

        flag = 0;
        if (atoi(Order.Date.Month) > 12 || atoi(Order.Date.Month) < 1) {
            strncpy(Order.Date.Month, "01", sizeof(Order.Date.Month)-1);
            flag = 1;
        }

        if (atoi(Order.Date.Day) < 1 || atoi(Order.Date.Day) > MONTH_LIMIT[atoi(Order.Date.Month)-1]) {
            strncpy(Order.Date.Day, "01", sizeof(Order.Date.Day)-1);
            flag = 1;
        }
        if (atoi(Order.Address.Appartament) < 1) {
            strncpy(Order.Address.Appartament, "1", sizeof(Order.Address.Appartament)-1);
            flag = 1;
        }

        if (flag) {
            kol++;
            fseek(fb, 0 - sizeof(Order), SEEK_CUR);
            nw = fwrite(&Order, sizeof(Order), 1, fb);
            fseek(fb, 0, SEEK_CUR);

            printf("Сделана корректировка:\n");
            printf("%25s%10s%10s%15s.%s.%s\n", Order.Address.Street, Order.Address.Building,
                   Order.Address.Appartament, Order.Date.Day, Order.Date.Month, Order.Date.Year);
        }
        nr = fread(&Order, sizeof(Order), 1, fb);
    }
    if (kol == 0)
        printf("Ни одной корректировки\n");
    else
        printf("Всего корректировок: %d\n", kol);

    fclose(fb);
    printf("Press any key to continue");
    getch();
}

void ReadFile() {
    FILE *fb = OpenBinFileMode(2);

    TOrder Order;
    int kol = 0, nr = 1;

    while (nr) {
        nr = fread(&Order, sizeof(Order), 1, fb);
        if (nr > 0) {
            printf("Найден заказ по адресу улица %s дом %s квартира %s от %s.%s.%s\n", Order.Address.Street,
                   Order.Address.Building, Order.Address.Appartament, Order.Date.Day, Order.Date.Month,
                   Order.Date.Year);
            kol++;
        }
    }
    if (kol == 0)
        printf("Данные, соответствующие запросу,не найдены\n");
    else
        printf("Всего найдено: %d записей\n", kol);
}

int main() {
    char ch;
    SetConsoleOutputCP(CP_UTF8);

    do {
        printf("\nN - создать новый тип.файл из текстового\nF - поиск\nC - коррекция\nR - чтение бинарного файла"
               "\nE - конец.\nВаш выбор?");
        ch = getchar();
        fflush(stdin);
        ch = toupper(ch);
        switch (ch) {
//----------первая часть: создание двоичного из текстового
            case 'N':
                CreateBinaryFile();
                break;
//-------------- вторая часть: поиск в двоичном файле ----
            case 'F':
                FindOrder();
                break;
//-------третья часть: корректировка в двоичном файле ----
            case 'C':
                CorrectFile();
                break;
//-------Чтение из файла----------------------------------
            case 'R':
                ReadFile();
                break;
//-----------выход----------------------------------------
            case 'E':
                return 0;
//--------------------------------------------------------
            default:
                printf("Нет такой команды\nPress any key");
                getch();
        }

    } while (ch != 'E');
}