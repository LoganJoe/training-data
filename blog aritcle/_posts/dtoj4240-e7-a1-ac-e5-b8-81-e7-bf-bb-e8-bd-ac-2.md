---
title: " DTOJ4240硬币翻转\t\t"
tags:
  - 思路
url: 7100.html
id: 7100
categories:
  - Solution
date: 2019-03-24 12:33:15
---

考虑首先随机出来一个$01$序列。其期望正确个数为$50$。 我们注意到其仅对猜对的硬币给予翻转操作。那么我们不妨让所有硬币全都猜错，最后取反，来避免其随机的翻转。 考虑我们依次确定每个位置，让这个位置的硬币翻到错误的状态。 假设当前位置硬币朝向对了。那么翻转一次这个硬币会翻到错误的哪面。正确数至少$-1$。因为随机翻转，后面还会有硬币翻转到错误的哪面。 假设当前位置硬币朝向错了。那么翻转一次这个硬币会翻到正确的哪面。这个时候正确数是不变或者$+1$的。我们要把这枚硬币翻回去。但是考虑其随后的那个随机翻转，有可能将其翻回错误的哪面，那么我们又会将其翻到正确的状态。 但是，每次其随机是在所有数内随机的。也就是说，其翻转到这一位的几率永远为$\\frac{1}{100}。那么我们就不停的对这位做操作，并且不回翻，直到其是由朝向对翻转到朝向错为止。这样在期望次数内是可以得到满分的。

#include "coin.h"
#include "grader.cpp"
#include <string>

void guess(){
	std::string s = "";
	srand(233);
	for (int x = 0; x < 100; ++x) s += rand() % 2 ? "0" : "1";
	int nowcorrect = ask(s);
	if (nowcorrect > 50) 
	{
		for (int i = 0; i < 100; i++) 
			if (s\[i\] == '1') s\[i\] = '0';
			else s\[i\] = '1';
		nowcorrect  = ask(s);
	}
	while(ask(s) > 0){
	for (int i = 0; i < 100 && nowcorrect > 0; i++)
	{
		while (1)
		{
			if (s\[i\] == '1') s\[i\] = '0';
			else s\[i\] = '1';

			int newcorrect = ask (s);

			if (newcorrect < nowcorrect) // switch to right WRONG place.
			{
				nowcorrect = newcorrect;
				break;
			}
			nowcorrect = newcorrect;
		}
	}
	}
	
	for (int i = 0; i < 100; i++) 
		if (s\[i\] == '1') s\[i\] = '0';
		else s\[i\] = '1';
	int fullcorrect = ask(s); 
}