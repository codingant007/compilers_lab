class Automata:

    def __init__(self):
        self.states = set()
        self.startState = None
        self.acceptingStates = set()
        self.transitions = dict()
        self.epsilon = '$'
        self.language = set()
    

    def getEpsilon(self):
        return self.epsilon
    
    def addState(self):
        stateName = len(self.states) + 1
        self.states.add(stateName)
        return stateName

    def displaySelf(self):
        print self.startState        
        print len(self.acceptingStates)
        for s in self.acceptingStates:
            print s
        l = 0
        for key,value in self.transitions.iteritems():
            for key2,value2 in value.iteritems():
                l +=len(value2)
        print l
        for key,value in self.transitions.iteritems():
            for key2,value2 in value.iteritems():
                toList = list(value2)
                for to in toList:
                    print key ,",", to , "," , key2
    
    
    def setStartState(self,state):
        self.startState = state
        self.states.add(state)

    def addAcceptingStates(self,state):
        if isinstance(state,int):
            state = set([state])
        if isinstance(state,list):
            state = set(state)
        self.acceptingStates = self.acceptingStates | state
    
    def removeAcceptingState(self, state):
        if state in states:
            states.remove(state)

    def addAllTransitionsOfAutomata(self,transitions):
        for fromState,toState in transitions.items():
            for s in toState:
                self.addTransition(fromState,s,toState[state])

    def addTransition(self,fromStates,toState,inp):
        if isinstance(fromStates,int):
            fromStates = [fromStates]
        
        if isinstance(fromStates,set):
            fromStates = list(fromStates)
        toState = set([toState])
        self.states = self.states | toState | set(fromStates)
        for fromState in fromStates:
            if fromState in self.transitions:
                if inp in self.transitions[fromState]:
                    #Both fromState and toState are in transition table
                    self.transitions[fromState][inp] = self.transitions[fromState][inp].union(toState)
                else:
                    #only fromState is present not toState
                    self.transitions[fromState][inp] = toState
            else:
                self.transitions[fromState] = {inp: toState}

    def getTransitions(self,states,inp):
        if isinstance(states,set):
            states = list(states)
        if isinstance(states,int):
            states = [states]
        returnStates = set()
        for state in states:
            if state in self.transitions:
                if inp in self.transitions[state]:
                    returnStates = returnStates|self.transitions[state][inp]
        return returnStates

    def getEpsilonClosure(self,state):
        
        if isinstance(state,int):
            state = set([state])
        if isinstance(state,list):
            state = set(state)

        returnStates = set()
        myQueue = set()
        myQueue = state
        returnStates = state
        while len(myQueue)>0:
            tempStates = self.getTransitions(myQueue,self.epsilon)
            tempStates = tempStates-returnStates
            myQueue = tempStates
            returnStates = returnStates | tempStates
        return returnStates
        
    def renumberFrom(self, start_num):
        self.startState += start_num
        list_state, list_accepting = list(self.states), list(self.acceptingStates)
        for i in range(len(list_state)):
            list_state[i] += start_num
        for i in range(len(list_accepting)):
            list_accepting[i] += start_num
        self.states, self.acceptingStates = set(list_state), set(list_accepting)
        shifted_transitions = {}
        for k,v in self.transitions.iteritems():
            temp_dict = {}
            for k1, v1 in v.iteritems():
                temp_dict[k1] = set(map(lambda x : x + start_num, v1))
            shifted_transitions[k + start_num] = temp_dict
        self.transitions = shifted_transitions
        
    def mergeWith(self, nfa):
        self.states = self.states.union(nfa.states)
        self.acceptingStates = self.acceptingStates.union(nfa.acceptingStates)
        self.transitions.update(nfa.transitions)
        self.language = self.language.union(nfa.language)

    # get the set of states which move to states in A on input c
    def getPrecursors(self,c,A):
        X = set()
        for from_state,val in self.transitions.items():
            for inp,to_states in val.items():
                for to_state in list(to_states):    
                    if to_state in A and c == inp:
                        X.add(from_state)
        return X

    # get the partitioned groups of states of DFA
    def getMinimalGroups(self):

        P = [set(self.acceptingStates),self.states.difference(set(self.acceptingStates))]
        W = [set(self.acceptingStates)]
        while(len(W) != 0):
            A=W[0]
            W.remove(A)
            X = set()
            for c in self.language:
                X = self.getPrecursors(c,A)
                for Y in P:
                    if not X.intersection(Y) == set() and not Y.difference(X) == set():
                        P.remove(Y)
                        P.append(X.intersection(Y))
                        P.append(Y.difference(X))
                        if Y in W:
                            W.remove(Y)
                            W.append(X.intersection(Y))
                            W.append(Y.difference(X))
                        else:
                            if len(X.intersection(Y)) <= len(Y.difference(X)):
                                W.append(X.intersection(Y))
                            else:
                                W.append(Y.difference(X))
        return P

    # return the group number of state in state_group map
    def getGroup(self,state_group,state):
        for group_no,group in state_group.items():
            if state in group:
                return group_no
    
    # build and return new minimal DFA
    def getMinimizedDFA(self,P):
        minDFA = Automata()
        state_group = {}
        for i in range(0,len(P)):
            state_group[i] = P[i]
        #adding transisitons to minDFA
        for from_state,val in self.transitions.items():
            for inp,to_states in val.items():
                tempToState = list(to_states)
                for to_state in tempToState:
                    minDFA.addTransition(self.getGroup(state_group,from_state),self.getGroup(state_group,to_state),inp)
        #adding accepting states to minDFA
        for f in self.acceptingStates:
            minDFA.acceptingStates.add(self.getGroup(state_group,f))
        #adding start state to minDFA
        minDFA.startState = self.getGroup(state_group,self.startState)
        return minDFA

def CharacterNFA(inp_char):
    char_nfa = Automata()
    start_state = char_nfa.addState()
    end_state = char_nfa.addState()
    char_nfa.setStartState(start_state)
    char_nfa.addAcceptingStates(end_state);
    char_nfa.addTransition(start_state, end_state, inp_char)
    char_nfa.language = set(inp_char)
    return  char_nfa

def ConvertToPostfix(regex):
    postfix_regex = ""
    precedence = {"*": 3, ".": 2, "+": 1}
    postfix_stack = []
    for i in range(len(regex)):
        if regex[i] in "abcdefghijklmnopqrstyuwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ": #  or regex[i] in "0123456789":
            postfix_regex += (regex[i])
        elif regex[i] == '(':
            postfix_stack.append(regex[i])
        elif regex[i] == ')':
            topToken = postfix_stack.pop()
            while topToken != '(':
                postfix_regex += (topToken)
                topToken = postfix_stack.pop()
        else:
            while len(postfix_stack) > 0 and postfix_stack[-1] != '(' and (precedence[postfix_stack[-1]] >= precedence[regex[i]]):
                  postfix_regex += (postfix_stack.pop())
            postfix_stack.append(regex[i])
    while len(postfix_stack) > 0:
        postfix_regex += (postfix_stack.pop())
    return postfix_regex

def RegexToNFA(regex):
    postfix_regex = ConvertToPostfix(regex)
    
    eval_stack = []
    for i in range(len(postfix_regex)): 
        if postfix_regex[i] in "abcdefghijklmnopqrstyuwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ":
            char_nfa = CharacterNFA(postfix_regex[i])
            eval_stack.append(char_nfa)
        elif postfix_regex[i]=="*":
            char_one=eval_stack.pop()
            start_state, final_state = char_one.addState(), char_one.addState()
            
            char_one.addTransition(start_state, char_one.startState, char_one.epsilon)
            char_one.addTransition(start_state, final_state, char_one.epsilon)
            char_one.addTransition(char_one.acceptingStates, char_one.startState, char_one.epsilon)
            char_one.addTransition(char_one.acceptingStates, final_state, char_one.epsilon)
            char_one.setStartState(start_state)
            char_one.acceptingStates = set([final_state])
            eval_stack.append(char_one)
        elif postfix_regex[i]==".":
            char_two=eval_stack.pop()
            char_one=eval_stack.pop()
            temp_f = char_one.acceptingStates
            char_two.renumberFrom(len(char_one.states))
            char_one.mergeWith(char_two)
            
            start_state, final_state = char_one.addState(), char_one.addState()
            char_one.addTransition(start_state, char_one.startState, char_one.epsilon)
            char_one.addTransition(temp_f, char_two.startState, char_one.epsilon)
            char_one.addTransition(char_two.acceptingStates, final_state, char_one.epsilon)
            char_one.setStartState(start_state)
            char_one.acceptingStates = set([final_state])
            eval_stack.append(char_one)
        elif postfix_regex[i]=="+":

            char_one=eval_stack.pop()
            char_two=eval_stack.pop()            
            char_two.renumberFrom(len(char_one.states))
            char_one.mergeWith(char_two)
            
            start_state, final_state = char_one.addState(), char_one.addState()
            char_one.addTransition(start_state, char_one.startState, char_one.epsilon)
            char_one.addTransition(start_state, char_two.startState, char_one.epsilon)
            char_one.addTransition(char_one.acceptingStates, final_state, char_one.epsilon)
            char_one.setStartState(start_state)
            char_one.acceptingStates = set([final_state])
            eval_stack.append(char_one)
             
    return eval_stack.pop()

def nfaToDfa(nfa):
    dfa = Automata()
    mapping = dict()
    statesNotSeen = set()
    language = list(nfa.language)
    dfa.language = nfa.language
    #Set the first state of new dfa
    startStateDfa = dfa.addState()
    dfa.setStartState(startStateDfa)
    mappedStatesNfa = nfa.getEpsilonClosure(nfa.startState)
    mapping[startStateDfa] = mappedStatesNfa
    
    statesNotSeen.add(startStateDfa)
    while len(statesNotSeen) > 0:
        checkState = statesNotSeen.pop()
        
        for char in language:
            mappedStatesNfa = nfa.getTransitions(mapping[checkState],char)
            mappedStatesNfa = nfa.getEpsilonClosure(mappedStatesNfa)
            toState = -1
            if len(mappedStatesNfa)>0:
                for key,value in mapping.iteritems():
                    if value == mappedStatesNfa:
                        toState = key
                        
                if toState<0:
                    newStateDfa = dfa.addState()
                    mapping[newStateDfa] = mappedStatesNfa
                    statesNotSeen.add(newStateDfa)
                    toState = newStateDfa
                
                dfa.addTransition(checkState,toState,char)
    
    for key,value in mapping.iteritems():
        tempSet = nfa.acceptingStates - value
        if tempSet != nfa.acceptingStates:
            dfa.addAcceptingStates(key)
    return dfa            


x = RegexToNFA("(a*+b*)*")
y = nfaToDfa(x)
z = y.getMinimizedDFA(y.getMinimalGroups())
z.displaySelf()
testString = "abbbbbccc"
print testString