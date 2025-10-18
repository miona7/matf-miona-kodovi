absSume :: [[Int]] -> [Int]
absSume lista_listi = map (\e -> abs e) (map (\e -> sum e) lista_listi)

absSume' :: [[Int]] -> [Int]
absSume' lista_listi = map (abs . sum) lista_listi

absSume'' :: [[Int]] -> [Int]
absSume'' = map (abs . sum) 