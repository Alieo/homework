/*************************************************************************
> File Name: a + b.c
> Author: xinyue
> Mail: 
> Created Time: 2018年08月21日 星期二 10时21分39秒
************************************************************************/

//a + b 的值

#include <stdio.h>

int main() {

    int a, b;
    while(scanf("%d %d", &a, &b) != EOF) {
        int c, d;
        while(b != 0) {
            c = a ^ b;
            d = (a & b) << 1;
            a = c;
            b = d;   //进位
        }
        printf("%d", a);
    }
    return 0;
}
