resi1(Vars):- Vars = [X, Y, Z, W],
            X :: 1..10,
            Y :: 1..2..51,
            Z :: 10..10..100,
            W :: 1..7..1000,
            2*W #=< X,
            3 + Y #=< Z,
            X - 11*W + Y + 11*Z #=< 100,
            labeling(Vars).