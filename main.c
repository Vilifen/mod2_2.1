
#include "PhoneBook.h"

#include <stdio.h>
#include <stdlib.h>

static int ReadMenuChoice(void)
{
    char line[51];
    char* end;
    long value;

    while (1)
    {
        printf("Введите команду: ");

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return 4;
        }

        value = strtol(line, &end, 10);

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' &&
            value >= 1 && value <= 4)
        {
            return (int)value;
        }

        printf("Введите число от 1 до 4.\n");
    }
}

static int ReadID(void)
{
    char line[51];
    char* end;
    long value;

    while (1)
    {
        printf("Введите ID контакта: ");

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return -1;
        }

        value = strtol(line, &end, 10);

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' &&
            value > 0 && value <= 2147483647L)
        {
            return (int)value;
        }

        printf("Введите корректный положительный ID.\n");
    }
}

static void Menu(void)
{
    int choice;
    int num_id;
    int index;

    printf("\n========== МЕНЮ ==========\n");
    printf("1 - Добавить контакт\n");
    printf("2 - Редактировать контакт\n");
    printf("3 - Удалить контакт\n");
    printf("4 - Выход\n");

    choice = ReadMenuChoice();

    switch (choice)
    {
        case 1:
            Insert();
            break;

        case 2:
            if (arr_size == 0)
            {
                printf("Телефонная книга пуста.\n");
                break;
            }

            num_id = ReadID();
            index = Find(num_id);

            if (index == -1)
            {
                printf("Контакт с таким ID не найден.\n");
            }
            else
            {
                Redact(index);
            }

            break;

        case 3:
            if (arr_size == 0)
            {
                printf("Телефонная книга пуста.\n");
                break;
            }

            num_id = ReadID();
            index = Find(num_id);

            if (index == -1)
            {
                printf("Контакт с таким ID не найден.\n");
            }
            else
            {
                Delete(index);
            }

            break;

        case 4:
            exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    printf("Задание 2.1: Телефонная книга\n");

    while (1)
    {
        Print();
        Menu();
    }

    return 0;
}
