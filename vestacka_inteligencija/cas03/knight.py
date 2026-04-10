from collections import defaultdict

class Edge:
    def __init__(self, start, end, weight):
        self.start = start
        self.end = end
        self.weight = weight

def iterate_edges(current):
    moves = [(1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1)]

    i, j = current
    neighbours = []

    for di, dj in moves:
        ni, nj = i + di, j + dj
        if 0 <= ni < BOARD_SIZE and 0 <= nj < BOARD_SIZE:
            neighbours.append(Edge(current, (ni, nj), 1))

    return neighbours

BOARD_SIZE = 8

def h(current, target):
    """
    Donja granica za broj poteza skakaca od polja ``current`` do ``target``.

    Ideja heuristike:

    - u jednom potezu skakac menja jednu koordinatu najvise za 2,
    - drugu koordinatu najvise za 1,
    - zbir apsolutnih razlika (`dx + dy`) moze da smanji najvise za 3.

    Zbog toga broj preostalih poteza mora biti bar:

    - ``ceil(dx / 2)`` da bi se nadoknadila veca razlika po x osi,
    - ``ceil(dy / 2)`` da bi se nadoknadila veca razlika po y osi,
    - ``ceil((dx + dy) / 3)`` jer jedan potez ne moze da smanji
      Menhetn rastojanje za vise od 3.

    Maksimum ove tri vrednosti je i dalje donja granica, pa je heuristika
    konzistentna: nikada ne precenjuje stvaran broj poteza do cilja
    """

    dx = abs(current[0] - target[0])
    dy = abs(current[1] - target[1])

               # ceil(dx / 2)
    return max((dx + 1) // 2, (dy + 1) // 2, (dx + dy + 2) // 3)

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
        
        for edge in iterate_edges(u):
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
    
    return None

def to_chess_notation(position):
    row, col = position
                 # karakter -> ascii kod
    return f"{chr(ord('a') + col)}{BOARD_SIZE - row}"
              # ascci kod -> karakter   # suprotni smer sahovske table

if __name__ == "__main__":
    start = (7, 1)  # b1
    goal = (0, 6)   # g8
    path = astar(start, goal)

    print("Kretanje skakaca na sahovskoj tabli")
    print("Putanja:", path)
    print("Sahovska notacija:", " -> ".join(to_chess_notation(step) for step in path))
    print("Broj poteza:", len(path) - 1 if path else "nema resenja")