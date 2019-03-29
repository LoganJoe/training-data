---
title: " DTOJ3873Game\t\t"
tags:
  - 博弈
url: 3631.html
id: 3631
categories:
  - DTOJ
  - Solution
date: 2018-08-26 20:30:41
---

和[DTOJ2152Madoka Magica](http://www.dtenomde.com/2018/08/author=jiangyutong/article=3431/)想法是一样的。 同样求出第$i$格子是白的，后面格子都是黑的SG值。 预处理出SG值的后缀异或和即可快速求出。 讲个笑话，写了正解然后在最后打了如下代码。

for(int i=1;i<=n;i++) if(A\[i\]) ans^=A\[i\];
puts(ans?"First":"Second");

还获得了87分的好成绩呢！