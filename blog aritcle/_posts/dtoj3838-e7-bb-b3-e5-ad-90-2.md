---
title: " DTOJ3838绳子\t\t"
tags:
  - 思路
  - 线段树
url: 3123.html
id: 3123
categories:
  - Solution
date: 2018-07-28 14:06:15
---

肯定是要染成两种颜色，然后再折过去最优。 假设绳子上只有两种颜色，那么能折到长度为 2 ，当且仅当除了头尾以外，每个极长颜色相同段长度都为偶数。也就是说，除了第一段以外，每一段的开头的 下标是同奇偶的。 这个玩意很科学对吧。因为假设有奇数长度，那么就折补到一块儿去了。 那么我们先枚举一种颜色a， 然后考虑染另外哪种颜色最优。枚举第二个块开头的奇偶性，因为确定了这个开头后面的开头也都确定了。考虑另外的一种颜色b，代价为n-suma-sumb，suma，sumb分别为颜色的个数。另外如果某个奇偶性不对并且相邻，那么我们会另外需要一点的代价把这个位置的颜色改对。 再考虑另外一种颜色要怎么找。枚举颜色a的每一段，然后再线段树上查询最小值。处理相邻的情况只要将相邻需要的代价+1，查询完再改回去就好了。 还是很好理解的。