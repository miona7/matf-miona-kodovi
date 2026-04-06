from collections import deque

def dfs(graph, start):
    if start not in graph:
        return []
    
    visited = set()
    order = []
    stack = [start]

    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            order.append(node)
            
                                    # uzmi listu suseda za taj cvor, ako ih nema, vrati praznu listu
                                    # reversed - da bi bilo isto kao u rekurzivnoj verziji
            for neighbour in reversed(graph.get(node, [])):
                if neighbour not in visited:
                    stack.append(neighbour)

    return order

def bfs(graph, start):
    if start not in graph:
        return []
    
    visited = set()
    order = []      
    q = deque([start])  # mnogo brzi   

    while q:    
        node = q.popleft()

        if node not in visited:
            visited.add(node)
            order.append(node)
            
            for neighbour in graph.get(node, []):
                if neighbour not in visited:
                    q.append(neighbour)

    return order

GRAPH = {
    "Subotica": ["Novi Sad", "Beograd"],
    "Novi Sad": ["Beograd"],
    "Beograd": ["Kragujevac", "Cacak", "Nis"],
    "Kragujevac": ["Nis"],
    "Cacak": ["Nis"],
    "Nis": ["Pirot"],
    "Pirot": [],
}

if __name__ == "__main__":
    print("DFS traversal order:", dfs(GRAPH, "Subotica"))
    print("BFS traversal order:", bfs(GRAPH, "Subotica"))