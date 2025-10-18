bezbedanRep :: [a] -> [a]
bezbedanRep l  
    | null l = []
    | otherwise = tail l

bezbedanRep1 :: [a] -> [a]
bezbedanRep1 [] = []
bezbedanRep1 (_:xs) = xs

bezbedanRep2 :: [a] -> [a]
bezbedanRep2 l = if null l then [] else tail l

