skalar([], [], 0).
skalar([G1 | R1], [G2 | R2], S):- skalar(R1, R2, S1), S is S1 + G1*G2.