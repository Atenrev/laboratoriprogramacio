# -*- coding: utf-8 -*-
"""
Created on Wed Jan 24 10:43:25 2018

@author: ernest
"""
import random


def afegeixSinonim(diccionari, paraula, sinonim):
    if paraula in diccionari:
        if sinonim not in diccionari[paraula]:
            diccionari[paraula].append(sinonim)
    else:
        diccionari[paraula] = [sinonim, ]


def conversioSinonims(frase, diccionari):
    converted = []

    for word in frase:
        if word in diccionari:
            converted.append(random.choice(diccionari[word]))
        else:
            converted.append(word)

    return converted
