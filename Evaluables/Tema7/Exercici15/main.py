# -*- coding: utf-8 -*-
import graf

nodes = [ "T0", "T1","T2","T3","T4","T5","T6","T7","T8","T9","T10", "T11"]
arestes = [ [ 0,1 ],[ 3,0 ],[ 4,1 ],[ 1,5 ],[ 3,5 ],[ 6,3 ],[ 5,4 ],[ 5,6 ],[ 4,7 ],[ 4,8 ],[ 6,8 ],[ 6,9 ],[ 7,8 ],[ 8,9 ],[ 7,10 ],[ 8,10 ],[ 9,10 ] ]
pesos = [ 5,5,7,7,4,4,6,6,3,3,9,9,1,8,2,8,4 ]


grade = 0
print ("Grade :=>>", grade)


print ("Comment :=>> Iniciant test")
print ("Comment :=>> =============")
print ("Comment :=>>")
print ("Comment :=>> Inicialitzant el graf .......")
g = graf.Graf(nodes, arestes, pesos)
print ("Comment :=>> -----------------------------")
print ("Comment :=>> Graf despres inicialitzacio:")
print (g)


reduccio = 0
print ("Comment :=>> ")
print ("Comment :=>> ========================================================")
print ("Comment :=>> Test del metode per trobar node amb maxim numero arestes" )
nodeMaxArestesEsperat = 'T8'
print ("Comment :=>> Resultat esperat: ", nodeMaxArestesEsperat)
print ("Comment :=>> ---")
nodeMaxArestesObtingut = g.nodeMaxArestes()
print ("Comment :=>> Resultat obtingut: ", nodeMaxArestesObtingut)
if (nodeMaxArestesEsperat == nodeMaxArestesObtingut):
    print ("Comment :=>> CORRECTE")
else:
    print ("Comment :=>> ERROR")
    reduccio = 3.0
grade = grade + (2.0 - reduccio)
if (grade < 0):
    grade = 0
print ("Grade :=>>", grade)


reduccio = 0
print ("Comment :=>> ")
print ("Comment :=>> ========================================")
print ("Comment :=>> Test del metode per trobar nodes aillats" )
nodesAillatsEsperats = ['T2', 'T11']
print ("Comment :=>> Resultat esperat: ", nodesAillatsEsperats)
print ("Comment :=>> ---")
nodesAillatsObtinguts = g.nodesAillats()
print ("Comment :=>> Resultat obtingut: ", nodesAillatsObtinguts)
correcte = True
for node in nodesAillatsObtinguts:
    if node not in nodesAillatsEsperats:
        correcte = False
if (correcte):
    for node in nodesAillatsEsperats:
        if node not in nodesAillatsObtinguts:
            correcte = False
if (correcte):
    print ("Comment :=>> CORRECTE")
else:
    print ("Comment :=>> ERROR")
    reduccio = 3.0
grade = grade + (2.0 - reduccio)
if (grade < 0):
    grade = 0
print ("Grade :=>>", grade)


reduccio = 0
print ("Comment :=>> ")
print ("Comment :=>> ====================================================")
print ("Comment :=>> Test del metode per trobar etiquetes nodes adjacents" )
nodesTest = ['T2', 'T5']
nodesAdjacentsEsperats = [[], ['T1', 'T3', 'T4', 'T6']]
for index, node in enumerate(nodesTest):
    print ("Comment :=>> --------------------")
    print ("Comment :=>> Node de test: ", node)
    print ("Comment :=>> Resultat esperat: ", nodesAdjacentsEsperats[index])
    print ("Comment :=>> ---")
    nodesAdjacentsObtinguts = g.etiquetesAdjacents(node)
    print ("Comment :=>> Resultat obtingut: ", nodesAdjacentsObtinguts)
    correcte = True
    for node in nodesAdjacentsObtinguts:
        if node not in nodesAdjacentsEsperats[index]:
            correcte = False
    if (correcte):
        for node in nodesAdjacentsEsperats[index]:
            if node not in nodesAdjacentsObtinguts:
                correcte = False
    if (correcte):
        print ("Comment :=>> CORRECTE")
    else:
        print ("Comment :=>> ERROR")
        reduccio = 1.5
grade = grade + (2.0 - reduccio)
if (grade < 0):
    grade = 0
print ("Grade :=>>", grade)


reduccio = 0
print ("Comment :=>> ")
print ("Comment :=>> =================================")
print ("Comment :=>> Test del metode per trobar cicles" )
ciclesEsperats = [['T1', 'T4', 'T5'], ['T3', 'T5', 'T6'], ['T4', 'T7', 'T8'], ['T6', 'T8', 'T9'], ['T7', 'T8', 'T10'], ['T8', 'T9', 'T10']]
print ("Comment :=>> Resultat esperat: ")
for cicle in ciclesEsperats:
    print ("Comment :=>>", cicle)
print ("Comment :=>> ---")
ciclesObtinguts = g.cicles()
print ("Comment :=>> Resultat obtingut: ")
for cicle in ciclesObtinguts:
    print ("Comment :=>>", cicle)
correcte = False
if (len(ciclesEsperats) == len(ciclesObtinguts)):
    correcte = True
    for cicleO in ciclesObtinguts:
        correcte = False
        for cicleE in ciclesEsperats:
            correcte = True
            for node in cicleO:
                if node not in cicleE:
                    correcte = False
            if (correcte):
                break
        if (correcte == False):
            break
if (correcte):
    print ("Comment :=>> CORRECTE")
else:
    print ("Comment :=>> ERROR")
    reduccio = 5.0
grade = grade + (4.0 - reduccio)
if (grade < 0):
    grade = 0
print ("Grade :=>>", grade)




print ("Comment :=>> ------------------------------------------")
if (grade == 10.0):
    print ("Comment :=>> Final del test sense errors")
print ("Grade :=>> ", grade)
