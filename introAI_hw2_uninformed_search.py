# Kevin O'Neill
# keoneill
# Homework 2
# Solving the 8-puzzle using uninformed search

import Queue
import copy

def printState(state):
    print "-------------------"
    print "| ", state[0][0], " | ", state[0][1], " | ", state[0][2], " |"
    print "-------------------"
    print "| ", state[1][0], " | ", state[1][1], " | ", state[1][2], " |"
    print "-------------------"
    print "| ", state[2][0], " | ", state[2][1], " | ", state[2][2], " |"
    print "-------------------"

def makeState(nw, n, ne, w, c, e, sw, s, se):
    return [[nw,n,ne],[w,c,e],[sw,s,se]]

def testUninformedSearch(state, goal, limit):
    q = Queue.Queue()
    q.put(makeNode(state, [[0,0,0],[0,0,0],[0,0,0]], 0, 0))
    generalSearch(q, 1000, 0)

def testProcedure(state):
    goal = makeState(1,2,3,4,5,6,7,8," ")
    if state == goal:
        return True
    else:
        return False

def outputProcedure(numRuns, q):
    print "numRuns = ", numRuns
    #printState(q.get())

def findBlank(state):
    for i in range(3):
        for j in range(3):
            if state[i][j] == " ":
                return (i + (j*10))

def expand(q, currentState, parent):
    
    #print "from inside expand.."
    blank = findBlank(currentState)
    row = blank % 10
    col = blank / 10
    #print "row = ", row, "; column = ", col
    #print "current state is "
    #printState(currentState)
    #print "the parent is"
    #printState(parent)
    
    left = True
    up = True
    right= True
    down = True

    if col == 0:
        left = False
    if (row == 0):
        up = False
    if (col == 2):
        right = False
    if (row == 2):
        down = False

    if left:
        leftSuccessor = copy.deepcopy(currentState)
        temp = leftSuccessor[row][col-1]
        leftSuccessor[row][col-1] = leftSuccessor[row][col]
        leftSuccessor[row][col] = temp
        if not (leftSuccessor == parent):
            q.put(makeNode(leftSuccessor, currentState, 1, 1))
            #print "the left successor is... "
            #printState(leftSuccessor)
    if up:
        upSuccessor = copy.deepcopy(currentState)
        temp = upSuccessor[row-1][col]
        upSuccessor[row-1][col] = upSuccessor[row][col]
        upSuccessor[row][col] = temp
        if not (upSuccessor == parent):
            q.put(makeNode(upSuccessor, currentState, 1, 1))
            #print "the up successor is... "
            #printState(upSuccessor)
    if right:
        rightSuccessor = copy.deepcopy(currentState)
        temp = rightSuccessor[row][col+1]
        rightSuccessor[row][col+1] = rightSuccessor[row][col]
        rightSuccessor[row][col] = temp
        if not (rightSuccessor == parent):
            q.put(makeNode(rightSuccessor, currentState, 1, 1))
            #print "the right successor is..."
            #printState(rightSuccessor)
    if down:
        downSuccessor = copy.deepcopy(currentState)
        temp = downSuccessor[row+1][col]
        downSuccessor[row+1][col] = downSuccessor[row][col]
        downSuccessor[row][col] = temp
        if not (downSuccessor == parent):
            q.put(makeNode(downSuccessor, currentState, 1, 1))
            #print "the down successor is..."
            #printState(downSuccessor)

#    for i in range(q.qsize()): # test queue
#        print "queue position ", i
#        node = q.get()
#        printState(node[0])
#        i += 1
    return q

def makeNode(state, parent, depth, pathCost):
    return [state, parent, depth, pathCost]

def generalSearch(q, limit, numRuns):

    if q.empty():
        print "empty"
        return False
    currentNode = q.get()
    currentState = currentNode[0]
    parent = currentNode[1]

    if testProcedure(currentState):
        print "Success"
        printState(currentState)
        print "number of runs = ", numRuns
        #outputProcedure(numRuns, currentState)
    elif limit == 0:
        print "Limit reached"
        printState(currentState) ###
    else:
        limit -= 1
        numRuns += 1
        generalSearch(expand(q, currentState, parent), limit, numRuns)


def main():
    goalState = makeState(1,2,3,4,5,6,7,8," ")

    # First group of test cases - should have solutions with depth <= 5
    initialState1 = makeState(2, " ", 3, 1, 5, 6, 4, 7, 8)
    initialState2 = makeState(1, 2, 3, " ", 4, 6, 7, 5, 8)


    # Second group of test cases - should have solutions with depth <= 10
    initialState3 = makeState(2, 8, 3, 1, " ", 5, 4, 7, 6)
    initialState4 = makeState(1, 2, 3, 4, 5, 6, " ", 7, 8)


    # Third group of test cases - should have solutions with depth <= 20
    initialState5 = makeState(" ", 5, 3, 2, 1, 6, 4, 7, 8)
    initialState6 = makeState(5, 1, 3, 2, " ", 6, 4, 7, 8)


    # Fourth group of test cases - should have solutions with depth <= 50
    initialState7 = makeState(2, 6, 5, 4, " ", 3, 7, 1, 8)
    initialState8 = makeState(3, 6, " ", 5, 7, 8, 2, 1, 4)

    print "Test 1 Uninformed ___________________"
    print "Initial State: "
    printState(initialState1)
    testUninformedSearch(initialState1, goalState, 10000000)
    print "Test 2 Uninformed ___________________"
    print "Initial State: "
    printState(initialState2)
    testUninformedSearch(initialState2, goalState, 10000000)
    print "Test 3 Uninformed ___________________"
    print "Initial State: "
    printState(initialState3)
    testUninformedSearch(initialState3, goalState, 10000000)
    print "Test 4 Uninformed ___________________"
    print "Initial State: "
    printState(initialState4)
    testUninformedSearch(initialState4, goalState, 10000000)
    print "Test 5 Uninformed ___________________"
    print "Initial State: "
    printState(initialState5)
    testUninformedSearch(initialState5, goalState, 10000000)
    print "Test 6 Uninformed ___________________"
    print "Initial State: "
    printState(initialState6)
    testUninformedSearch(initialState6, goalState, 10000000)
    #print "Test 7 Uninformed ___________________"
    #print "Initial State: "
    #printState(initialState7)    
    #testUninformedSearch(initialState7, goalState, 10000000)
    #print "Test 8 Uninformed ___________________"
    #print "Initial State: "
    #printState(initialState8)
    #testUninformedSearch(initialState8, goalState, 10000000)

main()
