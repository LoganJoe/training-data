---
title: " LOJ556「Antileaf's Round」咱们去烧菜吧\t\t"
tags:
  - 多项式
  - 生成函数
url: 6425.html
id: 6425
categories:
  - Solution
date: 2019-02-08 14:13:38
---

绿油油的题啊...牛逼。 考虑将完全背包化作多重背包。答案的生成函数为 $$A(x)=\\prod_{i=1}^m \\left(\\sum_{k=0}^{b\_i}x^{a\_ik}\\right)=\\prod_{k=1}^m \\frac{1-x^{a\_i(b\_i+1)}}{1-x^{a\_i}}$$ 两边取对数以化乘为加： $$\\ln A(x)=\\sum\_{i=1}^m \\left(\\ln\\left(1-x^{a\_i(b\_i+1)}\\right)-\\ln\\left(1-x^{a\_i}\\right)\\right)$$ 而我们知道 $$\\ln(1-x^k)=-\\sum\_{i=1}^\\infty\\frac{x^{ik}}i$$ 那么就很容易可以求得后面的东西了。得到$ln A(x)$，exp回去即求得答案。 什么时候写一写这套题的第二题呢？先咕着吧2333