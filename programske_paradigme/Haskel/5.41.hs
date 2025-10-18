spoji :: [[a]] -> [a]
spoji lista = foldl azuriraj [] lista
    where
        azuriraj ak l = ak ++ take (length l) l