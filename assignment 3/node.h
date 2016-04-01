#include <bits/stdc++.h>
using namespace std;
enum node_type {NONTERM, TERM, VAL}; 
struct node
{
	string content;
	node_type type;
	node *child, *sibling;

	node(string con, node_type t);
	node(const char* con, int t);
};
