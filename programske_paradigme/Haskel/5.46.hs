obrni :: [a] -> [a]
obrni l = foldl azuriraj [] l
    where
        azuriraj ak e = e : ak