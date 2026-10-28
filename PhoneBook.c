#include "PhoneBook.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

Phone_Book phone_book[N] = {0};
int arr_size = 0;

static void ReadLine(char* line, size_t size)
{
    if (fgets(line, (int)size, stdin) == NULL)
    {
        line[0] = '\0';
        return;
    }

    size_t len = strlen(line);

    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }
    else
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    len = strlen(line);
    if (len > 0 && line[len - 1] == '\r')
    {
        line[len - 1] = '\0';
    }
}

static int ReadInt(const char* prompt)
{
    char line[LINE_SIZE];
    char* end;
    long value;

    while (1)
    {
        printf("%s", prompt);
        ReadLine(line, sizeof(line));

        errno = 0;
        value = strtol(line, &end, 10);

        while (*end == ' ' || *end == '\t')
        {
            end++;
        }

        if (line[0] != '\0' &&
            *end == '\0' &&
            errno != ERANGE &&
            value >= INT_MIN &&
            value <= INT_MAX)
        {
            return (int)value;
        }

        printf("Введите корректное целое число.\n");
    }
}

static int ID_Exists(int id, int except_index)
{
    for (int i = 0; i < arr_size; i++)
    {
        if (i != except_index && phone_book[i].man.id == id)
        {
            return 1;
        }
    }

    return 0;
}

static int EnterUniqueID(int except_index)
{
    int id;

    while (1)
    {
        id = ReadInt("Введите ID: ");

        if (id <= 0)
        {
            printf("ID должен быть больше 0!\n");
            continue;
        }

        if (ID_Exists(id, except_index))
        {
            printf("Такой ID уже есть в телефонной книге!\n");
            continue;
        }

        return id;
    }
}

int Enter_ID(void)
{
    return EnterUniqueID(-1);
}

void Enter_Man(char* line, const char* data, int required)
{
    while (1)
    {
        printf("Введите %s", data);

        if (required)
        {
            printf(" (обязательное поле): ");
        }
        else
        {
            printf(" (Enter — пропустить): ");
        }

        ReadLine(line, LINE_SIZE);

        if (required && line[0] == '\0')
        {
            printf("Это поле обязательно для заполнения!\n");
            continue;
        }

        return;
    }
}

void Enter_Contact(char contact_arr[N][LINE_SIZE],
                   const char* data)
{
    char line[LINE_SIZE];

    memset(contact_arr, 0, N * LINE_SIZE);

    printf("Введите %s по одному на строку.\n", data);
    printf("Для завершения нажмите Enter на пустой строке.\n");

    for (int i = 0; i < N; i++)
    {
        printf("%s [%d]: ", data, i + 1);
        ReadLine(line, sizeof(line));

        if (line[0] == '\0')
        {
            break;
        }

        strcpy(contact_arr[i], line);
    }
}

Man Man_Init(void)
{
    Man man = {0};

    man.id = Enter_ID();

    Enter_Man(man.first_name, "фамилию", 1);
    Enter_Man(man.second_name, "имя", 1);
    Enter_Man(man.third_name, "отчество", 0);
    Enter_Man(man.place_of_work, "место работы", 0);
    Enter_Man(man.post, "должность", 0);

    return man;
}

Contact Contact_Init(void)
{
    Contact contact = {0};

    Enter_Contact(contact.phone_number, "номер телефона");
    Enter_Contact(contact.email, "адрес электронной почты");
    Enter_Contact(contact.references, "ссылки на соцсети");
    Enter_Contact(contact.messengers, "профили в мессенджерах");

    return contact;
}

int Insert(void)
{
    if (arr_size >= N)
    {
        printf("Телефонная книга заполнена!\n");
        return -1;
    }

    Phone_Book book = {0};

    book.man = Man_Init();
    book.contact = Contact_Init();

    phone_book[arr_size] = book;
    arr_size++;

    printf("Контакт успешно добавлен!\n");

    return arr_size;
}

int Find(int num_id)
{
    for (int i = 0; i < arr_size; i++)
    {
        if (phone_book[i].man.id == num_id)
        {
            printf("Контакт с ID %d найден.\n", num_id);
            return i;
        }
    }

    return -1;
}

int Redact(int index)
{
    if (index < 0 || index >= arr_size)
    {
        return -1;
    }

    int choice;

    printf("\nРедактирование контакта:\n");
    Print_Line(index);

    printf("\nЧто изменить?\n");
    printf("1 - ID\n");
    printf("2 - Фамилия\n");
    printf("3 - Имя\n");
    printf("4 - Отчество\n");
    printf("5 - Место работы\n");
    printf("6 - Должность\n");
    printf("7 - Номера телефонов\n");
    printf("8 - Адреса электронной почты\n");
    printf("9 - Ссылки на соцсети\n");
    printf("10 - Профили в мессенджерах\n");
    printf("11 - Отмена\n");

    choice = ReadInt("Введите номер: ");

    switch (choice)
    {
        case 1:
        {
            int new_id = EnterUniqueID(index);
            phone_book[index].man.id = new_id;
            break;
        }

        case 2:
            Enter_Man(phone_book[index].man.first_name,
                      "фамилию", 1);
            break;

        case 3:
            Enter_Man(phone_book[index].man.second_name,
                      "имя", 1);
            break;

        case 4:
            Enter_Man(phone_book[index].man.third_name,
                      "отчество", 0);
            break;

        case 5:
            Enter_Man(phone_book[index].man.place_of_work,
                      "место работы", 0);
            break;

        case 6:
            Enter_Man(phone_book[index].man.post,
                      "должность", 0);
            break;

        case 7:
            Enter_Contact(phone_book[index].contact.phone_number,
                          "номер телефона");
            break;

        case 8:
            Enter_Contact(phone_book[index].contact.email,
                          "адрес электронной почты");
            break;

        case 9:
            Enter_Contact(phone_book[index].contact.references,
                          "ссылки на соцсети");
            break;

        case 10:
            Enter_Contact(phone_book[index].contact.messengers,
                          "профили в мессенджерах");
            break;

        case 11:
            printf("Редактирование отменено.\n");
            return 0;

        default:
            printf("Некорректный номер поля.\n");
            return -1;
    }

    printf("Контакт успешно отредактирован!\n");
    return 1;
}

int Delete(int index)
{
    if (index < 0 || index >= arr_size)
    {
        return -1;
    }

    for (int i = index; i < arr_size - 1; i++)
    {
        phone_book[i] = phone_book[i + 1];
    }

    arr_size--;

    memset(&phone_book[arr_size], 0, sizeof(Phone_Book));

    printf("Контакт успешно удалён!\n");

    return arr_size;
}

void Print(void)
{
    if (arr_size == 0)
    {
        printf("\nТелефонная книга пуста.\n");
        return;
    }

    printf("\n========== ТЕЛЕФОННАЯ КНИГА ==========\n");

    for (int i = 0; i < arr_size; i++)
    {
        Print_Line(i);
        printf("--------------------------------------\n");
    }
}

void Print_Line(int i)
{
    printf("\nID: %d\n", phone_book[i].man.id);
    printf("Фамилия: %s\n", phone_book[i].man.first_name);
    printf("Имя: %s\n", phone_book[i].man.second_name);
    printf("Отчество: %s\n", phone_book[i].man.third_name);
    printf("Место работы: %s\n", phone_book[i].man.place_of_work);
    printf("Должность: %s\n", phone_book[i].man.post);

    Print_Contact(phone_book[i].contact.phone_number,
                  "Номера телефонов");

    Print_Contact(phone_book[i].contact.email,
                  "Адреса электронной почты");

    Print_Contact(phone_book[i].contact.references,
                  "Ссылки на соцсети");

    Print_Contact(phone_book[i].contact.messengers,
                  "Профили в мессенджерах");
}

void Print_Contact(char contact_arr[N][LINE_SIZE],
                   const char* data)
{
    printf("%s:\n", data);

    int empty = 1;

    for (int j = 0; j < N; j++)
    {
        if (contact_arr[j][0] == '\0')
        {
            break;
        }

        printf("  %s\n", contact_arr[j]);
        empty = 0;
    }

    if (empty)
    {
        printf("  не указаны\n");
    }
}