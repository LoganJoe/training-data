---
title: " DTOJ3601Judging Moose\t\t"
tags:
  - 无标签
url: 1469.html
id: 1469
categories:
  - DTOJ
  - Solution
date: 2018-04-15 13:21:39
---

思博题。 看题比写题久，题目比代码长系列。 努力压出的又短又好看的代码↓

#include<cstdio>
int main()
{
    int a,b;scanf("%d%d",&a,&b);
    return a+b?printf(a^b?"Odd %d":"Even %d",(a>b?a:b)<<1):puts("Not a moose"),0;
}