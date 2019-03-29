#include<bits/stdc++.h>
#define N 1005
int n, top, type, k;
std::vector<std::string> s;
std::string  tmp;
char ch[N];
int main ()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf ("%s", ch); n = strlen (ch);
	scanf ("%d%d", &type, &k);
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) tmp.resize (j - i + 1), tmp[j - i] = ch[j],s.push_back(tmp);
	std::sort (s.begin(), s.end());
	for (int i = 0; i < s.size(); i++)
	{ 
		if (type == 0 && i>=1 && s[i] == s[i - 1])  continue;
		k--;
		if (k == 0)
		{
			std::cout << s[i] << "\n";
			return 0;
		}
	}
	puts ("-1");
	return 0;
}

