#include "inc/automata.h"

class Automata{
  
  set<int> states;
  int startState;
  set<int> finalStates;
  transitionType transitions;
  set<char> language;
  
  static char getEpsilon(){
      return '$';
  }
  
  void setStartState(int state){
    startState = state;
    finalStates.insert(state);
  }
  
  void addFinalStates(vector<int> state){
   for (int i=0;i<state.size();i++){
       finalStates.insert(state[i]);
   }
  }
  
  void addFinalStates(int state){
   state.insert(state);
  }
  
  void addAllTransitions(transitionType allTransitions ){
      for(transitionType::iterator it=allTransitions:begin();it!=allTransitions.end();++it){
        transitionToType temp = it->second;
        for(transitionToType::iterator toS=temp.begin();toS!= temp.end();++toS){
            this.addTransition(it->first, toS->second , toS->first )      
        }
      }
  }
  
  void addTransitions(int fromState,int toState,char inp){
      vector<int> v1(1,toState);
      this.addTransitions(fromState,v1,inp);
  }
  
  void addTransitions(int fromState,vector<int> toStates,char inp ){
      
      if( transitions.find(fromState) != transitions.end() ){
        transitionType::iterator it = transitions.find(fromState);
        //map < int, map< char, vector<int> > >
        map < char,set<int> > tempMap = it->second;
        if(tempMap.find(inp)!=tempMap.end()){
            for(int i=0;i<toStates.size();i++){
                ((it->second[inp])->second).insert(toStates[i]);    
            }
            return;
        }
        set<int> toStatesSet(toStates.begin(),toStates.end());
        pair< char,set < int > > tempPair(inp,toStatesSet);
        (it->second).insert(tempPair);
      }
      else{
          states.insert(fromState);
          transitionToType tempTo;
          set<int> toStatesSet(toStates.begin(),toStates.end());
          pair< char, set<int> > tempPair(inp,toStateSet);
          tempTo.insert(tempPair);
          pair< int, map< char, set< int > > > tempP(fromState,tempTo);
          transitions.insert(tempTo);
      }
  }
  
  set<int> getTransitions(int state,char inp){
    set<int> s1;
    s1.insert(state);
    return getTransitions(s1,inp);
  }
  
  set<int> getTransitions(set<int> state,char inp){
    set<int> returnStates;
    set<int>::iterator it,itTempSet;
    for(it=state.begin();it!=state.end();++it){
        if(transitions.find(*it)!=transitions.end() && transitions[*it].find(inp)!=transitions[*it].end() ){
            for(itTempSet=transitions[*it][inp];itTempSet!=transitions[*it][inp];itTempSet++){
                returnStates.insert(*itTempSet);
            }
        }
    }
    return returnStates;
  }
  
  set<int> getEpsilonClosure(int state){
      set<int> s1;
      s1.insert(state);
      getEpsilonClosure(s1);
  }
  
  set<int> getEpsilonClosure(set<int> state){
      set<int> returnStates,tempSet;
      queue<int> toCheck;
      set<int>::iterator it;
      int temp;
      for(it=state.begin();it!=state.end();++it){
          toCheck.push(*it);
      }
      temp = toCheck.front();
      while(!toCheck.empty()){
          returnStates.insert(temp);
          tempSet = getTransitions(temp,'$');
          for(it=tempSet.begin();it!=tempSet.end();++it){
              queue.push(*it);
          }
          while(returnStates.find(temp)!=returnStates.end() && !toCheck.empty()){
              toCheck.pop();
              temp = toCheck.fron();
          }
      }
      return returnStates;
  }  
};