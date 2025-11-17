uparene :: (Int, Int) -> (Int, Int) -> Bool
uparene a b = snd a == fst b

listaUparenih :: [(Int, Int)] -> [(Int, Int)]
listaUparenih [] = []
listaUparenih [x] = [x]
listaUparenih (x:y:xs)  
    | uparene x y = x : listaUparenih(y:xs)
    | otherwise = [x]

domine :: [(Int, Int)] -> Bool
domine [] = True
domine [x] = True
domine (x:y:xs)  
    | uparene x y = domine (y:xs)
    | otherwise = False
--domine l = length (listaUparenih l) == length l 