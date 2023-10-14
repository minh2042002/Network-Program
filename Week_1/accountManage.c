#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "accountManage.h"
#include "user.h"

/// @brief Đăng nhập vào hệ thống quản lí
/// @param input dữ liệu nhập từ bàn phím
/// @param result kết quả thực thi của lệnh được lưu vào log
///                 +OK nếu thành công
///                 -ERR nếu có lỗi
/// @param isLogged Trạng thái đăng nhập, 1 - Đã đăng nhập, 0 - Chưa đăng nhập
void login(char input[], char result[], int *isLogged)
{
    if (*isLogged == 1)
    {
        printf("You are logged in.\n");
        strcpy(result, "-ERR");
    }
    else
    {
        char username[100];
        printf("Username: ");
        scanf("%s", username);

        strcpy(input, username);
        
        int loginStatus = searchByUsername(username);
        
        switch (loginStatus)
        {
        case 0:
            printf("Account is not exist!\n");
            strcpy(result, "-ERR");
            break;
        case 1:
            printf("Login is success with %s", username);
            *isLogged = 1;
            strcpy(result, "+OK");
            break;
        case 2:
            printf("Account is locked");
            strcpy(result, "-ERR");
            break;
        }
    }
}

/// @brief Post message lên hệ thống
/// @param input dữ liệu từ bàn phím
/// @param result kết quả thực thi của lệnh được lưu vào log
///                 +OK nếu thành công
///                 -ERR nếu có lỗi
/// @param message thông điệp được nhập từ bàn phím
/// @param isLogged Trạng thái đăng nhập, 1 - Đã đăng nhập, 0 - Chưa đăng nhập
void postMessage(char input[], char result[], char message[], int isLogged)
{
    if (isLogged) // Logined
    {
        printf("Enter message:");   
        getchar();
        fgets (message, 255, stdin);

        printf("Message: %s", message);
        // printf("%s", message);

        strcpy(input, message);
        strcpy(result, "+OK");
    }
    else
    {
        printf("Please login to message!\n");
        strcpy(result, "-ERR");
    }
}

/// @brief Logout khỏi hệ thống
/// @param result kết quả thực thi của lệnh được lưu vào log
///                 +OK nếu thành công
///                 -ERR nếu có lỗi
/// @param isLogged Trạng thái đăng nhập, 1 - Đã đăng nhập, 0 - Chưa đăng nhập
void logout(char result[], int *isLogged)
{
    if (*isLogged)
    {
        printf("Logout is success.\n");
        *isLogged = 0;
        
        strcpy(result, "+OK");
    }
    else
    {
        printf("You have not logged.\n");
        strcpy(result, "-ERR");
    }
}

/// @brief Đóng chương trình
/// @param result kết quả thực thi của lệnh được lưu vào log
///                 +OK nếu thành công
///                 -ERR nếu có lỗi
void exitProgram(char result[])
{
    printf("Program is close.\n");
    strcpy(result, "+OK");
    exit(0);
}