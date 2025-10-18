import Data.Char (isNumber, isLower)

broj :: [Char] -> Bool
broj s = and (map (\c -> isNumber c) s)

mala :: [Char] -> Bool
mala s = and (map (\c -> isLower c) s)

sifruj :: [[Char]] -> [[Char]]
sifruj ls = foldl azuriraj [] ls
    where
        azuriraj ak l  
            | broj l = ak ++ [['C'] ++ l ++ ['C']]
            | mala l = ak ++ [['M'] ++ l ++ ['M']]
            | otherwise = ak ++ [['O'] ++ l ++ ['O']]