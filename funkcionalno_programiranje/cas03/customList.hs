module Lib where

-- definicija rekurzivne liste
data UList a = Empty -- prazna lista
             | Cons a (UList a) -- glava liste nalepljena na ostatak liste
             deriving Show

-- nadovezivanje
ulConcat :: UList a -> UList a -> UList a
ulConcat Empty rs = rs
ulConcat (Cons l Empty) rs = Cons l rs
ulConcat (Cons l ls) rs = Cons l (ulConcat ls rs)

-- pravimo listu koja koristi simbole umesto reci
infixr 7 :/: -- desno asocijativan operator prioriteta 7 - isto kao :
data OList a = End -- prazna lista
             | (:/:) a (OList a) -- glava + ostatak liste

-- nasa verzija operatora ++
infixr 6 +/+
(+/+) :: OList a -> OList a -> OList a
End +/+ rs = rs
(l :/: End) +/+ rs = l :/: rs
(l :/: ls) +/+ rs = l :/: (ls +/+ rs)


-- da bismo prikazali listu elemenata tipa a, neophodno je da znamo kako da prikazemo jedan element tog tipa 
-- tip a mora isto da implementira Show
instance Show a => Show (OList a) where
    show End = ""
    show (x :/: End) = show x
    show (x :/: xs)  = show x ++ ", " ++ show xs


-- funkcija fmap transformise elemente kolekcije i kao rezultat vraca kolekciju transformisanih elemenata
instance Functor OList where
    fmap f End = End
    fmap f (x :/: xs) = f x :/: fmap f xs


-- funkcija foldr prolazi kroz kolekciju i akumulira sve elemente u kolekciji
instance Foldable OList where
    foldl f acc End = acc
    foldl f acc (x :/: xs) =
            let newAcc = f acc x
            in  foldr (flip f) newAcc xs
            -- foldl je memorijski skuplji

    foldr f init End = init
    foldr f init (x :/: xs) = f x (foldr f init xs)


