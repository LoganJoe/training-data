---
title: " DTOJ1810期望面积\t\t"
tags:
  - 期望
  - 概率
  - 计算几何
url: 656.html
id: 656
categories:
  - Solution
date: 2018-02-17 20:41:06
---

我们要考虑每条直线对于答案的贡献。对于形成一条直线的两点A，B，其出现概率为$p\_Ap\_B$，对于答案的贡献为$\\overrightarrow{OA}\\times\\overrightarrow{OB}/2$,但AB被取要求AB右侧（顺时针方向）的点都不出现，所以我们可以得到AB的期望贡献为： $$\\overrightarrow{OA}\\times\\overrightarrow{OB}/2 \\times p\_A\\times p\_B\\times \\prod{(1-p_k)}$$ 暴力枚举线段AB和一个点K，计算即可。