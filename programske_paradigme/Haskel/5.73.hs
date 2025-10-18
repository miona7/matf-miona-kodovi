magicniParovi :: [Int] -> [(Int, Int)]
magicniParovi l = map (\x -> (x, magicni x)) l
    where
        magicni :: Int -> Int
        magicni x 
            | x < 10 = x
            | otherwise = (x `mod` 10) * (magicni (x `div` 10))