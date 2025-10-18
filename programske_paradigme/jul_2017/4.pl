proizvodi(bravo,narandza).
proizvodi(next,narandza).
proizvodi(nectar,narandza).
proizvodi(fructal,narandza).
proizvodi(bravo,jabuka).
proizvodi(fructal,jabuka).
proizvodi(next,multivitamin).
proizvodi(nectar,multivitamin).
proizvodi(fructal,jagoda).
proizvodi(fructal,malina).
proizvodi(bravo,breskva).

procenatVoca(bravo,65).
procenatVoca(next,99).
procenatVoca(fructal,86).
procenatVoca(nectar,95).

pakuje(bravo,10).
pakuje(next,8).
pakuje(fructal,12).
pakuje(nectar,15).

bolji(F1, F2, S):- proizvodi(F1, S), procenatVoca(F1, PV1), proizvodi(F2, S), procenatVoca(F2, PV2), PV1 > PV2.
najbolji(S, F):- proizvodi(F, S), not(bolji(_, F, S)).
brojPaketa(BrojLitara, F, P):- pakuje(F, BL), X is BrojLitara / BL, P is ceiling(X).
kolicinaSoka(S, BrojKilogramaVoca, BrojLitara):- najbolji(S, F), procenatVoca(F, PV),
    BrojLitara is BrojKilogramaVoca + (BrojKilogramaVoca / PV) * (100 - PV).