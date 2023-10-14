#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "user.h"

/* Tìm kiếm tài khoản trong file account.txt, kiểm tra tài khoản có tồn tại hay không
 * 
 * @param userLogin Tên người dùng cần tìm kiếm
 * @return int:
 *         - 1 nếu tài khoản tồn tại và hợp lệ
 *         - 2 nếu tài khoản bị khóa
 *         - 0 nếu tài khoản không tồn tại/không hợp lệ
 */
int searchByUsername(char userLogin[100])
{
    User curUser;
    FILE *file = fopen("account.txt", "r");
    while (fscanf(file, "%s %d", curUser.username, &curUser.status) == 2)
    {
        if (strcmp(curUser.username, userLogin) == 0)
        {
            if (curUser.status == 1) return 1; 
            else if (curUser.status == 0) return 2;
        }
    }
    fclose(file);
    return 0;
}