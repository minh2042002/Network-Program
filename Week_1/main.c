#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "logging.h"
#include "accountManage.h"

char input[50];    // Dữ liệu nhập từ bàn phím
char result[5];    // Kết quả thực thi của lệnh

int isLogged = 0;  // Trạng thái đăng nhập
char message[255]; // Lưu trữ nội dung của thông điệp

void printMenu()
{
    printf("\n  MENU:\n");
    printf("1. Login\n");
    printf("2. Post message\n");
    printf("3. Logout\n");
    printf("4. Exit\n");
    printf("Enter selection 1-4: ");
}

int main()
{
    while (1)
    {
        strcpy(input, "");

        printMenu();

        int selection;
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            login(input, result, &isLogged);
            break;

        case 2:
            postMessage(input, result, message, isLogged);
            break;

        case 3:
            logout(result, &isLogged);
            break;

        case 4:
            exitProgram(result);
            break;
        default:
            printf("Please choose from 1 to 4.\n");
        }
        saveLog(selection, input, result); // ghi vào log
    }

    return 0;
}
