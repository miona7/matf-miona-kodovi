import Data.Char (isNumber, isLower)

cifre :: [Char] -> Int
cifre s = length (filter (\c -> isNumber c) s)

mala :: [Char] -> Int
mala s = length (filter (\c -> isLower c) s)

desifruj :: [[Char]] -> [[Char]]
desifruj ls = foldl azuriraj [] ls
    where 
        azuriraj ak (x:xs)  
            | isNumber x = ak ++ [drop (cifre (x:xs)) (x:xs)]
            | isLower x = ak ++ [drop (mala (x:xs)) (x:xs)]