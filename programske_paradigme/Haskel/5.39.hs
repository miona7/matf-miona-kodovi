zbirPar :: Int -> [(Int, Int)]
zbirPar n = [(a, b) | a <- [1..n], b <- [1..n], a + b == 10] 