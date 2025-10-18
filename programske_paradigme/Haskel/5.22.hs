fibLista :: Int -> [Int]
fibLista n = fibLista' n 1 1 1
 where 
    fibLista' :: Int -> Int -> Int -> Int -> [Int]
    fibLista' n br a b  
        | n == br = [a]
        | otherwise = [a] ++ fibLista' n (br+1) b (a+b)