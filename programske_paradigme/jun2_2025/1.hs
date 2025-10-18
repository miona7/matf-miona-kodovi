import Data.List (elemIndex, sortOn)

izbaci :: [[Char]] -> Int -> [[Char]]
izbaci deca k = foldl azuriraj [] deca 
    where
        azuriraj l d = if indeks d == (Just k) then l else l ++ [d]
        indeks d = elemIndex d deca

izbaci_vise :: [[Char]] -> [Int] -> [[Char]]
izbaci_vise deca [] = deca
izbaci_vise deca (k:indeksi) = izbaci_vise (izbaci deca k) indeksi

dodaj :: [[Char]] -> Int -> [Char] -> [[Char]]
dodaj deca i d = (take i deca) ++ [d] ++ (drop i deca) 

rekonstruisi :: [[Char]] -> [[Char]] -> [Int] -> [[Char]]
rekonstruisi deca izbaceni indeksi = foldl azuriraj deca (sortOn snd (zip izbaceni indeksi))
    where
        azuriraj l (d, i) = dodaj l i d 