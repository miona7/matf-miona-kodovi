module Lib where
import Data.List as List (elemIndex, sortBy)

data StepenStudija = OsnovneStudije | MasterStudije | DoktorskeStudije deriving Eq

instance Show StepenStudija where
    show OsnovneStudije = "BCs"
    show MasterStudije = "MSs"
    show DoktorskeStudije = "PhD"

data Student = MkStudent { indeks :: String
                         , ime :: String
                         , prezime :: String
                         , stepen :: StepenStudija
                         }

ispisiStudent :: Student -> String
ispisiStudent s = indeks s ++ " " ++ ime s ++ " " ++ prezime s ++ " " ++ show (stepen s)

instance Show Student where
    show = ispisiStudent

porediStudente :: Student -> Student -> Bool
porediStudente s1 s2 = (==) (indeks s1) (indeks s2) 

instance Eq Student where
    (==) = porediStudente

type Rezultat = (Student, Maybe Int)

rezultati :: [Student] -> [Rezultat]
rezultati = map (, Nothing)

poeni :: Student -> [Rezultat] -> Either String (Maybe Int)
poeni student rezultati = 
    case mi of 
        Nothing -> Left (show student ++ " ne studira na fakultetu")
        (Just i) -> Right (snd (rezultati !! i))       
    where mi = List.elemIndex student (map fst rezultati)

ponisti :: Student -> [Rezultat] -> [Rezultat]
ponisti student = foldr azuriraj []
    where 
        azuriraj r acc = if fst r == student then (student, Nothing) : acc else r : acc

ponistiSve :: [Rezultat] -> [Rezultat]
ponistiSve = map (\s -> (fst s, Nothing))

studije :: StepenStudija -> [Rezultat] -> [Rezultat]
studije s = filter (\r -> stepen (fst r) == s) 

polozeni :: [Rezultat] -> [Rezultat]
polozeni = filter (\(s, mozdaRez) -> izvuciPoene mozdaRez > 50) 
    where
        izvuciPoene Nothing = 0
        izvuciPoene (Just a) = a

upisi :: Student -> Int -> [Rezultat] -> [Rezultat]
upisi student poeni rezultati = if student `elem` studenti then foldr azuriraj [] rezultati
                                else (student, Just poeni) : rezultati
    where
        studenti = map fst rezultati
        azuriraj r acc = if fst r == student then (student, Just poeni) : acc else r : acc 

najbolji :: Int -> [Rezultat] -> [Int]
najbolji n rezultati = take n 
                        $ List.sortBy (flip compare) 
                        $ map (\(Just x) -> x) 
                        $ filter (Nothing /=) 
                        $ map snd rezultati
