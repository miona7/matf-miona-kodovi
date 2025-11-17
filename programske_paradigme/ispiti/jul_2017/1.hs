sortirana :: [Int] -> Bool
sortirana [] = True
sortirana [x] = True
sortirana (x:y:xs) 
    | x < y = sortirana (y:xs)
    | otherwise = False


pomeriPocetak :: [Int] -> Int -> [Int]
pomeriPocetak lista k = 
    case break (== k) lista of
        (_, []) -> lista
        (pre, suf) -> suf ++ pre
-- pomeriPocetak lista k = if elem k lista then pomeri lista else lista
    --where
        --pomeri [] = []
        --pomeri (x:xs) 
            -- | x == k = (x:xs)
            -- | otherwise = pomeri (xs ++ [x])  

cirkularnoIste :: [Int] -> [Int] -> Bool
cirkularnoIste [] [] = True
cirkularnoIste [] _ = False
cirkularnoIste _ [] = False
cirkularnoIste (x:xs) lista2 = (x:xs) == pomeriPocetak lista2 x
    -- where
        -- iste [] [] = True
        -- iste _ [] = False
        -- iste [] _ = False
        -- iste (x:xs) (y:ys)  
            -- | x == y = iste xs ys
            -- | otherwise = False
