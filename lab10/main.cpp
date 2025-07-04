#include <windows.h>  // SetConsoleOutputCP, SetConsoleCP
#include <cstdio>    // printf, fgets
#include <conio.h>   // getch
#include <cstring>   // strncmp
#include <cctype>    // isalpha

/*
 * Kadri RF A-09-24
 * Variant 16
 *
 * 16. Из одного стека, хранящего символы, собрать два новых стека:
 * один с латинскими буквами, другой со всеми остальными символами,
 * изменив связи между элементами стеков (не выделяя новую память).
 */

struct TElem {
    char Info;
    TElem *Next;
};

TElem *PushStack(TElem *St, char Info);

char PopStack(TElem **PSt);

void TopToTop(TElem **PSt1, TElem **PSt2);

TElem *CreateStack(TElem *St);

void OutputStack(TElem *&St);

void Decide(TElem **PSt1, TElem **PSt2, TElem **PSt3);

TElem *FreeStack(TElem *St);

int main() {
    TElem *StackTop1 = nullptr, *StackTop2 = nullptr, *StackTop3 = nullptr;
    char ch;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    do {
        printf("\nN - Create new stack; V - Print stack; D - Solution; F - Free stack; E - Exit.\nChoice?");
        ch = getchar();
        fflush(stdin);
        ch = toupper(ch);
        switch (ch) {
            case 'N':
                if (StackTop1) {
                    printf("Error: you have to free memory first!\nPress ENTER to continue");
                    getch();
                    break;
                }
                StackTop1 = CreateStack(StackTop1);
                break;
            case 'V':
                printf("First stack (original):\n");
                OutputStack(StackTop1);
                printf("\nSecond stack (non-latin):\n");
                OutputStack(StackTop2);
                printf("\nThird stack (latin):\n");
                OutputStack(StackTop3);
                printf("\nPress ENTER to continue");
                getch();
                break;
            case 'D':
                Decide(&StackTop1, &StackTop2, &StackTop3);
                break;
            case 'F':
                StackTop1 = FreeStack(StackTop1);
                StackTop2 = FreeStack(StackTop2);
                StackTop3 = FreeStack(StackTop3);
                printf("All memory for stacks is free\n");
                break;
            case 'E':
                return 0;
            default:
                printf("Unknown command\nPress ENTER");
                getch();
        }
        fflush(stdin);
    } while (true);
}

TElem *PushStack(TElem *St, char Info) {
    TElem *Elem = new TElem;
    Elem->Info = Info;
    Elem->Next = St;
    return Elem;
}

char PopStack(TElem **PSt) {
    if (!*PSt)
        return '\0';
    TElem *Elem = *PSt;
    char Info = Elem->Info;
    *PSt = Elem->Next;
    delete Elem;
    return Info;
}

void TopToTop(TElem **PSt1, TElem **PSt2) {
    if (!*PSt1)
        return;
    TElem *Elem = *PSt1;
    *PSt1 = Elem->Next;
    Elem->Next = *PSt2;
    *PSt2 = Elem;
}

TElem *CreateStack(TElem *St) {
    int kol = 0;
    char input[3];
    char Info;

    while (true) {
        printf("\nWait for char (or '**' for exit):");
        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        if (strncmp(input, "**", 2) == 0)
            break;

        Info = input[0];
        St = PushStack(St, Info);
        kol++;
    }
    printf("New stack of %d elements created\n", kol);
    printf("Press ENTER to continue");
    getch();
    return St;
}

void OutputStack(TElem *&St) {
    TElem *Dop = nullptr;
    char data;
    if (!St) {
        printf("empty");
    } else {
        while (St) {
            data = PopStack(&St);
            printf("%c ", data);

            Dop = PushStack(Dop, data);
        }
        while (Dop)
            TopToTop(&Dop, &St);
    }
    printf("\n");
}

void Decide(TElem **PSt1, TElem **PSt2, TElem **PSt3) {
    if (*PSt1) {
        while (*PSt1) {
            char info = PopStack(PSt1);

            if (isalpha(info)) {
                *PSt3 = PushStack(*PSt3, info);
            } else {
                *PSt2 = PushStack(*PSt2, info);
            }
        } //while
        printf("Stack has been separated for latin and non-latin chars.\n");
    } else {
        printf("Original stack is empty.\n");
    }

    printf("Press ENTER to continue");
    getch();
}

TElem *FreeStack(TElem *St) {
    while (St)
        PopStack(&St);
    return St;
}