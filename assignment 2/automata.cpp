#include <bits/stdc++.h>

#define map < int, map< char, set<int> > > transitionType 
#define map < char, set<int> > transitionToType

vector<char> ALPHABET;

class BuildAutomata
{
  private:
      int state_init, state_final;
      Automata temp_fa;
  public:
      static Automata& basicStruct(char transition_char);
      static Automata& plusStruct(Automata& a, Automata& b);
      static Automata& dotStruct(Automata& a, Automata& b);
      static Automata& starStruct(Automata& a);
};

class Operations
{
    private:
        
    public:
        static Automata& NFAtoDFA(Automata& nfa);
        static bool simulateDFA(Automata& dfa, string input);
        static Automata& minimizeDFA(Automata& dfa);
};

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


//Expects the transition character on which to create the struct as input....not NFAs/DFAs!
static Automata& BuildAutomata::basicStruct(char transition_char)
{
    state_init = 1, state_final = 2;
    temp_fa = new Automata();
    temp_fa.setStartState(state_init), temp_fa.addFinalStates(state_final);
    temp_fa.addTransitions(state_init, state_final, transition_char);
    return temp_fa;
}

static Automata& BuildAutomata::plusStruct(Automata& a, Automata& b)
{
    //Duddu: CHECK THAT STATE_INIT AND STATE_FINAL ARE REFERENCES!
    Automata t_a = a.newBuildFromNumber(2, state_init), t_b = b.newBuildFromNumber(state_init, state_final);
    state_init = 1;
    temp_fa = new Automata();
    temp_fa.setStartState(state_init), temp_fa.addFinalStates(state_final);
    temp_fa.addTransitions(temp_fa.startState, t_a.startState, Automata.getEpsilon());
    temp_fa.addTransitions(temp_fa.startState, t_b.startState, Automata.getEpsilon());
    temp_fa.addTransitions(*(t_a.finalStates.begin()), *(temp_fa.finalStates.begin()), Automata.getEpsilon());
    temp_fa.addTransitions(*(t_b.startState.begin()), *(temp_fa.finalStates.begin()), Automata.getEpsilon());
    
    delete a;
    delete b;
    
    return temp_fa;    
}

static Automata& BuildAutomata::dotStruct(Automata& a, Automata& b)
{
    //Duddu: CHECK THAT STATE_INIT AND STATE_FINAL ARE REFERENCES!
    Automata t_a = a.newBuildFromNumber(2, state_init), t_b = b.newBuildFromNumber(state_init, state_final);
    state_init = 1, state_final--;
    temp_fa = new Automata();
    temp_fa.setStartState(state_init), temp_fa.addFinalStates(state_final);
    temp_fa.addTransitions(*(t_a.finalStates.begin()), t_b.startState, Automata.getEpsilon());
    
    delete a; delete b;
    
    return temp_fa;
}

static Automata& BuildAutomata::starStruct(Automata& a)
{
    //Duddu: CHECK THAT STATE_INIT IS A REFERENCE!
    Automata t_a = a.newBuildFromNumber(2, state_final);
    state_init = 1;
    temp_fa = new Automata();
    temp_fa.setStartState(state_init), temp_fa.addFinalStates(state_final);
    temp_fa.addTransitions(temp_fa.startState, t_a.startState, Automata.getEpsilon());
    temp_fa.addTransitions(temp_fa.startState, *(temp_fa.finalStates.begin()), Automata.getEpsilon());
    temp_fa.addTransitions(*(t_a.finalStates.begin()), temp_fa.startState, Automata.getEpsilon());
    temp_fa.addTransitions(*(t_a.finalStates.begin()), t_a.startState, Automata.getEpsilon());
    
    delete a;
    
    return temp_fa;
}

static Automata& Operations::NFAtoDFA(Automata& nfa)
{
    //Duddu: CHECK THAT AUTOMATA::GET_TRANSITIONS RETURNS A SET
    Automata dfa = new Automata();
    map<int, set<int> > allStates, eClose;
    set<int> t_state, p_state;
    queue<int> states;
    int count = 1, to_idx;
    
    eClose[nfa.startState] = nfa.getEClose(nfa.startState);
    dfa.setStartState(count);
    states.push(count);
    allStates[count++] = eClose[nfa.startState];
    
    while(!states.empty())
    {
        int cur_state = states.front(); states.pop();
        
        //Duddu: CHECK THAT ALPHABET IS POPULATED BEFORE COMING HERE
        assert(ALPHABET.size() != 0);
        for(int i = 0; i < ALPHABET.size(); i++)
        {
            t_state.clear();
            t_state = nfa.getTransitions(allStates[cur_state], ALPHABET[i]);
            for(set<int>::iterator it = t_state.begin(); it != t_state.end(); it++)
            {
                if (!eClose.count(*it))
                    eClose[*it] = nfa.getEClose(*it);
                for (set<int>::iterator jt = eClose[*it].begin(); jt != eClose[*it].end(); jt++)
                    t_state.insert(*jt);
                if (t_state.size())
                {
                    bool flag = false;
                    for(map<int, set<int> >::iterator jt = allValues.begin(); jt != allValues.end(); jt++)
                        if(jt->second == t_state) { to_idx = jt->first; flag = true; break; }
                    if(!flag)
                    {
                        states.push(count);
                        to_idx = count;
                        allStates[count++] = t_state;
                    }
                    dfa.addTransition(cur_state, to_idx, ALPHABET[i]);
                }
            }
        }
    }
    
    to_idx = *(nfa.finalStates.begin());
    for( map<int, set<int> >::iterator it = allStates.begin(); it != allStates.end(); it++)
        if ((it->second).count(to_idx))
            dfa.addFinalStates(it->second);
    
    return dfa;
}




class NFAfromRegex
{
public:
  char star;
  char plus;
  char dot;
  char openingBracket;
  char closingBracket;
  vector<char> operators;
  string regex;
  vector<char> alphabet;
  vector<char>


  NFAfromRegex(string regex){
    this.star = '*';
    this.plus = '+';
    this.dot = '.';
    this.openingBracket = '(';
    this.closingBracket = ')';
    this.operators[0] = this.star;
    this.operators[1] = this.plus;
    this.regex = regex;

    for(int i=65;i<92;i++){
      this.alphabet.push_back(i);
    }
    for(int i=97;i<124;i++){
      this.alphabet.push_back(i);
    }
    for(int i=48;i<59;i++){
      this.alphabet.push_back(i);
    }
    this.buildNFA();
  }

  Automata getNFA(){

  }
  void displayNFA(){

  }
  void buildNFA(){
    set<char> language;
    self.sta
  }
  void addOperatorToStack(char op){

  }
  void processOperator(char op){

  }

};



int main()
{
    //Populate ALBHABET
}








  RegularExp(string regex){
    this.star = '*';
    this.plus = '+';
    this.dot = '.';
    this.openingBracket = '(';
    this.closingBracket = ')';
    this.operators[0] = this.star;
    this.operators[1] = this.plus;
    this.regex = regex;

    for(int i=65;i<92;i++){
      this.alphabet.push_back(i);
    }
    for(int i=97;i<124;i++){
      this.alphabet.push_back(i);
    }
    for(int i=48;i<59;i++){
      this.alphabet.push_back(i);
    }
    this.nfa = Automata();
    this.buildNFA();
  }

  Automata getNFA(){
    return this.nfa;
  }
  bool char_in_vector(vector<char> v,char c){
    find(v.begin(),v.end(),c) != v.end();
  }
  void buildNFA(){
    vector<char> stack;
    char previous = this.nfa.getEpsilon();
    for(int i=0;i<strlen(this.regex);i++){
      if(char_in_vector(this.alphabet,this.regex[i])){
        if(previous != this.dot && (char_in_vector(this.alphabet,previous) || previous == this.closingBracket || previous == this.star)){
          this.addOperatorToStack(this.dot);
        }
        this.nfa = BuildAutomata.basicStruct(regex[i]);
      }
      else
      if(this.regex[i] == this.openingBracket){
        if(previous != this.doc && (char_in_vector(this.alphabet,previous) || previous == this.closingBracket || previous == this.star)){
          this.addOperatorToStack(this.dot)
        }
        stack.push_back(this.regex[i]);
      }
      else
      if(this.regex[i] == this.closingBracket){
        if(char_in_vector(this.operators,previous)){
          fprintf(stderr, "Error proccessing %c in %s\n",this.regex[i],this.regex );
        }
        while(1){
          if(stack.size == 0){
            fprintf(stderr, "%s. Empty stack.\n",this.regex[i]);
          }
          char o = stack.pop();
          if(o == this.openingBracket){
            break;
          }
          else
          if(char_in_vector(this.operators,o)){
            this.processOperator(o);
          }
        }
      }
      else
      if(this.regex[i] == this.star){
        if(char_in_vector(this.operators,previous) || previous == this.openingBracket || previous == this.star){
          fprintf(stderr, "Error processing %c after %c",this.regex[i],previous);
        }
      }
      else
      if(char_in_vector(this.operators,this.regex[i])){
        if(char_in_vector(this.operators,previous) || previous == this.openingBracket){
          fprintf(stderr, "Error processing %c after %c\n",this.regex[i],previous );
        }
        else{
          this.addOperatorToStack(this.regex[i]);
        }
      }
      else{
        fprintf(stderr, "Symbol %s is not allowed!\n",this.regex[i] );
      }
      previous = this.regex[i]
    }
    while(this.stack.size != 0){
      char op = this.pop();
      this.processOperator(op);
    }
  }
  void displayNFA(){

  }
  void addOperatorToStack(char op){

  }
  void processOperator(char op){

  }

};