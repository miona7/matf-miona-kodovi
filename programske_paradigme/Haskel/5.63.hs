brisiPonavljanja :: [Int] -> [Int]
brisiPonavljanja l = foldl azuriraj [] l
    where
        azuriraj ak s = if elem s ak then ak else ak ++ [s]