import Data.Maybe (fromMaybe)
import Data.List (elemIndex)

prefiks :: [a] -> [[a]]
prefiks lista = foldl azuriraj [[]] lista
    where
        azuriraj ak e = ak ++ [poslednji ak ++ [e]]
        poslednji ak = last ak


prefiks' :: [a] -> [[a]]
prefiks' lista = scanl (\ak x -> ak ++ [x]) [] lista