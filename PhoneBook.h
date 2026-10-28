#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#define N 100
#define LINE_SIZE 51

typedef struct Man
{
    int id;
    char first_name[LINE_SIZE];
    char second_name[LINE_SIZE];
    char third_name[LINE_SIZE];
    char place_of_work[LINE_SIZE];
    char post[LINE_SIZE];
} Man;

typedef struct Contact
{
    char phone_number[N][LINE_SIZE];
    char email[N][LINE_SIZE];
    char references[N][LINE_SIZE];
    char messengers[N][LINE_SIZE];
} Contact;

typedef struct Phone_Book
{
    Man man;
    Contact contact;
} Phone_Book;

extern Phone_Book phone_book[N];
extern int arr_size;

int Insert(void);
int Find(int num_id);
int Redact(int index);
int Delete(int index);
void Print(void);

Man Man_Init(void);
Contact Contact_Init(void);

int Enter_ID(void);
void Enter_Man(char* line, const char* data,
               int required);
void Enter_Contact(char contact_arr[N][LINE_SIZE],
                   const char* data);

void Print_Line(int i);
void Print_Contact(char contact_arr[N][LINE_SIZE],
                   const char* data);

#endif