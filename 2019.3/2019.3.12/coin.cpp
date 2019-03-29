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
			if (s[i] == '1') s[i] = '0';
			else s[i] = '1';
		nowcorrect  = ask(s);
	}
	while(ask(s) > 0){
	for (int i = 0; i < 100 && nowcorrect > 0; i++)
	{
		if (s[i] == '1') s[i] = '0';
		else s[i] = '1';
		
		int newcorrect = ask(s);
	
		if (newcorrect < nowcorrect) // switch to right WRONG place.
		{
			nowcorrect = newcorrect;
			continue;
		} 
		else 
		{
			if (s[i] == '1') s[i] = '0';
			else s[i] = '1';
			//if (nowcorrect == newcorrect) i--, nowcorrect = ask(s);
			nowcorrect = newcorrect - 1;
		}
	}
	}
	
	for (int i = 0; i < 100; i++) 
		if (s[i] == '1') s[i] = '0';
		else s[i] = '1';
	int fullcorrect = ask(s); 
}
