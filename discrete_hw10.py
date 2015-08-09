# Discrete Structures
# Counting Sets

from sets import Set

Veg = Set(['bread', 'soup', 'potatoes','lentils','rice'])
NonVeg = Set(['chicken', 'goat','beef','lamb','fish',
      'stew','wat','tibs','anchotte','baduu',
      'kitfo','itto','waadii','marqaa','chechebsa'])
D = Veg & NonVeg

People = ['Alice','Bob','Carol','Dave']

V = ['V1','V2','V3','V4','V5']
N = ['R6','R7','R8','R9','R10',
     'R11','R12','R13','R14','R15',
     'R16','R17','R18','R19','R20']
F = ['F1','F2','F3']
D = ['D1','D2','D3','D4','D5',
     'D6','D7','D8','D9','D10',
     'D11','D12','D13','D14','D15',
     'D16','D17','D18','D19','D20']

##############################################
# Number 1

MealSets = Set([])
for v in V:
    for n in N:
        current_meal = Set([])
        current_meal.add(v)
        current_meal.add(n)
        MealSets.add(current_meal)
print "Number 1: "
print len(MealSets)

################################################
# Number 2

Combos = []
for choice1 in D:
    for choice2 in D:
        for choice3 in D:
            for choice4 in D:
                choice = [choice1, choice2, choice3, choice4]
                Combos.append(choice)
print "Number 2: "
print len(Combos)



##################################################
# Number 3 Alice and Bob are vegetarian

Combos = []
for choice1 in V:
    for choice2 in V:
        for choice3 in D:
            for choice4 in D:
                choice = [choice1, choice2, choice3, choice4]
                Combos.append(choice)

print "Number 3: "
print len(Combos)

##################################################
# Number 4 -- no repeats

Combos = []
for choice1 in D:
    for choice2 in D:
        if choice2 != choice1:
            for choice3 in D:
                if choice3 != choice2 and choice3 != choice1:
                    for choice4 in D:
                        if choice4 != choice3 and choice4 != choice2 and choice4 != choice1:
                            choice = [choice1, choice2, choice3, choice4]
                            Combos.append(choice)
    
print "Number 4: "
print len(Combos)


#######################################################
# Number 5 -- Emily alone; chooses 4 dishes, no repeats
MealSets = Set([])
for d in D:
    for d1 in D:
        for d2 in D:
            for d3 in D:
                current_meal = Set([])
                current_meal.add(d)
                if d1 not in current_meal:
                    current_meal.add(d1)
                    if d2 not in current_meal:
                        current_meal.add(d2)
                        if d3 not in current_meal:
                            current_meal.add(d3)
                            MealSets.add(current_meal)
print "Number 5: "
print len(MealSets)


##################################
# Number 6 Emily's choices
R6 = ['V1','V2','V3','V4','V5',
      'R6','R7','R8','R9','R10',
      'R11','R12','R13','R14','R15',
      'R16','R17','R18','R19','R20']

MealSets = Set([])
for v in V:
    for r in R6:
        for r2 in R6:
            for r3 in R6:
                current_meal = Set([])
                current_meal.add(v)
                if r not in current_meal:
                    current_meal.add(r)
                    if r2 not in current_meal:
                        current_meal.add(r2)
                        if r3 not in current_meal:
                            current_meal.add(r3)
                            MealSets.add(current_meal)
print "Number 6: "
print len(MealSets)
#print MealSets


#####################################
# Number 7
R7 = ['V1','V2','V3','V4','V5','F1','F2','F3',
     'R9','R10','R11','R12','R13','R14','R15','R16',
     'R17','R18','R19','R20']

MealSets = Set([])
for v in V:
    for f in F:
        for r in R7:
            for r2 in R7:
                current_meal = Set([])
                current_meal.add(v)
                current_meal.add(f)
                if r not in current_meal:
                    current_meal.add(r)
                    if r2 not in current_meal:
                        current_meal.add(r2)
                        MealSets.add(current_meal)
print "Number 7: "
print len(MealSets)
for element in MealSets:
    print element

        
