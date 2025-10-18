module Lib where

import Data.List (elemIndex, sortBy)

data StepenStudija = Osnovne | Master | Doktorske deriving Eq

instance Show StepenStudija where
    show Osnovne = "BCs"
    show Master = "MSs"
    show Doktorske = "PhD"

data Student = MkStudent { indeks :: String
                         , ime :: String
                         , prezime :: String
                         , stepen :: StepenStudija 
                         }

instance Show Student where
    show s = indeks s ++ ": " ++ ime s ++ " " ++ prezime s ++ " " ++ show (stepen s)

instance Eq Student where
    (==) s1 s2 = indeks s1 == indeks s2

type Rezultat = (Student, Maybe Int)

rezultati :: [Student] -> [Rezultat]
rezultati = map (\s -> (s, Nothing))

poeni :: Student -> [Rezultat] -> Either String (Maybe Int)
poeni student rezultati = 
    case ind of 
        Just i -> Right (snd (rezultati !! i))
        Nothing -> Left ("student " ++ indeks student ++ " se ne nalazi u listi")
        where
            ind = elemIndex student (map fst rezultati)

ponisti :: Student -> [Rezultat] -> [Rezultat]
ponisti student rezultati = foldr azuriraj [] rezultati
    where
        azuriraj s lista = if fst s == student then (fst s, Nothing) : lista else s : lista

ponistiSve :: [Rezultat] -> [Rezultat]
ponistiSve rezultati = map (\(s, p)-> (s, Nothing)) rezultati

studije :: StepenStudija -> [Rezultat] -> [Rezultat]
studije stepenStudija rezultati = foldr azuriraj [] rezultati
    where
        azuriraj r lista = if stepen (fst r) == stepenStudija then r : lista else lista

polozeni :: [Rezultat] -> [Rezultat]
polozeni rezultati = foldr azuriraj [] rezultati
    where 
        azuriraj r lista = if poeni (snd r) > 50 then r : lista else lista
        poeni Nothing = 0
        poeni (Just p) = p

upisi :: Student -> Int -> [Rezultat] -> [Rezultat]
upisi student poeni rezultati = if elem student (map fst rezultati) then foldr azuriraj [] rezultati else (student, Just poeni) : rezultati
    where
        azuriraj r lista = if student == fst r then (student, Just poeni) : lista else r : lista

najbolji :: Int -> [Rezultat] -> [Int]
najbolji n rezultati = take n
                       $ sortBy (flip compare)
                       $ map (\(Just p) -> p)
                       $ filter (/= Nothing) 
                       $ map (\r -> snd r) rezultati