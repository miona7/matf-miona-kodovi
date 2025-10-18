delioci :: Int -> [Int]
delioci n 
    | n == 1 = [1]
    | otherwise = pravi n 2 
    where
        pravi :: Int -> Int -> [Int]
        pravi n k 
            | k == n = []
            | mod n k == 0 = [k] ++ (pravi n (k+1))
            | otherwise = pravi n (k+1)