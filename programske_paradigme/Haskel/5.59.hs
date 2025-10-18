varijacije :: [Int] -> Int -> [[Int]]
varijacije l 0 = [[]]
varijacije l k = concat (map (\x -> map (x:) ys) l)
    where 
        ys = varijacije l (k-1)