module Lib where
import Data.Char (isSpace)

main :: IO ()
main = putStrLn "Hello"


-- obicna rekurzija
mySum :: Num a => [a] -> a
mySum [] = 0
mySum (x:xs) = x + mySum xs

-- repna rekurzija
-- prvi argument = akumulator, drugi argument = lista
mySum' :: Num a => [a] -> a
mySum' = mySumHelper 0
    where
        mySumHelper acc l =
            case l of
                [] -> acc
                (x:xs) -> mySumHelper (acc + x) xs

-- ekvivalentno 
mySum'' :: Num a => [a] -> a
mySum'' lst =
    let mySumHelper acc l =
            case l of
                [] -> acc
                (x:xs) -> mySumHelper (acc + x) xs
    in mySumHelper 0 lst

-- foldl je genericki algoritam koji implementira repnu rekurziju
mySum''' :: Num a => [a] -> a
mySum''' = foldl (+) 0


-- obicna rekurzija
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ [] = []
myFilter func (x:xs) =
    let filteredTail = myFilter func xs
    in if func x then x : filteredTail else filteredTail

-- repna rekurzija
myFilter' :: (a -> Bool) -> [a] -> [a]
myFilter' _ [] = []
myFilter' func lst =
    let myFilterHelper acc l =
            case l of
            [] -> acc
            (x:xs) -> myFilterHelper (if func x then x:acc else acc) xs
    in myFilterHelper [] (reverse lst)

-- filtriranje sa foldl
myFilter'' :: (a -> Bool) -> [a] -> [a]
myFilter'' func lst = foldl (\acc x -> if func x then x:acc else acc) [] (reverse lst)

-- filtriranje sa foldr
myFilter''' :: (a -> Bool) -> [a] -> [a]
myFilter''' func = foldr (\x acc -> if func x then x:acc else acc) []


-- konkatenacija sa foldr
myConcat :: [a] -> [a] -> [a]
myConcat lst1 lst2 = foldr (:) lst2 lst1


-- ekstraktuje rec iz recenice

-- ne ignorise beline na pocetku stringa
takeWord' :: String -> String
takeWord' = takeWhile (not . isSpace)
                    -- kompozicija

-- ignorise beline na pocetku stringa
takeWord'' :: String -> String
takeWord'' str = takeWhile (not . isSpace) (dropWhile isSpace str)

-- point-free verzija
takeWord :: String -> String
takeWord = takeWhile (not . isSpace) . dropWhile isSpace

takeWordVerbose :: String -> String
takeWordVerbose =
    let isNotSpace = not . isSpace
    in takeWhile isNotSpace . dropWhile isSpace


-- ekstraktuje prve dve reci iz recenice

breakWord :: String -> (String, String)
breakWord = break isSpace . dropWhile isSpace
            -- pravi torku na osnovu uslova, tj deli listu dok uslov ne postane tacan
            -- span deli listu dok je uslov tacan

-- spajamo pozive funkcija
takeWord2 :: String -> (String, String)
takeWord2 str =
    let (word1, rest1) = breakWord str
        (word2, rest2) = breakWord rest1
    in (word1, word2)

-- filtriranje po indeksima
filterByIndex :: (Int -> Bool) -> [b] -> [b]
filterByIndex func lst =
    let withIndices = zip [1..]
        indexed = withIndices lst
        pairpred = func . fst -- na prvi elemnent tj indeks primenjuje predikat func  
    in map snd $ filter pairpred indexed
                -- filtrira samo one parove koji zadovoljavaju uslov


-- pravimu f-ju koja racuna vrednosti liste f-ja u odredjenoj tacki
-- applyFunctions (pi/3) [sin, cos, tan, atan]

applyFunctions :: p -> [p -> b] -> [b]
applyFunctions x = map ($ x)
                        -- operator za primenu funkcije -> f $ x = f(x)

applyFunctions' :: p -> [p -> b] -> [b]
applyFunctions' x = map (\f -> f x)

applyFunctions'' :: p -> [p -> b] -> [b]
applyFunctions'' = map . flip id


-- cuvari (guards) su lepsi zapis za lanac if else if else if naredbi
accumulate :: (Eq a, Num a) => (a -> a -> a) -> [a] -> a
accumulate func lst
    | null lst = 0
    | otherwise = func (head lst) (accumulate func $ tail lst)

-- mogu da sadrze i pattern matching izraze (linije koje sadrze <- lst)
accumulate' :: (Eq a, Num a) => (a -> a -> a) -> [a] -> a
accumulate' func lst
    | null lst = 0
    | [x] <- lst = x
    | (x:xs) <- lst = func x (accumulate' func xs)