ucesljaj :: [String] -> [String] -> [String]
ucesljaj [] lista = lista
ucesljaj lista [] = lista
ucesljaj (x:xs) (y:ys) = [x] ++ [y] ++ ucesljaj xs ys

