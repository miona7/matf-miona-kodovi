brojDelilaca :: Int -> Int
brojDelilaca n 
    | n == 1 = 1
    | otherwise = pravi n 2
    where
        pravi :: Int -> Int -> Int
        pravi n k  
            | n == k = 0
            | mod n k == 0 = 1 + pravi n (k+1)
            | otherwise = pravi n (k+1)