sufiks :: [a] -> [[a]]
sufiks lista = scanr azuriraj [] lista
    where
        azuriraj e l = e : l 