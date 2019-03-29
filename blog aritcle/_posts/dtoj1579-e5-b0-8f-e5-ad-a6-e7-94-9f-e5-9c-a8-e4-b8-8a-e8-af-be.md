---
title: " DTOJ1579小学生在上课\t\t"
tags:
  - 数论
url: 717.html
id: 717
categories:
  - DTOJ
  - Solution
date: 2018-02-20 17:00:13
---

题目实际上求的是$\[1,n\]$内的整数在$\\%n$意义下的逆元和。 一个数$a$在$\\%n$意义下有逆元当且仅当$a$与$n$互质。 记$a$在$\\%n$意义下逆元为$b$，即有$ab\\equiv 1(mod\\space n)$。 那么有$a^{-1}\\equiv b(mod\\space n)$，$b^{-1}\\equiv a(mod\\space n)$。 根据同余的加法原理，有$a+b\\equiv a^{-1}+b^{-1}(mod\\space n)$。 由于题目要求的逆元是要在$n$以内的，因此逆元和也就是有逆元的数之和，即就是与$n$互质的数之和。 根据欧拉函数的性质，答案即为$\\frac{n*φ(n)}{2}$。