'''
Tekst zadatka:
Na šahovskoj tabli dimenzija nxn (gde je n zadato sa standardnog ulaza) nalazi se nekoliko već postavljenih figura 
koje se ne mogu pomerati. Vaš zadatak je da korišćenjem MiniSAT rešavača postavite topove na slobodna mesta tako da
na tabli bude tačno n topova i da se nikoja dva topa ne napadaju (topovi se napadaju ako su u istom redu ili istom koloni).

Zahtevi:
Implementirati funkciju koja generiše formulu u konjunktivnoj normalnoj formi (CNF) koja opisuje pravila igre i već 
postavljene topove, a zatim je konvertuje u DIMACS format. Pozvati MiniSAT rešavač i iz njegovog izlaza rekonstruisati i 
ispisati finalni izgled table.
'''

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


        table = [["." for _ in range(n)] for _ in range(n)]
        
        for var_name, _ in true_vars:
            # var_name je npr. "p_0_1"
            parts = var_name.split("_")
            r = int(parts[1])
            k = int(parts[2])
            table[r][k] = "X"
            
        print("\nFinalni izgled table:")
        for row in table:
            print(" ".join(row))
    else:
        print("UNSAT")

def n_gun(n, fixed_guns):
    # pij = True -> na polju (i, j) se nalazi top
    
    cnf = f.CNF()

    # na ovim mestima mora da se nadje top
    for (i, j) in fixed_guns:
        cnf.add_clause([f"p_{i}_{j}"])
    
    # u svakom redu moze da se nadje najvise jedan top
    # ~(pki & pkj), i != j <=> ~pki | ~pkj, i != j
    for k in range(n):
        for i in range(n-1):
            for j in range(i+1, n):
                cnf.add_clause([f"-p_{k}_{i}", f"-p_{k}_{j}"])

    # u svakoj koloni moze da se nadje najvise jedan top
    # ~(pik & pjk), i != j <=> ~pik | ~pjk, i != j
    for k in range(n):
        for i in range(n-1):
            for j in range(i+1, n):
                cnf.add_clause([f"-p_{i}_{k}", f"-p_{j}_{k}"])
    
    # u svakom redu mora da se nadje barem jedan top
    for i in range(n):
        cnf.add_clause([f"p_{i}_{j}" for j in range(n)])

    minisat_solve(f"{n}_guns", cnf.dimacs(), cnf.number_to_var_name)


if __name__ == "__main__":
    # cnf.add_clause(["p1", "p3"])
    # cnf.add_clause(["-p1", "p2", "-p3"])
    # print(cnf.dimacs())
    
    n = int(input("Unesite dimenziju table n: "))
    print(f"Neophodno je rasporediti {n} topova")

    fixed_guns = []

    print("Unesite pozicije fiksiranih topova (red i kolona razdvojeni razmakom).")
    print("Kada završite sa unosom, samo pritisnite Enter na praznu liniju:")

    while True:
        line = input()
        if line.strip() == "":
            break
            
        parts = line.split()
        if len(parts) == 2:
            i = int(parts[0])
            j = int(parts[1])
            fixed_guns.append((i, j))
        else:
            print("Nevalidan unos, unesite dva broja razdvojena razmakom.")

    print("Učitani fiksirani topovi:", fixed_guns)

    n_gun(n, fixed_guns)