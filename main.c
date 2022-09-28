#include "file_system.h"

int main(void)
{
    file_write("./test.txt", "Hello, world!");
    
    char buff[64];
    file_read("./test.txt", buff, 64);

    printf("%s\n", buff);
    return 0;
}