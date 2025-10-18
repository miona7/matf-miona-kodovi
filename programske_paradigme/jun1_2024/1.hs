module Lib where
import Data.List as List (sortBy)

polozili :: [(String, Int)] -> [String]
polozili studenti = foldr azuriraj [] studenti
    where 
        azuriraj (ime, poeni) l = if poeni > 50 then ime : l else l

polozili' :: [(String, Int)] -> [String]
polozili' studenti = foldl azuriraj [] studenti
    where
        azuriraj l (ime, poeni) = if poeni > 50 then l ++ [ime] else l

najbolji :: [(String, Int)] -> String
najbolji studenti = fst (foldr azuriraj ("", 0) studenti)
    where 
        azuriraj (ime, poeni) ("", 0) = (ime, poeni) 
        azuriraj (ime, poeni) (i, p)  
            | poeni > p = (ime, poeni)
            | otherwise = (i, p)

prosek :: [(String, Int)] -> Float
prosek studenti = fromIntegral (ukupnaOcena studenti) / brojStudenta studenti
    where 
        ukupnaOcena = foldr azuriraj 0
        azuriraj (ime, poeni) ak = if poeni > 50 then ak + ocena poeni else ak
        ocena n 
            | n >= 51 && n <= 60 = 6
            | n >= 61 && n <= 70 = 7
            | n >= 71 && n <= 80 = 8
            | n >= 81 && n <= 90 = 9
            | otherwise = 10
        
        brojStudenta = foldr azuriraj1 0
        azuriraj1 (ime, poeni) ak = if poeni > 50 then ak + 1 else ak

-- data Student = MkStudent { ime :: String, poeni :: Int } deriving Show

data Student = MkStudent String Int deriving Show

ime :: Student -> String
ime (MkStudent i _) = i

poeni :: Student -> Int
poeni (MkStudent _ p) = p                               

instance Eq Student where
    (==) (MkStudent _ p1) (MkStudent _ p2) = p1 == p2 

instance Ord Student where
    compare (MkStudent _ p1) (MkStudent _ p2) = compare p1 p2

rangLista :: [Student] -> [Student]
rangLista studenti = List.sortBy (flip compare) studenti

poeniStudenata :: [Student] -> [(String, Maybe Int)]
poeniStudenata studenti = foldr azuriraj [] studenti
    where 
        azuriraj s l  
            | poeni s > 50 = (ime s, Just (poeni s)) : l
            | otherwise = (ime s, Nothing) : l
