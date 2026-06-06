import numpy as np

T = [
           # a0             # a1             # a2
    [[0.7, 0.3, 0.0], [1.0, 0.0, 0.0], [0.8, 0.2, 0.0]], # s0
    [[0.0, 1.0, 0.0],       None,      [0.0, 0.0, 1.0]], # s1
    [      None,      [0.8, 0.1, 0.1],       None     ]  # s2
]

num_of_states = 3
num_of_actions = 3
R = np.zeros((num_of_states, num_of_actions, num_of_states))
R[0][0][0] = +10.0
R[1][2][2] = -50.0
R[2][1][0] = +40.0

alpha0 = 0.05 # inicijalni faktor ucenja
decay = 0.005 # faktor slabljenja ucenja
gamma = 0.9 # faktor umanjenja nagrada
state = 0 # inicijalno stanje ce biti 0

possible_actions = [[0, 1, 2], [0, 2], [1]]

Q_values = np.full((num_of_states, num_of_actions), -np.inf)
for state, actions in enumerate(possible_actions):
    Q_values[state, actions] = 0.0 
    
# na osnovu trenutno stanja bira sledecu akciju
def exploration_policy(state):
    return np.random.choice(possible_actions[state])

# vraca u koje smo stanje presli iz stanja state akcijom action i nagradu koju smo dobili
def step(state, action):
    p = T[state][action]
    next_state = np.random.choice([0, 1, 2], p = p)
    r = R[state][action][next_state]
    return next_state, r

for iteration in range(10000):
    action = exploration_policy(state)
    next_state, reward = step(state, action)
    next_value = np.max(Q_values[next_state])
    alpha = alpha0 / (1 + iteration * decay)
    Q_values[state, action] *= 1 - alpha
    Q_values[state, action] += alpha*(reward + gamma*next_value)
    state = next_state

print(Q_values)
print(np.argmax(Q_values, axis = 1))