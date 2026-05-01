import os
import cnf as f
from itertools import product

def minisat_solve(problem_name, problem_dimacs, number_to_var_name):
    with open(f"{problem_name}.cnf", "w") as file:
        file.write(problem_dimacs)

    os.system(f"minisat {problem_name}.cnf {problem_name}_result.cnf")

    with open(f"{problem_name}_result.cnf", "r") as file:
        lines = file.readlines()

    if lines[0].startswith("SAT"):
        print("SAT")

        var_values = {}
        for var in lines[1].split(" ")[:-1]:
            var_number = int(var)
            var_name = number_to_var_name[abs(var_number)]
            var_values[var_name] = var_number > 0
        true_vars = list(filter(lambda v: v[1] is True, var_values.items()))
        true_vars.sort()

        for var in true_vars:
            print(var)
    else:
        print("UNSAT")

def in_same_subsquare(r1, c1, r2, c2, n):
    block_size = int(n**.5)
    block_1 = (r1 // block_size, c1 // block_size)
    block_2 = (r2 // block_size, c2 // block_size)
    return block_1 == block_2

def sudoku_cnf(initial_board):
    # S_i_j_k -> na polju (i, j) se nalazi vrednost k
    n = len(initial_board)
    cnf = f.CNF()

    # na popunjenim poljima moraju da ostane zadate vrednosti
    # S_0_0_8, S_1_2_3, S_1_3_6, ...
    for i, j in product(range(n), repeat = 2):
        k = initial_board[i][j]
        if k != 0:
            cnf.add_clause([f"S_{i}_{j}_{k}"])

    # na svakom polju mora da se nalazi vrednost od 1 do n
    for i, j in product(range(n), repeat = 2):
        cnf.add_clause([f"S_{i}_{j}_{k}" for k in range(1, n+1)])

    # na jednom polju ne smeju da se nadju dva razlicita broja
    # ~(S_i_j_k & S_i_j_k'), k != k' <=> ~S_i_j_k | ~S_i_j_k', k != k'
    for i, j in product(range(n), repeat = 2):
        for num1, num2 in product(range(1, n+1), repeat = 2):
            if num1 != num2:
                cnf.add_clause([f"-S_{i}_{j}_{num1}", f"-S_{i}_{j}_{num2}"])
    '''
    # u istom redu ne smeju da se nadju dva ista broja
    # ~(S_i_j_k & S_i_j'_k), j != j' <=> ~S_i_j_k | ~S_i_j'_k, j != j'
    for i, k in product(range(n), repeat = 2):
        k += 1
        for j1, j2 in product(range(n), repeat = 2):
            if j1 != j2:
                cnf.add_clause([f"-S_{i}_{j1}_{k}", f"-S_{i}_{j2}_{k}"])

    # u istoj koloni ne smeju da se nadju dva ista broja
    # ~(S_i_j_k & S_i'_j_k), i != i' <=> ~S_i_j_k | ~S_i'_j_k, i != i'
    for j, k in product(range(n), repeat = 2):
        k += 1
        for i1, i2 in product(range(n), repeat = 2):
            if i1 != i2:
                cnf.add_clause([f"-S_{i1}_{j}_{k}", f"-S_{i2}_{j}_{k}"])

    # u istom podkvadratu ne smeju da se nadju dva ista broja
    # S_i_j_k => ~S_i'_j'_k, i != i', j != j' <=> ~S_i_j_k | ~S_i'_j'_k, i != i', j != j'
    for i1, j1, i2, j2, k in product(range(n), repeat = 5):
        k += 1
        if (i1, j1) != (i2, j2) and in_same_subsquare(i1, j1, i2, j2, n):
            cnf.add_clause([f"-S_{i1}_{j1}_{k}", f"-S_{i2}_{j2}_{k}"])
    '''
    # prethodna 3 uslova odjednom
    for i1, j1, i2, j2, k in product(range(n), repeat = 5):
        k += 1
        if (i1 == i2 and j1 < j2) or (j1 == j2 and i1 < i2) or \
            ((i1, j1) != (i2, j2) and in_same_subsquare(i1, j1, i2, j2, n)):
            cnf.add_clause([f"-S_{i1}_{j1}_{k}", f"-S_{i2}_{j2}_{k}"])

    minisat_solve("sudoku", cnf.dimacs(), cnf.number_to_var_name)

if __name__ == "__main__":
    hardest_sudoku = [
        [8,0,0,0,0,0,0,0,0],
        [0,0,3,6,0,0,0,0,0],
        [0,7,0,0,9,0,2,0,0],
        [0,5,0,0,0,7,0,0,0],
        [0,0,0,0,4,5,7,0,0],
        [0,0,0,1,0,0,0,3,0],
        [0,0,1,0,0,0,0,6,8],
        [0,0,8,5,0,0,0,1,0],
        [0,9,0,0,0,0,4,0,0]
    ]
    sudoku_cnf(hardest_sudoku)