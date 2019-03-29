### 沙雕出题

##### 一个离线算法

考虑对操作分块，每 $T$ 个操作一起处理。对于每块操作，选取操作 $1$、$2$、$4$、$5$ 中的 $u$，操作 $3$ 中的 $u$，$par_u$，$v$ 作为关键点。对所有关键点建虚树，将虚树的边，以虚树为根且内部没有关键点的子树，序树每个点本身，分别看作一个整体。这样所有的操作都会定位到若干个整块，对于每块维护一个有序表即可。单次操作 $4$、$5$ 的时间复杂度为 $O(T \log^2 n)$，重构块的时间复杂度为 $O(n \log n)$，取 $T = \sqrt{\frac{n}{\log n}}$，

时间复杂度为 $O((n\log n)^{1.5})$。

##### 一个在线算法

考虑维护LCT所对应的ETT，当在LCT进行access操作时对ETT进行相应的修改。如此一来，所有操作都会对应到一个区间，而在ETT上进行的操作只有区间加、区间移动与问区间第 $k$ 小，直接块状链表维护可即可。设平均块长为 $T$，则合并相邻两块、分离某一块的时间复杂度为 $O(T)$，access的时间复杂度为均摊 $O(T\log n)$，询问区间第 $k$ 小的复杂度为 $O(\frac{n\log^2n}{T})$，取 $T = \sqrt{n\log n}$，

时间复杂度为 $O((n\log n)^{1.5})$。

事实上，在实现的时候并不需要维护LCT，可以使用平衡树在ETT上直接模拟access。令左括号的点权 $1$，右括号的点权为 $-1$，access本质上是两步的迭代：

1.找到当前节点 $x$ 的父节点 $f$ 并将 $x$ 移动到 $f$ 后。

2.找到当前节点 $x$ 所在重链的链顶 $y$，并将指针移动到 $y$。

对于第一步，$f$ 是 $x$ 左侧第一个满足 $f$ 到 $x$ （包括 $f$ 但不包括 $x$）之间的点权和为 $1$ 的节点。

对于第二步，$y$ 是 $x$ 左侧最后一个满足 $y$ 与 $x$ 之间的点权全是 $1$ 的节点。

维护区间内点的数量、区间的点权和与区间后缀点权和的最大值，就可以找到这两个节点了。

使用 splay 估计可以分析到 $O(n \log n)$，可以在一定程度上代替 top tree（只要没有换根操作）。

### 人与三

对于任意数论函数 $P(x)$ ，定义 $(\sum P)(x) = \sum_{i=1}^{x} P(i)$。 将 $1, 2, \dots, \lfloor \sqrt{n} \rfloor, \dots , \lfloor \frac{n}{2}\rfloor, n$ 作为 $x$ 带 $(\sum P)(x)$ 后可以得到 $O(\sqrt{n})$ 个点值，在后文中，我们将这张表称作 $P(x)$ 的点值表示。

此外，后文中所有对于两个函数的乘法都定义为狄利克雷卷积。 

众所周知，对于如果知道了两个函数 $F, G$ 的点值表示，是可以算出 $(\sum(F \ast G))(n)$ 的。

然后用似的方法，实际上是可以求出 $\sum(F \ast G)$ 的点值表示的。

$$
(\sum(F \ast G)) (x) = \sum_{i=1}^{\lfloor \sqrt{x} \rfloor}((\sum F)(i)  -(\sum F)(i - 1))(\sum G)(\lfloor \frac{x}{i} \rfloor) \\  + \sum_{i=1}^{\lfloor \sqrt{x} \rfloor}((\sum G)(i) -(\sum G)(i - 1))(\sum F)(\lfloor \frac{x}{i} \rfloor)  \\ - (\sum F)(\lfloor \sqrt{x} \rfloor)(\sum G)(\lfloor \sqrt{x} \rfloor)
$$

这样的话直接求狄利克雷卷积卷积的复杂度是 $O(n^{\frac{3}{4}})$ 的。

如果使用 $O(n \log n)$ 的做法去算 $\sum(F \ast G) $ 的 $O(n ^ {\frac{2}{3}})$ 项，那么就可以在 $O(n^{\frac{2}{3}} \log n) $ 的时间复杂度内求任意两数论函数的狄利克雷卷积了。

在本题中，最终要算的函数是 $(\sum(1 \ast H) ^ m)(n)$。直接使用上面所说的算法即可。

时间复杂度为 $O(n^\frac{2}{3}\log n \log m)$。

### 道良心题