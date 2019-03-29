---
title: " DTOJ2926Solar Panels\t\t"
tags:
  - 数学
url: 4269.html
id: 4269
categories:
  - DTOJ
  - Solution
date: 2018-10-21 11:59:47
---

考虑枚举答案$g$，如果$g$可行的话，说明 $$\\left \\lfloor \\frac{smin-1}{g}\\right \\rfloor<\\left \\lfloor \\frac{smax}{g}\\right \\rfloor$$ $$\\left \\lfloor \\frac{wmin-1}{g}\\right \\rfloor<\\left \\lfloor \\frac{wmax}{g}\\right \\rfloor$$ 都成立。 下取整的值最多只会有根号个，直接数论分块即可。