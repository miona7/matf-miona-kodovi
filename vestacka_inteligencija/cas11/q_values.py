import numpy as np

# T(s, a, s') - verovatnoca da agent predje iz stanja s u stanje s' akcijom a
# T(s, a, s') -> shape = [len(S), len(A), len(S)]

T = [
           # a0             # a1             # a2
    [[0.7, 0.3, 0.0], [1.0, 0.0, 0.0], [0.8, 0.2, 0.0]], # s0
    [[0.0, 1.0, 0.0],       None,      [0.0, 0.0, 1.0]], # s1
    [      None,      [0.8, 0.1, 0.1],       None     ]  # s2
]

# print(T)
# print(T[0]) # verovatnoce prelaska u sva stanja za sve akcije koje mogu da se preduzmu u stanju S0
# print(T[0][1]) # verovatnoce prelaska iz stanja S0 u sva stanja akcijom a1 
# print(T[0][1][1]) # verovatnoca prelaska iz stanja S0 u stanje S1 akcijom a1 


# R(s, a, s') - nagrada koju agent dobija ako predje iz stanja s u stanje s' akcijom a
# R(s, a, s') -> shape = [len(S), len(A), len(S)]

R = [
             # a0             # a1             # a2
    [[+10.0, 0.0, 0.0], [0.0, 0.0, 0.0],   [0.0, 0.0, 0.0]], # s0
    [[0.0, 0.0, 0.0],   [0.0, 0.0, 0.0],   [0.0, 0.0, -50.0]], # s1
    [[0.0, 0.0, 0.0],   [+40.0, 0.0, 0.0], [0.0, 0.0, 0.0]]  # s2
]

# print(R)


                        # s0    # s1    # s2
possible_actions = [[0, 1, 2], [0, 2], [1]] # moguce akcije za sva stanja

Q_values = np.full((3, 3), -np.inf) # pravi matricu 3x3 i popunjava je sa -np.inf
for state, actions in enumerate(possible_actions):
    Q_values[state, actions] = 0.0 # na dozvoljenim akcijama inicijalizuje Q vrednost na 0

gamma = 0.95 # sto je blizi jedinici to se vise znacaja pridaje kasnijim nagradama

for iteration in range(500):
    Q_prev = Q_values.copy() # pravimo kopiju prethodnih vrednosti -> tokom racunanja ne smemo da koristimo popravljene vrednosti
    for s in range(3):
        for a in possible_actions[s]:
            Q_values[s, a] = np.sum([
                T[s][a][sp] * (R[s][a][sp] + gamma*np.max(Q_prev[sp])) 
                for sp in range(3)
            ])

print(Q_values)
print(np.argmax(Q_values, axis = 1)) # za svaki red nalazi najbolji potez, tj bira optimalnu polisu za svako stanje po akcijama