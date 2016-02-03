//Register and Label Managers
#include <bits/stdc++.h>

using namespace std;

class RegisterManager
{
public:
	RegisterManager();
	int allocReg();
	int checkReg(int, int);
	void deallocReg(int);
	bool isFree(int);	
	string getRegName(int);
private:
	set<int> isUsed;
	static char* Names[];
	int freeCount, MAX;
};

class LabelManager
{
public:
	LabelManager();
	string getLabel();
	string freeLabel();
private:
	int l_count=0;
	string toString(int);
};