import Data.List (elemIndex)

izbaci :: Int -> [Int] -> [Int]
izbaci k lista = foldl azuriraj [] lista
    where
        azuriraj l e = if (index e) == (Just k) then l else l ++ [e]
        index elem = elemIndex elem lista