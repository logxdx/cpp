#include<stdio.h>


int main () {
    int x, y, z;
    char xc, yc, zc;

    x = 0xF0;
    xc = x;
    yc = y;
    y = 0x8D;
    z = x & y;

    printf("X : %d %X %o \n", x, x, x);
    printf("Xc : %d %X %o \n", xc, xc, xc);
    printf("y : %d %X %o \n", y, y, y);
    printf("yc : %d %X %o \n", yc, yc, yc);
    printf("z : %d %X %o \n", z, z, z);

    z = x>>2;
    printf("z : %d %X %o \n", z, z, z);

    z = y<<1;
    printf("z : %d %X %o \n", z, z, z);

    z = (x>>2) | (y<<1);
    printf("z : %d %X %o \n", z, z, z);



}