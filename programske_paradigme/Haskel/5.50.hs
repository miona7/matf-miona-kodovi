ukloniDuplikate :: Eq a => [a] -> [a]
ukloniDuplikate lista = foldl azuriraj [] lista
   where
        azuriraj l e = if elem e l then l else l ++ [e]