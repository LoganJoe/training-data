---
title: " DTOJ3136修路\t\t"
tags:
  - 思路
  - 斯坦纳树
  - 状压dp
url: 2295.html
id: 2295
categories:
  - Solution
date: 2018-06-09 20:19:57
---

观察到d很小。那么这肯定有玄机。 然后我们可以想到一个￥dp￥，设状态￥S￥表示￥S￥中的所有点联通，￥dis\[s\]\[i\]￥为￥s￥中所有点与点$i$的距离和。这个东西可以枚举$s$的子集然后由子集转移而来，另外的情况（之间不相交）用$spfa$来找到答案。即有： $$\\forall s' \\subset s,dis\[s\]\[i\]=\\min\\{dis\[s'\]\[i\]+dis\[s-s'\]\[i\]\\}$$ 以及 $$dis\[s\]\[v\]=\\min\\{dis\[s\]\[u\]+w_{u \\to v}\\}$$ 之后我们考虑答案怎么得到。设ans\[s\]为集合s中所有点联通的最小花费。那么很明显，前后每对点都要同时联通。枚举所有的dis\[s+s<<d\]\[i\]去最小值可以得到答案。另外不同点对的答案也可以不相交，那么枚举子集转移即可。 第一步中，dis\[s\]\[i\]的转移类似于这样：

std::queue<int>q;
    for(int i=1;i<=n;i++)
    {   
        for(int k=S&(S-1);k;k=S&(k-1)) dis\[S\]\[i\]=std::min(dis\[S\]\[i\],dis\[k\]\[i\]+dis\[S-k\]\[i\]);
        if(dis\[S\]\[i\]!=1e9) vis\[i\]=1,q.push(i);else vis\[i\]=0;
    }
    while(!q.empty())
    {
        int u=q.front();q.pop();vis\[u\]=0;
        for(int i=head\[u\];i;i=e\[i\].next)
        {
            int v=e\[i\].v;
            if(dis\[S\]\[v\]>dis\[S\]\[u\]+e\[i\].w) 
            {
                dis\[S\]\[v\]=dis\[S\]\[u\]+e\[i\].w;
                if(!vis\[v\]) vis\[v\]=1,q.push(v);
            }
        }
    }

答案的状压dp注意要考虑的是一对的点的答案。

for(int S=0;S<=(1<<d)-1;S++)
    {
        ans\[S\]=1e9;
        for(int i=1;i<=n;i++) ans\[S\]=std::min(ans\[S\],dis\[S+(S<<d)\]\[i\]);
        for(int k=S&(S-1);k;k=S&(k-1)) ans\[S\]=std::min(ans\[S\],ans\[k\]+ans\[S-k\]);
         
    }

这就是斯坦纳树了。