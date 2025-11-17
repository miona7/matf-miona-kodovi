module Lib where

import Data.Char (toLower, isUpper, chr)
import Data.List (intercalate, insert)

najduza :: [String] -> String
najduza lst = fst (foldl azuriraj ("", 0) lst)
    where
        azuriraj ("", 0) l = (l, length l)
        azuriraj (s, d) l = if length l > d then (l, length l) else (s, d)

-- ne mora eksplicitno da se cuvaju duzine

najduza' :: [String] -> String
najduza' = foldl1 (\s l -> if length l > length s then l else s) 

umanji :: String -> String
umanji str = map (\c -> if isUpper c then toLower c else c) str

razdvoj :: Char -> String -> [String]
razdvoj sep str = case break (== sep) str of
    (tmp, []) -> [tmp]
    (tmp, _:ost) -> tmp : razdvoj sep ost

spoj :: String -> [String] -> String
spoj sep str = intercalate sep str

data Poklapanje = MkPoklapanje Char Int deriving Show

kar :: Poklapanje -> Char
kar (MkPoklapanje c _) = c

poz :: Poklapanje -> Int
poz (MkPoklapanje _ p) = p

poklapanjeShow :: Poklapanje -> String
poklapanjeShow poklapanje = [kar poklapanje] ++ " (" ++ show (poz poklapanje) ++ ")"
    -- spoj " " [[kar poklapanje], '(' : show (poz poklapanje) ++ [')']]

poklapanjeM :: Int -> String -> Maybe Poklapanje
poklapanjeM i str  
    | i >= length str = Nothing
    | otherwise = Just (MkPoklapanje (str !! i) i)

poklapanjeE :: Int -> String -> Either String Poklapanje
poklapanjeE i str  
    | i >= length str = Left "Index error"
    | otherwise = Right (MkPoklapanje (str !! i) i)

pronadjiM :: Poklapanje -> String -> Maybe Bool
pronadjiM k str 
    | poz k >= length str = Nothing
    | otherwise = if (kar k) == (str !! (poz k)) then Just True else Just False


pronadjiE :: Poklapanje -> String -> Either String Bool
pronadjiE k str 
    | poz k >= length str = Left "Index error"
    | otherwise = if (kar k) == (str !! (poz k)) then Right True else Right False