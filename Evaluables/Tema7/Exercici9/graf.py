# -*- coding: utf-8 -*-


class Graf:
    __slots__ = {"__nodes"}

    def __init__(self, nodes, arestes, pesos):
        self.__nodes = [[node, []] for node in nodes]
        for aresta, pes in zip(arestes, pesos):
            self.__nodes[aresta[0]][1].append([aresta[1], pes])
            self.__nodes[aresta[1]][1].append([aresta[0], pes])

    def __str__(self):
        s = ""
        for node in self.__nodes:
            s = s + "Comment :=>> Etiqueta: " + str(node[0]) + "\n"
            s = s + "Comment :=>> Arestes: " + str(node[1]) + "\n"
        return s

    def is_neigh(self, x, y):
        for i, j in self.__nodes[x][1]:
            if i == y:
                return True

    def cicles(self):
        cicles = []

        for n in self.__nodes:
            for x in range(len(n[1])):
                v1 = n[1][x]
                if v1[0] > self.__nodes.index(n):
                    for y in range(x+1, len(n[1])):
                        v2 = n[1][y]
                        if self.is_neigh(v1[0], v2[0]):
                            cicles.append(
                                [n[0], self.__nodes[v1[0]][0], self.__nodes[v2[0]][0]])

        return cicles

    def nodeMaxArestes(self):
        node = []

        for n in self.__nodes:
            if len(node) == 0 or len(n[1]) > len(node[1]):
                node = n

        return node[0]

    def nodesAillats(self):
        aillats = []

        for node in self.__nodes:
            if len(node[1]) == 0:
                aillats.append(node[0])

        return aillats

    def etiquetesAdjacents(self, node):
        adj = []

        for n in self.__nodes:
            if n[0] == node:
                for a in n[1]:
                    adj.append(self.__nodes[a[0]][0])
                break

        return adj
