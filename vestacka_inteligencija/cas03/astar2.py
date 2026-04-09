from typing import List
from collections import defaultdict
import json

class Edge:
    def __init__(self, start, end, weight):
        self.start = start
        self.end = end
        self.weight = weight

def load_graph(path):
    try:
        with open(path, "r") as f:
            data = json.load(f)
        
        # automatski pravi praznu listu za novi grad
        graph = defaultdict(list)

        for node, neighbours in data.items():
            for neighbour, weight in neighbours.items():
                edge = Edge(node, neighbour, weight)
                graph[node].append(edge)

        return dict(graph)
    except:
        print("Error loading graph from file.")
        return None

def h(n : str):
    H = {
        "Oradea": 380,
        "Zerind": 374,
        "Arad": 366,
        "Timisoara": 329,
        "Lugoj": 244,
        "Mehadia": 241,
        "Drobeta": 242,
        "Sibiu": 253,
        "Fagaras": 176,
        "Rimnicu Vilcea": 193,
        "Pitesti": 100,
        "Craiova": 160,
        "Bucharest": 0,
        "Giurgiu": 77,
        "Urziceni": 80,
        "Hirsova": 151,
        "Eforie": 161,
        "Vaslui": 199,
        "Iasi": 226,
        "Neamt": 234
    }

    return H[n]

def astar(graph : dict, start : str, end : str) -> List[str]:
    if start not in graph or end not in graph:
        return []
    
    open_list = set([start])
    closed_list = set()

    g = defaultdict(lambda: float("inf"))
    g[start] = 0

    parent = {start: None}

    while open_list:
        u = min(open_list, key = lambda v: g[v] + h(v))
        
        if u is None:
            break
    
        path = []
        if u == end:
            print("Path found!\n")
            
            while u is not None:
                path.append(u)
                u = parent[u]

            path.reverse()
            return path

        for edge in graph[u]:
            w = edge.end
            weight = edge.weight
            
            if w not in open_list and w not in closed_list:
                open_list.add(w)
                parent[w] = u
                g[w] = g[u] + weight
            elif g[w] > g[u] + weight:
                parent[w] = u
                g[w] = g[u] + weight
                
                if w in closed_list:
                    closed_list.remove(w)
                    open_list.add(w)

        open_list.remove(u)
        closed_list.add(u)

    return []

if __name__ == "__main__":
    graph = load_graph("cities.json")
    start = input()
    end = input()
    print(astar(graph, start, end))
    