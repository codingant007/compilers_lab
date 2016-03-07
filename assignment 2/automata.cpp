#include <bits/stdc++.h>



class Automata{
	
  string epsilon;
  int startState;
  set<int> finalStates;
  map < int, vector<int> > transitions;
  string language;
  
  void setStartState(int state){
  	startState = state;
    finalStates.insert(state);
  }
  
  void addFinalStates(int state){
  	
  }
  
};