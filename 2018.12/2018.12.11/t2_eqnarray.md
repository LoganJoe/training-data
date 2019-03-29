$$
\begin{aligned}
ans&=\sum_{i=1}^{n}\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}i[gcd(i,j)=1]\newline
&=\sum_{i=1}^{n}\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}i\sum_{d|gcd(i,j)}\mu(d)\newline
&=\sum_{d=1}^{n}d\mu(d)\sum_{i=1}^{\left\lfloor\frac nd\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{n}{id^2}\right\rfloor}i\newline
&=\sum_{d=1}^{n}d\mu(d)\sum_{i=1}^{\left\lfloor\frac nd\right\rfloor}i\left\lfloor\frac{n}{id^2}\right\rfloor\newline
&=\sum_{d=1}^{\sqrt{n}}d\mu(d)\sum_{i=1}^{\left\lfloor\frac nd\right\rfloor }\left\lfloor \frac { \left\lfloor \frac { m } { d ^ { 2 } } \right\rfloor } { i } \right\rfloor
\end{aligned}
$$

注意到，前面的枚举只需要到$\sqrt{n}​$,而后面当$\mu(d)=0​$的时候没有意义。后面的部分可以关于$\lfloor\frac{n}{d}\rfloor​$整除分块。这样就过得去了。时间复杂度在$O(\sqrt{n}\log n)​$