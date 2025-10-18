jednocifreniDelioci :: Int -> [Int]
jednocifreniDelioci n = jednocifreniDelioci' n 1
    where 
        jednocifreniDelioci' :: Int -> Int -> [Int]
        jednocifreniDelioci' n k 
            | n < k = []
            | mod n k == 0 && div k 10 == 0 = [k] ++ jednocifreniDelioci' n (k+1)
            | otherwise = jednocifreniDelioci' n (k+1)