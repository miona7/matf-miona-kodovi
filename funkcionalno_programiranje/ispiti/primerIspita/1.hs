module Zad1 where

import Test.QuickCheck

-- Zadatak 1:
-- Definisati tip podataka `Point2D` koji se može konstruisati 
-- putem konstruktora `MkPoint2D` i koji se sastoji od atributa:
--  * `x` (tipa `Double`) koje predstavlja x-koordinatu tačke 
--  * `y` (tipa `Double`) koje predstavlja y-koordinatu tačke 
--
-- Definisati tip podataka `Rectangle` koji se može konstruisati 
-- putem konstruktora `MkRectangle` i koji se sastoji od atributa:
--  * `bott_left` (tipa `Point2D`) koje predstavlja teme A pravougaonika 
--  * `top_right` (tipa `Point2D`) koje predstavlja teme C pravougaonika
-- (pretpostaviti da su stranice pravougaonika paralelene koordinatnim osama)
--
--             D     (C)
--
--            (A)     B
--
-- Definisati klasu `Traversible a` koja sadrži funkciju `traverse :: a -> [Point2D]`
--
-- Instancirati `Traversible` za `Rectangle` tako da funkcija `traverse` vrati listu [A,B,C,D]
--
-- Definisati funkciju `rotTrans rect` koja rotira pravougaonik za 90 stepeni
-- u smeru kazaljke na satu ali tako da teme B dođe na mesto temena A 
-- (kao na slici ispod) i vraća dobijeni pravougaonik:
--
--            | D     (C)         | A   (D)
--            |             ->    |
--            |(A)     B          |(B)   C
--            ````````````        ``````````
--
-- Napisati QuickCheck test koji testira funkciju `rotTrans`. 
-- Pomoc: Iskoristiti činjenicu da dva puta primenjena rotacija na ovakav nacin predstavlja identitet.

data Point2D = MkPoint2D { x :: Double, y :: Double } deriving (Show, Eq)

data Rectangle = MkRectangle { bott_left :: Point2D, top_right :: Point2D } deriving (Show, Eq)

class Traversible a where
    traverse :: a -> [Point2D]

instance Traversible Rectangle where
    traverse (MkRectangle a c) = [a, b, c, d]
        where 
            b = MkPoint2D (x c) (y a)
            d = MkPoint2D (x a) (y c)

rotTrans_rect :: Rectangle -> Rectangle
rotTrans_rect r = (MkRectangle b d)
    where
        t = Zad1.traverse r
        b = t !! 1
        d = t !! 3

-- klasa unutar QuickCheck biblioteke koja mu govori kako da napravi nasumican podatak za odgovarajuci tip
instance Arbitrary Point2D where
    arbitrary = do
        x' <- arbitrary
        y' <- arbitrary
        return (MkPoint2D x' y')

instance Arbitrary Rectangle where
    arbitrary = do
        a <- arbitrary
        
        w <- fmap abs arbitrary -- mapiramo u apsolutnu vrednosti kako sirina ne bi bila negativna
        h <- fmap abs arbitrary

        let c = MkPoint2D (x a + w + 1) (y a + h + 1)

        return (MkRectangle a c)

prop_rotTrans :: Rectangle -> Bool 
prop_rotTrans r = rotTrans_rect (rotTrans_rect r) == r

-- p1 = MkPoint2D 1 1
-- p2 = MkPoint2D 5 3
-- r1 = MkRectangle p1 p2
-- r2 = rotTrans_rect r1
-- t = Zad1.traverse r2
