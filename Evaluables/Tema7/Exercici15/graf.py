# -*- coding: utf-8 -*-
import copy as cp
import numpy as np


class Graf:
    __slots__ = {"__nodes", "__arestes"}

    def __init__(self, nodes, arestes, pesos):
        self.__nodes = cp.deepcopy(nodes)
        self.__arestes = np.zeros([len(nodes), len(nodes)])
        for aresta, pes in zip(arestes, pesos):
            self.__arestes[aresta[0], aresta[1]] = pes
            self.__arestes[aresta[1], aresta[0]] = pes

    def __str__(self):
        s = ""
        for posNode, node in enumerate(self.__nodes):
            s = s + "Etiqueta: " + str(node) + "\n"
            s = s + "Arestes: " + \
                str([[vei[0], pes] for vei, pes in np.ndenumerate(
                    self.__arestes[posNode, :]) if pes != 0]) + "\n"
        return s

    def num_arestes(self, x):
        n = 0

        for i in self.__arestes[x]:
            if i != 0:
                n += 1

        return n

    def is_neigh(self, x, y):
        if self.__arestes[x][y] != 0:
            return True
        else:
            return False

    def cicles(self):
        cicles = []

        for i in range(len(self.__nodes)):
            for j in range(len(self.__arestes[i])):
                if self.__arestes[i][j] != 0 and j > i:
                    for k in range(j+1, len(self.__arestes[j])):
                        if self.__arestes[i][k] != 0 and self.is_neigh(j, k):
                            cicles.append(
                                [self.__nodes[i], self.__nodes[j], self.__nodes[k]])

        return cicles

    def nodeMaxArestes(self):
        node = [0, 0]

        for n in range(len(self.__nodes)):
            n_a = self.num_arestes(n)
            if n_a > node[1]:
                node = [n, n_a]

        return self.__nodes[node[0]]

    def nodesAillats(self):
        aillats = []

        for n in range(len(self.__arestes)):
            if self.num_arestes(n) == 0:
                aillats.append(self.__nodes[n])

        return aillats

    def etiquetesAdjacents(self, node):
        adj = []
        i = self.__nodes.index(node)

        for v in range(len(self.__nodes)):
            if self.is_neigh(i, v):
                adj.append(self.__nodes[v])

        return adj
