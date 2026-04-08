from typing import List
import json

def load_graph(path):
    try:
        with open(path, "r") as f:
            data = json.load(f)
            return dict(data)
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

def astar(graph : dict, start : str, end : str) -> List[str] :
    open_list = set([start])
    closed_list = set([])

    g = {}
    g[start] = 0

    parent = {}
    parent[start] = None

    while open_list:
        u = None
        for v in open_list:
            if u is None or g[v] + h(v) < g[u] + h(u):
                u = v

        if u is None:
            break

        if u == end:
            print(f"Path found!\n")
            path = []
            while u != None:
                path.append(u) 
                u = parent[u]

            path.reverse()
            return path

        for w, weight in graph[u].items():
            if w not in open_list and w not in closed_list:
                open_list.add(w)
                parent[w] = u
                g[w] = g[u] + weight
            else:
                if g[w] > g[u] + weight:
                    g[w] = g[u] + weight
                    parent[w] = u

                    if w in closed_list:
                        closed_list.remove(w)
                        open_list.add(w)

        open_list.remove(u)
        closed_list.add(u)

    return []

if __name__ == "__main__":
    G = load_graph("cities.json")
    start = input()
    end = input()

    print(astar(G, start, end))