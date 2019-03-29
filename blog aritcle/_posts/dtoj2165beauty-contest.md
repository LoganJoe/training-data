---
title: " DTOJ2165Beauty Contest\t\t"
tags:
  - 凸包
  - 旋转卡壳
url: 629.html
id: 629
categories:
  - Solution
date: 2018-02-17 11:15:58
---

平面上的最远点对，一定在凸包上。 那么我们只需要对这些点找出凸包然后做一下旋转卡壳即可。 凸包的话找出以y升序为第一关键字，以x降序为第二关键字，取出基准点，再让其他点以基准点的极角排序。然后维护一个仅凸的栈即可。最后栈中的点均是凸包上的点。 旋转卡壳的做法则是维护两个指针i，j，分别记录当前点和对锺点。绕着卡一遍过去即可。 Code： \[cc lang="C++"\] #include using namespace std; #define N 50005 #define ll long long int n, top; struct node { int x, y; }p\[N\],p0,s\[N\]; long long cross(int x1, int y1, int x2, int y2){return (ll)x1 * y2 - (ll)x2 * y1;} long long compare(node a, node b, node c){return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);} bool cmp(node a, node b) { double A = atan2(a.y - p0.y, a.x - p0.x); double B = atan2(b.y - p0.y, b.x - p0.x); if (A != B)return A p\[i\].y || (p0.y == p\[i\].y && p0.x > p\[i\].x)) p0 = p\[i\], k = i; } swap(p\[1\], p\[k\]); sort(p + 2, p + 1 + n,cmp); s\[1\] = p\[1\], s\[2\] = p\[2\], top = 2; for(int i = 3; i <= n;) { if (top - 1 && compare(s\[top - 1\], p\[i\], s\[top\]) >= 0) top--; else s\[++top\] = p\[i++\]; } } long long getmax() { long long res = 0; if (top == 2) return dis(s\[1\], s\[2\]); s\[++top\] = s\[1\]; int j = 3; for (int i = 1; i < top; i++) { while (compare(s\[i\], s\[i + 1\], s\[j\]) < compare(s\[i\], s\[i + 1\], s\[j + 1\])) j = (j + 1) % top; res = max(res, max(dis(s\[i\], s\[j\]), dis(s\[i + 1\], s\[j\]))); } return res; } int main() { scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d%d", &p\[i\].x, &p\[i\].y); graham(); printf("%lld\\n", getmax()); } \[/cc\]