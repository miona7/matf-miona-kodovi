ubaci :: Int -> Int -> [Int] -> [Int]
ubaci k n lista = take k lista ++ [n] ++ drop k lista