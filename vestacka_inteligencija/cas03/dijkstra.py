import sys
import os
import json

def load_graph(path):
    try:
        with open(path, "r") as f:
            data = json.load(f) 
            return dict(data)
    except:
        print("Error loading graph from file.")
        return None
    
def dijkstra(graph, start, end):
    if start not in graph or end not in graph:
        return []

    Q = set(graph.keys())
    
    parent = {}
    cost = {}

    for node in Q:
        cost[node] = float("inf")
        parent[node] = None

    cost[start] = 0

    while Q:
        u = None
        for v in Q:
            if u is None or (cost[v] != float("inf") and cost[v] < cost[u]):
                u = v

        if u is None or cost[u] == float("inf"):
            break
        
        Q.remove(u)

        if u == end:
            print("Path found!\n")
            
            path = []
            while u is not None:
                path.append(u)
                u = parent[u]
            
            path.reverse()
            return path

        for w, weight in graph[u].items():
            if cost[w] == float("inf") or cost[u] + weight < cost[w]: 
                cost[w] = cost[u] + weight
                parent[w] = u

    return []

if __name__ == "__main__":
    G = load_graph("cities.json")
    start = input()
    end = input()

    print(dijkstra(G, start, end))