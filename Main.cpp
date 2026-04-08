#include "Integer.h"

int main()
{
    Integer int1 = 99999;
    Integer int2 = 99999;
    int1 = int1 + int2;
    int1.print();
    printf("\n");
    Integer int3 = -1234;
    Integer int4 = 7855;
    int4 = int4 + int3;
    int4.print();
    printf("\n");
    int4 = int2 * int3;
    int4.print();
    return 0;
}