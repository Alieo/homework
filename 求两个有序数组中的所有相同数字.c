/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Mar 2019 08:42:55 PM CST
 ************************************************************************/
/*
题目：给你两个有序数组，找出两数组中都有的所有数字
方法１：哈希：哈希 + 抵消。
        先将a1存入哈希中，放a2时如果有冲突，输出并抵消
方法２：双指针O(n + m)：类似于归并排序的合并操作(本题最优)
方法３：一个数组遍历，一个数组二分O(nlogm)
* */
#include<stdio.h>
#include<stdlib.h>

void func(int *a1, int *a2, int len1, int len2) {
    int *temp = (int *)malloc(sizeof(int) * (len1 + len2));
    int p1 = 0, p2 = 0, i = 0;
    while (p1 < len1 && p2 < len2) {
        if (a1[p1] == a2[p2]) temp[i++] = a1[p1];
        else if (a1[p1] > a2[p2]) {
            p2++; continue;
        } else if (a1[p1] < a2[p2]) {
            p1++; continue;
        }
        p1++;
        p2++;
    }
    for (int j = 0; j < i; j++) { 
        printf(" %d", temp[j]);
    }
} 

int main() {
    int a1[5] = {2, 4, 7, 7, 7};
    int a2[5] = {1, 4, 6, 7, 7};
    func(a1, a2, 5, 5);
    return 0;
}
