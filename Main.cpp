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

    printf("int1=");
    int1.print();
    printf("\n");

    printf("int2=");
    int2.print();
    printf("\n");

    Integer int3 = int1 + int2;
    printf("int1+int2=");
    int3.print();
    printf("\n");

    int3 = int1 * int2;
    printf("int1*int2=");
    int3.print();
    printf("\n");
    return 0;
}