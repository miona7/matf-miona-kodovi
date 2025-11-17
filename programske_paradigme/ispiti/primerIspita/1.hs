module Lib where

delioci:: Int -> [Int]
delioci n  
    | n == 1 = []
    | otherwise = delioci' n 2
    where 
        delioci' :: Int -> Int -> [Int]
        delioci' n k 
            | n == k = []
            | n `mod` k == 0 = k : delioci' n (k+1)
            | otherwise = delioci' n (k+1)  

delioci'' :: Int -> [Int]
delioci'' n = [k | k <- [2..n-1], n `mod` k == 0] 


prost :: Int -> Bool
prost n  
    | n == 1 = False
    | otherwise =  null (delioci n)  -- if delioci n == [] then True else False

prost' :: Int -> Bool
prost' n = n > 1 && null (delioci n) 


generisiProste :: Int -> [Int]
generisiProste n = [k | k <- [2..n], prost' k]


data Broj = MkBroj { tip :: String, vrednost :: Int } deriving Show

-- data Broj = MkBroj String Int
-- tip :: Broj -> String
-- tip (MkBroj t _) = t 
-- vrednost :: Broj -> Int
-- vrednost (MkBroj _ v) = v

instance Eq Broj where
    (==) (MkBroj _ v1) (MkBroj _ v2) = v1 == v2

instance Ord Broj where
    compare (MkBroj _ v1) (MkBroj _ v2) = compare v1 v2


sumaProstih :: [Broj] -> Int
sumaProstih = foldl saberi 0 
    where 
        saberi ak b = if tip b == "prost" then ak + vrednost b else ak


sviDelioci :: Int -> [Int]
sviDelioci n 
    | n == 1 = []
    | otherwise = sviDelioci' n 2
    where
        sviDelioci' :: Int -> Int -> [Int]
        sviDelioci' n k  
            | n <= 1 = []
            | n `mod` k == 0 = k : sviDelioci' (n `div` k) k
            | otherwise = sviDelioci' n (k+1)

faktori :: Broj -> [(Int, Int)]
faktori n = foldr azuriraj [] (map (\d -> (d, 1)) (sviDelioci (vrednost n)))
    where
        azuriraj (x, 1) [] = [(x, 1)]
        azuriraj (x, 1) ((y, c):ys) 
            | x == y = (y, c+1):ys
            | otherwise = (x, 1) : ((y, c):ys)