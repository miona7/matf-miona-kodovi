parni :: Int -> Int -> [Int]
parni a b = parni' a b [] 
    where
        parni' k b l 
            | k == b = if k `mod` 2 == 0 then l ++ [k] else l
            | k `mod` 2 == 0 = l ++ [k] ++ parni' (k+1) b l
            | otherwise = l ++ parni' (k+1) b l 

parni1 :: Int -> Int -> [Int]
parni1 a b = [x | x <- [a..b], even x]

neparni :: Int -> Int -> [Int]
neparni a b = neparni' a b [] 
    where
        neparni' k b l 
            | k == b = if k `mod` 2 /= 0 then l ++ [k] else l
            | k `mod` 2 /= 0 = l ++ [k] ++ neparni' (k+1) b l
            | otherwise = l ++ neparni' (k+1) b l 

neparni1 :: Int -> Int -> [Int]
neparni1 a b = [x | x <- [a..b], odd x]
