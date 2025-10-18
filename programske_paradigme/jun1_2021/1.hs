import Data.List (sortBy)

dodaj :: [(Int, Char)] -> (Int, Char) -> [(Int, Char)]
dodaj ruka karta = foldl azuriraj [] ruka
    where
        azuriraj l k  
            | fst karta < fst k = l ++ [karta] ++ [k]
            | fst karta == fst k = if snd karta < snd k then l ++ [karta] ++ [k] else l ++ [k]
            | otherwise = l ++ [k]

ukloni :: [(Int, Char)] -> (Int, Char) -> [(Int, Char)]
ukloni ruka karta = foldl azuriraj [] ruka
    where
        azuriraj l k  
            | fst karta == fst k && snd karta == snd k = l 
            | otherwise = l ++ [k]

uporedi :: [(Int, Char)] -> [(Int, Char)] -> Ordering
uporedi ruka1 ruka2 = compare ruka1 ruka2

data Znak = Herc | Karo | Pik | Tref deriving (Show, Eq, Ord)

data Karta = MkKarta { vrednost :: Int, znak :: Znak } deriving (Show, Eq, Ord)

type Ruka = [Karta]

izlistaj :: Znak -> Ruka -> [Karta]
izlistaj z ruka = foldl azuriraj [] ruka
    where
        azuriraj l k  
            | znak k == z = l ++ [k]
            | otherwise = l 

dodaj' :: Ruka -> Karta -> Ruka
dodaj' ruka karta = foldl azuriraj [] ruka
    where
        azuriraj l k  
            | vrednost karta < vrednost k = l ++ [karta] ++ [k]
            | vrednost karta == vrednost k = if znak karta < znak k then l ++ [karta] ++ [k] else l ++ [k]
            | otherwise = l ++ [k]

najjaca :: Ruka -> Karta
najjaca ruka = head $ sortBy (flip compare) ruka