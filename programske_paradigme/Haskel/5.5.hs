sumaPrvih :: Int -> Int
sumaPrvih n 
    | n == 0 = 0
    | otherwise = n + sumaPrvih (n - 1) 