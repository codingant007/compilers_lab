#include <bits/stdc++.h>

#define map < int, map< char, set<int> > > transitionType 
#define map < char, set<int> > transitionToType

extern vector<char> ALPHABET;

class Automata{
  
  public:  
    set<int> states;
    int startState;
    set<int> finalStates;
    transitionType transitions;
    set<char> language;
    
  static char getEpsilon();  
  void setStartState(int state);  
  void addFinalStates(vector<int> state);  
  void addFinalStates(int state);  
  void addAllTransitions(transitionType allTransitions );  
  void addTransitions(int fromState,int toState,char inp);  
  void addTransitions(int fromState,vector<int> toStates,char inp );  
  set<int> getTransitions(int state,char inp);  
  set<int> getTransitions(set<int> state,char inp);  
  set<int> getEpsilonClosure(int state);  
  set<int> getEpsilonClosure(set<int> state);  
};
