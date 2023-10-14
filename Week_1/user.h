#ifndef USER_H
#define USER_H

typedef struct
{
    char username[100];
    int status;
} User;

int searchByUsername(char userLogin[100]);

#endif