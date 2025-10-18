% 1, 2, 5, 10, 20

kombinacije(Vars):- Vars = [A, B, C, D, E],
                    A :: 1..50,
                    B :: 1..25,
                    C :: 1..10,
                    D :: 1..5,
                    E :: 1..2,
                    A + 2*B + 5*C + 10*D + 20*E #= 50,
                    labeling(Vars),
                    write(A + 2*B + 5*C + 10*D + 20*E), nl.
