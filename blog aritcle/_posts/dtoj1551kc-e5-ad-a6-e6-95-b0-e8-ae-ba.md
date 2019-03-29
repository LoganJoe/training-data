---
title: " DTOJ1551KC学数论\t\t"
tags:
  - 数论
url: 1187.html
id: 1187
categories:
  - Solution
date: 2018-03-22 16:12:35
---

我们注意到要求的东西： \\\[\\sum_{i=1}^{a}{\\sum_{j=1}^{b}{\\sum_{k=1}^{c}{d(i\*j\*k)}}}\\\] 这个东西中，abc都很小，可以满足$n^3$复杂度。我们考虑如何求出$d(i\*j\*k)$. 先来了解一个东西： $$\\sigma\_x(n)=\\sum\_{d|n}{d^x}$$ 这个是除数函数。显然在x=0时函数值为x的约数个数。 除数函数是积性函数，但不是完全积性函数。因此我们可以用线性筛求出。给出以下代码:

void get_facnum()
{
    f\[1\]=1;
    for(int i=2;i<=N;i++)
    {
        if(!vis\[i\]) pri\[++cnt\]=i,d\[i\]=1,f\[i\]=2;
        for(int j=1;j<=cnt && i*pri\[j\]<=N;j++)
        {
            vis\[i*pri\[j\]\]=1;
            if(i%pri\[j\]==0)
            {
                f\[i\*pri\[j\]\]=f\[i\]/(d\[i\]+1)\*(d\[i\]+2);
                d\[i*pri\[j\]\]=d\[i\]+1;
                break;   
            }
            f\[i\*pri\[j\]\]=f\[i\]\*2;
            d\[i*pri\[j\]\]=1;
        }
    }
}

那么就可以在$O(1)下求的一个数的d(x).f\[i\]表示一个数的约数个数。