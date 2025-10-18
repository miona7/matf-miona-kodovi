nadovezi :: [Int] -> [Int] -> Int -> [Int]
nadovezi l1 l2 n 
    | n == 1 = l1 ++ l2 
    | otherwise = (nadovezi l1 l2 (n-1)) ++ l2