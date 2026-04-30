import os
import cnf as f
from itertools import product

def minisat_solve(problem_name, problem_dimacs, number_to_var):
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
            var_name = number_to_var[abs(var_number)]
            var_values[var_name] = var_number > 0
                                                        # pretvara mapu u listu torki tj parova
        true_vars = list(filter(lambda v: v[1] is True, var_values.items()))
                        # uzima sve one za koje lambda vrati True
        true_vars.sort()

        for var in true_vars:
            print(var)

    else:
        print("UNSAT")

def n_queens_cnf(n):
    # pij = True -> na polju (i, j) se nalazi dama
    cnf = f.CNF()
    
    # na bilo kom polju moze da se nadje dama
    for i in range(n):
        cnf.add_clause([f"p_{i}_{j}" for j in range(n)])

    # u svakoj koloni moze da se nadje najvise jedna dama
    # ~(pik & pjk), i != j <=> ~pik | ~pjk, i != j
    for k in range(n):
        for i in range(n-1):
            for j in range(i+1, n):
                cnf.add_clause([f"-p_{i}_{k}", f"-p_{j}_{k}"])

    # u svakoj vrsti moze da se nadje najvise jedna dama
    # ~(pki & pkj), i != j <=> ~pki | ~pkj, i != j 
    for k in range(n):
        for i in range(n-1):
            for j in range(i+1, n):
                cnf.add_clause([f"-p_{k}_{i}", f"-p_{k}_{j}"])

    # dame ne smeju da se napadaju dijagonalno
    # ~(pij & pkl), abs(i-k) == abs(j-l) <=> ~pij | ~pkl, abs(i-k) == abs(j-l)
                    # pravi dekartov proizvod <=> 4 ugnjezdene petlje
    for i, j, k, l in product(range(n), repeat = 4):
        if k > i and abs(k-i) == abs(j-l):
            cnf.add_clause([f"-p_{i}_{j}", f"-p_{k}_{l}"])

    minisat_solve(f'{n}_queens', cnf.dimacs(), cnf.number_to_var_name)

if __name__ == "__main__":
    n_queens_cnf(8)