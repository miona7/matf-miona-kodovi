from collections import defaultdict

class Edge:
    def __init__(self, start, end, weight):
        self.start = start
        self.end = end
        self.weight = weight

def iterate_edges(current):
    rows = len(MAZE)
    cols = len(MAZE[0])
    i, j = current
    neighbours = []

    for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        ni, nj = i + di, j + dj
        if 0 <= ni < rows and 0 <= nj < cols and MAZE[ni][nj] != "#":
            neighbours.append(Edge(current, (ni, nj), 1))

    return neighbours


MAZE = [
    "S....#....",
    ".##..#..#.",
    ".#...#..#.",
    ".#.#....#.",
    "...#.##...",
    "##.#..##..",
    "...#...#G.",
]

def find_symbol(symbol):
    for i, row in enumerate(MAZE):
        for j, value in enumerate(row):
            if value == symbol:
                return i, j
            
    return None, None

def h(current, target):
    return abs(current[0] - target[0]) + abs(current[1] - target[1])

def astar(start, end):
    open_list, closed_list = {start}, set()

    g = defaultdict(lambda: float("inf"))
    g[start] = 0

    parent = {start: None}

    while open_list:
        u = min(open_list, key = lambda v: g[v] + h(v, end))

        path = []
        if u == end:
            print("Path found")
            while u is not None:
                path.append(u)
                u = parent[u]

            path.reverse()
            return path

        for edge in iterate_edges(u):
            neigbour = edge.end
            weight = edge.weight

            if neigbour not in open_list and neigbour not in closed_list:
                open_list.add(neigbour)
                parent[neigbour] = u
                g[neigbour] = g[u] + weight
            elif g[neigbour] > g[u] + weight:
                parent[neigbour] = u
                g[neigbour] = g[u] + weight

                if neigbour in closed_list:
                    closed_list.remove(neigbour)
                    open_list.add(neigbour)

        open_list.remove(u)
        closed_list.add(u)

    return None

def draw_path(path):
    # svaki red pretvaramo u listu karaktera
    overlay = [list(row) for row in MAZE]
    for i, j in path:
        if overlay[i][j] not in {"S", "G"}:
            overlay[i][j] = "*"
    
    # spaja strringove u lavirint <- spaja karaktere nazad u stringove
    return "\n".join("".join(row) for row in overlay)

if __name__ == "__main__":
    start = find_symbol("S")
    end = find_symbol("G")

    path = astar(start, end)

    print("Lavirint:")
    print("\n".join(MAZE))
    print()
    print("Najkraca putanja:", path)
    print("Broj koraka:", len(path) - 1 if path else "nema resenja")
    if path:
        print()
        print(draw_path(path))

