def readNextInt():
	return int(raw_input().strip().split()[0])

def checkString(inp):
	currentState = startState
	for i in inp:
		if currentState in transitions and i in transitions[currentState]:
			currentState = transitions[currentState][i]
		else:
			return False
	if currentState in finalStates:
		return True
	else:
		return False


startState = readNextInt()
lenFinalStates = readNextInt()
finalStates = set()
for x in xrange(lenFinalStates):
	finalStates = finalStates | set([readNextInt()])
lenTransitions = readNextInt()

transitions = dict()
#print "len: ",lenTransitions
for x in xrange(lenTransitions):
	line = raw_input().strip().split(',')
	fromState = int(line[0].strip())
	toState = int(line[1].strip())
	chars = line[2]
	for char in chars:
		if fromState in transitions:
			transitions[fromState][char] = toState
		else:
			transitions[fromState] = {char:toState}


inp = raw_input().strip().split()

if checkString(list(inp[0])):
	print "DFA accepts the string."
else:
	print "DFA rejects the string."