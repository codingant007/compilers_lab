#include <bits/stdc++.h>
using namespace std;

extern int yylineno;

class RegisterManager
{
public:
	RegisterManager();
	int allocReg();
	void deallocReg(int);
	bool isFree(int);
	string getRegName(int);
private:
	set<int> isUsed;
	static char* Names[];
	int freeCount, MAX;
};

char* RegisterManager::Names[] = { "%rbx", "%rcx", "%rdx","%r8","%r9","%r10","%r11","%r12","%r13","%r14","%r15" }; //"%rax"

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

RegisterManager::RegisterManager()
{
	isUsed.clear();
	MAX=sizeof(Names)/sizeof(Names[0]);
	freeCount=MAX;
}

int RegisterManager::allocReg()
{
	if(freeCount)
		for(int i = 0; i < MAX; i++)
			if(isUsed.find(i) != isUsed.end())
			{	freeCount--; isUsed.insert(i); return i; }
	else
	{
		fprintf(stderr, "ERROR: Expression too complex to handle at %d. Exiting now.\n", yylineno);
		assert(1==0);
	}
	return 0;
}

void RegisterManager::deallocReg(int reg_num)
{
	if(freeCount == MAX)
		{ fprintf(stderr, "ERROR: %d: All registers already free.\n", yylineno); assert(2==1); }
	if(isFree(reg_num))
		{ fprintf(stderr, "ERROR: Invalid register deallocation at %d. Exiting now.\n", yylineno);assert(2==1);	}
	isUsed.erase(reg_num);
	freeCount++;
}

bool RegisterManager::isFree(int reg_num)
{
	set<int>::iterator it = isUsed.find(reg_num);
	if(it == isUsed.end())
		return true;
	return false;
}

string RegisterManager::getRegName(int reg_num)
{
	string t(Names[reg_num]);
	return t;
}

LabelManager::LabelManager()
{
	l_count=0;
}

string LabelManager::toString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

string LabelManager::getLabel()
{
	return "Label" + this->toString(l_count++);
}

string LabelManager::freeLabel()
{
	return "Label" + this->toString(l_count-1); 
}
