# -*- coding: utf-8 -*-

import sinonims as s
diccionari = dict()
diccionari['feta'] = ['realitzada', 'produida', 'elaborada']
diccionari['content'] = ['encantat', 'satisfet', 'cofoi']
diccionari['molt'] = ['força']
diccionari['feina'] = ['tasca', 'ocupacio']


grade = 0
print("Grade :=>>", grade)


print("Comment :=>> Iniciant test")
print("Comment :=>> =============")
print("Comment :=>>")
print("Comment :=>> Inicialitzant el diccionari .......")
diccionariObtingut = dict()
for paraula, sinonims in diccionari.items():
    print("Comment :=>> Afegint sinonims de:", paraula, "-->", sinonims)
    for sinonim in sinonims:
        s.afegeixSinonim(diccionariObtingut, paraula, sinonim)
print("Comment :=>> Afegint sinonims de:", 'content', "-->", 'cofoi')
s.afegeixSinonim(diccionariObtingut, 'content', 'cofoi')
print("Comment :=>> Afegint sinonims de:", 'feta', "-->", 'realitzada')
s.afegeixSinonim(diccionariObtingut, 'feta', 'realitzada')
print("Comment :=>> Afegint sinonims de:", 'molt', "-->", 'força')
s.afegeixSinonim(diccionariObtingut, 'molt', 'força')
print("Comment :=>> -----------------------------")
print("Comment :=>> Diccionari Esperat:")
for paraula, sinonims in diccionari.items():
    print("Comment :=>>", paraula, ": ", sinonims)
print("Comment :=>> -----------------------------")
print("Comment :=>> Diccionari Obtingut:")
for paraula, sinonims in diccionariObtingut.items():
    print("Comment :=>>", paraula, ": ", sinonims)

reduccio = 0
correcte = False
if (len(diccionari) == len(diccionariObtingut)):
    correcte = True
    for paraula in diccionariObtingut.keys():
        if paraula not in diccionari:
            correcte = False
            break
        if (len(diccionariObtingut[paraula]) != len(diccionari[paraula])):
            correcte = False
            break
        for sinonim in diccionariObtingut[paraula]:
            if sinonim not in diccionari[paraula]:
                correcte = False
                break
if (correcte):
    print("Comment :=>> CORRECTE")
else:
    print("Comment :=>> ERROR")
    reduccio = 6.0
grade = grade + (5.0 - reduccio)
print("Grade :=>>", grade)


reduccio = 0
print("Comment :=>> ")
print("Comment :=>> =======================================")
print("Comment :=>> Test del metode per convertir una frase")
frase = ['està', 'molt', 'content', 'de', 'la', 'feina', 'feta']
print("Comment :=>> Frase original: ", frase)
fraseEsperada = ['està', 'força', ['encantat', 'satisfet', 'cofoi'], 'de', 'la', [
    'tasca', 'ocupacio'], ['realitzada', 'produida', 'elaborada']]
print("Comment :=>> ---")
print("Comment :=>> Resultat esperat (pot ser qualsevol sinonim de cada llista): ", fraseEsperada)
print("Comment :=>> ---")
novaFrase = s.conversioSinonims(frase, diccionariObtingut)
print("Comment :=>> Resultat obtingut: ", novaFrase)
correcte = False
if (len(fraseEsperada) == len(novaFrase)):
    correcte = True
    for sinonimEsperat, sinonimObtingut in zip(fraseEsperada, novaFrase):
        if (type(sinonimEsperat) == str):
            if (sinonimEsperat != sinonimObtingut):
                correcte = False
                break
        if (type(sinonimEsperat) == list):
            if (sinonimObtingut not in sinonimEsperat):
                correcte = False
                break
if (correcte):
    print("Comment :=>> CORRECTE")
else:
    print("Comment :=>> ERROR")
    reduccio = 6.0
grade = grade + (5.0 - reduccio)
if (grade < 0):
    grade = 0
print("Grade :=>>", grade)


print("Comment :=>> ------------------------------------------")
if (grade == 10.0):
    print("Comment :=>> Final del test sense errors")
print("Grade :=>> ", grade)
