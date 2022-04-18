#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <cstdio>
#include <stdarg.h>

const int N = 24; // Количество чисел в файле

void print_bin(const char* file_name); // Вывод содержимого бинарного файла на экран (целые\вещественные числа)

void create_txt(const char* a); // Создание текстового файла данных, ввод чисел с клавиатуры

void create_bin(const char* a); // Создание бинарного файла данных, ввод чисел с клавиатуры

void concat_files(const char* file_type, const char* result_file, const char* fname, ...); // Копирование данных из текстовых файлов в один (файл-результат)

void concat_files(const char* file_type, const char* result_file, const char* fname, ...); // Копирование данных из бинарных файлов в один (файл-результат)

void incr(const char* file_type, const char* f); // Вызов сортировки по возрастанию для текстовых\бинарных файлов

void decr(const char* file_type, const char* f); // Вызов сортировки по убыванию для текстовых\бинарных файлов

typedef void (*MENU)(const char*, const char*); // Массив указателей на функции

void menu(const char* f, const char* file_type); // Меню для выбора типа сортировки

int file_read(FILE* A, const char* file_type, const char* format, int* buff); // Чтение целых чисел из бинарных / текстовых файлов

int file_read(FILE* A, const char* file_type, const char* format, float* buff); // Чтение вещественных чисел из бинарных / текстовых файлов

void file_write(FILE* A, const char* file_type, const char* format, int buff); // Запись целых чисел в бинарные / тектовые файлы

void file_write(FILE* A, const char* file_type, const char* format, float* buff); // Запись вещественных чисел в бинарные / текстовые файлы

void print_txt(const char* file_name);

template <typename DATA_TYPE>
int vnsort1_decr(const char* file_type, const char* ff); // Сортировка по убыванию для текстовых / бинарных файлов, целых / вещественных чисел
template <typename DATA_TYPE> 
int vnsort2_decr(const char* file_type, const char* a); 

template <typename DATA_TYPE> 
int vnsort1_incr(const char* file_type, const char* ff); // Сортировка по возрастанию для текстовых / бинарных файлов, целых / вещественных чисел
template <typename DATA_TYPE> 
int vnsort2_incr(const char* file_type, const char* a);

int main()
{
    concat_files("dat", "i_result.dat", "i_1.dat", "i_2.dat", NULL);
    menu("i_result.dat", "dat");
    print_txt("i_result.dat");
    //print_bin("f_result.bin");
    return 0;
}

int file_read(FILE* A, const char* file_type, const char* format, int* buff) {
    if (file_type == "dat") {
        if (fscanf(A, format, buff) == EOF) return EOF;
    }
    else {
        if (!fread(buff, sizeof(int), 1, A)) return EOF;
    }
    return 1;
}

void file_write(FILE* A, const char* file_type, const char* format, int buff) {
    if (file_type == "dat") fprintf(A, format, buff);
    else fwrite(&buff, sizeof(int), 1, A);
}

int file_read(FILE* A, const char* file_type, const char* format, float* buff) {
    if (file_type == "dat") {
        if (fscanf(A, format, buff) == EOF) return EOF;
    }
    else {
        if (!fread(buff, sizeof(float), 1, A)) return EOF;
    }
    return 1;
}

void file_write(FILE* A, const char* file_type, const char* format, float buff) {
    if (file_type == "dat") fprintf(A, format, buff);
    else fwrite(&buff, sizeof(float), 1, A);
}

template <typename DATA_TYPE> 
int vnsort1_decr(const char* file_type, const char* ff)
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    DATA_TYPE a1, a2;
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    const char* read_sign;
    const char* write_sign;

    if (file_type == "dat") {
        read_sign = "r";
        write_sign = "w";
    }
    else {
        read_sign = "rb";
        write_sign = "wb";
    }

    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, read_sign)) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            return -1;
        }
        if ((B = fopen("B", write_sign)) == NULL)
        {
            printf("\n Файл B не открывается");
            return -1;
        }
        if ((C = fopen("C", write_sign)) == NULL)
        {
            printf("\n Файл C не открывается");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;
        const char* format;
        const char* format_with_space;

        if (ff[0] == 'i') {
            format = "%d";
            format_with_space = " %d";
        }
        else {
            format = "%f";
            format_with_space = " %f";
        }
        
        if (file_read(A, file_type, format, &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            return -1;
        }
        else
        {
            file_write(B, file_type, format_with_space, a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (file_read(A, file_type, format, &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 <= a1)  /* запишем в серию в файле В */
                    {
                        file_write(B, file_type, format_with_space, a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        file_write(C, file_type, format_with_space, a2);
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
                if (file_read(A, file_type, format, &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 <= a1)  /* запишем в серию в файле С */
                    {
                        file_write(C, file_type, format_with_space, a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        file_write(B, file_type, format_with_space, a2);
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
        if (pb && pc) /* исходный файл записан в оба файла разделения */
            if (ff[0] == 'i') vnsort2_decr<int>(file_type, ff);  /* вызов функции слияния */
            else vnsort2_decr<float>(file_type, ff);

        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}
template <typename DATA_TYPE> 
int vnsort2_decr(const char* file_type, const char* a)
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    DATA_TYPE b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */

    const char* read_sign;
    const char* write_sign;

    if (file_type == "dat") {
        read_sign = "r";
        write_sign = "w";
    }
    else {
        read_sign = "rb";
        write_sign = "wb";
    }

    if ((A = fopen(a, write_sign)) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        return -1;
    }
    if ((B = fopen("B", read_sign)) == NULL)
    {
        printf("\n Файл B не открывается");
        return -1;
    }
    if ((C = fopen("C", read_sign)) == NULL)
    {
        printf("\n Файл C не открывается");
        return -1;
    }

    const char* format;
    const char* format_with_space;

    if (a[0] == 'i') {
        format = "%d";
        format_with_space = " %d";
    }
    else {
        format = "%f";
        format_with_space = " %f";
    }

    rb = file_read(B, file_type, format, &b2);
    rc = file_read(C, file_type, format, &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            file_write(A, file_type, format_with_space, b2);
            while (file_read(B, file_type, format, &b2) > 0)
                file_write(A, file_type, format_with_space, b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            file_write(A, file_type, format_with_space, c2);
            while (file_read(C, file_type, format, &c2) > 0)
                file_write(A, file_type, format_with_space, c2);
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
                file_write(A, file_type, format_with_space, b2); b1 = b2;
                rb = file_read(B, file_type, format, &b2);
                continue;
            }
            else
            {
                file_write(A, file_type, format_with_space, c2);
                c1 = c2;
                rc = file_read(C, file_type, format, &c2);
                continue;
            }
        }

        if ((b2 <= b1) && (c2 > c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                file_write(A, file_type, format_with_space, b2);
                b1 = b2;
                rb = file_read(B, file_type, format, &b2);
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
                file_write(A, file_type, format_with_space, c2);
                c1 = c2;
                rc = file_read(C, file_type, format, &c2);
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

template <typename DATA_TYPE>
int vnsort1_incr(const char* file_type, const char* ff)
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    DATA_TYPE a1, a2;
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    const char* read_sign;
    const char* write_sign;

    if (file_type == "dat") {
        read_sign = "r";
        write_sign = "w";
    }
    else {
        read_sign = "rb";
        write_sign = "wb";
    }

    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, read_sign)) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            return -1;
        }
        if ((B = fopen("B", write_sign)) == NULL)
        {
            printf("\n Файл B не открывается");
            return -1;
        }
        if ((C = fopen("C", write_sign)) == NULL)
        {
            printf("\n Файл C не открывается");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;
        const char* format;
        const char* format_with_space;

        if (ff[0] == 'i') {
            format = "%d";
            format_with_space = " %d";
        }
        else {
            format = "%f";
            format_with_space = " %f";
        }
        
        if (file_read(A, file_type, format, &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            return -1;
        }
        else
        {
            file_write(B, file_type, format_with_space, a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (file_read(A, file_type, format, &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле В */
                    {
                        file_write(B, file_type, format_with_space, a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        file_write(C, file_type, format_with_space, a2);
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
                if (file_read(A, file_type, format, &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле С */
                    {
                        file_write(C, file_type, format_with_space, a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        file_write(B, file_type, format_with_space, a2);
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
        if (pb && pc) /* исходный файл записан в оба файла разделения */
            if (ff[0] == 'i') vnsort2_incr<int>(file_type, ff);  /* вызов функции слияния */
            else vnsort2_incr<float>(file_type, ff);

        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}

template <typename DATA_TYPE> 
int vnsort2_incr(const char* file_type, const char* a)
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    DATA_TYPE b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */

    const char* read_sign;
    const char* write_sign;

    if (file_type == "dat") {
        read_sign = "r";
        write_sign = "w";
    }
    else {
        read_sign = "rb";
        write_sign = "wb";
    }

    if ((A = fopen(a, write_sign)) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        return -1;
    }
    if ((B = fopen("B", read_sign)) == NULL)
    {
        printf("\n Файл B не открывается");
        return -1;
    }
    if ((C = fopen("C", read_sign)) == NULL)
    {
        printf("\n Файл C не открывается");
        return -1;
    }

    const char* format;
    const char* format_with_space;

    if (a[0] == 'i') {
        format = "%i";
        format_with_space = " %i";
    }
    else {
        format = "%f";
        format_with_space = " %f";
    }

    rb = file_read(B, file_type, format, &b2);
    rc = file_read(C, file_type, format, &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            file_write(A, file_type, format_with_space, b2);
            while (file_read(B, file_type, format, &b2) > 0)
                file_write(A, file_type, format_with_space, b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            file_write(A, file_type, format_with_space, c2);
            while (file_read(C, file_type, format, &c2) > 0)
                file_write(A, file_type, format_with_space, c2);
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
                file_write(A, file_type, format_with_space, b2); b1 = b2;
                rb = file_read(B, file_type, format, &b2);
                continue;
            }
            else
            {
                file_write(A, file_type, format_with_space, c2);
                c1 = c2;
                rc = file_read(C, file_type, format, &c2);
                continue;
            }
        }

        if ((b2 >= b1) && (c2 < c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                file_write(A, file_type, format_with_space, b2);
                b1 = b2;
                rb = file_read(B, file_type, format, &b2);
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
        if ((b2 < b1) && (c2 >= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                file_write(A, file_type, format_with_space, c2);
                c1 = c2;
                rc = file_read(C, file_type, format, &c2);
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

void concat_files(const char* file_type, const char* result_file, const char* fname, ...)
{
    va_list ptr;
    const char* name = fname;
    va_start(ptr, fname);

    FILE* file = NULL;
    FILE* result = NULL;
    if (file_type == "dat") {
        result = fopen(result_file, "w");

        while (name) {
            file = fopen(name, "r");
            if (file != NULL)
                if (name[0] == 'i')
                {
                    int i;
                    while ((fscanf(file, "%d", &i)) != EOF) fprintf(result, " %d", i);
                }
                else
                {
                    float i;
                    while ((fscanf(file, "%f", &i)) != EOF) fprintf(result, " %f", i);
                }
            name = va_arg(ptr, const char*);
            fclose(file);
        }
        printf("Все текстовые файлы успешно объединены\n");
    }
    else {
        result = fopen(result_file, "wb");

        while (name) {
            file = fopen(name, "rb");
            if (file != NULL) {
                if (name[0] == 'i')  // Файл с целыми числами
                {
                    int i;
                    while (fread(&i, sizeof(int), 1, file)) fwrite(&i, sizeof(int), 1, result);
                }
                else // Файл с вещественными числами
                {
                    float i;
                    while (fread(&i, sizeof(float), 1, file)) fwrite(&i, sizeof(float), 1, result);
                }
            }
            name = va_arg(ptr, const char*);
            fclose(file);
        }
        printf("Все бинарные файлы успешно объединены\n");
    }
    va_end(ptr);

    fclose(result);
    return;
}

void print_bin(const char* file_name)
{
    FILE* file = fopen(file_name, "rb");

    if (file_name[0] == 'i')
    {
        int value;
        while (fread(&value, sizeof(int), 1, file)) printf("%i ", value);
    }
    else
    {
        float value;
        while (fread(&value, sizeof(float), 1, file)) printf("%f ", value);
    }

    fclose(file);
}

void print_txt(const char* file_name)
{
    FILE* file = fopen(file_name, "r");

    if (file_name[0] == 'i')
    {
        int value;
        while (fscanf(file, "%i", &value) != EOF) printf("%i ", value);
    }
    else if (file_name[0] == 'f')
    {
        float value;
        while (fscanf(file, "%f", &value) != EOF) printf("%f ", value);
    }

    fclose(file);
}

void incr(const char* file_type, const char* f)
{
    if (f[0] == 'i') vnsort1_incr<int>(file_type, f);
    else vnsort1_incr<float>(file_type, f);
}

void decr(const char* file_type, const char* f)
{
    if (f[0] == 'i') vnsort1_decr<int>(file_type, f);
    else vnsort1_decr<float>(file_type, f);
}

void menu(const char* f, const char* file_type)
{
    int c;
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
            return;
        default:
            printf("Ошибка! Введите число от 1 до %d", l);
            printf("\n");
            break;
        }
    }
}























