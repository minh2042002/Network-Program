#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "logging.h"

/**
 * Ghi thông tin thực hiện lệnh vào log.
 * 
 * @param func Biểu thị chức năng số 1-4.
 * @param input Dữ liệu nhập từ bàn phím.
 * @param result kết quả thực thi của lệnh được lưu vào log
///                 +OK nếu thành công
///                 -ERR nếu có lỗi.
 */
void saveLog(int func, const char *input, const char *result)
{
    time_t t = time(NULL);
    struct tm ltm = *localtime(&t);

    FILE *fLog = fopen("log_20205003.txt", "a");
    
    fprintf(fLog, "[%02d/%02d/%04d %02d:%02d:%02d] $ %d $ %s $ %s\n",
            ltm.tm_mday, 
            ltm.tm_mon + 1, 
            ltm.tm_year + 1900,
            ltm.tm_hour, 
            ltm.tm_min, 
            ltm.tm_sec,
            func, 
            input, 
            result);

    fclose(fLog);
}