qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (p:xs) = 
    let manji = [x | x <- xs, x <= p]
        veci = [x | x <- xs, x > p]
    in qsort manji ++ [p] ++ qsort veci 