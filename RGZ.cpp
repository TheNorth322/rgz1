#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h> 
#include <cstdio>

const int N = 24; // Количество чисел в файле

void print_bin(const char* file_name); // Вывод содержимого бинарного файла на экран (целые\вещественные числа)

void create_txt(const char* a); // Создание текстового файла данных, ввод чисел с клавиатуры

void create_bin(const char* a); // Создание бинарного файла данных, ввод чисел с клавиатуры

void concat_files(DAT_FILE_SIGNATURE _, const char* result_file, const char* fname, ...); // Копирование данных из текстовых файлов в один (файл-результат)

void concat_files(BIN_FILE_SIGNATURE _, const char* result_file, const char* fname, ...); // Копирование данных из бинарных файлов в один (файл-результат)

void incr(const char* file_type, const char* f); // Вызов сортировки по возрастанию для текстовых\бинарных файлов

void decr(const char* file_type, const char* f); // Вызов сортировки по убыванию для текстовых\бинарных файлов

void menu(const char* f, const char* file_type); // Меню для выбора типа сортировки

template <typename FT, typename DT>

int vnsort1_decr(FT ftype, DT dtype, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    DT a1, a2;
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "r")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fscanf(A, "%d", &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fprintf(B, " %d", a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 <= a1)  /* запишем в серию в файле В */
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }
            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 <= a1)  /* запишем в серию в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }
            }
            if (p)
                break; /* выход из цикла 2 */
        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_decr(DAT_FILE, INT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}

int vnsort2_decr(FILE_TYPE, DATA_TYPE, const char* a)// фаза слияния
int vnsort1_incr(FILE_TYPE, DATA_TYPE, const char* ff);  
int vnsort2_incr(FILE_TYPE, DATA_TYPE, const char* a);  
int vnsort1_decr(FILE_TYPE, DATA_TYPE, const char* ff);  
int vnsort2_decr(FILE_TYPE, DATA_TYPE, const char* a);   

int main()
{
    concat_files(DAT_FILE, "i_result.dat", "i_1.dat", "i_2.dat", NULL);
    menu("i_result.dat", "dat");
    return 0;
}

int vnsort1_incr(DAT_FILE_SIGNATURE _, INT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    int a1, a2;
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "r")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fscanf(A, "%d", &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fprintf(B, " %d", a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле В */
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }
            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }
            }
            if (p)
                break; /* выход из цикла 2 */
        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_incr(DAT_FILE, INT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_incr(DAT_FILE_SIGNATURE _, INT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    int b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "w")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "r")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "r")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fscanf(B, "%d", &b2);
    rc = fscanf(C, "%d", &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fprintf(A, " %d", b2);
            while (fscanf(B, "%d", &b2) > 0)
                fprintf(A, " %d", b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fprintf(A, " %d", c2);
            while (fscanf(C, "%d", &c2) > 0)
                fprintf(A, " %d", c2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 >= b1) && (c2 >= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 <= c2)
            {
                fprintf(A, " %d", b2); b1 = b2;
                rb = fscanf(B, "%d", &b2);
                continue;
            }
            else
            {
                fprintf(A, " %d", c2);
                c1 = c2;
                rc = fscanf(C, "%d", &c2);
                continue;
            }
        }

        if ((b2 >= b1) && (c2 < c1)) // серия файла C кончилась 
        {
            c1 = c2;
            flag = false;
            do
            {
                fprintf(A, " %d", b2);
                b1 = b2;
                rb = fscanf(B, "%d", &b2);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 < b1) && (c2 >= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fprintf(A, " %d", c2);
                c1 = c2;
                rc = fscanf(C, "%d", &c2);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 < c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

int vnsort1_decr(DAT_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    float a1, a2;
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "r")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fscanf(A, "%f", &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fprintf(B, " %f", a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (fscanf(A, " %f", &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 <= a1)  /* запишем в серию в файле В */
                    {
                        fprintf(B, " %f", a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fprintf(C, " %f", a2);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }
            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                if (fscanf(A, "%f", &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 <= a1)  /* запишем в серию в файле С */
                    {
                        fprintf(C, " %f", a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %f", a2);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }
            }
            if (p)
                break; /* выход из цикла 2 */
        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_decr(DAT_FILE, FLOAT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_decr(DAT_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    float b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "w")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "r")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "r")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fscanf(B, "%f", &b2);
    rc = fscanf(C, "%f", &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fprintf(A, " %f", b2);
            while (fscanf(B, "%f", &b2) > 0)
                fprintf(A, " %f", b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fprintf(A, " %f", c2);
            while (fscanf(C, "%f", &c2) > 0)
                fprintf(A, " %f", c2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 <= b1) && (c2 <= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 >= c2)
            {
                fprintf(A, " %f", b2); b1 = b2;
                rb = fscanf(B, "%f", &b2);
                continue;
            }
            else
            {
                fprintf(A, " %f", c2);
                c1 = c2;
                rc = fscanf(C, "%f", &c2);
                continue;
            }
        }

        if ((b2 <= b1) && (c2 > c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                fprintf(A, " %f", b2);
                b1 = b2;
                rb = fscanf(B, "%f", &b2);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 > b1) && (c2 <= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fprintf(A, " %f", c2);
                c1 = c2;
                rc = fscanf(C, "%f", &c2);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 < c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

int vnsort1_incr(DAT_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    float a1, a2;
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "r")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fscanf(A, "%f", &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fprintf(B, " %f", a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (fscanf(A, "%f", &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле В */
                    {
                        fprintf(B, " %f", a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fprintf(C, " %f", a2);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }
            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                if (fscanf(A, "%f", &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле С */
                    {
                        fprintf(C, " %f", a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %f", a2);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }
            }
            if (p)
                break; /* выход из цикла 2 */
        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_incr(DAT_FILE, FLOAT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_incr(DAT_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    float b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "w")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "r")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "r")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fscanf(B, "%f", &b2);
    rc = fscanf(C, "%f", &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fprintf(A, " %f", b2);
            while (fscanf(B, "%f", &b2) > 0)
                fprintf(A, " %f", b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fprintf(A, " %f", c2);
            while (fscanf(C, "%f", &c2) > 0)
                fprintf(A, " %f", c2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 >= b1) && (c2 >= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 <= c2)
            {
                fprintf(A, " %f", b2); b1 = b2;
                rb = fscanf(B, "%f", &b2);
                continue;
            }
            else
            {
                fprintf(A, " %f", c2);
                c1 = c2;
                rc = fscanf(C, "%f", &c2);
                continue;
            }
        }

        if ((b2 >= b1) && (c2 < c1)) // серия файла C кончилась 
        {
            c1 = c2;
            flag = false;
            do
            {
                fprintf(A, " %f", b2);
                b1 = b2;
                rb = fscanf(B, "%f", &b2);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 < b1) && (c2 >= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fprintf(A, " %f", c2);
                c1 = c2;
                rc = fscanf(C, "%f", &c2);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 < c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

int vnsort1_incr(BIN_FILE_SIGNATURE _, INT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    int a1, a2;
    /* файлы "B", "C" в функциях - временные */
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */

    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "rb")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "wb")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "wb")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fread(&a1, sizeof(int), 1, A) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fwrite(&a1, sizeof(int), 1, B);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                fread(&a2, sizeof(int), 1, A);
                if (feof(A)) {
                    p = 1;
                    break;
                }
                else {
                    if (a2 >= a1)  /* запишем в серию в файле В */
                    {
                        fwrite(&a2, sizeof(int), 1, B);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fwrite(&a2, sizeof(int), 1, C);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }

            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                fread(&a2, sizeof(int), 1, A);
                if (feof(A)) {
                    p = 1; break;
                }
                else {
                    if (a2 >= a1)  /* запишем в серию в файле С */
                    {
                        fwrite(&a2, sizeof(int), 1, C);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fwrite(&a2, sizeof(int), 1, B);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }

            }

            if (p)
                break; /* выход из цикла 2 */

        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_incr(BIN_FILE, INT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_incr(BIN_FILE_SIGNATURE _, INT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    int b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "wb")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "rb")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "rb")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fread(&b2, sizeof(int), 1, B);
    rc = fread(&c2, sizeof(int), 1, C);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fwrite(&b2, sizeof(int), 1, A);
            while (fread(&b2, sizeof(int), 1, B) > 0)
                fwrite(&b2, sizeof(int), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fwrite(&c2, sizeof(int), 1, A);
            while (fread(&c2, sizeof(int), 1, C) > 0)
                fwrite(&c2, sizeof(int), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 >= b1) && (c2 >= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 <= c2)
            {
                fwrite(&b2, sizeof(int), 1, A); b1 = b2;
                rb = fread(&b2, sizeof(int), 1, B);
                continue;
            }
            else
            {
                fwrite(&c2, sizeof(int), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(int), 1, C);
                continue;
            }
        }

        if ((b2 >= b1) && (c2 < c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                fwrite(&b2, sizeof(int), 1, A);
                b1 = b2;
                rb = fread(&b2, sizeof(int), 1, B);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 < b1) && (c2 >= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fwrite(&c2, sizeof(int), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(int), 1, C);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 < c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

int vnsort1_incr(BIN_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    float a1, a2;
    /* файлы "B", "C" в функциях - временные */
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */

    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "rb")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "wb")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "wb")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fread(&a1, sizeof(float), 1, A) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fwrite(&a1, sizeof(float), 1, B);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                fread(&a2, sizeof(float), 1, A);
                if (feof(A)) {
                    p = 1;
                    break;
                }
                else {
                    if (a2 >= a1)  /* запишем в серию в файле В */
                    {
                        fwrite(&a2, sizeof(float), 1, B);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fwrite(&a2, sizeof(float), 1, C);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }

            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                fread(&a2, sizeof(float), 1, A);
                if (feof(A)) {
                    p = 1; break;
                }
                else {
                    if (a2 >= a1)  /* запишем в серию в файле С */
                    {
                        fwrite(&a2, sizeof(float), 1, C);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fwrite(&a2, sizeof(float), 1, B);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }

            }

            if (p)
                break; /* выход из цикла 2 */

        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_incr(BIN_FILE, FLOAT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_incr(BIN_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    float b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "wb")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "rb")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "rb")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fread(&b2, sizeof(float), 1, B);
    rc = fread(&c2, sizeof(float), 1, C);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fwrite(&b2, sizeof(float), 1, A);
            while (fread(&b2, sizeof(float), 1, B) > 0)
                fwrite(&b2, sizeof(float), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fwrite(&c2, sizeof(float), 1, A);
            while (fread(&c2, sizeof(float), 1, C) > 0)
                fwrite(&c2, sizeof(float), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 >= b1) && (c2 >= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 <= c2)
            {
                fwrite(&b2, sizeof(float), 1, A); b1 = b2;
                rb = fread(&b2, sizeof(float), 1, B);
                continue;
            }
            else
            {
                fwrite(&c2, sizeof(float), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(float), 1, C);
                continue;
            }
        }

        if ((b2 >= b1) && (c2 < c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                fwrite(&b2, sizeof(float), 1, A);
                b1 = b2;
                rb = fread(&b2, sizeof(float), 1, B);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 < b1) && (c2 >= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fwrite(&c2, sizeof(float), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(float), 1, C);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 < c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

int vnsort1_decr(BIN_FILE_SIGNATURE _, INT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    int a1, a2;
    /* файлы "B", "C" в функциях - временные */
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */

    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "rb")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "wb")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "wb")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fread(&a1, sizeof(int), 1, A) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fwrite(&a1, sizeof(int), 1, B);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                fread(&a2, sizeof(int), 1, A);
                if (feof(A)) {
                    p = 1;
                    break;
                }
                else {
                    if (a2 <= a1)  /* запишем в серию в файле В */
                    {
                        fwrite(&a2, sizeof(int), 1, B);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fwrite(&a2, sizeof(int), 1, C);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }

            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                fread(&a2, sizeof(int), 1, A);
                if (feof(A)) {
                    p = 1; break;
                }
                else {
                    if (a2 <= a1)  /* запишем в серию в файле С */
                    {
                        fwrite(&a2, sizeof(int), 1, C);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fwrite(&a2, sizeof(int), 1, B);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }

            }

            if (p)
                break; /* выход из цикла 2 */

        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_decr(BIN_FILE, INT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_decr(BIN_FILE_SIGNATURE _, INT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    int b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "wb")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "rb")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "rb")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fread(&b2, sizeof(int), 1, B);
    rc = fread(&c2, sizeof(int), 1, C);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fwrite(&b2, sizeof(int), 1, A);
            while (fread(&b2, sizeof(int), 1, B) > 0)
                fwrite(&b2, sizeof(int), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fwrite(&c2, sizeof(int), 1, A);
            while (fread(&c2, sizeof(int), 1, C) > 0)
                fwrite(&c2, sizeof(int), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 <= b1) && (c2 <= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 >= c2)
            {
                fwrite(&b2, sizeof(int), 1, A); b1 = b2;
                rb = fread(&b2, sizeof(int), 1, B);
                continue;
            }
            else
            {
                fwrite(&c2, sizeof(int), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(int), 1, C);
                continue;
            }
        }

        if ((b2 <= b1) && (c2 > c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                fwrite(&b2, sizeof(int), 1, A);
                b1 = b2;
                rb = fread(&b2, sizeof(int), 1, B);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 > b1) && (c2 <= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fwrite(&c2, sizeof(int), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(int), 1, C);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 > c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

int vnsort1_decr(BIN_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    float a1, a2;
    /* файлы "B", "C" в функциях - временные */
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */

    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "rb")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "wb")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "wb")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;

        if (fread(&a1, sizeof(float), 1, A) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fwrite(&a1, sizeof(float), 1, B);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                fread(&a2, sizeof(float), 1, A);
                if (feof(A)) {
                    p = 1;
                    break;
                }
                else {
                    if (a2 <= a1)  /* запишем в серию в файле В */
                    {
                        fwrite(&a2, sizeof(float), 1, B);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fwrite(&a2, sizeof(float), 1, C);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }

            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                fread(&a2, sizeof(float), 1, A);
                if (feof(A)) {
                    p = 1; break;
                }
                else {
                    if (a2 <= a1)  /* запишем в серию в файле С */
                    {
                        fwrite(&a2, sizeof(float), 1, C);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fwrite(&a2, sizeof(float), 1, B);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }

            }

            if (p)
                break; /* выход из цикла 2 */

        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2_decr(BIN_FILE, FLOAT_VAL, ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
int vnsort2_decr(BIN_FILE_SIGNATURE _, FLOAT_SIGNATURE, const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    float b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "wb")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "rb")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "rb")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }

    rb = fread(&b2, sizeof(float), 1, B);
    rc = fread(&c2, sizeof(float), 1, C);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fwrite(&b2, sizeof(float), 1, A);
            while (fread(&b2, sizeof(float), 1, B) > 0)
                fwrite(&b2, sizeof(float), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fwrite(&c2, sizeof(float), 1, A);
            while (fread(&c2, sizeof(float), 1, C) > 0)
                fwrite(&c2, sizeof(float), 1, A);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 <= b1) && (c2 <= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 >= c2)
            {
                fwrite(&b2, sizeof(float), 1, A); b1 = b2;
                rb = fread(&b2, sizeof(float), 1, B);
                continue;
            }
            else
            {
                fwrite(&c2, sizeof(float), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(float), 1, C);
                continue;
            }
        }

        if ((b2 <= b1) && (c2 > c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                fwrite(&b2, sizeof(float), 1, A);
                b1 = b2;
                rb = fread(&b2, sizeof(float), 1, B);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 > b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 > b1) && (c2 <= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fwrite(&c2, sizeof(float), 1, A);
                c1 = c2;
                rc = fread(&c2, sizeof(float), 1, C);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 > c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }

    }
}

void create_txt(const char* a)
{
    FILE* A;

    if ((A = fopen(a, "w")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return;
    }

    if (a[0] == 'i')
    { // Запись целых чисел
        int n;
        printf("\n Введите целых %d чисел: ", N);
        for (size_t i = 0; i < N; i++)
        {
            scanf("%d", &n);
            fprintf(A, " %d", n);
        }
        fclose(A);
    }
    else
    { // Запись вещественных чисел
        float n;
        printf("\n Введите вещественных %d чисел: ", N);
        for (size_t i = 0; i < N; i++)
        {
            scanf("%f", &n);
            fprintf(A, " %f", n);
        }
        fclose(A);
    }
}

void create_bin(const char* a)
{
    FILE* A;

    if ((A = fopen(a, "wb")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return;
    }

    if (a[0] == 'i') // Запись целых чисел
    {
        int n;
        printf("\n Введите %d целых чисел: ", N);
        for (size_t i = 0; i < N; i++)
        {
            scanf("%d", &n);
            fwrite(&n, sizeof(int), 1, A);
        }
    }
    else // Запись вещественных чисел
    {
        float n;
        printf("\n Введите %d вещественных чисел: ", N);
        for (size_t i = 0; i < N; i++)
        {
            scanf("%f", &n);
            fwrite(&n, sizeof(float), 1, A);
        }
    }
    fclose(A);
}

void concat_files(DAT_FILE_SIGNATURE _, const char* result_file, const char* fname, ...)
{
    va_list ptr;
    const char* name = fname;
    va_start(ptr, fname);

    FILE* file = NULL;
    FILE* result = NULL;

    result = fopen(result_file, "w");

    while (name) {
        file = fopen(name, "r");
        if (file != NULL)
            if (name[0] == 'i')
            {
                int i;
                while ((fscanf(file, "%d", &i) != EOF)) fprintf(result, " %d", i);
            }
            else
            {
                float i;
                while ((fscanf(file, "%f", &i) != EOF)) fprintf(result, " %f", i);
            }
        name = va_arg(ptr, const char*);
        fclose(file);
    }
    va_end(ptr);

    fclose(result);
    printf("Все текстовые файлы успешно объединены\n");
}

void concat_files(BIN_FILE_SIGNATURE _, const char* result_file, const char* fname, ...)
{
    va_list ptr;
    FILE* file = NULL;
    FILE* result = NULL;
    const char* name = fname;
    va_start(ptr, fname);

    result = fopen(result_file, "wb");

    while (name) {
        file = fopen(name, "rb");
        if (file != NULL) {
            if (name[0] == 'i')  // Файл с целыми числами
            {
                int i;
                while (fread(&i, sizeof(int), 1, file))
                    fwrite(&i, sizeof(int), 1, result);
            }
            else // Файл с вещественными числами
            {
                float i;
                while (fread(&i, sizeof(float), 1, file))
                    fwrite(&i, sizeof(float), 1, result);
            }
        }
        name = va_arg(ptr, const char*);
        fclose(file);
    }
    va_end(ptr);

    fclose(result);
    printf("Данные из файлов скопированы в файл-результат.\n");
}

void print_bin(const char* file_name)
{
    FILE* file = fopen(file_name, "rb");

    if (file_name[0] == 'i')
    {
        int value;
        while (fread(&value, sizeof(int), 1, file))
            printf("%d ", value);
    }
    else
    {
        float value;
        while (fread(&value, sizeof(float), 1, file))
            printf("%f ", value);
    }

    fclose(file);
}

void incr(const char* file_type, const char* f)
{
    if (file_type == "dat") // Сортировка по возрастанию для текстовых файлов
        if (f[0] == 'i') vnsort1_incr(DAT_FILE, INT_VAL, f);
        else vnsort1_incr(DAT_FILE, FLOAT_VAL, f);
    else // Сортировка по возрастанию для бинарных файлов
        if (f[0] == 'i')
        {
            vnsort1_incr(BIN_FILE, INT_VAL, f);
            print_bin(f);
        }
        else 
        {
            vnsort1_incr(BIN_FILE, FLOAT_VAL, f);
            print_bin(f);
        }
}

void decr(const char* file_type, const char* f)
{
    if (file_type == "dat") // Сортировка по убыванию для текстовых файлов
        if (f[0] == 'i') 
            vnsort1_decr(DAT_FILE, INT_VAL, f);
        else
            vnsort1_decr(DAT_FILE, FLOAT_VAL, f);
    else // Сортировка по убыванию для бинарных файлов
        if (f[0] == 'i')
        {
            vnsort1_decr(BIN_FILE, INT_VAL, f);
            print_bin(f);
        }
        else 
        {
            vnsort1_decr(BIN_FILE, FLOAT_VAL, f);
            print_bin(f);
        }
}

typedef void (*MENU)(const char*, const char*);

void menu(const char* f, const char* file_type) // Меню для выбора типа сортировки
{
    int c = NULL;
    const char* options[] = { "1-Сортировка по возрастанию", "2-Сортировка по убыванию","3-ВЫХОД" };
    int i, num = 0,
        l = sizeof(options) / sizeof(char*); // Количество действий с программой
    MENU action[] = { incr, decr };

    while (1)
    {
        printf("----------РАБОТА С ФАЙЛАМИ----------\n");
        for (i = 0; i < l; i++)
            printf("%s\n", options[i]);
        printf("Выберите номер опции: ");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            action[c - 1](file_type, f);
            printf("\nСортировка успешно завершена\n");
            break;
        case 2:
            action[c - 1](file_type, f);
            printf("\nСортировка успешно завершена\n");
            break;
        case 3:
            exit(1);
        default:
            printf("Ошибка! Введите число от 1 до %d", l);
            printf("\n");
            break;
        }
    }
}























