zavisnoY :: Int -> Int -> [(Int, Int)]
zavisnoY a b = [(x, y) | x <- [a..b], y <- [x..b]]