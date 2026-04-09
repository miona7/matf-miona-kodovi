from typing import List
from collections import defaultdict
import json
import copy

# matrica -> json stringova
def serialize(matrix):
    # dump string
    return json.dumps(matrix)

# json stringova -> matrica
def deserialize(value: str):
    # load string
    return json.loads(value)

class Edge:
    def __init__(self, start, end, weight):
        self.start = start
        self.end = end
        self.weight = weight

def iterate_edges(state: str):
    matrix = deserialize(state)
    blank_i, blank_j = -1, -1

    n = len(matrix)
    for i in range(n):
        for j in range(n):
            if matrix[i][j] == 0:
                blank_i, blank_j = i, j
                break

    neighbours = []

    if blank_i > 0:
        new_matrix = copy.deepcopy(matrix)
        new_matrix[blank_i][blank_j] = new_matrix[blank_i - 1][blank_j]
        new_matrix[blank_i - 1][blank_j] = 0
        neighbours.append(Edge(matrix, serialize(new_matrix), 1))

    if blank_i < n-1:
        new_matrix = copy.deepcopy(matrix)
        new_matrix[blank_i][blank_j] = new_matrix[blank_i + 1][blank_j]
        new_matrix[blank_i + 1][blank_j] = 0
        neighbours.append(Edge(matrix, serialize(new_matrix), 1))

    if blank_j > 0:
        new_matrix = copy.deepcopy(matrix)
        new_matrix[blank_i][blank_j] = new_matrix[blank_i][blank_j - 1]
        new_matrix[blank_i][blank_j - 1] = 0
        neighbours.append(Edge(matrix, serialize(new_matrix), 1))

    if blank_j < n-1:
        new_matrix = copy.deepcopy(matrix)
        new_matrix[blank_i][blank_j] = new_matrix[blank_i][blank_j + 1]
        new_matrix[blank_i][blank_j + 1] = 0
        neighbours.append(Edge(matrix, serialize(new_matrix), 1))

    return neighbours

def find_in_matrix(value, matrix):
    n = len(matrix)
    for i in range(n):
        for j in range(n):
            if value == matrix[i][j]:
                return i, j

    return None, None

def h(current, target):
    """
        Suma menhetn rastojanja izmedju elemenata iz current_matrix i target_matrix
            1|3|2         1|2|3
        A = 4|6|5    B =  4|7|5
            7|8|0         0|8|6
        
        suma menhetn rastojanja za elemente iz prve matrice u odnosu na elemente iz druge matrice:
        H = d(A,B,1) + d(A,B,3) + d(A,B,2) + d(A,B,4) + d(A,B,6) + d(A,B,5) + d(A,B,7) + d(A,B,8) + d(A,B,0)
        H = 0 + 1 + 1 + 0 + 2 + 0 + 2 + 0 + 2
    """
    A = deserialize(current)
    B = deserialize(target)

    n = len(A)
    H = 0
    for i in range(n):
        for j in range(n):
            value = A[i][j]
            target_i, target_j = find_in_matrix(value, B)
            H += abs(i - target_i) + abs(j - target_j)

    return H

def astar(start, end):
    open_list, closed_list = set([start]), set()

    g = defaultdict(lambda: float("inf"))
    g[start] = 0

    parent = {start: None}
    
    while open_list:
        u = min(open_list, key = lambda v: g[v] + h(v, end))
        
        if u is None:
            break
        
        path = []
        if u == end:
            print("Path found!")
            while u is not None:
                path.append(u)
                u = parent[u]

            path.reverse()
            return path
        
        for edge in iterate_edges(u):
            neighbour = edge.end
            weight = edge.weight

            if neighbour not in open_list and neighbour not in closed_list:
                open_list.add(neighbour)
                parent[neighbour] = u
                g[neighbour] = g[u] + weight
            elif g[neighbour] > g[u] + weight:
                parent[neighbour] = u
                g[neighbour] = g[u] + weight

                if neighbour in closed_list:
                    closed_list.remove(neighbour)
                    open_list.add(neighbour)
        
        open_list.remove(u)
        closed_list.add(u)

    return []

if __name__ == '__main__':
    start = [
        [4, 1, 3],
        [0, 2, 5],
        [7, 8, 6]
    ]
    target = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 0]
    ]

    path = astar(serialize(start), serialize(target))
    for state in path: 
        print(state)