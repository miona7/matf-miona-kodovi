uvecaj :: [Int] -> [Int]
uvecaj lista = map (\e -> e + 1) lista

uvecaj' :: [Int] -> [Int]
uvecaj' = map (\e -> e + 1)

uvecaj'' :: [Int] -> [Int]
uvecaj'' = map (+1)