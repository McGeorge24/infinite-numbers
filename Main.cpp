#include "Integer.h"

int main()
{
    char buffer[20];

    printf("Vpisi dve stevili:\nStevilo1: ");

    scanf("%s", buffer);
    Integer int1(buffer);

    printf("Stevilo2: ");
    scanf("%s", buffer);
    Integer int2(buffer);

    printf("int1=%s\n", int1.to_str().c_str());

    printf("int2=%s\n", int2.to_str().c_str());

    Integer int3 = int1 + int2;
    printf("int1+int2=%s\n", int3.to_str().c_str());
    int3 = int1 * int2;
    printf("int1*int2=%s\n", int3.to_str().c_str());
    return 0;
}