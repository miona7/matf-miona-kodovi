module Zad3 where

import Test.QuickCheck

-- Zadatak 3:

-- Definisati strukturu podataka `Stek a`, gde je `a`
-- proizvoljan tip. Stek moze biti prazan ili sadrzati
-- proizvoljan broj elemenata tipa `a`.

-- Kreirati funkcije `fromList` i `toList` koje konvertuju
-- [a] u `Stek a`, i `Stek a` u `[a]`, redom.

-- Napisati QuickCheck test za funkcije `fromList` i `toList`.

-- Instancirati Show nad `Stek a` (pretpostaviti da je
-- `a` u klasi Show) tako da se stek ispise u formatu:
--       < dno, ... , vrh >
-- (vrh i dno su elementi steka)
-- Za prazan stek:  </>

-- Instancirati Functor nad `Stek a`

newtype Stek a = Stek [a] 
-- data Stek' a = Empty | a (Stek' a)

fromList :: [a] -> Stek a
fromList = Stek

toList :: Stek a -> [a]
toList (Stek lst) = lst

prop_fromList_toList :: (Eq a) => [a] -> Bool
prop_fromList_toList lst = (toList $ fromList lst) == lst

instance Show a => Show (Stek a) where
    show s = "<" ++ show' s ++ ">"
        where
            show' :: Stek a -> String
            show' (Stek []) = "/"
            show' (Stek [x]) = show x
            show' (Stek (x:xs)) = show x ++ ", " ++ show' (Stek xs)

instance Functor Stek where
    fmap f (Stek lst) = fromList $ fmap f lst 