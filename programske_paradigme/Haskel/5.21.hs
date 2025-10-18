parni :: Int -> [Int]
parni n = parni' n 1 0 
 where
    parni' :: Int -> Int -> Int -> [Int]
    parni' n k br 
        | n == br = []
        | mod k 2 == 0 = [k] ++ parni' n (k+1) (br+1)
        | otherwise = parni' n (k+1) br