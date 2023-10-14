#ifndef ACCOUNT_MANAGE_H
#define ACCOUNT_MANAGE_H

void login(char input[], char result[], int *isLogged);

void postMessage(char input[], char result[], char message[], int isLogged);

void logout(char result[], int *isLogged);

void exitProgram(char result[]);

#endif