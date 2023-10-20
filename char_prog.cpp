#include <stdio.h>

int main() {

    int x, y, i;
    unsigned int z;
    char xc, yc;
    unsigned char zc;
    float f1 = 1, f2 = 0, f3;
    for (i = 0; i < 100; i++) f2 += 100;
    if (f1 == f2) printf(" f1 and f2 are equal \n");
    else printf(" f1 and f2 are different \n");
    f1 = 1e30; f2 = 1e-30;
    f3 = f1 + f2;
    if (f3 == f1) printf(" f1 and f2 are equal \n");
    else printf(" f1 and f2 are different \n");
    xc = 0x81; x = xc;
    printf("x is : %x \n", x);
    zc = 0x81; z = zc;
    printf("z is : %x \n", z);
    x = -14;
    printf("x in hex is %x \n", x);
    printf("x in octal is %o \n", x);
    zc = -14;
    if (14 < zc) printf("14 is less than -14 \n");
    else printf(" 14 is greater than or equal to -14 \n");
    printf("zc is : %d %x %o \n", zc, zc, zc);
    printf("zc >> 1  is : %d \n", zc>>1);
    printf("-14 >> 1  is : %d \n", (-14)>>1);
    printf("-14 << 1  is : %d \n", (-14)<<1);
}
