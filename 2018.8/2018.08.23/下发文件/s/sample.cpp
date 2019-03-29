#include "s.hpp"
#include "grader.cpp" 
//using namespace std;
std::vector<std::string> guess (int n, int a, int b, int t)
{
	std::vector<std::string> v (n, "0");
	if (t == 1)
	{
		std::vector<std::string> res;
		for (int i = 1; i <= n; i++)
		{
			v[i - 1] = "1";
			res.push_back (prod (v));
			v[i - 1] = "0";
		}
		return res;
	}
	if (t == 2)
	{
		for (int i = 0; i<n; i++)
		{
			v[i].resize (i * 2 + 1);
			for (int j = 1; j <= i * 2; j++) v[i][j] = '0';
			v[i][0] = '1';
		}
		std::string res = prod (v);
		std::vector<std::string> ans;
		for (int i = 0; i < n; i++) ans.push_back (res.substr (2 * i, 2));
		for (int i = 0; i<n; i++) if (ans[i][0] == '0') ans[i][0] = ans[i][1], ans[i].resize (1);
		std::reverse (ans.begin (), ans.end ());
		return ans;
	}
	if (t == 3)
	{
		std::vector<std::string> ans (n, "0");
		for (int i = 0; i<n - 1; i += 3)
		{
			v[i] = "1", v[i + 1] = "100", v[i + 2] = "10000";
			std::string res = prod (v);
			ans[i] = res.substr (4, 2);
			ans[i + 1] = res.substr (2, 2);
			ans[i + 2] = res.substr (0, 2);
			for (int j = 0; j<n; j++) v[j] = "0";
		}
		v[24] = "1", ans[24] = prod (v);
		for (int i = 0; i<n; i++) if (ans[i][0] == '0') ans[i][0] = ans[i][1], ans[i].resize (1);
		return ans;
	}

}
