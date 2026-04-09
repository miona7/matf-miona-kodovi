from collections import defaultdict

class Edge:
    def __init__(self, start, end, weight):
        self.start = start
        self.end = end
        self.weight = weight

COORDINATES = {
    "Beograd": (0, 0),
    "Novi Sad": (-1, 3),
    "Sabac": (-2, 0),
    "Smederevo": (2, 1),
    "Pozarevac": (4, 1),
    "Jagodina": (6, -1),
    "Kragujevac": (5, -3),
    "Nis": (10, -4),
}

GRAPH = {
    "Beograd": [
        Edge("Beograd", "Novi Sad", 95),
        Edge("Beograd", "Sabac", 90),
        Edge("Beograd", "Smederevo", 50),
        Edge("Beograd", "Kragujevac", 140),
    ],
    "Novi Sad": [
        Edge("Novi Sad", "Beograd", 95),
        Edge("Novi Sad", "Sabac", 110),
    ],
    "Sabac": [
        Edge("Sabac", "Beograd", 90),
        Edge("Sabac", "Novi Sad", 110),
        Edge("Sabac", "Kragujevac", 160),
    ],
    "Smederevo": [
        Edge("Smederevo", "Beograd", 50),
        Edge("Smederevo", "Pozarevac", 45),
        Edge("Smederevo", "Kragujevac", 95),
    ],
    "Pozarevac": [
        Edge("Pozarevac", "Smederevo", 45),
        Edge("Pozarevac", "Jagodina", 90),
        Edge("Pozarevac", "Nis", 190),
    ],
    "Jagodina": [
        Edge("Jagodina", "Pozarevac", 90),
        Edge("Jagodina", "Kragujevac", 35),
        Edge("Jagodina", "Nis", 110),
    ],
    "Kragujevac": [
        Edge("Kragujevac", "Beograd", 140),
        Edge("Kragujevac", "Sabac", 160),
        Edge("Kragujevac", "Smederevo", 95),
        Edge("Kragujevac", "Jagodina", 35),
        Edge("Kragujevac", "Nis", 150),
    ],
    "Nis": [
        Edge("Nis", "Pozarevac", 190),
        Edge("Nis", "Jagodina", 110),
        Edge("Nis", "Kragujevac", 150),
    ],
}

def h(current, end):
    current_i, current_j = COORDINATES[current]
    end_i, end_j = COORDINATES[end]

    return ((current_i - end_i)**2 + (current_j - end_j)**2)**0.5

def astar(start, end):
    open_list, closed_list = {start}, set()

    g = defaultdict(lambda: float("inf"))
    g[start] = 0

    parent = {start: None}

    while open_list:
        u = min(open_list, key = lambda v: g[v] + h(v, end))
        
        if u is None:
            break

        if u == end:
            path = []
            while u is not None:
                path.append(u)
                u = parent[u]
            
            path.reverse()
            return path
        
        for edge in GRAPH[u]:
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


def path_cost(path):
    cost = 0
                        # svaki par gradova na putu
    for start, end in zip(path, path[1:]):
        for edge in GRAPH[start]:
            if edge.end == end:
                cost += edge.weight
                break
    
    return cost

if __name__ == "__main__":
    start = "Beograd"
    goal = "Nis"
    path = astar(start, goal)

    print("Planiranje rute izmedju gradova")
    print("Putanja:", " -> ".join(path))
    print("Ukupna cena:", path_cost(path), "km")