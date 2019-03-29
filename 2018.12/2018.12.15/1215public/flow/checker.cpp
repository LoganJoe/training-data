#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<deque>
#include<cassert>
#include<complex>
using namespace std;

FILE *inf;
string logFile;

void Grade(bool flag) {
	FILE *grad;
	if(logFile.size() > 0) {
		grad = fopen(logFile.c_str(),"w");
		if(grad == NULL) grad = stderr;
	} else grad = stderr;
	
	if(flag)
		fprintf(grad, "1.00 Correct!\n");
	else
		fprintf(grad, "0.00 Wrong Answer!\n");
	exit(0);
}

void outUsage() {
	cerr << "Parameter Parsing Error!"<<endl;
	cerr << "> Usage : check.exe <input file> <output file> [answer file] [log file]"<<endl;
	Grade(false);
}

void Error(string str) {
	cerr << "Error: "<<str << endl;
	Grade(false);
}

int n, c;
char G[20][20];

char buf[20*20];
int sx[20],sy[20],ex[20],ey[20],cnt[256];

bool LoadInput() {
	fgets(buf, 100, inf);
	if(sscanf(buf, "%d %d", &n, &c) != 2 || n < 5 || n > 14 || c < 1 || c > 14) return false;
	for(int i=0;i<n;++i)
		fgets(G[i], n + 3, inf);
	memset(cnt,0,sizeof(cnt));
	memset(sx,-1,sizeof(sx));
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
		{
			++ cnt[G[i][j]];
			if(G[i][j] == '.') continue;
			if(!islower(G[i][j]) && !isupper(G[i][j])) return false;
			char t=tolower(G[i][j]);
			if(t < 'a' || t >= 'a' + c) return false;
			int k = t - 'a';
			if(islower(G[i][j]))
				ex[k] = i, ey[k] = j;
			else
				sx[k] = i, sy[k] = j;
		}
	for(int i=0;i<c;++i) {
		if(cnt['a' + i] != 1 || cnt['A' + i] != 1) return false;
	}
	return true;
}

char S[20][20];
int dir_ind[256];
const int dir[4][2]={{0,-1},{0,1},{-1,0},{1,0}};// L R U D

bool LoadOutput() {
	memset(dir_ind,-1,sizeof(dir_ind));
	dir_ind['L'] = 0;
	dir_ind['R'] = 1;
	dir_ind['U'] = 2;
	dir_ind['D'] = 3;
	for(int i=0;i<n;++i)
		fgets(S[i],n + 3,inf);
	for(int i=0;i<c;++i) {
		fgets(buf, n * n + 10, inf);
		int l = strlen(buf);
		while(l > 0 && (buf[l-1]=='\n'||buf[l-1]=='\r'||isspace(buf[l - 1]))) -- l; buf[l]=0;
		if(l < 5 || buf[0] != 'A' + i) return false;		
		char * ptr = buf + 4;
		l -= 4;
		int x = sx[i], y = sy[i];
		for(int j = 0; j < l; ++ j) {
			int d = dir_ind[ptr[j]];
			if(d < 0) {puts("d");return false;} 
			int tx = x + dir[d][0], ty= y + dir[d][1];
			if(tx < 0 || ty < 0 || tx >= n || ty >= n) {puts("Out");return false;} 
			x= tx; y = ty;
			if(G[x][y] == 'a' + i && j == l - 1) break;
			if(G[x][y] != '.'){std::cout<<x<<" "<<y<<" "<<G[x][y]<<"\n";puts("...");return false;} 
			G[x][y]='A' + i;
		}
		if(x != ex[i] || y != ey[i]) {puts("WP");return false;} 
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j) {
			if(S[i][j] != G[i][j]) {std::cout<<i<<" "<<j<<" "<<S[i][j]<<" "<<G[i][j]<<"\n";puts("Dif");return false;} 
			if(S[i][j]=='.') {puts("..");return false;} 
		}
	return true;
}

int main(int argc, char ** argv) {
	if(argc < 3) outUsage();
	logFile = "";
	if(argc >= 5) {
		logFile = argv[4];
	}
	
	inf = fopen(argv[1], "r");
	if(inf == NULL) Error("Cannot read from Input File <"+string(argv[1])+">");
	
	if(!LoadInput()) {
		fclose(inf);
		Error("Input File Format Error!");
	}
	fclose(inf);
	inf = fopen(argv[2], "r");
	if(inf == NULL) Error("Cannot read from Output File <"+string(argv[2])+">");
	
	bool res = LoadOutput();
	fclose(inf);
	Grade(res);
}
