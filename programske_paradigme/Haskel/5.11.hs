tipJednacine :: Int -> Int -> Int -> String
tipJednacine a b c 
    | a == 0 = "Degenerisana"
    | d == 0 = "Jedno resenje"
    | d > 0 = "Dva resenja"
    | otherwise = "Nema resenja"
    where 
        d = b*b - 4*a*c 